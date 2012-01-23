#include "BaseLib/FileSystem.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TextFile.h"
#include "TestLib/Assert.h"
#include "TestFileSystem.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileSystemInit(void)
{
	CFileSystem		cSystem;
	char*			szFullName;
	CFileUtil		cFileUtil;
	CChars			szWorkingDirectory;
	CChars			szTemp;
	CTextFile		cTextFile;

	szWorkingDirectory.Init("Finder");
	cFileUtil.FullPath(&szWorkingDirectory);

	cSystem.Init("Finder");

	szFullName = cSystem.GetFileName("Lord/1.rar");
	szTemp.Init(szFullName);
	szTemp.RemoveFromStart(szWorkingDirectory.Length()+1);
	szTemp.Replace(FILE_SEPARATOR[0], '/');

	AssertString("Lord/1.rar", szTemp.Text());
	szTemp.Kill();

	szFullName = cSystem.GetFileName("File.txt");
	cTextFile.Init();
	cTextFile.Read(szFullName);

	AssertString("Hello World.", cTextFile.Text());

	cTextFile.Kill();

	cSystem.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileSystemNearest(void)
{
	CFileSystem				cSystem;
	CFileUtil				cFileUtil;
	CChars					szWorkingDirectory;
	CFileNodeSystemFile*	pcNode;
	CChars					szRemaining;

	szWorkingDirectory.Init("Finder");
	cFileUtil.FullPath(&szWorkingDirectory);

	cSystem.Init("Finder");

	szRemaining.Init();
	pcNode = cSystem.GetFileNode("Lord/1.rar/Happy/Quan", &szRemaining);
	AssertNotNull(pcNode);
	AssertString("Happy/Quan", szRemaining.Text());
	szRemaining.Kill();

	szRemaining.Init();
	pcNode = cSystem.GetFileNode("File.txt/Sad/Quan", &szRemaining);
	AssertNotNull(pcNode);
	AssertString("Sad/Quan", szRemaining.Text());
	szRemaining.Kill();

	cSystem.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileSystemFindExtension(void)
{
	CFileSystem					cSystem;
	CArraySystemFileNodePtrs	aFileNodePtrs;

	cSystem.Init("Finder");

	aFileNodePtrs.Init(8);
	cSystem.GetFileExtension(&aFileNodePtrs, "rar");

	AssertInt(6, aFileNodePtrs.NumElements());

	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Lord\\1.rar", (*aFileNodePtrs.Get(0))->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Rising\\2.rar", (*aFileNodePtrs.Get(1))->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Storm\\3.rar", (*aFileNodePtrs.Get(2))->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Ants.rar", (*aFileNodePtrs.Get(3))->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Echo.rar", (*aFileNodePtrs.Get(4))->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\March.rar", (*aFileNodePtrs.Get(5))->GetFullName(), FALSE);

	aFileNodePtrs.Kill();
	cSystem.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileSystem(void)
{
	BeginTests();
	FastFunctionsInit();

	TestFileSystemInit();
	TestFileSystemNearest();
	TestFileSystemFindExtension();

	FastFunctionsKill();
	TestStatistics();
}

