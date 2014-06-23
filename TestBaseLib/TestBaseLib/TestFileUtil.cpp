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
void TestFindExtension(void)
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
void TestRemoveExtension(void)
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
void TestMakeNameFromDirectory(void)
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
void TestFileUtil(void)
{
	BeginTests();

	TestRemoveExtension();
	TestFindExtension();
	TestFileUtilNaming();
	TestFileUtilMisc();
	TestMakeNameFromDirectory();

	TestStatistics();
}

