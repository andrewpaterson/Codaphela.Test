#include "BaseLib/TextFile.h"
#include "BaseLib/DebugOutput.h"
#include "CoreLib/Files.h"
#include "TestLib/Assert.h"
#include "TestFiles.h"


void AssertPakFile(char* szFileName, char* szContents, CFiles* pcFiles);
void AssertFileName(CMapStringInt* pcMap, int iIndex, int iCount, char* szFileName);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFilesSimple(void)
{
	CFiles			cFiles;
	CAbstractFile*	pcFile;
	CTextFile		cTextFile;

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
	
	AssertFileName(&cFileNames,  0, 2, "Models/Cars.txt");
	AssertFileName(&cFileNames,  1, 2, "Models/Super/Barbie.txt");
	AssertFileName(&cFileNames,  2, 2, "Models/Super/Ken.txt");
	AssertFileName(&cFileNames,  3, 2, "Sounds/Ambient.txt");
	AssertFileName(&cFileNames,  4, 2, "Sounds/Cheese/Moose.txt");
	AssertFileName(&cFileNames,  5, 2, "Sounds/Cheese/Scream.txt");
	AssertFileName(&cFileNames,  6, 1, "Sounds/General.txt");
	AssertFileName(&cFileNames,  7, 3, "Sounds/Santa/Seattle.txt");
	AssertFileName(&cFileNames,  8, 1, "Sounds/Santa/Slay/Spelling.txt");
	AssertFileName(&cFileNames,  9, 2, "Videos/Intro.txt");
	AssertFileName(&cFileNames, 10, 1, "Videos/Outro.txt");

	cFileNames.Kill();
	
	cFiles.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertFileName(CMapStringInt* pcMap, int iIndex, int iCount, char* szFileName)
{
	CChars*			pszKey;
	int*			piValue;
	BOOL			bResult;

	bResult = pcMap->GetAtIndex(iIndex, &pszKey, &piValue);
	AssertTrue(bResult);

	AssertString(szFileName, pszKey->Text());
	AssertInt(iCount, *piValue);
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

	TestFilesSimple();
	TestGetFileNames();
	TestFilesWholeDirectory();

	TestStatistics();
}

