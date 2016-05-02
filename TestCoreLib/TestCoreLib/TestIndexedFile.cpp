#include "BaseLib/FastFunctions.h"
#include "BaseLib/TextFile.h"
#include "CoreLib/IndexedFile.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFile(void)
{
	BeginTests();

	FastFunctionsInit();
	
	CIndexedFile				cIndexedFile;
	CDurableFileController		cDurableController;
	CFileUtil					cFileUtil;
	CChars						szWrite;
	CChars						szRewrite;
	BOOL						bResult;
	char						sz1[] = "12345678";
	char						sz2[] = "ABCDEFGH";
	char						sz3[] = "iopfghjk";
	filePos						iFilePos;
	CTextFile					cTextFile;
	char						szTemp[16];
	char						szDirectory[] = "IndexedFile";
	char						szRewriteDirectory[] = "_IndexedFile";

	bResult = cFileUtil.MakeDirs(TRUE, szDirectory, szRewriteDirectory, NULL);
	AssertTrue(bResult);

	szWrite.Init(szDirectory);
	szWrite.Append(FILE_SEPARATOR[0]);
	szWrite.Append("File.DAT");
	szRewrite.Init(szRewriteDirectory);
	szRewrite.Append(FILE_SEPARATOR[0]);
	szRewrite.Append("_File.DAT");

	cDurableController.Init(szDirectory, szRewriteDirectory);
	cDurableController.Begin();

	cIndexedFile.Init(&cDurableController, 0, szWrite.Text(), szRewrite.Text(), 9, 0);

	iFilePos = cIndexedFile.Write(sz3);
	AssertLongLongInt(0, iFilePos / cIndexedFile.miDataSize);

	iFilePos = cIndexedFile.Write(sz2);
	AssertLongLongInt(1, iFilePos / cIndexedFile.miDataSize);

	bResult = cIndexedFile.Write(0, sz1);
	AssertTrue(bResult);
	AssertLongLongInt(18, cIndexedFile.mcFile.Size());

	bResult = cDurableController.End();
	AssertTrue(bResult);
	cIndexedFile.Kill();

	cDurableController.Kill();

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


	cDurableController.Init(szDirectory, szRewriteDirectory);
	cDurableController.Begin();

	cIndexedFile.Init(&cDurableController, 0, szWrite.Text(), szRewrite.Text(), 9, 0);

	bResult = cIndexedFile.Read(1, szTemp);
	AssertTrue(bResult);
	AssertString(sz2, szTemp);

	bResult = cIndexedFile.Read(0, szTemp);
	AssertTrue(bResult);
	AssertString(sz1, szTemp);

	bResult = cIndexedFile.Read(1, szTemp);
	AssertTrue(bResult);
	AssertString(sz2, szTemp);
	AssertInt(18, (int)cIndexedFile.mcFile.Size());

	bResult = cDurableController.End();
	AssertTrue(bResult);
	cIndexedFile.Kill();

	cDurableController.Kill();

	szWrite.Kill();
	szRewrite.Kill();

	bResult = cFileUtil.RemoveDirs(szDirectory, szRewriteDirectory, NULL);
	AssertTrue(bResult);

	FastFunctionsKill();

	TestStatistics();
}
