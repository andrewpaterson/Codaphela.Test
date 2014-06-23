#include "BaseLib/FileSystem.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TextFile.h"
#include "TestLib/Assert.h"


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
	CFileSystem				cSystem;
	CArraySystemFilePtrs	aFileNodePtrs;

	cSystem.Init("Finder");

	aFileNodePtrs.Init(8);
	cSystem.GetFiles(&aFileNodePtrs, "rar");

	AssertInt(6, aFileNodePtrs.NumElements());

	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Lord\\1.rar", (*aFileNodePtrs.Get(0))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Rising\\2.rar", (*aFileNodePtrs.Get(1))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Storm\\3.rar", (*aFileNodePtrs.Get(2))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Ants.rar", (*aFileNodePtrs.Get(3))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Echo.rar", (*aFileNodePtrs.Get(4))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\March.rar", (*aFileNodePtrs.Get(5))->File()->GetFullName(), FALSE);

	aFileNodePtrs.Kill();
	cSystem.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileSystemGetFiles(void)
{
	CFileSystem							cSystem;
	CArraySystemFilePtrs				cArrayFiles;

	cSystem.Init("Finder");
	cArrayFiles.Init();

	cSystem.GetFiles(&cArrayFiles);

	AssertInt(12, cArrayFiles.NumElements());

	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Lord\\1.rar", (*cArrayFiles.Get(0))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Rising\\2.rar", (*cArrayFiles.Get(1))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Storm\\3.rar", (*cArrayFiles.Get(2))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Ants.rar", (*cArrayFiles.Get(3))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Ants.txt", (*cArrayFiles.Get(4))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Echo.rar", (*cArrayFiles.Get(5))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\File.txt", (*cArrayFiles.Get(6))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Glenmark.wav", (*cArrayFiles.Get(7))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Last.txt", (*cArrayFiles.Get(8))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\March.rar", (*cArrayFiles.Get(9))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Marching.txt", (*cArrayFiles.Get(10))->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Ninja.txt", (*cArrayFiles.Get(11))->File()->GetFullName(), FALSE);

	cArrayFiles.Kill();
	cSystem.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileSystemIterator(void)
{
	CFileSystem			cSystem;
	CFileSystemIterator	cIter;

	cSystem.Init("Finder");

	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Lord\\1.rar", cSystem.StartIteration(&cIter)->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Rising\\2.rar", cSystem.Iterate(&cIter)->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Storm\\3.rar", cSystem.Iterate(&cIter)->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Ants.rar", cSystem.Iterate(&cIter)->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Ants.txt", cSystem.Iterate(&cIter)->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Echo.rar", cSystem.Iterate(&cIter)->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\File.txt", cSystem.Iterate(&cIter)->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Glenmark.wav", cSystem.Iterate(&cIter)->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Last.txt", cSystem.Iterate(&cIter)->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\March.rar", cSystem.Iterate(&cIter)->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Marching.txt", cSystem.Iterate(&cIter)->File()->GetFullName(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Ninja.txt", cSystem.Iterate(&cIter)->File()->GetFullName(), FALSE);
	AssertNull(cSystem.Iterate(&cIter));
	cSystem.StopIteration(&cIter);

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
	TestFileSystemGetFiles();
	TestFileSystemIterator();

	FastFunctionsKill();
	TestStatistics();
}

