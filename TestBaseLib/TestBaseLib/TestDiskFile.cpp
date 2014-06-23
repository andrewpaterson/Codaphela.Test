#include "BaseLib/DiskFile.h"
#include "BaseLib/FileUtil.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDiskFileEndOfFile(void)
{
	CDiskFile	cDiskFile;
	CFileUtil	cFileUtil;
	char		szHello[] = "Hello";
	BOOL		bResult;
	int			iResult;
	char		szResult[100];

	cFileUtil.Delete("Test.txt");

	cDiskFile.Init("Test.txt");
	bResult = cDiskFile.Open(EFM_Write_Create);
	AssertTrue(bResult);
	iResult = (int)cDiskFile.Write(szHello, (filePos)strlen(szHello)+1, 1);
	AssertInt(1, iResult);
	bResult = cDiskFile.Eof();
	AssertFalse(bResult);
	bResult = cDiskFile.Close();
	AssertTrue(bResult);
	cDiskFile.Kill();

	bResult = cFileUtil.Exists("Test.txt");
	AssertTrue(bResult);

	cDiskFile.Init("Test.txt");
	bResult = cDiskFile.Open(EFM_Read);
	AssertTrue(bResult);
	iResult = (int)cDiskFile.Read(szResult, (filePos)strlen(szHello)+1, 1);
	AssertInt(1, iResult);
	AssertString(szHello, szResult);
	bResult = cDiskFile.Eof();
	AssertFalse(bResult);

	cDiskFile.Seek(2, EFSO_SET);
	iResult = (int)cDiskFile.Read(szResult, (filePos)strlen(szHello)+1-2, 1);
	AssertInt(1, iResult);
	AssertString(&szHello[2], szResult);
	bResult = cDiskFile.Eof();
	AssertFalse(bResult);

	cDiskFile.Seek(2, EFSO_SET);
	iResult = (int)cDiskFile.Read(szResult, 1, (filePos)strlen(szHello)+1);
	AssertInt((int)strlen(szHello)+1-2, iResult);
	AssertString(&szHello[2], szResult);
	bResult = cDiskFile.Eof();
	AssertTrue(bResult);

	bResult = cDiskFile.Close();
	AssertTrue(bResult);
	cDiskFile.Kill();

	cFileUtil.Delete("Test.txt");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDiskFile(void)
{
	BeginTests();

	TestDiskFileEndOfFile();

	TestStatistics();
}

