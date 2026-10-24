#include <string.h>
#include <stdlib.h>
#include "TestCPP65Context.h"
#include "Assembler65Lib/Asm65Assembler.h"
#include "BaseLib/TextFile.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/ConstructorCall.h"
#include "BaseLib/PointerFunctions.h"
#include "CppParserLib/CPP65Generator.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
// Adds the include directory szRelative (to this test's directory) as a full path.
//
//////////////////////////////////////////////////////////////////////////
static void TestCPP65AddIncludeDirectory(CCPP65Builder* pcBuilder, const char* szRelative, bool bIncludeSubDirectories, bool bSystem)
{
	CFileUtil	cFileUtil;
	CChars		szDirectory;

	szDirectory.Init(szRelative);
	cFileUtil.FullPath(&szDirectory);
	pcBuilder->AddIncludeDirectory(szDirectory.Text(), bIncludeSubDirectories, bSystem);
	szDirectory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// <stdint.h> and the rest are the 65C64's (Libc65), "BaseLib/..." are the libraries', and the test's own headers
// are in Input/CPP65.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65AddIncludeDirectories(CCPP65Builder* pcBuilder)
{
	TestCPP65AddIncludeDirectory(pcBuilder, ".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65", false, true);
	TestCPP65AddIncludeDirectory(pcBuilder, ".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries", true, false);
	TestCPP65AddIncludeDirectory(pcBuilder, "Input" _FS_ "CPP65", true, false);
	TestCPP65AddIncludeDirectory(pcBuilder, ".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "BaseLib", false, false);
}


//////////////////////////////////////////////////////////////////////////
//
// Preprocesses, parses and generates szSource, as a whole program with its start up if bProgram, otherwise as
// an object, appended to pszAssembly, and the errors to pszErrors.  The labels it uses but does not define are
// added to paszExternals.
//
//////////////////////////////////////////////////////////////////////////
bool TestCPP65Generate(CChars* pszAssembly, CChars* pszErrors, const char* szSource, bool bProgram, CArrayChars* paszExternals)
{
	CCPP65Builder	cBuilder;
	bool			bResult;

	cBuilder.Init();
	TestCPP65AddIncludeDirectories(&cBuilder);
	bResult = CCPP65Builder::Generate(pszAssembly, pszErrors, cBuilder.GetIncludeDirectories(), "Generated.cpp", szSource, bProgram, paszExternals);
	cBuilder.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles and assembles szSource as a program, loads it and runs reset.
//
//////////////////////////////////////////////////////////////////////////
bool TestCPP65Begin(STestCPP65Run* psRun, const char* szSource)
{
	CChars	szAssembly;
	CChars	szErrors;
	bool	bResult;

	szAssembly.Init();
	szErrors.Init();
	bResult = TestCPP65Generate(&szAssembly, &szErrors, szSource, true);
	AssertString("", szErrors.Text());
	bResult &= TestCPP65BeginAssembly(psRun, szAssembly.Text());
	szErrors.Kill();
	szAssembly.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Loads a linked program into new memory and runs reset.  A program linked lazily
// gets a drive with its units from TEST_CPP65_FIRST_SECTOR.
//
//////////////////////////////////////////////////////////////////////////
bool TestCPP65BeginBuilt(STestCPP65Run* psRun, CCPP65Builder* pcBuilder)
{
	CArrayUint8*	pcImage;

	psRun->pcContext = (CAsm65Memory*)malloc(sizeof(CAsm65Memory));
	psRun->pcContext->Init();
	psRun->uiInstructions = 0;
	psRun->pcContext->LoadProgram(pcBuilder->GetOutput(), CPP65_PROGRAM_ADDRESS);

	psRun->pcDrive = NULL;
	psRun->uiUnits = pcBuilder->NumUnits();
	if (psRun->uiUnits > 0)
	{
		pcImage = pcBuilder->GetLazyImage();
		psRun->pcDrive = NewMalloc<CMemoryDrive>();
		psRun->pcDrive->Init(TEST_CPP65_FIRST_SECTOR * TEST_CPP65_SECTOR_SIZE + pcImage->NumElements(), TEST_CPP65_SECTOR_SIZE);
		memcpy((uint8*)psRun->pcDrive->GetMemory() + TEST_CPP65_FIRST_SECTOR * TEST_CPP65_SECTOR_SIZE, pcImage->GetData(), pcImage->NumElements());
		psRun->pcContext->SetDrive(psRun->pcDrive);
	}

	psRun->cMeta.Init(CAsm65Memory::TickHigh, CAsm65Memory::TickLow, psRun->pcContext);
	psRun->cMeta.TickInstruction();
	return true;
}


//////////////////////////////////////////////////////////////////////////
//
// Assembles a program (one object with its start up), links it, loads it and runs reset.  A label it uses but
// doesn't define is a link error.
//
//////////////////////////////////////////////////////////////////////////
bool TestCPP65BeginAssembly(STestCPP65Run* psRun, const char* szAssembly)
{
	CCPP65Builder	cBuilder;
	bool			bResult;

	cBuilder.Init();
	cBuilder.SetStubMissing(false);
	bResult = cBuilder.AddAssembly("program", szAssembly);
	bResult &= cBuilder.Link();
	AssertString("", cBuilder.GetErrors());
	bResult &= TestCPP65BeginBuilt(psRun, &cBuilder);
	cBuilder.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Runs until the processor stops.  Returns the number of instructions.
//
//////////////////////////////////////////////////////////////////////////
size TestCPP65Run(STestCPP65Run* psRun, size uiMaxInstructions)
{
	size	i;

	for (i = 0; i < uiMaxInstructions; i++)
	{
		if (!psRun->cMeta.TickInstruction())
		{
			psRun->uiInstructions += i + 1;
			return i + 1;
		}
	}
	psRun->uiInstructions += i;
	return i;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
C65C64* TestCPP65MPU(STestCPP65Run* psRun)
{
	return psRun->cMeta.GetMPU();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65End(STestCPP65Run* psRun)
{
	AssertSize(0, psRun->pcContext->NumBadAccesses());
	psRun->cMeta.Kill();
	free(psRun->pcContext);
	SafeKill(psRun->pcDrive);
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles szSource (as a program with its start up if bProgram) and assembles it as an object.  Returns the
// number of labels it uses but does not define.
//
//////////////////////////////////////////////////////////////////////////
int TestCPP65Assemble(const char* szSource, bool bProgram)
{
	CChars				szAssembly;
	CChars				szErrors;
	CArrayChars			aszExternals;
	CAsm65Assembler		cAssembler;
	CAsm65Object		cObject;
	int					iExternals;

	szAssembly.Init();
	szErrors.Init();
	aszExternals.Init();
	AssertTrue(TestCPP65Generate(&szAssembly, &szErrors, szSource, bProgram, &aszExternals));
	AssertString("", szErrors.Text());

	cObject.Init("unit");
	cAssembler.Init();
	AssertTrue(cAssembler.AssembleObject(szAssembly.Text(), &cObject));
	AssertString("", cAssembler.GetErrors());
	cAssembler.Kill();
	cObject.Kill();

	iExternals = (int)aszExternals.NumElements();
	aszExternals.Kill();
	szErrors.Kill();
	szAssembly.Kill();
	return iExternals;
}


//////////////////////////////////////////////////////////////////////////
//
// TestCPP65Assemble on a file of the libraries, as a translation unit.
//
//////////////////////////////////////////////////////////////////////////
int TestCPP65AssembleLibraryFile(const char* szFilename)
{
	CTextFile	cFile;
	CChars		szPath;
	int			iExternals;

	szPath.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_);
	szPath.Append(szFilename);
	cFile.Init();
	AssertTrue(cFile.Read(szPath.Text()));
	cFile.PassifyNewlines();
	iExternals = TestCPP65Assemble(cFile.Text(), false);
	cFile.Kill();
	szPath.Kill();
	return iExternals;
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles and runs Input/CPP65/szFilename.  Returns what main returned.
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP65MainFile(const char* szFilename)
{
	CTextFile	cFile;
	CChars		szPath;
	int32		iResult;

	szPath.Init("Input" _FS_ "CPP65" _FS_);
	szPath.Append(szFilename);
	cFile.Init();
	AssertTrue(cFile.Read(szPath.Text()));
	cFile.PassifyNewlines();
	iResult = TestCPP65Main(cFile.Text());
	cFile.Kill();
	szPath.Kill();
	return iResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles and runs szSource.  Returns what main returned.  The program must stop within a million instructions
// with the stack where it started.
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP65Main(const char* szSource)
{
	STestCPP65Run	sRun;
	int32			iResult;

	AssertTrue(TestCPP65Begin(&sRun, szSource));
	AssertTrue(TestCPP65Run(&sRun, 1000000) < 1000000);
	AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());
	iResult = (int32)TestCPP65MPU(&sRun)->GetA();
	TestCPP65End(&sRun);
	return iResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles every .cpp file of a library under commonlibraries (szLibrary, such as "BaseLib") as a link library,
// with a main that uses none of it, and links.  pszErrors gets the compiler's and linker's errors.  Returns how
// many files were compiled.
//
//////////////////////////////////////////////////////////////////////////
size TestCPP65CompileLibrary(const char* szLibrary, CChars* pszErrors)
{
	CCPP65Builder	cBuilder;
	CFileUtil		cFileUtil;
	CArrayChars		aszFiles;
	CChars			szDirectory;
	CChars*			pszFile;
	size			i;
	size			iSlash;

	cBuilder.Init();
	TestCPP65AddIncludeDirectories(&cBuilder);
	cBuilder.SetStubMissing(true);
	cBuilder.AddStartUp();
	cBuilder.AddSource("Main.cpp", "int main() { return 0; }\n");

	szDirectory.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_);
	szDirectory.Append(szLibrary);
	cFileUtil.FullPath(&szDirectory);
	aszFiles.Init();
	cFileUtil.FindFilesWithExtension(szDirectory.Text(), "cpp", &aszFiles);
	aszFiles.QuickSort();
	for (i = 0; i < aszFiles.NumElements(); i++)
	{
		pszFile = aszFiles.Get(i);
		iSlash = pszFile->FindFromEnd(FILE_SEPARATOR[0]);
		cBuilder.AddUnit(szLibrary, szDirectory.Text(), pszFile->Text(iSlash + 1), true);
	}

	cBuilder.Link();
	pszErrors->Append(cBuilder.GetErrors());
	i = aszFiles.NumElements();
	aszFiles.Kill();
	szDirectory.Kill();
	cBuilder.Kill();
	return i;
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles the units (paths under commonlibraries, or under this test's directory when they start with "Input")
// and szSource if it is given, each into an object, links them after the start up and loads the program.  The
// units in a directory share a CLibrary (their include settings).  The labels in szStubs (space separated,
// sorted) must be exactly the ones used but defined by no unit; the linker makes each a stp so a call to one
// stops the program.  pszMap, if given, gets the linker's map.
//
//////////////////////////////////////////////////////////////////////////
bool TestCPP65BeginProject(STestCPP65Run* psRun, const char** aszUnits, const char* szStubs, const char* szSource, CChars* pszMap, bool bLazy)
{
	CCPP65Builder	cBuilder;
	CFileUtil		cFileUtil;
	CChars			szDirectory;
	CChars			szLibrary;
	CChars			szFile;
	CChars			szMissing;
	size			iSlash;
	size			i;
	bool			bResult;

	cBuilder.Init();
	TestCPP65AddIncludeDirectories(&cBuilder);
	if (bLazy)
	{
		cBuilder.SetLazy(TEST_CPP65_SECTOR_SIZE, TEST_CPP65_FIRST_SECTOR);
	}

	bResult = cBuilder.AddStartUp();
	if (szSource)
	{
		bResult &= cBuilder.AddSource("source", szSource);
	}
	for (i = 0; aszUnits[i]; i++)
	{
		szLibrary.Init(aszUnits[i]);
		iSlash = szLibrary.FindFromEnd('/');
		szFile.Init(szLibrary.Text(iSlash + 1));
		szLibrary.SetLength(iSlash);
		if (szLibrary.StartsWith("Input"))
		{
			szDirectory.Init(szLibrary);
		}
		else
		{
			szDirectory.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_);
			szDirectory.Append(szLibrary);
		}
		szDirectory.Replace('/', FILE_SEPARATOR[0]);
		cFileUtil.FullPath(&szDirectory);
		cBuilder.AddUnit(szLibrary.Text(), szDirectory.Text(), szFile.Text());
		szDirectory.Kill();
		szFile.Kill();
		szLibrary.Kill();
	}

	//A program that doesn't build isn't loaded.
	bResult &= cBuilder.Link();
	AssertString("", cBuilder.GetErrors());
	if (bResult)
	{
		TestCPP65BeginBuilt(psRun, &cBuilder);
	}

	//What is used but written by no unit.
	szMissing.Init();
	cBuilder.GetMissingNames(&szMissing);
	AssertString(szStubs, szMissing.Text());
	if (pszMap)
	{
		pszMap->Append(cBuilder.GetMap());
	}

	szMissing.Kill();
	cBuilder.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Builds a project (see TestCPP65BeginProject) and runs it.  Returns A when main returns.
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP65RunProject(const char** aszUnits, const char* szStubs, size uiMaxInstructions, const char* szSource)
{
	STestCPP65Run	sRun;
	int32			iResult;

	iResult = 0;
	if (TestCPP65BeginProject(&sRun, aszUnits, szStubs, szSource))
	{
		AssertTrue(TestCPP65Run(&sRun, uiMaxInstructions) < uiMaxInstructions);
		AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());
		iResult = (int32)TestCPP65MPU(&sRun)->GetA();
		TestCPP65End(&sRun);
	}
	return iResult;
}


//////////////////////////////////////////////////////////////////////////
//
// TestCPP65RunProject with the functions loaded when they are first called.  Returns A
// when main returns; *puiUnits is how many units there are and *puiLoads how many were
// loaded.
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP65RunProjectLazy(const char** aszUnits, const char* szStubs, size* puiUnits, size* puiLoads, const char* szSource)
{
	STestCPP65Run	sRun;
	int32			iResult;

	iResult = 0;
	*puiUnits = 0;
	*puiLoads = 0;
	if (TestCPP65BeginProject(&sRun, aszUnits, szStubs, szSource, NULL, true))
	{
		AssertTrue(TestCPP65Run(&sRun, 20000000) < 20000000);
		AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());
		iResult = (int32)TestCPP65MPU(&sRun)->GetA();
		*puiUnits = sRun.uiUnits;
		*puiLoads = sRun.pcContext->NumDriveReads();
		TestCPP65End(&sRun);
	}
	return iResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles and runs szSource with Libc65's soft float runtime.  Returns what main returned.
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP65MainFloat(const char* szSource)
{
	static const char*	aszUnits[] = { "Libc65/softfloat.cpp", "Libc65/softfloat.asm", NULL };

	return TestCPP65RunProject(aszUnits, "", 20000000, szSource);
}

