#include "BaseLib/MemoryFile.h"
#include "BaseLib/PointerFunctions.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/FileUtil.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


//////////////////////////////////////////////////////////////////////////
//
// Assembles an object and returns its dump ("" when the source has errors).
//
//////////////////////////////////////////////////////////////////////////
static void AssembleObject(CChars* pszDump, const char* szSource)
{
	CAsm65Object	cObject;

	cObject.Init("test");
	TestAsm65AssembleObject(&cObject, szSource);
	pszDump->Init();
	cObject.Dump(pszDump);
	cObject.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void AssertObjectError(const char* szExpected, const char* szSource)
{
	CAsm65Assembler	cAssembler;
	CAsm65Object	cObject;

	cObject.Init("test");
	cAssembler.Init();
	cAssembler.AssembleObject(szSource, &cObject);
	AssertString(szExpected, cAssembler.GetErrors());
	cAssembler.Kill();
	cObject.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Every way a section address is used: an immediate, a memory address, an external
// call, branches within and between sections and data.  Local labels relocate by
// section, global labels and externals by name.  A branch within its section and a
// difference of two labels in one section need no relocation.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ObjectRelocations(void)
{
	CChars	szDump;

	AssembleObject(&szDump,
		"	.global Start\n"
		"Start:\n"
		"	cpy A, Table\n"
		"	cpy B, [Counter]\n"
		"	jsr Helper\n"
		"	brac z, Other\n"
		"	bra Start\n"
		"	cpy X, End - Start\n"
		"End:\n"
		"	stp\n"
		"	.section rodata\n"
		"Table:\n"
		"	.long Start + 2, Table + 4, Helper\n"
		"	.section bss\n"
		"Counter:\n"
		"	.space 6\n"
		"	.section text.other\n"
		"Other:\n"
		"	stp\n");

	AssertString(
		"section 0 text align 2 size 32\n"
		"  $10 $24 $00 $00 $00 $00 $20 $10 $00 $00 $00 $00 $aa $20 $00 $00\n"
		"  $00 $00 $1c $66 $00 $00 $00 $00 $1c $cd $10 $c1 $1e $00 $3b $00\n"
		"section 1 rodata align 1 size 12\n"
		"  $00 $00 $00 $00 $00 $00 $00 $00 $00 $00 $00 $00\n"
		"section 2 bss align 1 size 6\n"
		"section 3 text.other align 2 size 2\n"
		"  $3b $00\n"
		"symbol 0 Helper global undefined\n"
		"symbol 1 Start global section 0 + 0\n"
		"symbol 2 End local section 0 + 30\n"
		"symbol 3 Table local section 1 + 0\n"
		"symbol 4 Counter local section 2 + 0\n"
		"symbol 5 Other local section 3 + 0\n"
		"relocation section 0 + 2 absolute 4 bytes = section 1 + 0\n"
		"relocation section 0 + 8 absolute 4 bytes = section 2 + 0\n"
		"relocation section 0 + 14 absolute 4 bytes = Helper + 0\n"
		"relocation section 0 + 20 relative signed 4 bytes = section 3 - 4\n"
		"relocation section 1 + 0 absolute 4 bytes = Start + 2\n"
		"relocation section 1 + 4 absolute 4 bytes = section 1 + 4\n"
		"relocation section 1 + 8 absolute 4 bytes = Helper + 0\n",
		szDump.Text());
	szDump.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// :16 makes an address an offset, :8 to :64 an immediate's width, :s16 signed; the
// linker checks the address fits.  A constant can be a label plus a value.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ObjectWidths(void)
{
	CChars	szDump;

	AssembleObject(&szDump,
		"Low = Value + 2\n"
		"	cpy B, [Value:16]\n"
		"	cpy A, Value:16\n"
		"	cpy A, Value:s16\n"
		"	cpy A, Low:64\n"
		"	.section data\n"
		"Value:\n"
		"	.word Value\n"
		"	.byte Low\n");

	AssertString(
		"section 0 text align 2 size 22\n"
		"  $60 $10 $00 $00 $10 $22 $00 $00 $10 $2a $00 $00 $10 $27 $00 $00\n"
		"  $00 $00 $00 $00 $00 $00\n"
		"section 1 data align 1 size 3\n"
		"  $00 $00 $00\n"
		"symbol 0 Low local section 1 + 2\n"
		"symbol 1 Value local section 1 + 0\n"
		"relocation section 0 + 2 absolute 2 bytes = section 1 + 0\n"
		"relocation section 0 + 6 absolute 2 bytes = section 1 + 0\n"
		"relocation section 0 + 10 absolute signed 2 bytes = section 1 + 0\n"
		"relocation section 0 + 14 absolute 8 bytes = section 1 + 2\n"
		"relocation section 1 + 0 absolute 2 bytes = section 1 + 0\n"
		"relocation section 1 + 2 absolute 1 bytes = section 1 + 2\n",
		szDump.Text());
	szDump.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A COMDAT section's group is its name unless given; .weak, .extern and alignment.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ObjectSectionsAndBindings(void)
{
	CChars	szDump;

	AssembleObject(&szDump,
		"	.weak Hook, Optional\n"
		"	.extern Outside\n"
		"	.section text.Inline, comdat\n"
		"	.global Inline\n"
		"Inline:\n"
		"	ret\n"
		"	.section rodata.Inline, comdat Inline\n"
		"	.align 8\n"
		"Hook:\n"
		"	.long Outside, Optional\n");

	AssertString(
		"section 0 text align 1 size 0\n"
		"section 1 text.Inline comdat text.Inline align 2 size 2\n"
		"  $0b $01\n"
		"section 2 rodata.Inline comdat Inline align 8 size 8\n"
		"  $00 $00 $00 $00 $00 $00 $00 $00\n"
		"symbol 0 Outside global undefined\n"
		"symbol 1 Optional weak undefined\n"
		"symbol 2 Hook weak section 2 + 0\n"
		"symbol 3 Inline global section 1 + 0\n"
		"relocation section 2 + 0 absolute 4 bytes = Outside + 0\n"
		"relocation section 2 + 4 absolute 4 bytes = Optional + 0\n",
		szDump.Text());
	szDump.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// keep and associated (for removing unused sections), alone and with comdat.  An
// association may name a section that comes later.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ObjectSectionOptions(void)
{
	CChars	szDump;

	AssembleObject(&szDump,
		"	.section text.Start, keep\n"
		"	stp\n"
		"	.section init.Make, associated data.gThing\n"
		"	.long 0\n"
		"	.section text.Shared, comdat Group, keep\n"
		"	ret\n"
		"	.section data.gThing\n"
		"	.long 0\n");

	AssertString(
		"section 0 text align 1 size 0\n"
		"section 1 text.Start keep align 2 size 2\n"
		"  $3b $00\n"
		"section 2 init.Make associated 4 align 1 size 4\n"
		"  $00 $00 $00 $00\n"
		"section 3 text.Shared comdat Group keep align 2 size 2\n"
		"  $0b $01\n"
		"section 4 data.gThing align 1 size 4\n"
		"  $00 $00 $00 $00\n",
		szDump.Text());
	szDump.Kill();

	AssertObjectError("1:33: Unknown section 'data.gMissing'\n", "	.section init.Make, associated data.gMissing\n	.long 0\n");
	AssertObjectError("1:23: Expected comdat, associated, keep, resident or at 'always'\n", "	.section text.Start, always\n");

	AssembleObject(&szDump, "	.section text.Fixed, comdat, resident\n	stp\n");
	AssertString(
		"section 0 text align 1 size 0\n"
		"section 1 text.Fixed comdat text.Fixed resident align 2 size 2\n"
		"  $3b $00\n",
		szDump.Text());
	szDump.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ObjectErrors(void)
{
	CAsm65Assembler	cAssembler;

	AssertObjectError("1:6: .org is only allowed in absolute mode; use .section '$1000'\n", ".org $1000\n");
	AssertObjectError("2:12: A section address can only have a constant added or subtracted '*'\n", "L:\n	cpy A, L2 * 2\nL2:\n");
	AssertObjectError("4:14: Addresses in different sections cannot be combined '-'\n", "Start:\n	stp\n	.section data\n	.long Start - Data\nData:\n");
	AssertObjectError("2:9: An address must be one label plus or minus a constant 'Start'\n", "Start:\n	cpy A, Start + Start\n");
	AssertObjectError("2:9: A section address cannot be used here 'Start'\n", "Start:\n	shl A, Start\n");
	AssertObjectError("2:8: A bss section only has labels, .space and .align '0'\n", "	.section bss\n	.long 0\n");
	AssertObjectError("2:2: A bss section only has labels, .space and .align 'nop'\n", "	.section bss\n	nop\n");
	AssertObjectError("1:11: A section name starts with text, rodata, init, fini, data or bss 'code'\n", "	.section code\n");
	AssertObjectError("2:1: Symbol is declared external 'Twice'\n", "	.extern Twice\nTwice:\n");
	AssertObjectError("1:8: A global symbol cannot be an external plus a value 'Other'\n", "Near = Other + 2\n	.global Near\n	jmp Other\n");

	TestAsm65Assemble(&cAssembler, "");
	cAssembler.Kill();
	cAssembler.Init();
	AssertFalse(cAssembler.Assemble("	.section text\n	.global Start\n"));
	AssertString("1:11: .section is only allowed when assembling an object 'text'\n2:2: Symbol bindings are only allowed when assembling an object '.global'\n", cAssembler.GetErrors());
	cAssembler.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Writes the object to pcWrite, reads it back from pcRead and compares the dumps.
//
//////////////////////////////////////////////////////////////////////////
static void AssertReadsBack(CAsm65Object* pcObject, CAbstractFile* pcWrite, CAbstractFile* pcRead)
{
	CAsm65Object	cRead;
	CChars			szExpected;
	CChars			szActual;

	AssertTrue(pcObject->Write(pcWrite));
	cRead.Init("");
	AssertTrue(cRead.Read(pcRead));
	szExpected.Init();
	pcObject->Dump(&szExpected);
	szActual.Init();
	cRead.Dump(&szActual);
	AssertString(szExpected.Text(), szActual.Text());
	AssertString(pcObject->GetName(), cRead.GetName());
	szActual.Kill();
	szExpected.Kill();
	cRead.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// An object written as a ChunkFile (to memory and to disk) reads back the same.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ObjectFile(void)
{
	CAsm65Object	cObject;
	CAsm65Object	cRead;
	CMemoryFile*	pcMemoryFile;
	CFileUtil		cFileUtil;
	char			acJunk[64];

	cObject.Init("file");
	AssertTrue(TestAsm65AssembleObject(&cObject,
		"	.global Start\n"
		"	.weak Hook\n"
		"Start:\n"
		"	cpy A, [Data]\n"
		"	jsr Helper\n"
		"	bras z, Hook\n"
		"	stp\n"
		"	.section data\n"
		"Data:\n"
		"	.long Start, Data + 4\n"
		"	.section bss\n"
		"	.space 16\n"
		"	.section text.Hook, comdat Hooks\n"
		"Hook:\n"
		"	ret\n"));

	pcMemoryFile = MemoryFile();
	pcMemoryFile->mbBasicFileMustFree = false;
	AssertReadsBack(&cObject, pcMemoryFile, pcMemoryFile);
	SafeKill(pcMemoryFile);

	cFileUtil.MakeDir("Output");
	cFileUtil.Delete("Output" _FS_ "Asm65Object.o65");
	AssertReadsBack(&cObject, DiskFile("Output" _FS_ "Asm65Object.o65"), DiskFile("Output" _FS_ "Asm65Object.o65"));

	//Not an object.
	memset(acJunk, 0x5A, sizeof(acJunk));
	cRead.Init("");
	AssertFalse(cRead.Read(MemoryFile(acJunk, sizeof(acJunk))));
	cRead.Kill();

	cObject.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Object(void)
{
	BeginTests();

	TestAsm65ObjectRelocations();
	TestAsm65ObjectWidths();
	TestAsm65ObjectSectionsAndBindings();
	TestAsm65ObjectErrors();
	TestAsm65ObjectSectionOptions();
	TestAsm65ObjectFile();

	TestStatistics();
}
