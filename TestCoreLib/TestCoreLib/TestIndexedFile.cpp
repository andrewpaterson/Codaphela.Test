#include "BaseLib/FastFunctions.h"
#include "BaseLib/TextFile.h"
#include "CoreLib/IndexedFile.h"
#include "TestLib/Assert.h"
#include "TestIndexedFile.h"


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
	int							iIndex;
	CTextFile					cTextFile;
	char						szTemp[16];

	bResult = cFileUtil.RemoveDir("IndexedFile");
	AssertTrue(bResult);

	bResult = cFileUtil.MakeDir("IndexedFile");
	AssertTrue(bResult);

	szWrite.Init("IndexedFile");
	szWrite.Append(FILE_SEPARATOR[0]);
	szWrite.Append("File.DAT");
	szRewrite.Init("IndexedFile");
	szRewrite.Append(FILE_SEPARATOR[0]);
	szRewrite.Append("_File.DAT");

	cDurableController.Init("IndexedFile", TRUE);
	cDurableController.mcDurableSet.Begin();

	cIndexedFile.Init(&cDurableController, 0, szWrite.Text(), szRewrite.Text(), 9, 0);

	iIndex = cIndexedFile.Write(sz3);
	AssertInt(0, iIndex);

	iIndex = cIndexedFile.Write(sz2);
	AssertInt(1, iIndex);

	bResult = cIndexedFile.Write(0, sz1);
	AssertTrue(bResult);
	AssertInt(18, (int)cIndexedFile.mcFile.Size());

	bResult = cDurableController.mcDurableSet.End();
	AssertTrue(bResult);
	bResult = cIndexedFile.Kill();
	AssertTrue(bResult);

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


	cDurableController.Init("IndexedFile", TRUE);
	cDurableController.mcDurableSet.Begin();

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

	bResult = cDurableController.mcDurableSet.End();
	AssertTrue(bResult);
	bResult = cIndexedFile.Kill();
	AssertTrue(bResult);

	cDurableController.Kill();

	szWrite.Kill();
	szRewrite.Kill();

	bResult = cFileUtil.RemoveDir("IndexedFile");
	AssertTrue(bResult);

	FastFunctionsKill();

	TestStatistics();
}
