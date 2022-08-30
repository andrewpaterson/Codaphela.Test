#include "BaseLib/FastFunctions.h"
#include "BaseLib/TextFile.h"
#include "CoreLib/IndexedFile.h"
#include "TestLib/Assert.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFileWrite(void)
{
	CIndexedFile				cIndexedFile;
	CDurableFileController		cController;
	CFileUtil					cFileUtil;
	CChars						szWrite;
	CChars						szRewrite;
	BOOL						bResult;
	char						sz1[] = "12345678";
	char						sz2[] = "ABCDEFGH";
	char						sz3[] = "iopfghjk";
	filePos						iFileIndex;
	CTextFile					cTextFile;
	char						szTemp[16];
	char						szDirectory[] = "Output" _FS_ "IndexedFile";
	char						szRewriteDirectory[] = "Output" _FS_ "_IndexedFile";

	bResult = cFileUtil.MakeDirs(TRUE, szDirectory, szRewriteDirectory, NULL);
	AssertTrue(bResult);

	szWrite.Init("Output" _FS_ "IndexedFile" _FS_ "File.DAT");
	szRewrite.Init("Output" _FS_ "_IndexedFile" _FS_ "_File.DAT");

	cController.Init(szDirectory, szRewriteDirectory);
	cController.Begin();

	cIndexedFile.Init(&cController, 0, "File.DAT", "_File.DAT", 9, 0);

	iFileIndex = cIndexedFile.Write(sz3);
	AssertLongLongInt(0, iFileIndex);
	AssertLongLongInt(9, cIndexedFile.GetFileSize());

	iFileIndex = cIndexedFile.Write(sz2);
	AssertLongLongInt(1, iFileIndex);
	AssertLongLongInt(18, cIndexedFile.GetFileSize());

	bResult = cIndexedFile.Write(0, sz1);
	AssertTrue(bResult);
	AssertLongLongInt(18, cIndexedFile.GetFileSize());

	bResult = cController.End();
	AssertTrue(bResult);
	cIndexedFile.Kill();

	cController.Kill();

	cTextFile.Init();
	cTextFile.Read(szWrite.Text());
	AssertString(sz1, cTextFile.mcText.Text(0));
	AssertString(sz2, cTextFile.mcText.Text(9));
	cTextFile.Kill();

	cTextFile.Init();
	cTextFile.Read(szRewrite.Text());
	AssertString(sz1, cTextFile.mcText.Text(0));
	AssertString(sz2, cTextFile.mcText.Text(9));
	cTextFile.Kill();


	cController.Init(szDirectory, szRewriteDirectory);
	cController.Begin();

	cIndexedFile.Init(&cController, 0, "File.DAT", "_File.DAT", 9, 0);

	bResult = cIndexedFile.Read(1, szTemp);
	AssertTrue(bResult);
	AssertString(sz2, szTemp);

	bResult = cIndexedFile.Read(0, szTemp);
	AssertTrue(bResult);
	AssertString(sz1, szTemp);

	bResult = cIndexedFile.Read(1, szTemp);
	AssertTrue(bResult);
	AssertString(sz2, szTemp);
	AssertInt(18, (int)cIndexedFile.GetFileSize());

	bResult = cController.End();
	AssertTrue(bResult);
	cIndexedFile.Kill();

	cController.Kill();

	szWrite.Kill();
	szRewrite.Kill();

	bResult = cFileUtil.RemoveDirs(szDirectory, szRewriteDirectory, NULL);
	AssertTrue(bResult);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFile(void)
{
	BeginTests();

	TestIndexedFileWrite();

	TestStatistics();
}

