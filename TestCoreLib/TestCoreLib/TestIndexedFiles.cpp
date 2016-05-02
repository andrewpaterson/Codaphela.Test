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
	CChars					szName;
	CChars					szRewrite;

	cFileUtil.RemoveDirs(szDirectorty, szRewriteDirectorty, NULL);

	szName.Init();
	szRewrite.Init();

	cFileUtil.AppendToPath(&szName, szDirectorty);
	cFileUtil.AppendToPath(&szRewrite, szRewriteDirectorty);

	cController.Init(szName.Text(), szRewrite.Text());
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
	CChars					szName;
	CChars					szRewrite;


	cFileUtil.RemoveDirs(szDirectorty, szRewriteDirectorty, NULL);

	szName.Init();
	szRewrite.Init();

	cFileUtil.AppendToPath(&szName, szDirectorty);
	cFileUtil.AppendToPath(&szRewrite, szRewriteDirectorty);

	cController.Init(szName.Text(), szRewrite.Text());
	cIndexedFiles.Init(&cController, "DAT", "Files.IDX", "_Files.IDX");

	cIndexedFiles.Kill();
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

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

