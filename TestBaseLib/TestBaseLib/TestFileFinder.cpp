#include "BaseLib/FileUtil.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileFinder(void)
{
	BeginTests();

	CFileUtil		cFileUtil;
	CArrayString	aszFiles;

	aszFiles.Init(1);
	cFileUtil.FindFilesWithExtension("Finder", "txt", &aszFiles);
	AssertInt(5, aszFiles.NumElements());
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Ants.txt", aszFiles.Get(0)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\File.txt", aszFiles.Get(1)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Last.txt", aszFiles.Get(2)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Marching.txt", aszFiles.Get(3)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Ninja.txt", aszFiles.Get(4)->Text(), FALSE);
	aszFiles.Kill();

	aszFiles.Init(1);
	cFileUtil.FindFilesWithNameContaining("Finder", "Mar", &aszFiles);
	AssertInt(3, aszFiles.NumElements());
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Glenmark.wav", aszFiles.Get(0)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\March.rar", aszFiles.Get(1)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Marching.txt", aszFiles.Get(2)->Text(), FALSE);
	aszFiles.Kill();

	aszFiles.Init(1);
	cFileUtil.FindAllDirectories("Finder", &aszFiles);
	aszFiles.QuickSort();
	AssertInt(5, aszFiles.NumElements());
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\.", aszFiles.Get(0)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\..", aszFiles.Get(1)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Lord", aszFiles.Get(2)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Rising", aszFiles.Get(3)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Storm", aszFiles.Get(4)->Text(), FALSE);
	aszFiles.Kill();

	aszFiles.Init(1);
	cFileUtil.FindFilesWithExtension("Finder", "rar", &aszFiles, TRUE);
	AssertInt(6, aszFiles.NumElements());
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Lord\\1.rar", aszFiles.Get(0)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Rising\\2.rar", aszFiles.Get(1)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Storm\\3.rar", aszFiles.Get(2)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Ants.rar", aszFiles.Get(3)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\Echo.rar", aszFiles.Get(4)->Text(), FALSE);
	AssertStringCase("C:\\gameengine\\Test\\TestBaseLib\\TestBaseLib\\Finder\\March.rar", aszFiles.Get(5)->Text(), FALSE);
	aszFiles.Kill();

	aszFiles.Init(1);
	cFileUtil.FindAllFiles("Finder", &aszFiles, TRUE);
	AssertInt(12, aszFiles.NumElements());
	aszFiles.Kill();

	TestStatistics();
}

