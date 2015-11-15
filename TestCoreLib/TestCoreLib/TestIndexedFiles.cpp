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
	CChars					szName;
	CChars					szRewrite;


	cFileUtil.RemoveDir(szDirectorty);
	szName.Init();
	szRewrite.Init();

	cFileUtil.AppendToPath(&szName, szDirectorty);
	cFileUtil.AppendToPath(&szRewrite, szDirectorty);

	cController.Init(szName.Text(), szRewrite.Text(), TRUE);
	cIndexedFiles.Init(&cController, "DAT");
	cIndexedFiles.Open();

	cIndexedFiles.Close();
	cIndexedFiles.Kill();
	cController.Kill();

	cFileUtil.RemoveDir(szDirectorty);
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
	CChars					szName;
	CChars					szRewrite;


	cFileUtil.RemoveDir(szDirectorty);
	szName.Init();
	szRewrite.Init();

	cFileUtil.AppendToPath(&szName, szDirectorty);
	cFileUtil.AppendToPath(&szRewrite, szDirectorty);

	cController.Init(szName.Text(), szRewrite.Text(), TRUE);
	cIndexedFiles.Init(&cController, "DAT");

	cIndexedFiles.Kill();
	cController.Kill();

	cFileUtil.RemoveDir(szDirectorty);
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

