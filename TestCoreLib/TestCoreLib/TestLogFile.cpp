#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/TextFile.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/Logger.h"
#include "CoreLib/LogFile.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogFileOpen(void)
{
	CLogFile*		pcLogFile;
	CMemoryFile*	pcMemoryFile;
	CFileBasic		cFile;
	SLogConfig		sLogConfig;

	pcMemoryFile = MemoryFile();
	pcLogFile = LogFile(pcMemoryFile);
	AssertNotNull(pcLogFile);

	cFile.Init(pcLogFile);

	sLogConfig = gcLogger.SetSilent();
	AssertFalse(cFile.Open(EFM_ReadWrite_Create));
	gcLogger.SetConfig(&sLogConfig);

	AssertTrue(pcLogFile->Begin());

	AssertTrue(cFile.Open(EFM_ReadWrite_Create));

	AssertTrue(cFile.Close());

	pcLogFile->End();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogFileRead(void)
{
	CLogFile*		pcLogFile;
	CMemoryFile*	pcMemoryFile;
	CFileBasic		cFile;
	BOOL			bResult;
	int				iLength;
	char			sz[200];
	filePos			iRead;
	SLogConfig		sLogConfig;

	pcMemoryFile = MemoryFile();
	cFile.Init(pcMemoryFile);
	cFile.Open(EFM_Write_Create);
	cFile.WriteString("The suspense is killing me!");
	cFile.Close();

	pcLogFile = LogFile(pcMemoryFile);
	cFile.Init(pcLogFile);

	sLogConfig = gcLogger.SetSilent();;
	bResult = cFile.Open(EFM_Read);
	AssertFalse(bResult);
	gcLogger.SetConfig(&sLogConfig);

	AssertTrue(pcLogFile->Begin());
	AssertTrue(cFile.Open(EFM_Read));

	bResult = cFile.ReadStringLength(&iLength);
	AssertTrue(bResult);
	AssertInt(28, iLength);
	AssertFalse(cFile.IsEndOfFile());
	bResult = cFile.ReadStringChars(sz, iLength);
	AssertString("The suspense is killing me!", sz);
	AssertTrue(cFile.IsEndOfFile());

	memset(sz, 0, 200);
	bResult = cFile.Seek(20);
	AssertTrue(bResult);
	bResult = cFile.ReadStringChars(sz, 8);
	AssertString("killing ", sz);
	AssertLongLongInt(28, cFile.GetFilePos());
	AssertFalse(cFile.IsEndOfFile());

	memset(sz, 0, 200);
	bResult = cFile.ReadStringChars(sz, 4);
	AssertString("me!", sz);
	AssertLongLongInt(32, cFile.GetFilePos());
	AssertTrue(cFile.IsEndOfFile());

	iRead = cFile.Read(sz, 1, 1);
	AssertLongLongInt(0, iRead);
	AssertLongLongInt(32, cFile.GetFilePos());
	AssertTrue(cFile.IsEndOfFile());

	AssertLongLongInt(32, cFile.GetFilePos());
	AssertTrue(cFile.IsEndOfFile());

	bResult = cFile.Close();
	AssertTrue(bResult);

	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogFileWriteMemory(void)
{
	CLogFile*		pcLogFile;
	CMemoryFile*	pcMemoryFile;
	CFileBasic		cFile;
	BOOL			bResult;
	int				iLength;
	char			sz[200];

	pcMemoryFile = MemoryFile();
	pcLogFile = LogFile(pcMemoryFile);
	cFile.Init(pcLogFile);

	pcLogFile->Begin();
	bResult = cFile.Open(EFM_ReadWrite_Create);
	AssertTrue(bResult);

	bResult = cFile.WriteString("The suspense is killing me!");
	AssertTrue(bResult);
	AssertNull((char*)pcMemoryFile->GetBufferPointer());
	
	AssertInt(1, pcLogFile->GetNumWrites());
	AssertLongLongInt(32, pcLogFile->GetWriteSize(0));

	bResult = cFile.Seek(8);
	AssertTrue(bResult);

	bResult = cFile.WriteData("camisole", 8);
	AssertTrue(bResult);
	AssertInt(1, pcLogFile->GetNumWrites());
	AssertLongLongInt(32, pcLogFile->GetWriteSize(0));
	
	AssertNull((char*)pcMemoryFile->GetBufferPointer());
	cFile.Seek(0);
	bResult = cFile.ReadStringLength(&iLength);
	AssertTrue(bResult);
	AssertInt(28, iLength);
	AssertFalse(cFile.IsEndOfFile());
	bResult = cFile.ReadStringChars(sz, iLength);
	AssertString("The camisole is killing me!", sz);
	AssertTrue(cFile.IsEndOfFile());

	bResult = pcLogFile->Commit();
	AssertTrue(bResult);
	AssertString("The camisole is killing me!", (char*)RemapSinglePointer(pcMemoryFile->GetBufferPointer(), sizeof(int)));

	bResult = cFile.Close();  //This should go before Commit
	AssertTrue(bResult);

	pcLogFile->Commit();
	pcLogFile->End();
	pcLogFile->Begin();
	
	bResult = cFile.Open(EFM_ReadWrite_Create);
	AssertTrue(bResult);

	bResult = cFile.Seek(4);
	AssertTrue(bResult);
	bResult = cFile.WriteData("Dog", 3);

	bResult = cFile.Seek(20);
	AssertTrue(bResult);
	bResult = cFile.WriteData("plurgle", 7);

	AssertInt(2, pcLogFile->GetNumWrites());
	AssertLongLongInt(3, pcLogFile->GetWriteSize(0));
	AssertLongLongInt(7, pcLogFile->GetWriteSize(1));

	AssertString("The camisole is killing me!", (char*)RemapSinglePointer(pcMemoryFile->GetBufferPointer(), sizeof(int)));
	cFile.Seek(0);
	bResult = cFile.ReadStringLength(&iLength);
	AssertTrue(bResult);
	AssertInt(28, iLength);
	AssertFalse(cFile.IsEndOfFile());
	bResult = cFile.ReadStringChars(sz, iLength);
	AssertTrue(bResult);
	AssertString("Dog camisole is plurgle me!", sz);
	AssertTrue(cFile.IsEndOfFile());

	bResult = pcLogFile->Commit();
	AssertTrue(bResult);
	AssertString("Dog camisole is plurgle me!", (char*)RemapSinglePointer(pcMemoryFile->GetBufferPointer(), sizeof(int)));

	bResult = cFile.Close();
	AssertTrue(bResult);

	pcLogFile->Commit();
	pcLogFile->End();
	pcLogFile->Begin();

	bResult = cFile.Open(EFM_ReadWrite_Create);
	AssertTrue(bResult);

	cFile.Seek(4);
	cFile.WriteData("X", 1);
	cFile.Seek(6);
	bResult = cFile.WriteData("Z", 1);
	cFile.Seek(28);
	cFile.WriteData("A", 1);
	cFile.Seek(30);
	bResult = cFile.WriteData("C", 1);
	AssertInt(4, pcLogFile->GetNumWrites());

	cFile.Seek(5);
	cFile.WriteData("Y", 1);
	AssertInt(3, pcLogFile->GetNumWrites());
	
	cFile.Seek(29);
	cFile.WriteData("B", 1);
	AssertInt(2, pcLogFile->GetNumWrites());

	cFile.Seek(0);
	bResult = cFile.ReadStringLength(&iLength);
	AssertTrue(bResult);
	bResult = cFile.ReadStringChars(sz, iLength);
	AssertString("XYZ camisole is plurgle ABC", sz);
	AssertTrue(cFile.IsEndOfFile());

	bResult = pcLogFile->Commit();
	AssertTrue(bResult);
	AssertString("XYZ camisole is plurgle ABC", (char*)RemapSinglePointer(pcMemoryFile->GetBufferPointer(), sizeof(int)));

	bResult = cFile.Close();
	AssertTrue(bResult);

	pcLogFile->Commit();
	pcLogFile->End();

	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogFileWriteDiskSingle(void)
{
	CLogFile*		pcLogFile;
	CDiskFile*		pcDiskFile;
	CFileBasic		cFile;
	BOOL			bResult;
	CFileUtil		cFileUtil;
	char			szDirectory[] = "Output" _FS_ "LogFile4";
	char			szFileName[] = "Output" _FS_ "LogFile4" _FS_ "File.txt";
	CTextFile		cTextFile;

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);
	pcDiskFile = DiskFile(szFileName);

	pcLogFile = LogFile(pcDiskFile);
	cFile.Init(pcLogFile);

	AssertTrue(pcLogFile->Begin());
	AssertTrue(cFile.Open(EFM_ReadWrite_Create));

	bResult = cFile.WriteString("The suspense is killing me!");
	AssertTrue(bResult);

	bResult = cFile.Close();  
	AssertTrue(bResult);
	AssertInt(3, pcLogFile->GetNumCommands());

	AssertTrue(pcLogFile->Commit());
	AssertTrue(cFileUtil.Exists(szFileName));

	AssertTrue(pcLogFile->End());

	cTextFile.Init();
	cTextFile.Read(DiskFile(szFileName));
	AssertString("The suspense is killing me!", cTextFile.Text(sizeof(int)));
	cTextFile.Kill();

	cFile.Kill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogFileWriteDisk(void)
{
	CLogFile*		pcLogFile;
	CDiskFile*		pcDiskFile;
	CFileBasic		cFile;
	BOOL			bResult;
	int				iLength;
	char			sz[200];
	CFileUtil		cFileUtil;
	char			szDirectory[] = "Output" _FS_ "LogFile3";
	char			szFileName[] = "Output" _FS_ "LogFile3" _FS_ "File.txt";
	CTextFile		cTextFile;

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);
	pcDiskFile = DiskFile(szFileName);

	pcLogFile = LogFile(pcDiskFile);
	cFile.Init(pcLogFile);

	AssertTrue(pcLogFile->Begin());
	AssertTrue(cFile.Open(EFM_ReadWrite_Create));

	bResult = cFile.WriteString("The suspense is killing me!");
	AssertTrue(bResult);
	AssertFalse(cFileUtil.Exists(szFileName));

	AssertInt(1, pcLogFile->GetNumWrites());
	AssertLongLongInt(32, pcLogFile->GetWriteSize(0));

	bResult = cFile.Seek(8);
	AssertTrue(bResult);

	bResult = cFile.WriteData("camisole", 8);
	AssertTrue(bResult);
	AssertInt(1, pcLogFile->GetNumWrites());
	AssertLongLongInt(32, pcLogFile->GetWriteSize(0));

	AssertFalse(cFileUtil.Exists(szFileName));
	cFile.Seek(0);
	bResult = cFile.ReadStringLength(&iLength);
	AssertTrue(bResult);
	AssertInt(28, iLength);
	AssertFalse(cFile.IsEndOfFile());
	bResult = cFile.ReadStringChars(sz, iLength);
	AssertString("The camisole is killing me!", sz);
	AssertTrue(cFile.IsEndOfFile());

	bResult = cFile.Close();  //This should go before Commit
	AssertTrue(bResult);
	AssertInt(3, pcLogFile->GetNumCommands());

	AssertTrue(pcLogFile->Commit());
	AssertTrue(cFileUtil.Exists(szFileName));
	AssertTrue(pcLogFile->End());

	cTextFile.Init();
	cTextFile.Read(DiskFile(szFileName));
	AssertString("The camisole is killing me!", cTextFile.Text(sizeof(int)));
	cTextFile.Kill();

	cFile.Kill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogFileFindHoles(void)
{
	CLogFile*				pcLogFile;
	CFileBasic				cFile;
	BOOL					bResult;
	int						iInt1;
	int						iInt2;
	int						iInt3;
	CArrayIntAndPointer		apvOverlapping;
	int						i;
	int						iSize;
	CMemoryFile*			pcMemoryFile;

	pcMemoryFile = MemoryFile();
	pcLogFile = LogFile(pcMemoryFile);
	cFile.Init(pcLogFile);

	pcLogFile->Begin();

	bResult = cFile.Open(EFM_ReadWrite_Create);
	AssertTrue(bResult);
	
	iInt1 = 872349342;
	iInt2 = 763421934;
	iInt3 = 158723346;
	iSize = sizeof(int);

	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, 1);
	AssertTrue(bResult);
	AssertInt(0, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	cFile.Write(&iInt1, 4, 1);
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, 4);
	AssertFalse(bResult);

	cFile.Write(&iInt2, 4, 1);
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, 8);
	AssertFalse(bResult);

	for (i = 0; i < 8; i++)
	{
		bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, i);
		AssertFalse(bResult);
	}
	for (i = 0; i < 8; i++)
	{
		bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, i, 8 -i);
		AssertFalse(bResult);
	}
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 7, 2);
	AssertTrue(bResult);
	AssertInt(1, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	cFile.Seek(4, EFSO_CURRENT);
	cFile.Write(&iInt3, 4, 1);
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, 16);
	AssertTrue(bResult);
	AssertInt(2, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 12, 4);
	AssertFalse(bResult);

	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 11, 5);
	AssertTrue(bResult);
	AssertInt(1, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, 8);
	AssertFalse(bResult);

	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, 9);
	AssertTrue(bResult);
	AssertInt(1, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 7, 2);
	AssertTrue(bResult);
	AssertInt(1, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 8, 1);
	AssertTrue(bResult);
	AssertInt(0, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 8, 4);
	AssertTrue(bResult);
	AssertInt(0, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 8, 5);
	AssertTrue(bResult);
	AssertInt(1, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, 0);
	AssertFalse(bResult);
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 7, 0);
	AssertFalse(bResult);
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 8, 0);
	AssertFalse(bResult);

	cFile.Close();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogFileCommandsSimple(void)
{
	CLogFile*		pcLogFile;
	CMemoryFile*	pcMemoryFile;
	CFileBasic		cFile;
	BOOL			bResult;
	int				iInt;
	int				iWritten;
	int				iResult;
	int				iRead;

	pcMemoryFile = MemoryFile();
	pcLogFile = LogFile(pcMemoryFile);
	cFile.Init(pcLogFile);

	pcLogFile->Begin();

	bResult = cFile.Open(EFM_ReadWrite_Create);
	AssertTrue(bResult);
	AssertTrue(cFile.IsOpen());

	iInt = 872349342;
	iWritten = (int)cFile.Write(&iInt, sizeof(int), 1);
	AssertInt(1, iWritten);
	AssertInt(0, pcMemoryFile->GetBufferSize());

	bResult = cFile.Close();
	AssertTrue(bResult);
	AssertInt(3, pcLogFile->GetNumCommands());

	bResult = cFile.Open(EFM_ReadWrite_Create);
	AssertTrue(bResult);
	AssertTrue(cFile.IsOpen());
	AssertInt(sizeof(int), (int)cFile.GetFileLength());
	iRead = (int)cFile.Read(&iResult, sizeof(int), 1);
	AssertInt(1, iRead);
	AssertInt(iInt, iResult);
	bResult = cFile.Close();
	AssertTrue(bResult);
	AssertInt(5, pcLogFile->GetNumCommands());

	bResult = pcLogFile->Commit();
	AssertTrue(bResult);
	AssertFalse(pcMemoryFile->IsOpen());
	AssertInt(sizeof(int), pcMemoryFile->GetBufferSize());
	AssertInt(iInt, *((int*)pcMemoryFile->GetBufferPointer()));

	pcLogFile->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogFileCommandsComplex(void)
{
	CLogFile*		pcLogFile;
	CMemoryFile*	pcMemoryFile;
	CFileBasic		cFile;
	BOOL			bResult;
	int				iWritten;
	char			szABC[] = {"ABCDEFGHIJK"};
	char			sz123[] = {"123"};
	char			sz4[] = {"4"};
	char			szExclamation[] = {"!?"};
	char			szQWE[] = {"_QWE_"};
	char			szResult[12];

	pcMemoryFile = MemoryFile();
	pcMemoryFile->Open(EFM_ReadWrite_Create);
	pcMemoryFile->Write(szABC, 1, 12);
	pcMemoryFile->Close();

	pcLogFile = LogFile(pcMemoryFile);
	cFile.Init(pcLogFile);

	pcLogFile->Begin();

	cFile.Open(EFM_ReadWrite_Create);
	AssertInt(12, (int)cFile.GetFileLength());

	iWritten = (int)cFile.Write(sz123, 1, 3);
	AssertInt(3, iWritten);
	iWritten = (int)cFile.Write(sz4, 1, 1);
	AssertInt(1, iWritten);
	cFile.Close();

	cFile.Open(EFM_ReadWrite_Create);
	cFile.Write(szExclamation, 1, 2);
	cFile.Seek(3, EFSO_CURRENT);
	cFile.Write(szQWE, 5, 1);
	cFile.Close();

	cFile.Open(EFM_Read);
	AssertInt(12, (int)cFile.GetFileLength());
	memset(szResult, 0, 12);
	cFile.Read(szResult, 12, 1);
	AssertString("!?34E_QWE_K", szResult);
	cFile.Close();
	
	bResult = pcLogFile->Commit();
	AssertTrue(bResult);
	AssertFalse(pcMemoryFile->IsOpen());
	AssertInt(12, pcMemoryFile->GetBufferSize());
	AssertString("!?34E_QWE_K", (char*)pcMemoryFile->GetBufferPointer());

	pcLogFile->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogFileDelete(void)
{
	CLogFile*		pcLogFile;
	CDiskFile*		pcDiskFile;
	CFileBasic		cFile;
	CFileUtil		cFileUtil;
	char			szSource[] = {"The Name of the Wise Man"};
	int				iSourcelen;
	char			szResult[50];
	char			szWrite[] = {"Cat Catt ct... "};
	int				iWriteLen;
	char			szA[] = {"A"};
	char			szDirectory[] = "Output" _FS_ "LogFile";
	char			szFileName[] = "Output" _FS_ "LogFile" _FS_ "File.txt";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);
	pcDiskFile = DiskFile(szFileName);
	pcDiskFile->Open(EFM_ReadWrite_Create);
	iSourcelen = (int)strlen(szSource);
	pcDiskFile->Write(szSource, iSourcelen + 1, 1);
	pcDiskFile->Close();
	AssertTrue(cFileUtil.Exists(szFileName));

	pcLogFile = LogFile(pcDiskFile);
	cFile.Init(pcLogFile);
	pcLogFile->Begin();

	AssertTrue(cFile.Open(EFM_Read));
	AssertInt(iSourcelen + 1, (int)cFile.GetFileSize());
	cFile.ReadData(szResult, iSourcelen + 1);
	AssertString(szSource, szResult);
	cFile.Close();

	cFile.Open(EFM_ReadWrite_Create);
	iWriteLen = (int)strlen(szWrite);
	cFile.WriteData(szWrite, iWriteLen);
	AssertInt(iSourcelen + 1, (int)cFile.GetFileSize());
	
	pcLogFile->Close();
	AssertInt(5, pcLogFile->GetNumCommands());
	AssertInt(25, (int)cFile.GetFileSize())l

	cFile.Delete();
	AssertTrue(cFileUtil.Exists(szFileName));
	AssertInt(1, pcLogFile->GetNumCommands());
	AssertInt(0, (int)cFile.GetFileSize())l

	cFile.Open(EFM_ReadWrite_Create);
	cFile.Write(szA, 2, 1);
	AssertInt(2, (int)cFile.GetFileSize())l
	cFile.Close();

	pcLogFile->Commit();
	cFile.Kill();

	AssertTrue(cFileUtil.Exists(szFileName));
	AssertLongLongInt(2, cFileUtil.Size(szFileName));

	pcDiskFile = DiskFile(szFileName);
	pcLogFile = LogFile(pcDiskFile);
	cFile.Init(pcLogFile);
	pcLogFile->Begin();

	AssertTrue(cFile.Open(EFM_Read));
	cFile.ReadData(szResult, 2);
	AssertString("A", szResult);
	cFile.Close();

	cFile.Delete();
	pcLogFile->Commit();
	cFile.Kill();

	AssertFalse(cFileUtil.Exists(szFileName));
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogFileMultipleReadsAfterOpens(void)
{
	CLogFile*		pcLogFile;
	CDiskFile*		pcDiskFile;
	CFileBasic		cFile;
	CFileUtil		cFileUtil;
	char			szSource[] = {"The Name of the Wise Man"};
	int				iSourcelen;
	char			szResult[50];
	char			szWrite[] = {"Cat Catt ct... "};
	int				iWriteLen;
	char			szA[] = {"A"};
	char			szDirectory[] = "Output" _FS_ "LogFile2";
	char			szFileName[] = "Output" _FS_ "LogFile2" _FS_ "OpenClose.txt";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);
	pcDiskFile = DiskFile(szFileName);
	pcDiskFile->Open(EFM_ReadWrite_Create);
	iSourcelen = (int)strlen(szSource);
	pcDiskFile->Write(szSource, iSourcelen + 1, 1);
	pcDiskFile->Close();
	AssertTrue(cFileUtil.Exists(szFileName));

	pcLogFile = LogFile(pcDiskFile);
	cFile.Init(pcLogFile);
	pcLogFile->Begin();

	AssertTrue(cFile.Open(EFM_Read));
	AssertInt(iSourcelen + 1, (int)cFile.GetFileSize());
	cFile.ReadData(szResult, iSourcelen + 1);
	AssertString(szSource, szResult);
	cFile.Close();

	cFile.Open(EFM_ReadWrite_Create);
	iWriteLen = (int)strlen(szWrite);
	cFile.WriteData(szWrite, iWriteLen);
	AssertInt(iSourcelen + 1, (int)cFile.GetFileSize());
	pcLogFile->Close();

	cFile.Delete();
	AssertTrue(cFileUtil.Exists(szFileName));
	AssertInt(0, (int)cFile.GetFileSize());

	cFile.Open(EFM_ReadWrite_Create);
	cFile.Write(szA, 2, 1);
	AssertInt(2, (int)cFile.GetFileSize());

	cFile.Close();

	pcLogFile->Commit();
	cFile.Kill();

	AssertTrue(cFileUtil.Exists(szFileName));
	AssertLongLongInt(2, cFileUtil.Size(szFileName));

	pcDiskFile = DiskFile(szFileName);
	pcLogFile = LogFile(pcDiskFile);
	cFile.Init(pcLogFile);
	pcLogFile->Begin();

	AssertTrue(cFile.Open(EFM_Read));
	cFile.ReadData(szResult, 2);
	AssertString("A", szResult);

	cFile.Seek(0);
	cFile.ReadData(szResult, 2);
	AssertString("A", szResult);

	cFile.Close();

	cFile.Delete();
	pcLogFile->Commit();
	cFile.Kill();

	AssertFalse(cFileUtil.Exists(szFileName));

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogFile(void)
{
	BeginTests();

	FastFunctionsInit();
	TypeConverterInit();

	TestLogFileOpen();
	TestLogFileRead();
	TestLogFileWriteMemory();
	TestLogFileWriteDiskSingle();
	TestLogFileWriteDisk();
	TestLogFileFindHoles();
	TestLogFileCommandsSimple();
	TestLogFileCommandsComplex();
	TestLogFileDelete();
	TestLogFileMultipleReadsAfterOpens();

	FastFunctionsKill();
	TypeConverterKill();

	TestStatistics();
}

