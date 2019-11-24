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
	CIndexedDataDescriptor	cDescriptor3;
	CIndexedDataDescriptor	cDescriptor4;
	char					szData1[] = "For the single case of just one bed of a certain type, you use bed directly with a text.";
	char					szData2[] = "Text's trusty Rights and Export Coordinator, Khadija Caffoor, went to the London Book Fair in March.";
	char					szData3[] = "Unpleasant nor diminution excellence apartments imprudence the met new.  Draw part them.";
	char					szData4[] = "Nor hence hoped he after her other known to defer his. For county sister seasonal better had waited.";
	int						iLen1;
	int						iLen2;
	int						iLen3;
	int						iLen4;
	CChars					szTemp;
	CFileDataIndex			cDataIndex;
	unsigned int			uiDataSize;
	char					szData[1024];

	iLen1 = strlen(szData1);
	iLen2 = strlen(szData2);
	AssertInt(88, iLen1);
	AssertInt(100, iLen2);

	cFileUtil.RemoveDirs(szDirectorty, szRewriteDirectorty, NULL);
	AssertFalse(cFileUtil.Exists(szDirectorty));
	AssertFalse(cFileUtil.Exists(szRewriteDirectorty));

	cController.Init(szDirectorty, szRewriteDirectorty);
	cIndexedFiles.Init(&cController, "DAT", "Files.IDX", "_Files.IDX");

	AssertTrue(cController.Begin());
	AssertTrue(cIndexedFiles.ReadIndexedFileDescriptors());
	AssertLongLongInt(0, cIndexedFiles.NumData());

	cDescriptor1.Init(iLen1);
	AssertFalse(cDescriptor1.HasFile());
	AssertTrue(cIndexedFiles.Write(&cDescriptor1, szData1));
	AssertTrue(cDescriptor1.HasFile());
	AssertInt(0, cDescriptor1.GetFileIndex());
	AssertLongLongInt(0, cDescriptor1.GetPositionInFile());
	AssertLongLongInt(1, cIndexedFiles.NumData());

	cDescriptor2.Init(iLen2);
	AssertTrue(cIndexedFiles.Write(&cDescriptor2, szData2));
	AssertInt(1, cDescriptor2.GetFileIndex());
	AssertLongLongInt(0, cDescriptor2.GetPositionInFile());
	AssertLongLongInt(2, cIndexedFiles.NumData());

	AssertTrue(cController.End());
	AssertLongLongInt(2, cIndexedFiles.NumData());

	AssertTrue(cFileUtil.Exists(szDirectorty));
	AssertTrue(cFileUtil.Exists(szRewriteDirectorty));

	AssertIndexedFile(szDirectorty, "88_0.DAT", szData1, iLen1);
	AssertIndexedFile(szDirectorty, "100_0.DAT", szData2, iLen2);
	AssertIndexedFile(szRewriteDirectorty, "_88_0.DAT", szData1, iLen1);
	AssertIndexedFile(szRewriteDirectorty, "_100_0.DAT", szData2, iLen2);

	cIndexedFiles.Kill();
	cController.Kill();


	iLen3 = strlen(szData3);
	iLen4 = strlen(szData4);
	AssertInt(88, iLen3);
	AssertInt(100, iLen4);

	cController.Init(szDirectorty, szRewriteDirectorty);
	cIndexedFiles.Init(&cController, "DAT", "Files.IDX", "_Files.IDX");

	AssertFalse(cIndexedFiles.ReadIndexedFileDescriptors());  //Controller not begun.

	AssertTrue(cController.Begin());
	AssertTrue(cIndexedFiles.ReadIndexedFileDescriptors());
	AssertFalse(cIndexedFiles.ReadIndexedFileDescriptors());  //Indices already read.
	AssertTrue(cController.End());
	AssertLongLongInt(2, cIndexedFiles.NumData());

	AssertInt(2, cIndexedFiles.NumFiles());
	AssertLongLongInt(1, cIndexedFiles.NumData(88));
	AssertLongLongInt(0, cIndexedFiles.NumData(89));
	AssertLongLongInt(1, cIndexedFiles.NumData(100));
	AssertLongLongInt(0, cIndexedFiles.NumData(101));

	AssertTrue(cController.Begin());
	cDescriptor3.Init(iLen3);
	AssertTrue(cIndexedFiles.Write(&cDescriptor3, szData3));
	AssertInt(0, cDescriptor3.GetFileIndex());
	AssertLongLongInt(1, cDescriptor3.GetPositionInFile());
	AssertLongLongInt(3, cIndexedFiles.NumData());

	cDescriptor4.Init(iLen4);
	AssertTrue(cIndexedFiles.Write(&cDescriptor4, szData4));
	AssertInt(1, cDescriptor4.GetFileIndex());
	AssertLongLongInt(1, cDescriptor4.GetPositionInFile());
	AssertLongLongInt(4, cIndexedFiles.NumData());

	AssertTrue(cController.End());

	szTemp.InitList(szData1, szData3, NULL);
	AssertIndexedFile(szDirectorty, "88_0.DAT", szTemp.Text(), szTemp.Length());
	AssertIndexedFile(szRewriteDirectorty, "_88_0.DAT", szTemp.Text(), szTemp.Length());
	szTemp.Kill();
	szTemp.InitList(szData2, szData4, NULL);
	AssertIndexedFile(szDirectorty, "100_0.DAT", szTemp.Text(), szTemp.Length());
	AssertIndexedFile(szRewriteDirectorty, "_100_0.DAT", szTemp.Text(), szTemp.Length());
	cIndexedFiles.Kill();
	cController.Kill();

	cController.Init(szDirectorty, szRewriteDirectorty);
	cIndexedFiles.Init(&cController, "DAT", "Files.IDX", "_Files.IDX");
	AssertTrue(cController.Begin());
	cIndexedFiles.ReadIndexedFileDescriptors();
	AssertTrue(cController.End());

	AssertInt(2, cIndexedFiles.NumFiles());
	AssertLongLongInt(2, cIndexedFiles.NumData(88));
	AssertLongLongInt(0, cIndexedFiles.NumData(89));
	AssertLongLongInt(2, cIndexedFiles.NumData(100));
	AssertLongLongInt(0, cIndexedFiles.NumData(101));

	cIndexedFiles.Kill();
	cController.Kill();


	cController.Init(szDirectorty, szRewriteDirectorty);
	cIndexedFiles.Init(&cController, "DAT", "Files.IDX", "_Files.IDX");
	AssertTrue(cController.Begin());
	AssertTrue(cIndexedFiles.ReadIndexedFileDescriptors());
	AssertTrue(cController.End());
	AssertLongLongInt(4, cIndexedFiles.NumData());

	cIndexedFiles.Kill();
	cController.Kill();

	cController.Init(szDirectorty, szRewriteDirectorty);
	cIndexedFiles.Init(&cController, "DAT", "Files.IDX", "_Files.IDX");
	cController.Begin();
	cIndexedFiles.ReadIndexedFileDescriptors();

	uiDataSize = cIndexedFiles.GetFileDataSize(0);
	AssertInt(88, uiDataSize);

	cDataIndex.Init(0, 0);
	memset(szData, 0, 1024);
	AssertTrue(cIndexedFiles.Read(&cDataIndex, szData));
	AssertString(szData1, szData);

	cDataIndex.Init(0, 1);
	memset(szData, 0, 1024);
	AssertTrue(cIndexedFiles.Read(&cDataIndex, szData));
	AssertString(szData3, szData);

	uiDataSize = cIndexedFiles.GetFileDataSize(1);
	AssertInt(100, uiDataSize);

	cDataIndex.Init(1, 0);
	memset(szData, 0, 1024);
	AssertTrue(cIndexedFiles.Read(&cDataIndex, szData));
	AssertString(szData2, szData);

	cDataIndex.Init(1, 1);
	memset(szData, 0, 1024);
	AssertTrue(cIndexedFiles.Read(&cDataIndex, szData));
	AssertString(szData4, szData);

	AssertTrue(cController.End());
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
	TestIndexedFilesWrite();

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

