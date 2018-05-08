#include "BaseLib/TextFile.h"
#include "BaseLib/DebugOutput.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/Files.h"
#include "TestLib/Assert.h"


void AssertPakFile(char* szFileName, char* szContents, CFiles* pcFiles);
void AssertFileName(CMapStringInt* pcMap, int iCount, int iRank, char* szFileName);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFilesSimple(void)
{
	CFiles			cFiles;
	CAbstractFile*	pcFile;
	CTextFile		cTextFile;

	//If this test fails you probably need to re-generate the source PAK files.
	//Use TestPackFilesPackerSimple to do this.

	cFiles.Init("Game", "PAK");
	AssertInt(6, cFiles.GetNumPackFiles());

	pcFile = cFiles.GetFile("Sounds/Santa/Seattle.txt");
	AssertNotNull(pcFile);

	cTextFile.Init();
	cTextFile.Read(pcFile);
	AssertString("All night long\r\n", cTextFile.Text());
	cTextFile.Kill();

	pcFile = cFiles.GetFile("Sounds/General.txt");
	AssertNotNull(pcFile);

	cTextFile.Init();
	cTextFile.Read(pcFile);
	AssertString("General", cTextFile.Text());
	cTextFile.Kill();

	pcFile = cFiles.GetFile("Sounds/Santa/Slay/Spelling.txt");
	AssertNotNull(pcFile);

	cTextFile.Init();
	cTextFile.Read(pcFile);
	AssertString("Spelling", cTextFile.Text());
	cTextFile.Kill();

	cFiles.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileSystemIteration(void)
{
	CFileSystem				cFileSystem;
	CFileSystemIterator		cIter;
	CSystemFileNode*		pcSystemFile;
	CChars					szName;
	int						i;
	CArrayChars				aszExpected;
	CChars*					pszExpected;

	aszExpected.Init(10);
	aszExpected.AddList("Models/Super/Barbie.txt",
		"Models/Super/Ken.txt",
		"Models/Cars.txt",
		"Sounds/Santa/Seattle.txt",
		"Sounds/Ambient.txt",
		"Sounds/Cheese.PAK",
		"Sounds/Santa.PAK",
		"Videos/Intro.txt",
		"Videos/Outro.txt",
		"Models.PAK",
		"Sounds.PAK",
		"Textures.PAK",
		"Videos.PAK",
		NULL);

	cFileSystem.Init("Game");

	i = 0;
	pcSystemFile = cFileSystem.StartIteration(&cIter);
	while (pcSystemFile)
	{ 
		szName.Init();
		pcSystemFile->GetFullName(&szName);
		pszExpected = aszExpected.Get(i);
		AssertString(pszExpected->Text(), szName.Text());
		szName.Kill();

		i++;
		pcSystemFile = cFileSystem.Iterate(&cIter);
	}
	aszExpected.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFilesIteration(void)
{
	CFiles			cFiles;
	CFileIterator	cIter;

	cFiles.Init("Game", "PAK");
	AssertInt(6, cFiles.GetNumPackFiles());
	AssertString("C:\\gameengine\\Test\\TestCoreLib\\TestCoreLib\\Game\\Sounds\\Cheese.PAK", cFiles.GetPackFiles(0)->GetFileName());
	AssertString("C:\\gameengine\\Test\\TestCoreLib\\TestCoreLib\\Game\\Sounds\\Santa.PAK", cFiles.GetPackFiles(1)->GetFileName());
	AssertString("C:\\gameengine\\Test\\TestCoreLib\\TestCoreLib\\Game\\Textures.PAK", cFiles.GetPackFiles(2)->GetFileName());
	AssertString("C:\\gameengine\\Test\\TestCoreLib\\TestCoreLib\\Game\\Models.PAK", cFiles.GetPackFiles(3)->GetFileName());
	AssertString("C:\\gameengine\\Test\\TestCoreLib\\TestCoreLib\\Game\\Sounds.PAK", cFiles.GetPackFiles(4)->GetFileName());
	AssertString("C:\\gameengine\\Test\\TestCoreLib\\TestCoreLib\\Game\\Videos.PAK", cFiles.GetPackFiles(5)->GetFileName());

	AssertStringCase("Sounds/Cheese/Moose.txt", cFiles.StartIteration(&cIter)->GetFullName(), FALSE);
	AssertInt(1, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_PackFiles, cIter.GetCurrent()->GetType());

	AssertStringCase("Sounds/Cheese/Scream.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(1, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_PackFiles, cIter.GetCurrent()->GetType());

	AssertStringCase("Sounds/Santa/Slay/Spelling.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(1, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_PackFiles, cIter.GetCurrent()->GetType());

	AssertStringCase("Sounds/Santa/Seattle.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(1, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_PackFiles, cIter.GetCurrent()->GetType());

	AssertStringCase("Models/Super/Barbie.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(0, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_PackFiles, cIter.GetCurrent()->GetType());

	AssertStringCase("Models/Super/Ken.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(0, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_PackFiles, cIter.GetCurrent()->GetType());

	AssertStringCase("Models/Cars.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(0, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_PackFiles, cIter.GetCurrent()->GetType());

	AssertStringCase("Sounds/Cheese/Moose.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(0, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_PackFiles, cIter.GetCurrent()->GetType());

	AssertStringCase("Sounds/Cheese/Scream.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(0, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_PackFiles, cIter.GetCurrent()->GetType());

	AssertStringCase("Sounds/Santa/Seattle.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(0, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_PackFiles, cIter.GetCurrent()->GetType());

	AssertStringCase("Sounds/Ambient.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(0, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_PackFiles, cIter.GetCurrent()->GetType());

	AssertStringCase("Sounds/General.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(0, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_PackFiles, cIter.GetCurrent()->GetType());

	AssertStringCase("Videos/Intro.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(0, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_PackFiles, cIter.GetCurrent()->GetType());

	AssertStringCase("Models/Super/Barbie.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(FILE_SYSTEM_RANK, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_FileSystem, cIter.GetCurrent()->GetType());

	AssertStringCase("Models/Super/Ken.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(FILE_SYSTEM_RANK, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_FileSystem, cIter.GetCurrent()->GetType());

	AssertStringCase("Models/Cars.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(FILE_SYSTEM_RANK, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_FileSystem, cIter.GetCurrent()->GetType());

	AssertStringCase("Sounds/Santa/Seattle.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(FILE_SYSTEM_RANK, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_FileSystem, cIter.GetCurrent()->GetType());

	AssertStringCase("Sounds/Ambient.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(FILE_SYSTEM_RANK, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_FileSystem, cIter.GetCurrent()->GetType());

	AssertStringCase("Videos/Intro.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(FILE_SYSTEM_RANK, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_FileSystem, cIter.GetCurrent()->GetType());

	AssertStringCase("Videos/Outro.txt", cFiles.Iterate(&cIter)->GetFullName(), FALSE); 
	AssertInt(FILE_SYSTEM_RANK, cIter.GetCurrent()->GetFileRank());
	AssertInt(FIRT_FileSystem, cIter.GetCurrent()->GetType());

	AssertNull(cFiles.Iterate(&cIter));
	AssertNull(cIter.GetCurrent());
	cFiles.StopIteration(&cIter);

	cFiles.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGetFileNames(void)
{
	CFiles			cFiles;
	CMapStringInt	cFileNames;
	int				iNumFiles;

	cFiles.Init("Game", "PAK");

	cFileNames.Init(2, TRUE);
	cFiles.GetFileNames(&cFileNames);

	iNumFiles = cFileNames.NumElements();
	AssertInt(11, iNumFiles);
	
	AssertFileName(&cFileNames, 2, FILE_SYSTEM_RANK, "Models/Cars.txt");
	AssertFileName(&cFileNames, 2, FILE_SYSTEM_RANK, "Models/Super/Barbie.txt");
	AssertFileName(&cFileNames, 2, FILE_SYSTEM_RANK, "Models/Super/Ken.txt");
	AssertFileName(&cFileNames, 2, FILE_SYSTEM_RANK, "Sounds/Ambient.txt");
	AssertFileName(&cFileNames, 2, 1,                "Sounds/Cheese/Moose.txt");
	AssertFileName(&cFileNames, 2, 1,                "Sounds/Cheese/Scream.txt");
	AssertFileName(&cFileNames, 1, 0,                "Sounds/General.txt");
	AssertFileName(&cFileNames, 3, FILE_SYSTEM_RANK, "Sounds/Santa/Seattle.txt");
	AssertFileName(&cFileNames, 1, 1,                "Sounds/Santa/Slay/Spelling.txt");
	AssertFileName(&cFileNames, 2, FILE_SYSTEM_RANK, "Videos/Intro.txt");
	AssertFileName(&cFileNames, 1, FILE_SYSTEM_RANK, "Videos/Outro.txt");

	cFileNames.Kill();
	
	cFiles.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertFileName(CMapStringInt* pcMap, int iCount, int iRank, char* szFileName)
{
	int*			piValue;

	piValue = pcMap->Get(szFileName);
	AssertNotNull(piValue);

	AssertInt(iCount, *piValue & 0xFFFF);
	AssertInt(iRank, *piValue >> 16);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFilesWholeDirectory(void)
{
	CFiles			cFiles;

	cFiles.Init("Game", "PAK");

	AssertPakFile("Models/Super/Barbie.txt",		"Barbie",				&cFiles);
	AssertPakFile("Models/Super/Ken.txt",			"Ken",					&cFiles);
	AssertPakFile("Models/Cars.txt",				"Cars",					&cFiles);
	AssertPakFile("Sounds/Cheese/Moose.txt",		"Moose with a view",	&cFiles);
	AssertPakFile("Sounds/Cheese/Scream.txt",		"Scream in a space",	&cFiles);
	AssertPakFile("Sounds/Santa/Seattle.txt",		"All night long\r\n",	&cFiles);
	AssertPakFile("Sounds/Santa/Slay/Spelling.txt", "Spelling",				&cFiles);
	AssertPakFile("Sounds/Ambient.txt",				"Ambient occlusion",	&cFiles);
	AssertPakFile("Sounds/General.txt",				"General",				&cFiles);
	AssertPakFile("Videos/Intro.txt",				"Intro",				&cFiles);
	AssertPakFile("Videos/Outro.txt",				"Outro.txt",			&cFiles);

	cFiles.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertPakFile(char* szFileName, char* szContents, CFiles* pcFiles)
{
	CAbstractFile*	pcFile;
	CTextFile		cTextFile;

	pcFile = pcFiles->GetFile(szFileName);
	AssertNotNull(pcFile);

	cTextFile.Init();
	cTextFile.Read(pcFile);
	AssertString(szContents, cTextFile.Text());
	cTextFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFiles(void)
{
	BeginTests();
	
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();

	TestFilesSimple();
	TestFileSystemIteration();
	TestFilesIteration();
	TestGetFileNames();
	TestFilesWholeDirectory();

	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();

	TestStatistics();
}

