#include "BaseLib/MemoryFile.h"
#include "BaseLib/PointerFunctions.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


#define LINKER_MAX_OBJECTS	4


//Objects assembled from sources and the linker that links them.
struct SLinkTest
{
	CAsm65Object	acObjects[LINKER_MAX_OBJECTS];
	int				iNumObjects;
	CAsm65Library	cLibrary;
	CAsm65Linker	cLinker;
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void LinkTestInit(SLinkTest* psTest)
{
	psTest->iNumObjects = 0;
	psTest->cLibrary.Init("library");
	psTest->cLinker.Init();
}


//////////////////////////////////////////////////////////////////////////
//
// The object is named a, b, c ... in the order added.
//
//////////////////////////////////////////////////////////////////////////
static void LinkTestObject(SLinkTest* psTest, const char* szSource)
{
	CAsm65Object*	pcObject;
	char			szName[2];

	szName[0] = (char)('a' + psTest->iNumObjects);
	szName[1] = '\0';
	pcObject = &psTest->acObjects[psTest->iNumObjects];
	psTest->iNumObjects++;
	pcObject->Init(szName);
	TestAsm65AssembleObject(pcObject, szSource);
	psTest->cLinker.AddObject(pcObject);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void LinkTestLibraryObject(SLinkTest* psTest, const char* szName, const char* szSource)
{
	TestAsm65AssembleObject(psTest->cLibrary.AddObject(szName), szSource);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void LinkTestKill(SLinkTest* psTest)
{
	int	i;

	psTest->cLinker.Kill();
	psTest->cLibrary.Kill();
	for (i = 0; i < psTest->iNumObjects; i++)
	{
		psTest->acObjects[i].Kill();
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Links, runs from the start of the text and returns A.
//
//////////////////////////////////////////////////////////////////////////
static uint64 LinkAndRun(SLinkTest* psTest, STestAsm65Run* psRun)
{
	AssertTrue(psTest->cLinker.Link());
	AssertString("", psTest->cLinker.GetErrors());
	TestAsm65BeginOutput(psRun, psTest->cLinker.GetOutput(), ASM65_DEFAULT_TEXT_ADDRESS);
	AssertTrue(TestAsm65Run(psRun, 10000) < 10000);
	return TestAsm65MPU(psRun)->GetA();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static int64 LinkedSymbol(SLinkTest* psTest, const char* szName)
{
	int64	iValue;

	iValue = -1;
	AssertTrue(psTest->cLinker.GetSymbol(szName, &iValue));
	return iValue;
}


//////////////////////////////////////////////////////////////////////////
//
// A call to a function in another object, data read through an address in another
// section and a branch between sections.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LinkerCall(void)
{
	SLinkTest		sTest;
	STestAsm65Run	sRun;

	LinkTestInit(&sTest);
	LinkTestObject(&sTest,
		"Start:\n"
		"	cpy A, [Four]\n"
		"	jsr AddThree\n"
		"	bras z, Done\n"
		"	stp\n"
		"	.section rodata\n"
		"Four:\n"
		"	.long 4\n"
		"	.section text.done\n"
		"Done:\n"
		"	add A, 100\n"
		"	stp\n");
	LinkTestObject(&sTest,
		"	.global AddThree\n"
		"AddThree:\n"
		"	add A, 3\n"
		"	cmp A, 7\n"
		"	ret\n");

	AssertLong(107, LinkAndRun(&sTest, &sRun));
	AssertString(
		"Sections\n"
		"  $00010000 $00000014 text (a)\n"
		"  $00010014 $00000006 text.done (a)\n"
		"  $0001001a $00000006 text (b)\n"
		"  $00010020 $00000004 rodata (a)\n"
		"Symbols\n"
		"  $00010000 L Start (a)\n"
		"  $00010000 G __text_start (linker)\n"
		"  $00010014 L Done (a)\n"
		"  $0001001a G AddThree (b)\n"
		"  $00010020 L Four (a)\n"
		"  $00010020 G __rodata_start (linker)\n"
		"  $00010020 G __text_end (linker)\n"
		"  $00010024 G __bss_end (linker)\n"
		"  $00010024 G __bss_start (linker)\n"
		"  $00010024 G __data_end (linker)\n"
		"  $00010024 G __data_start (linker)\n"
		"  $00010024 G __end (linker)\n"
		"  $00010024 G __fini_end (linker)\n"
		"  $00010024 G __fini_start (linker)\n"
		"  $00010024 G __init_end (linker)\n"
		"  $00010024 G __init_start (linker)\n"
		"  $00010024 G __rodata_end (linker)\n",
		sTest.cLinker.GetMap());
	AssertLongLongIntHex(0x10000, LinkedSymbol(&sTest, "__text_start"));
	AssertLongLongIntHex(0x1001A, LinkedSymbol(&sTest, "AddThree"));
	AssertLongLongIntHex(0x10020, LinkedSymbol(&sTest, "__text_end"));
	AssertLongLongIntHex(0x10020, LinkedSymbol(&sTest, "__rodata_start"));
	AssertLongLongIntHex(0x10024, LinkedSymbol(&sTest, "__end"));
	TestAsm65End(&sRun);
	LinkTestKill(&sTest);
}


//////////////////////////////////////////////////////////////////////////
//
// :16 addresses work while the data is below 0001:0000 and are an error above.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LinkerOffsetAddresses(void)
{
	SLinkTest		sTest;
	STestAsm65Run	sRun;
	const char*		szSource;

	szSource =
		"	wth A, 32\n"
		"	cpy A, [Value:16]\n"
		"	add A, Value:16\n"
		"	stp\n"
		"	.section data\n"
		"Value:\n"
		"	.long $1234\n";

	LinkTestInit(&sTest);
	sTest.cLinker.SetAddress(ASK65_Data, 0x8000);
	LinkTestObject(&sTest, szSource);
	AssertLongLongIntHex(0x1234 + 0x8000, LinkAndRun(&sTest, &sRun));
	TestAsm65End(&sRun);
	LinkTestKill(&sTest);

	LinkTestInit(&sTest);
	sTest.cLinker.SetAddress(ASK65_Data, 0x30000);
	LinkTestObject(&sTest, szSource);
	AssertFalse(sTest.cLinker.Link());
	AssertString(
		"a:2:10: Relocated value does not fit '196608 in 2 bytes'\n"
		"a:3:9: Relocated value does not fit '196608 in 2 bytes'\n",
		sTest.cLinker.GetErrors());
	LinkTestKill(&sTest);
}


//////////////////////////////////////////////////////////////////////////
//
// A global definition replaces a weak one; an undefined weak name is 0.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LinkerWeak(void)
{
	SLinkTest		sTest;
	STestAsm65Run	sRun;

	LinkTestInit(&sTest);
	LinkTestObject(&sTest,
		"	.weak Get, Optional\n"
		"	jsr Get\n"
		"	add A, Optional\n"
		"	stp\n"
		"Get:\n"
		"	cpy A, 1\n"
		"	ret\n");
	LinkTestObject(&sTest,
		"	.global Get\n"
		"Get:\n"
		"	cpy A, 2\n"
		"	ret\n");
	AssertLong(2, LinkAndRun(&sTest, &sRun));
	TestAsm65End(&sRun);
	LinkTestKill(&sTest);
}


//////////////////////////////////////////////////////////////////////////
//
// Both objects have the COMDAT group Shared: the first copy is kept and both call it.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LinkerComdat(void)
{
	SLinkTest		sTest;
	STestAsm65Run	sRun;

	LinkTestInit(&sTest);
	LinkTestObject(&sTest,
		"	cpy A, 0\n"
		"	jsr Shared\n"
		"	jsr Second\n"
		"	stp\n"
		"	.section text.Shared, comdat\n"
		"	.global Shared\n"
		"Shared:\n"
		"	add A, 1\n"
		"	ret\n");
	LinkTestObject(&sTest,
		"	.global Second\n"
		"Second:\n"
		"	jsr Shared\n"
		"	shl A, 4\n"
		"	ret\n"
		"	.section text.Shared, comdat\n"
		"	.global Shared\n"
		"Shared:\n"
		"	add A, 2\n"
		"	ret\n");
	AssertLong(0x20, LinkAndRun(&sTest, &sRun));
	AssertTrue(strstr(sTest.cLinker.GetMap(), "Dropped COMDAT sections\n  text.Shared comdat text.Shared (b)\n") != NULL);
	TestAsm65End(&sRun);
	LinkTestKill(&sTest);

	//A local label in a dropped copy cannot be used.
	LinkTestInit(&sTest);
	LinkTestObject(&sTest,
		"	.section text.Shared, comdat\n"
		"Copy:\n"
		"	ret\n");
	LinkTestObject(&sTest,
		"	jsr Copy\n"
		"	.section text.Shared, comdat\n"
		"Copy:\n"
		"	ret\n");
	AssertFalse(sTest.cLinker.Link());
	AssertString("b:1:6: Refers to a dropped COMDAT section 'text.Shared'\n", sTest.cLinker.GetErrors());
	LinkTestKill(&sTest);
}


//////////////////////////////////////////////////////////////////////////
//
// A start up that calls the init table (in link order) then the fini table backwards.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LinkerInitFini(void)
{
	SLinkTest		sTest;
	STestAsm65Run	sRun;

	LinkTestInit(&sTest);
	LinkTestObject(&sTest,
		"	wtth (A, X), 32\n"
		"	cpy A, 0\n"
		"	cpy X, __init_start\n"
		"NextInit:\n"
		"	cmp X, __init_end\n"
		"	bras c, Finalise\n"
		"	jsr [X]\n"
		"	add X, 4\n"
		"	bra NextInit\n"
		"Finalise:\n"
		"	cpy X, __fini_end\n"
		"NextFini:\n"
		"	cmp X, __fini_start\n"
		"	bras z, Run\n"
		"	sub X, 4\n"
		"	jsr [X]\n"
		"	bra NextFini\n"
		"Run:\n"
		"	stp\n"
		"	.section init\n"
		"	.long First\n"
		"	.section fini\n"
		"	.long FirstEnd\n"
		"	.section text\n"
		"First:\n"
		"	shl A, 4\n"
		"	add A, 1\n"
		"	ret\n"
		"FirstEnd:\n"
		"	shl A, 4\n"
		"	add A, 4\n"
		"	ret\n");
	LinkTestObject(&sTest,
		"	.section init\n"
		"	.long Second\n"
		"	.section fini\n"
		"	.long SecondEnd\n"
		"	.section text\n"
		"Second:\n"
		"	shl A, 4\n"
		"	add A, 2\n"
		"	ret\n"
		"SecondEnd:\n"
		"	shl A, 4\n"
		"	add A, 3\n"
		"	ret\n");
	AssertLongLongIntHex(0x1234, LinkAndRun(&sTest, &sRun));
	TestAsm65End(&sRun);
	LinkTestKill(&sTest);
}


//////////////////////////////////////////////////////////////////////////
//
// Library objects are linked only when needed, including by other library objects.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LinkerLibrary(void)
{
	SLinkTest		sTest;
	STestAsm65Run	sRun;

	LinkTestInit(&sTest);
	LinkTestObject(&sTest,
		"	wth A, 32\n"
		"	cpy A, 1\n"
		"	jsr Outer\n"
		"	stp\n");
	LinkTestLibraryObject(&sTest, "inner",
		"	.global Inner\n"
		"Inner:\n"
		"	add A, 20\n"
		"	ret\n");
	LinkTestLibraryObject(&sTest, "unused",
		"	.global Unused\n"
		"Unused:\n"
		"	ret\n");
	LinkTestLibraryObject(&sTest, "outer",
		"	.global Outer\n"
		"Outer:\n"
		"	add A, 300\n"
		"	jsr Inner\n"
		"	ret\n");
	sTest.cLinker.AddLibrary(&sTest.cLibrary);
	AssertLong(321, LinkAndRun(&sTest, &sRun));
	AssertTrue(LinkedSymbol(&sTest, "Inner") > 0);
	AssertTrue(strstr(sTest.cLinker.GetMap(), "unused") == NULL);
	TestAsm65End(&sRun);
	LinkTestKill(&sTest);
}


//////////////////////////////////////////////////////////////////////////
//
// A library written as a PackFile reads back and links the same.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LinkerLibraryFile(void)
{
	SLinkTest		sTest;
	STestAsm65Run	sRun;
	CAsm65Library	cLibrary;
	CMemoryFile*	pcMemoryFile;

	cLibrary.Init("maths");
	TestAsm65AssembleObject(cLibrary.AddObject("double"),
		"	.global Double\n"
		"Double:\n"
		"	add A, A\n"
		"	ret\n");
	TestAsm65AssembleObject(cLibrary.AddObject("square"),
		"	.global Square\n"
		"Square:\n"
		"	cpy B, [Table + A]\n"
		"	cpy A, B\n"
		"	ret\n"
		"	.section rodata\n"
		"Table:\n"
		"	.byte 0, 1, 4, 9, 16, 25, 36, 49\n");
	pcMemoryFile = MemoryFile();
	pcMemoryFile->mbBasicFileMustFree = false;
	AssertTrue(cLibrary.Write(pcMemoryFile));
	cLibrary.Kill();

	LinkTestInit(&sTest);
	pcMemoryFile->mbBasicFileMustFree = false;
	AssertTrue(sTest.cLibrary.Read(pcMemoryFile));
	SafeKill(pcMemoryFile);
	AssertString("maths", sTest.cLibrary.GetName());
	AssertSize(2, sTest.cLibrary.NumObjects());
	AssertString("double", sTest.cLibrary.GetObject(0)->GetName());
	AssertString("square", sTest.cLibrary.GetObject(1)->GetName());

	LinkTestObject(&sTest,
		"	cpy A, 3\n"
		"	jsr Square\n"
		"	jsr Double\n"
		"	stp\n");
	sTest.cLinker.AddLibrary(&sTest.cLibrary);
	AssertLong(18, LinkAndRun(&sTest, &sRun));
	TestAsm65End(&sRun);
	LinkTestKill(&sTest);
}


//////////////////////////////////////////////////////////////////////////
//
// Undefined and twice defined names, overlapping sections and the limit.  With
// SetStubMissing an undefined name is a stp.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LinkerErrors(void)
{
	SLinkTest		sTest;
	STestAsm65Run	sRun;

	LinkTestInit(&sTest);
	LinkTestObject(&sTest, "	jsr Missing\n");
	AssertFalse(sTest.cLinker.Link());
	AssertString("a: Undefined symbol 'Missing'\n", sTest.cLinker.GetErrors());
	LinkTestKill(&sTest);

	LinkTestInit(&sTest);
	sTest.cLinker.SetStubMissing(true);
	LinkTestObject(&sTest,
		"	cpy A, 5\n"
		"	jsr Missing\n"
		"	cpy A, 6\n"
		"	stp\n");
	AssertLong(5, LinkAndRun(&sTest, &sRun));
	AssertSize(1, sTest.cLinker.NumMissing());
	AssertString("Missing", sTest.cLinker.GetMissing(0));
	TestAsm65End(&sRun);
	LinkTestKill(&sTest);

	LinkTestInit(&sTest);
	LinkTestObject(&sTest, "	.global Twice\nTwice:\n	ret\n");
	LinkTestObject(&sTest, "	.global Twice\nTwice:\n	ret\n");
	AssertFalse(sTest.cLinker.Link());
	AssertString("b: Symbol is also defined in a 'Twice'\n", sTest.cLinker.GetErrors());
	LinkTestKill(&sTest);

	LinkTestInit(&sTest);
	sTest.cLinker.SetAddress(ASK65_Data, 0x10002);
	sTest.cLinker.SetLimit(0x10004);
	LinkTestObject(&sTest, "	nop\n	nop\n	nop\n	.section data\n	.long 0\n");
	AssertFalse(sTest.cLinker.Link());
	AssertString(
		"link: Sections overlap: text and data\n"
		"link: Sections end past the limit $00010004 'text'\n"
		"link: Sections end past the limit $00010004 'data'\n",
		sTest.cLinker.GetErrors());
	LinkTestKill(&sTest);
}


//////////////////////////////////////////////////////////////////////////
//
// SetRemoveUnused: what the keep section reaches (Used, gUsed), the init entry that
// is not associated (InitAlways) and the one whose global is used (InitUsed) are
// linked.  Unused, gUnused, the init entry associated with gUnused and its routine
// are removed, and Missing (only Unused needs it) is not missing.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LinkerRemoveUnused(void)
{
	SLinkTest		sTest;
	STestAsm65Run	sRun;
	const char*		szSource;
	int64			iValue;

	szSource =
		"	.section text, keep\n"
		"	wtth (A, X), 32\n"
		"	cpy A, 0\n"
		"	cpy X, __init_start\n"
		"NextInit:\n"
		"	cmp X, __init_end\n"
		"	bras c, Run\n"
		"	jsr [X]\n"
		"	add X, 4\n"
		"	bra NextInit\n"
		"Run:\n"
		"	jsr Used\n"
		"	add A, [gUsed]\n"
		"	stp\n"
		"	.section text.Used\n"
		"	.global Used\n"
		"Used:\n"
		"	add A, 100\n"
		"	ret\n"
		"	.section text.Unused\n"
		"	.global Unused\n"
		"Unused:\n"
		"	jsr Missing\n"
		"	cpy B, [gUnused]\n"
		"	ret\n"
		"	.section data.gUsed\n"
		"gUsed:\n"
		"	.long 20\n"
		"	.section data.gUnused\n"
		"gUnused:\n"
		"	.long 30\n"
		"	.section text.InitUsed\n"
		"InitUsed:\n"
		"	add A, 1\n"
		"	ret\n"
		"	.section init.InitUsed, associated data.gUsed\n"
		"	.long InitUsed\n"
		"	.section text.InitUnused\n"
		"InitUnused:\n"
		"	add A, 1000\n"
		"	ret\n"
		"	.section init.InitUnused, associated data.gUnused\n"
		"	.long InitUnused\n"
		"	.section text.InitAlways\n"
		"InitAlways:\n"
		"	add A, 3\n"
		"	ret\n"
		"	.section init.InitAlways\n"
		"	.long InitAlways\n";

	//Everything is linked without SetRemoveUnused, so Missing is needed.
	LinkTestInit(&sTest);
	LinkTestObject(&sTest, szSource);
	AssertFalse(sTest.cLinker.Link());
	AssertString("a: Undefined symbol 'Missing'\n", sTest.cLinker.GetErrors());
	LinkTestKill(&sTest);

	LinkTestInit(&sTest);
	sTest.cLinker.SetRemoveUnused(true);
	LinkTestObject(&sTest, szSource);
	AssertLong(1 + 3 + 100 + 20, LinkAndRun(&sTest, &sRun));
	AssertSize(0, sTest.cLinker.NumMissing());
	AssertTrue(sTest.cLinker.GetSymbol("Used", &iValue));
	AssertFalse(sTest.cLinker.GetSymbol("Unused", &iValue));
	AssertTrue(strstr(sTest.cLinker.GetMap(),
		"Removed unused sections\n"
		"  $0000000e text.Unused (a)\n"
		"  $00000004 data.gUnused (a)\n"
		"  $00000006 text.InitUnused (a)\n"
		"  $00000004 init.InitUnused (a)\n") != NULL);
	TestAsm65End(&sRun);
	LinkTestKill(&sTest);
}


//////////////////////////////////////////////////////////////////////////
//
// With SetRemoveUnused a library object is only linked for a name a used section
// needs: Unused needs Helper, so helper (and its init entry, which would add 1000)
// is left out.  Used needs Other, so other is linked.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LinkerRemoveUnusedLibrary(void)
{
	SLinkTest		sTest;
	STestAsm65Run	sRun;
	int64			iValue;

	LinkTestInit(&sTest);
	sTest.cLinker.SetRemoveUnused(true);
	LinkTestObject(&sTest,
		"	.section text, keep\n"
		"	wtth (A, X), 32\n"
		"	cpy A, 0\n"
		"	cpy X, __init_start\n"
		"NextInit:\n"
		"	cmp X, __init_end\n"
		"	bras c, Run\n"
		"	jsr [X]\n"
		"	add X, 4\n"
		"	bra NextInit\n"
		"Run:\n"
		"	jsr Other\n"
		"	stp\n"
		"	.section text.Unused\n"
		"Unused:\n"
		"	jsr Helper\n"
		"	ret\n");
	TestAsm65AssembleObject(sTest.cLibrary.AddObject("helper"),
		"	.global Helper\n"
		"Helper:\n"
		"	ret\n"
		"	.section text.Init\n"
		"Init:\n"
		"	add A, 1000\n"
		"	ret\n"
		"	.section init\n"
		"	.long Init\n");
	TestAsm65AssembleObject(sTest.cLibrary.AddObject("other"),
		"	.global Other\n"
		"Other:\n"
		"	add A, 7\n"
		"	ret\n");
	sTest.cLinker.AddLibrary(&sTest.cLibrary);
	AssertLong(7, LinkAndRun(&sTest, &sRun));
	AssertFalse(sTest.cLinker.GetSymbol("Helper", &iValue));
	AssertTrue(strstr(sTest.cLinker.GetMap(), "(helper)") == NULL);
	AssertTrue(strstr(sTest.cLinker.GetMap(), "(other)") != NULL);
	TestAsm65End(&sRun);
	LinkTestKill(&sTest);
}


//////////////////////////////////////////////////////////////////////////
//
// Feature programs assembled as objects and linked give the same results.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LinkerPrograms(void)
{
	STestAsm65Run	sRun;
	CChars			szSource;

	szSource.Init();
	TestAsm65ReadSource(&szSource, "Sieve.asm");
	AssertTrue(TestAsm65BeginLinked(&sRun, szSource.Text(), 0x1000));
	AssertTrue(TestAsm65Run(&sRun, 1000000) < 1000000);
	AssertInt(1229, sRun.pcContext->GetLong(0x0100));
	AssertInt(9973, sRun.pcContext->GetLong(0x20000 + 4 * 1228));
	TestAsm65End(&sRun);
	szSource.Kill();

	szSource.Init();
	TestAsm65ReadSource(&szSource, "Sha256.asm");
	szSource.Append("\t\t.byte \"abc\"\nMessageEnd:\n");
	AssertTrue(TestAsm65BeginLinked(&sRun, szSource.Text(), 0x1000));
	AssertTrue(TestAsm65Run(&sRun, 1000000) < 1000000);
	AssertIntHex(0xba7816bf, sRun.pcContext->GetLong(0x0200));
	AssertIntHex(0xf20015ad, sRun.pcContext->GetLong(0x0200 + 28));
	TestAsm65End(&sRun);
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Linker(void)
{
	BeginTests();

	TestAsm65LinkerCall();
	TestAsm65LinkerOffsetAddresses();
	TestAsm65LinkerWeak();
	TestAsm65LinkerComdat();
	TestAsm65LinkerInitFini();
	TestAsm65LinkerLibrary();
	TestAsm65LinkerLibraryFile();
	TestAsm65LinkerErrors();
	TestAsm65LinkerRemoveUnused();
	TestAsm65LinkerRemoveUnusedLibrary();
	TestAsm65LinkerPrograms();

	TestStatistics();
}
