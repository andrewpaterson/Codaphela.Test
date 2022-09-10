#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilMisc(void)
{
	CFileUtil	cFileUtil;
	bool		bResult;
	CChars		szPath;

	szPath.Init("TestFileUtil");
	cFileUtil.RemoveDir(szPath.Text());

	bResult = cFileUtil.MakeDir(szPath.Text());
	AssertTrue(bResult);

	cFileUtil.AppendToPath(&szPath, "FileOfDoom.Indiana");
	bResult = cFileUtil.Touch(szPath.Text());
	AssertTrue(bResult);

	bResult = cFileUtil.Exists(szPath.Text());
	AssertTrue(bResult);

	cFileUtil.RemoveLastFromPath(&szPath);
	cFileUtil.AppendToPath(&szPath, "AnotherDir");
	bResult = cFileUtil.MakeDir(szPath.Text());
	AssertTrue(bResult);

	cFileUtil.RemoveLastFromPath(&szPath);
	cFileUtil.AppendToPath(&szPath, "Master.Chief");
	bResult = cFileUtil.Touch(szPath.Text());
	AssertTrue(bResult);

	bResult = cFileUtil.Delete(szPath.Text());
	AssertTrue(bResult);

	bResult = cFileUtil.Exists(szPath.Text());
	AssertFalse(bResult);

	cFileUtil.RemoveLastFromPath(&szPath);
	cFileUtil.RemoveDir(szPath.Text());
	szPath.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilNaming(void)
{
	CFileUtil	cFileUtil;
	CChars		sz;
	CChars		szExpected;

	sz.Init();
	cFileUtil.FullPath(&sz);
	sz.LowerCase();
	szExpected.Init("D:\\GameEngine\\Test\\TestBaseLib\\TestBaseLib");
	szExpected.LowerCase();
	AssertString(szExpected.Text(), sz.Text());
	szExpected.Kill();
	sz.Kill();

	sz.Init("c:\\Documents and Settings\\Joe\\..\\..\\");
	cFileUtil.CollapsePath(&sz);
	AssertStringCase("C:\\", sz.Text(), false);
	sz.Kill();

	sz.Init("\\Documents\\and\\Settings\\..\\..\\Joe");
	cFileUtil.CollapsePath(&sz);
	AssertString("\\Documents\\Joe", sz.Text());
	sz.Kill();

	sz.Init("\\Documents\\and\\Settings\\..\\..\\Joe\\");
	cFileUtil.CollapsePath(&sz);
	AssertString("\\Documents\\Joe", sz.Text());
	sz.Kill();

	sz.Init(".\\.\\.\\.");
	cFileUtil.CollapsePath(&sz);
	AssertString("", sz.Text());
	sz.Kill();

	sz.Init(".\\.\\.\\");
	cFileUtil.CollapsePath(&sz);
	AssertString("", sz.Text());
	sz.Kill();

	sz.Init("c:\\..");
	cFileUtil.CollapsePath(&sz);
	AssertString("c:", sz.Text());
	sz.Kill();

	sz.Init("c:\\..\\..");
	cFileUtil.CollapsePath(&sz);
	AssertString("c:", sz.Text());
	sz.Kill();

	sz.Init("\\..\\..");
	cFileUtil.CollapsePath(&sz);
	AssertString("", sz.Text());
	sz.Kill();
}




//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilFindExtension(void)
{
	CFileUtil	cFileUtil;
	int			iIndex;

	iIndex = cFileUtil.FindExtension("/mnt/world/hello.txt");
	AssertInt(16, iIndex);

	iIndex = cFileUtil.FindExtension(".");
	AssertInt(0, iIndex);

	iIndex = cFileUtil.FindExtension("We.Are.The.Champions");
	AssertInt(10, iIndex);

	iIndex = cFileUtil.FindExtension("c:\\In\\The\\Age");
	AssertInt(-1, iIndex);

	iIndex = cFileUtil.FindExtension(NULL);
	AssertInt(-1, iIndex);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilRemoveExtension(void)
{
	CChars		szFilename;
	CFileUtil	cFileUtil;

	szFilename.Init("/mnt/world/hello.txt");
	cFileUtil.RemoveExtension(&szFilename);
	AssertString("/mnt/world/hello", szFilename.Text());

	cFileUtil.RemoveExtension(&szFilename);
	AssertString("/mnt/world/hello", szFilename.Text());
	szFilename.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilMakeNameFromDirectory(void)
{
	CFileUtil	cFileUtil;
	CChars		szName;
	CChars		szDirectory;
	CChars		szFilename;

	szDirectory.Init("c:" _FS_ "Some" _FS_ "Directory" _FS_ "Or" _FS_ "Other" _FS_);
	szFilename.Init("c:" _FS_ "Some" _FS_ "Directory" _FS_ "Or" _FS_ "Other" _FS_ "More" _FS_ "Dir" _FS_ "Filename.txt");
	cFileUtil.MakeNameFromDirectory(&szName, &szFilename, &szDirectory);

	AssertString("More/Dir/Filename.txt", szName.Text());
	szName.Kill();

	cFileUtil.MakeNameFromDirectory(&szName, &szDirectory, &szDirectory);

	AssertString("", szName.Text());
	szName.Kill();

	szDirectory.Kill();
	szFilename.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilMakeDirectory(void)
{
	CFileUtil		cFileUtil;
	CChars			szDirectory;
	CChars			szFilename;
	CArrayChars		aszFiles;
	CChars			szParentDirectory;
	CChars			szCurrentDirectory;
	bool			bResult;

	cFileUtil.RemoveDir("file_util");

	szParentDirectory.Init("file_util" _FS_ "directory" _FS_ "make" _FS_ "test");
	szDirectory.Init(szParentDirectory);
	szDirectory.Append(_FS_);
	szDirectory.Append("GABBA");
	szFilename.Init(szDirectory);
	szFilename.Append(_FS_);
	szFilename.Append("Filename.txt");

	bResult = cFileUtil.Touch(szFilename.Text());
	AssertFalse(bResult);

	bResult = cFileUtil.TouchDir(szDirectory.Text(), false);
	AssertTrue(bResult);

	szCurrentDirectory.Init();
	cFileUtil.CurrentDirectory(&szCurrentDirectory);
	szCurrentDirectory.Append(_FS_);
	szCurrentDirectory.Append(szDirectory);

	aszFiles.Init();
	cFileUtil.FindAllDirectories(szParentDirectory.Text(), &aszFiles, false);
	AssertInt(1, aszFiles.NumElements());
	AssertString(szCurrentDirectory.Text(), aszFiles.GetText(0));
	aszFiles.Kill();

	bResult = cFileUtil.Touch(szFilename.Text());
	AssertTrue(bResult);

	szCurrentDirectory.Kill();
	szParentDirectory.Kill();
	szDirectory.Kill();
	szFilename.Kill();

	cFileUtil.RemoveDir("file_util");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilRemoveLastFromPath(void)
{
	CFileUtil	cFileUtil;
	CChars		szFilename;

	szFilename.Init("home\\directory");
	cFileUtil.RemoveLastFromPath(&szFilename);
	AssertString("home", szFilename.Text());
	szFilename.Kill();

	szFilename.Init("\\directory");
	cFileUtil.RemoveLastFromPath(&szFilename);
	AssertString("\\", szFilename.Text());
	szFilename.Kill();

	szFilename.Init("\\home\\directory");
	cFileUtil.RemoveLastFromPath(&szFilename);
	AssertString("\\home", szFilename.Text());
	szFilename.Kill();

	szFilename.Init("C:\\directory");
	cFileUtil.RemoveLastFromPath(&szFilename);
	AssertString("C:\\", szFilename.Text());
	szFilename.Kill();

	szFilename.Init("C:\\home\\directory");
	cFileUtil.RemoveLastFromPath(&szFilename);
	AssertString("C:\\home", szFilename.Text());
	szFilename.Kill();

	szFilename.Init("directory");
	cFileUtil.RemoveLastFromPath(&szFilename);
	AssertString("", szFilename.Text());
	szFilename.Kill();

	szFilename.Init("");
	cFileUtil.RemoveLastFromPath(&szFilename);
	AssertString("", szFilename.Text());
	szFilename.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilTouchDirectory(void)
{
	CFileUtil		cFileUtil;
	CChars			szDirectory;
	CChars			szFilename;

	cFileUtil.RemoveDir("file_util");

	szDirectory.Init("file_util" _FS_ "directory" _FS_ "make" _FS_ "test");
	cFileUtil.FullPath(&szDirectory);
	szFilename.Init(szDirectory);
	cFileUtil.AppendToPath(&szFilename, "Warthog.PIG");
	AssertTrue(cFileUtil.TouchDir(szFilename.Text(), true));
	AssertTrue(cFileUtil.Touch(szFilename.Text()));

	szDirectory.Kill();
	szFilename.Kill();

	cFileUtil.RemoveDir("file_util");

	AssertFalse(cFileUtil.TouchDir("C:\\Warthog.PIG", true));
	AssertFalse(cFileUtil.TouchDir("\\Warthog.PIG", true));

	szDirectory.Init();
	cFileUtil.CurrentDirectory(&szDirectory);
	szDirectory.Append("War-pig.hog");
	AssertFalse(cFileUtil.TouchDir(szDirectory.Text(), true));
	szDirectory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilTouchDirectoryOnlyFilename(void)
{
	CFileUtil		cFileUtil;
	CChars			szDirectory;

	szDirectory.Init("War-pig.hog");
	AssertFalse(cFileUtil.TouchDir(szDirectory.Text(), true));
	szDirectory.Kill();

	szDirectory.Init("C:\\War-pig.hog");
	AssertFalse(cFileUtil.TouchDir(szDirectory.Text(), true));
	szDirectory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilPrependToPath(void)
{
	CFileUtil		cFileUtil;
	CChars			szPathName;

	szPathName.Init("C:\\Games\\R\\Us\\");
	cFileUtil.PrependToPath(&szPathName, "Extraordinary");
	AssertString("C:\\Extraordinary\\Games\\R\\Us\\", szPathName.Text());
	szPathName.Kill();

	szPathName.Init("Games\\R\\Us\\");
	cFileUtil.PrependToPath(&szPathName, "Extraordinary");
	AssertString("Extraordinary\\Games\\R\\Us\\", szPathName.Text());
	szPathName.Kill();

	szPathName.Init("\\Games\\R\\Us\\");
	cFileUtil.PrependToPath(&szPathName, "Extraordinary");
	AssertString("\\Extraordinary\\Games\\R\\Us\\", szPathName.Text());
	szPathName.Kill();

	szPathName.Init("Games");
	cFileUtil.PrependToPath(&szPathName, "Extraordinary");
	AssertString("Extraordinary\\Games", szPathName.Text());
	szPathName.Kill();

	szPathName.Init("C:\\");
	cFileUtil.PrependToPath(&szPathName, "Extraordinary");
	AssertString("C:\\Extraordinary\\", szPathName.Text());
	szPathName.Kill();

	szPathName.Init("\\");
	cFileUtil.PrependToPath(&szPathName, "");
	AssertString("\\", szPathName.Text());
	szPathName.Kill();

	szPathName.Init("");
	cFileUtil.PrependToPath(&szPathName, "Giana");
	AssertString("Giana\\", szPathName.Text());
	szPathName.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilRootDirectory(void)
{
	CFileUtil		cFileUtil;
	AssertTrue(cFileUtil.IsRootDirectory("C:\\"));
	AssertFalse(cFileUtil.IsRootDirectory("C:\\A"));
	AssertTrue(cFileUtil.IsRootDirectory("\\"));
	AssertFalse(cFileUtil.IsRootDirectory("\\A"));
	AssertFalse(cFileUtil.IsRootDirectory("C:\\A\\"));
	AssertFalse(cFileUtil.IsRootDirectory("\\A\\"));
	AssertFalse(cFileUtil.IsRootDirectory("A\\"));

	AssertFalse(cFileUtil.IsRootDirectory(""));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtil(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestFileUtilRemoveExtension();
	TestFileUtilFindExtension();
	TestFileUtilNaming();
	TestFileUtilMisc();
	TestFileUtilMakeNameFromDirectory();
	TestFileUtilMakeDirectory();
	TestFileUtilRemoveLastFromPath();
	TestFileUtilTouchDirectory();
	TestFileUtilTouchDirectoryOnlyFilename();
	TestFileUtilPrependToPath();
	TestFileUtilRootDirectory();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

