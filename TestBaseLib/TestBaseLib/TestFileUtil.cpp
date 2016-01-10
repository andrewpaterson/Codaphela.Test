#include "BaseLib/FileUtil.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilMisc(void)
{
	CFileUtil	cFileUtil;
	BOOL		bResult;
	CChars		szPath;

	szPath.Init("TestFileUtil");
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
	szExpected.Init("C:\\GameEngine\\Test\\TestBaseLib\\TestBaseLib");
	szExpected.LowerCase();
	AssertString(szExpected.Text(), sz.Text());
	szExpected.Kill();
	sz.Kill();

	sz.Init("c:\\Documents and Settings\\Joe\\..\\..\\");
	cFileUtil.CollapsePath(&sz);
	AssertStringCase("C:\\", sz.Text(), FALSE);
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
	CChars		szFileName;
	CFileUtil	cFileUtil;

	szFileName.Init("/mnt/world/hello.txt");
	cFileUtil.RemoveExtension(&szFileName);
	AssertString("/mnt/world/hello", szFileName.Text());

	cFileUtil.RemoveExtension(&szFileName);
	AssertString("/mnt/world/hello", szFileName.Text());
	szFileName.Kill();
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
	CChars		szFileName;

	szDirectory.Init("c:"_FS_"Some"_FS_"Directory"_FS_"Or"_FS_"Other"_FS_);
	szFileName.Init("c:"_FS_"Some"_FS_"Directory"_FS_"Or"_FS_"Other"_FS_"More"_FS_"Dir"_FS_"FileName.txt");
	cFileUtil.MakeNameFromDirectory(&szName, &szFileName, &szDirectory);

	AssertString("More/Dir/FileName.txt", szName.Text());
	szName.Kill();

	cFileUtil.MakeNameFromDirectory(&szName, &szDirectory, &szDirectory);

	AssertString("", szName.Text());
	szName.Kill();

	szDirectory.Kill();
	szFileName.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilMakeDirectory(void)
{
	CFileUtil		cFileUtil;
	CChars			szDirectory;
	CChars			szFileName;
	CArrayString	aszFiles;
	CChars			szParentDirectory;
	CChars			szCurrentDirectory;
	BOOL			bResult;

	cFileUtil.RemoveDir("file_util");

	szParentDirectory.Init("file_util"_FS_"directory"_FS_"make"_FS_"test");
	szDirectory.Init(szParentDirectory);
	szDirectory.Append(_FS_);
	szDirectory.Append("GABBA");
	szFileName.Init(szDirectory);
	szFileName.Append(_FS_);
	szFileName.Append("FileName.txt");

	bResult = cFileUtil.Touch(szFileName.Text());
	AssertFalse(bResult);

	cFileUtil.MakeDir(szDirectory.Text());

	szCurrentDirectory.Init();
	cFileUtil.CurrentDirectory(&szCurrentDirectory);
	szCurrentDirectory.Append(_FS_);
	szCurrentDirectory.Append(szDirectory);

	aszFiles.Init(1);
	cFileUtil.FindAllDirectories(szParentDirectory.Text(), &aszFiles, FALSE);
	AssertInt(1, aszFiles.NumElements());
	AssertString(szCurrentDirectory.Text(), aszFiles.GetText(0));

	bResult = cFileUtil.Touch(szFileName.Text());
	AssertTrue(bResult);

	szParentDirectory.Kill();
	szDirectory.Kill();
	szFileName.Kill();

	cFileUtil.RemoveDir("file_util");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilRemoveLastFromPath(void)
{
	CFileUtil	cFileUtil;
	CChars		szFileName;

	szFileName.Init("home\\directory");
	cFileUtil.RemoveLastFromPath(&szFileName);
	AssertString("home", szFileName.Text());
	szFileName.Kill();

	szFileName.Init("\\directory");
	cFileUtil.RemoveLastFromPath(&szFileName);
	AssertString("\\", szFileName.Text());
	szFileName.Kill();

	szFileName.Init("\\home\\directory");
	cFileUtil.RemoveLastFromPath(&szFileName);
	AssertString("\\home", szFileName.Text());
	szFileName.Kill();

	szFileName.Init("C:\\directory");
	cFileUtil.RemoveLastFromPath(&szFileName);
	AssertString("C:\\", szFileName.Text());
	szFileName.Kill();

	szFileName.Init("C:\\home\\directory");
	cFileUtil.RemoveLastFromPath(&szFileName);
	AssertString("C:\\home", szFileName.Text());
	szFileName.Kill();

	szFileName.Init("directory");
	cFileUtil.RemoveLastFromPath(&szFileName);
	AssertString("", szFileName.Text());
	szFileName.Kill();

	szFileName.Init("");
	cFileUtil.RemoveLastFromPath(&szFileName);
	AssertString("", szFileName.Text());
	szFileName.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtilTouchDirectory(void)
{
	CFileUtil		cFileUtil;
	CChars			szDirectory;
	CChars			szFileName;

	cFileUtil.RemoveDir("file_util");

	szDirectory.Init("file_util"_FS_"directory"_FS_"make"_FS_"test");
	cFileUtil.FullPath(&szDirectory);
	szFileName.Init(szDirectory);
	cFileUtil.AppendToPath(&szFileName, "Warthog.PIG");
	AssertTrue(cFileUtil.TouchDir(szFileName.Text()));
	AssertTrue(cFileUtil.Touch(szFileName.Text()));

	szDirectory.Kill();
	szFileName.Kill();

	cFileUtil.RemoveDir("file_util");

	AssertFalse(cFileUtil.TouchDir("C:\\Warthog.PIG"));
	AssertFalse(cFileUtil.TouchDir("\\Warthog.PIG"));

	szDirectory.Init();
	cFileUtil.CurrentDirectory(&szDirectory);
	szDirectory.Append("War-pig.hog");
	AssertFalse(cFileUtil.TouchDir(szDirectory.Text()));
	szDirectory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileUtil(void)
{
	BeginTests();

	TestFileUtilRemoveExtension();
	TestFileUtilFindExtension();
	TestFileUtilNaming();
	TestFileUtilMisc();
	TestFileUtilMakeNameFromDirectory();
	TestFileUtilMakeDirectory();
	TestFileUtilRemoveLastFromPath();
	TestFileUtilTouchDirectory();

	TestStatistics();
}

