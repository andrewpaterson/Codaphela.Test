#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "CoreLib/TypeConverter.h"
#include "CoreLib/IndexedFiles.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesWorkingDirectory(void)
{
	CIndexedFiles			cIndexedFiles;
	CFileUtil				cFileUtil;
	CDurableFileController	cController;
	char					szDirectorty[] = "Files1";
	char					szRewriteDirectorty[] = "_Files1";

	cFileUtil.RemoveDirs(szDirectorty, szRewriteDirectorty, NULL);

	cController.Init(szDirectorty, szRewriteDirectorty);
	cIndexedFiles.Init(&cController, "DAT", "Files.IDX", "_Files.IDX");
	cController.Begin();

	cController.End();
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
	char					szDirectorty[] = "Files2";
	char					szRewriteDirectorty[] = "_Files2";


	cFileUtil.RemoveDirs(szDirectorty, szRewriteDirectorty, NULL);

	cController.Init(szDirectorty, szRewriteDirectorty);
	cIndexedFiles.Init(&cController, "DAT", "Files.IDX", "_Files.IDX");

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
	char					szDirectorty[] = "Files3";
	char					szRewriteDirectorty[] = "_Files3";
	CIndexedDataDescriptor	cDescriptor1;
	CIndexedDataDescriptor	cDescriptor2;
	char					szData1[] = "For the single case of just one bed of a certain type, you use bed directly with a text.";
	char					szData2[] = "Text's trusty Rights and Export Coordinator, Khadija Caffoor, went to the London Book Fair in March.";
	int						iLen1;
	int						iLen2;

	iLen1 = strlen(szData1);
	iLen2 = strlen(szData2);

	cFileUtil.RemoveDirs(szDirectorty, szRewriteDirectorty, NULL);

	cController.Init(szDirectorty, szRewriteDirectorty);
	cController.Begin();
	cIndexedFiles.Init(&cController, "DAT", "Files.IDX", "_Files.IDX");
	cController.End();

	cController.Begin();
	cDescriptor1.Init(3LL, iLen1);
	cIndexedFiles.Write(&cDescriptor1, szData1);

	cDescriptor2.Init(5LL, iLen2);
	cIndexedFiles.Write(&cDescriptor2, szData2);
	cController.End();

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

