#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NaiveFile.h"
#include "CoreLib/IndexedFiles.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertIndexedFile(char* szDirectory, char* szFileName, void* pvExpectedData, int iExpectedLen)
{
	CChars		szTemp;
	CFileUtil	cFileUtil;

	szTemp.Init(szDirectory);
	cFileUtil.AppendToPath(&szTemp, szFileName);
	AssertTrue(cFileUtil.Exists(szTemp.Text()));
	AssertInt(0, CompareFileToMemory(szTemp.Text(), pvExpectedData, iExpectedLen));
	szTemp.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesWorkingDirectory(void)
{
	CIndexedFiles			cIndexedFiles;
	CFileUtil				cFileUtil;
	CDurableFileController	cController;
	char					szDirectorty[] = "Output" _FS_ "Files1";
	char					szRewriteDirectorty[] = "Output" _FS_ "_Files1";

	cFileUtil.RemoveDirs(szDirectorty, szRewriteDirectorty, NULL);

	cController.Init(szDirectorty, szRewriteDirectorty);
	cController.Begin();
	cIndexedFiles.Init(&cController, "DAT", "Files.IDX", "_Files.IDX");
	AssertTrue(cIndexedFiles.ReadIndexedFileDescriptors());
	AssertFalse(cFileUtil.Exists(szDirectorty));
	AssertFalse(cFileUtil.Exists(szRewriteDirectorty));

	cController.End();
	AssertTrue(cFileUtil.Exists(szDirectorty));
	AssertTrue(cFileUtil.Exists(szRewriteDirectorty));

	cIndexedFiles.Kill();
	cController.Kill();

	cFileUtil.RemoveDirs(szDirectorty, szRewriteDirectorty, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesInitAndKillWihtoutOpen(void)
{
	CIndexedFiles			cIndexedFiles;
	CFileUtil				cFileUtil;
	CDurableFileController	cController;
	char					szDirectorty[] = "Output" _FS_ "Files2";
	char					szRewriteDirectorty[] = "Output" _FS_ "_Files2";
	char					cZero = 0;

	cFileUtil.RemoveDirs(szDirectorty, szRewriteDirectorty, NULL);

	cController.Init(szDirectorty, szRewriteDirectorty);
	cIndexedFiles.Init(&cController, "DAT", "Files.IDX", "_Files.IDX");
	AssertFalse(cIndexedFiles.ReadIndexedFileDescriptors());

	AssertFalse(cFileUtil.Exists(szDirectorty));
	AssertFalse(cFileUtil.Exists(szRewriteDirectorty));

	cIndexedFiles.Kill();
	cController.Kill();

	cFileUtil.RemoveDirs(szDirectorty, szRewriteDirectorty, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesWrite(void)
{
	CIndexedFiles			cIndexedFiles;
	CFileUtil				cFileUtil;
	CDurableFileController	cController;
	char					szDirectorty[] = "Output" _FS_ "Files3";
	char					szRewriteDirectorty[] = "Output" _FS_ "_Files3";
	CIndexedDataDescriptor	cDescriptor1;
	CIndexedDataDescriptor	cDescriptor2;
	char					szData1[] = "For the single case of just one bed of a certain type, you use bed directly with a text.";
	char					szData2[] = "Text's trusty Rights and Export Coordinator, Khadija Caffoor, went to the London Book Fair in March.";
	int						iLen1;
	int						iLen2;


	iLen1 = strlen(szData1);
	iLen2 = strlen(szData2);
	AssertInt(88, iLen1);
	AssertInt(100, iLen2);

	cFileUtil.RemoveDirs(szDirectorty, szRewriteDirectorty, NULL);
	AssertFalse(cFileUtil.Exists(szDirectorty));
	AssertFalse(cFileUtil.Exists(szRewriteDirectorty));

	cController.Init(szDirectorty, szRewriteDirectorty);
	cController.Begin();
	cIndexedFiles.Init(&cController, "DAT", "Files.IDX", "_Files.IDX");
	cController.End();

	AssertTrue(cController.Begin());
	cDescriptor1.Init(3LL, iLen1);
	AssertTrue(cIndexedFiles.Write(&cDescriptor1, szData1));

	cDescriptor2.Init(5LL, iLen2);
	AssertTrue(cIndexedFiles.Write(&cDescriptor2, szData2));
	AssertTrue(cController.End());

	AssertTrue(cFileUtil.Exists(szDirectorty));
	AssertTrue(cFileUtil.Exists(szRewriteDirectorty));

	AssertIndexedFile(szDirectorty, "88_0.DAT", szData1, iLen1);
	AssertIndexedFile(szDirectorty, "100_0.DAT", szData2, iLen2);
	AssertIndexedFile(szRewriteDirectorty, "_88_0.DAT", szData1, iLen1);
	AssertIndexedFile(szRewriteDirectorty, "_100_0.DAT", szData2, iLen2);

	cController.Begin();
	cIndexedFiles.Kill();
	cController.End();
	cController.Kill();

	cFileUtil.RemoveDirs(szDirectorty, szRewriteDirectorty, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFiles(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	BeginTests();

	TestIndexedFilesInitAndKillWihtoutOpen();
	TestIndexedFilesWorkingDirectory();
	TestIndexedFilesWrite();

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

