#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/TextFile.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/Logger.h"
#include "BaseLib/LogFile.h"
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
	bool			bResult;
	size			iLength;
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
	AssertSize(28, iLength);
	bResult = cFile.ReadStringChars(sz, iLength);
	AssertString("The suspense is killing me!", sz);

	memset(sz, 0, 200);
	bResult = cFile.Seek(20);
	AssertTrue(bResult);
	bResult = cFile.ReadStringChars(sz, 8);
	AssertString("killing ", sz);
	AssertLong(28, cFile.GetFilePos());

	memset(sz, 0, 200);
	bResult = cFile.ReadStringChars(sz, 4);
	AssertString("me!", sz);
	AssertLong(32, cFile.GetFilePos());

	iRead = cFile.Read(sz, 1, 1);
	AssertLong(0, iRead);
	AssertLong(32, cFile.GetFilePos());

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
	bool			bResult;
	size			iLength;
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
	
	AssertSize(1, pcLogFile->GetNumWrites());
	AssertSize(32, pcLogFile->GetWriteSize(0));

	bResult = cFile.Seek(8);
	AssertTrue(bResult);

	bResult = cFile.WriteData("camisole", 8);
	AssertTrue(bResult);
	AssertSize(1, pcLogFile->GetNumWrites());
	AssertSize(32, pcLogFile->GetWriteSize(0));
	
	AssertNull((char*)pcMemoryFile->GetBufferPointer());
	cFile.Seek(0);
	bResult = cFile.ReadStringLength(&iLength);
	AssertTrue(bResult);
	AssertSize(28, iLength);
	bResult = cFile.ReadStringChars(sz, iLength);
	AssertString("The camisole is killing me!", sz);

	bResult = pcLogFile->Commit();
	AssertTrue(bResult);
	AssertString("The camisole is killing me!", (char*)RemapSinglePointer(pcMemoryFile->GetBufferPointer(), sizeof(int32)));

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

	AssertSize(2, pcLogFile->GetNumWrites());
	AssertLong(3, pcLogFile->GetWriteSize(0));
	AssertLong(7, pcLogFile->GetWriteSize(1));

	AssertString("The camisole is killing me!", (char*)RemapSinglePointer(pcMemoryFile->GetBufferPointer(), sizeof(int32)));
	cFile.Seek(0);
	bResult = cFile.ReadStringLength(&iLength);
	AssertTrue(bResult);
	AssertSize(28, iLength);
	bResult = cFile.ReadStringChars(sz, iLength);
	AssertTrue(bResult);
	AssertString("Dog camisole is plurgle me!", sz);

	bResult = pcLogFile->Commit();
	AssertTrue(bResult);
	AssertString("Dog camisole is plurgle me!", (char*)RemapSinglePointer(pcMemoryFile->GetBufferPointer(), sizeof(int32)));

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
	AssertSize(4, pcLogFile->GetNumWrites());

	cFile.Seek(5);
	cFile.WriteData("Y", 1);
	AssertSize(3, pcLogFile->GetNumWrites());
	
	cFile.Seek(29);
	cFile.WriteData("B", 1);
	AssertSize(2, pcLogFile->GetNumWrites());

	cFile.Seek(0);
	bResult = cFile.ReadStringLength(&iLength);
	AssertTrue(bResult);
	bResult = cFile.ReadStringChars(sz, iLength);
	AssertString("XYZ camisole is plurgle ABC", sz);

	bResult = pcLogFile->Commit();
	AssertTrue(bResult);
	AssertString("XYZ camisole is plurgle ABC", (char*)RemapSinglePointer(pcMemoryFile->GetBufferPointer(), sizeof(int32)));

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
	bool			bResult;
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
	AssertSize(3, pcLogFile->GetNumCommands());

	AssertTrue(pcLogFile->Commit());
	AssertTrue(cFileUtil.Exists(szFileName));

	AssertTrue(pcLogFile->End());

	cTextFile.Init();
	cTextFile.Read(DiskFile(szFileName));
	AssertString("The suspense is killing me!", cTextFile.Text(sizeof(int32)));
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
	bool			bResult;
	size			iLength;
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

	AssertSize(1, pcLogFile->GetNumWrites());
	AssertLong(32, pcLogFile->GetWriteSize(0));

	bResult = cFile.Seek(8);
	AssertTrue(bResult);

	bResult = cFile.WriteData("camisole", 8);
	AssertTrue(bResult);
	AssertSize(1, pcLogFile->GetNumWrites());
	AssertLong(32, pcLogFile->GetWriteSize(0));

	AssertFalse(cFileUtil.Exists(szFileName));
	cFile.Seek(0);
	bResult = cFile.ReadStringLength(&iLength);
	AssertTrue(bResult);
	AssertSize(28, iLength);
	bResult = cFile.ReadStringChars(sz, iLength);
	AssertString("The camisole is killing me!", sz);

	bResult = cFile.Close();  //This should go before Commit
	AssertTrue(bResult);
	AssertSize(3, pcLogFile->GetNumCommands());

	AssertTrue(pcLogFile->Commit());
	AssertTrue(cFileUtil.Exists(szFileName));
	AssertTrue(pcLogFile->End());

	cTextFile.Init();
	cTextFile.Read(DiskFile(szFileName));
	AssertString("The camisole is killing me!", cTextFile.Text(sizeof(int32)));
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
	bool					bResult;
	int32					iInt1;
	int32					iInt2;
	int32					iInt3;
	CArrayIntAndPointer		apvOverlapping;
	size					i;
	size						iSize;
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
	iSize = sizeof(int32);

	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, 1);
	AssertTrue(bResult);
	AssertSize(0, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	apvOverlapping.Init();
	cFile.Write(&iInt1, 4, 1);
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, 4);
	AssertFalse(bResult);
	apvOverlapping.Kill();

	apvOverlapping.Init();
	cFile.Write(&iInt2, 4, 1);
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, 8);
	AssertFalse(bResult);
	apvOverlapping.Kill();

	for (i = 0; i < 8; i++)
	{
		apvOverlapping.Init();
		bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, i);
		AssertFalse(bResult);
		apvOverlapping.Kill();
	}
	for (i = 0; i < 8; i++)
	{
		apvOverlapping.Init();
		bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, i, 8 -i);
		AssertFalse(bResult);
		apvOverlapping.Kill();
	}
	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 7, 2);
	AssertTrue(bResult);
	AssertSize(1, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	apvOverlapping.Init();
	cFile.Seek(4, EFSO_CURRENT);
	cFile.Write(&iInt3, 4, 1);
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, 16);
	AssertTrue(bResult);
	AssertSize(2, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 12, 4);
	AssertFalse(bResult);
	apvOverlapping.Kill();

	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 11, 5);
	AssertTrue(bResult);
	AssertSize(1, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, 8);
	AssertFalse(bResult);
	apvOverlapping.Kill();

	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, 9);
	AssertTrue(bResult);
	AssertSize(1, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 7, 2);
	AssertTrue(bResult);
	AssertSize(1, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 8, 1);
	AssertTrue(bResult);
	AssertSize(0, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 8, 4);
	AssertTrue(bResult);
	AssertSize(0, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 8, 5);
	AssertTrue(bResult);
	AssertSize(1, apvOverlapping.NumElements());
	apvOverlapping.Kill();

	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 0, 0);
	AssertFalse(bResult);
	apvOverlapping.Kill();
	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 7, 0);
	AssertFalse(bResult);
	apvOverlapping.Kill();
	apvOverlapping.Init();
	bResult = pcLogFile->TestFindHoles(1, &apvOverlapping, 8, 0);
	AssertFalse(bResult);
	apvOverlapping.Kill();

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
	bool			bResult;
	int32			iInt;
	size			iWritten;
	int32			iResult;
	size			iRead;

	pcMemoryFile = MemoryFile();
	pcLogFile = LogFile(pcMemoryFile);
	cFile.Init(pcLogFile);

	pcLogFile->Begin();

	bResult = cFile.Open(EFM_ReadWrite_Create);
	AssertTrue(bResult);
	AssertTrue(cFile.IsOpen());

	iInt = 872349342;
	iWritten = cFile.Write(&iInt, sizeof(int32), 1);
	AssertSize(1, iWritten);
	AssertSize(0, pcMemoryFile->GetBufferSize());

	bResult = cFile.Close();
	AssertTrue(bResult);
	AssertSize(3, pcLogFile->GetNumCommands());

	bResult = cFile.Open(EFM_ReadWrite_Create);
	AssertTrue(bResult);
	AssertTrue(cFile.IsOpen());
	AssertLong(sizeof(int32), cFile.GetFileLength());
	iRead = cFile.Read(&iResult, sizeof(int32), 1);
	AssertSize(1, iRead);
	AssertSize(iInt, iResult);
	bResult = cFile.Close();
	AssertTrue(bResult);
	AssertSize(5, pcLogFile->GetNumCommands());

	bResult = pcLogFile->Commit();
	AssertTrue(bResult);
	AssertFalse(pcMemoryFile->IsOpen());
	AssertSize(sizeof(int32), pcMemoryFile->GetBufferSize());
	AssertInt(iInt, *((int32*)pcMemoryFile->GetBufferPointer()));

	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogFileCommandsComplex(void)
{
	CLogFile* pcLogFile;
	CMemoryFile* pcMemoryFile;
	CFileBasic		cFile;
	bool			bResult;
	size			iWritten;
	char			szABC[] = { "ABCDEFGHIJK" };
	char			sz123[] = { "123" };
	char			sz4[] = { "4" };
	char			szExclamation[] = { "!?" };
	char			szQWE[] = { "_QWE_" };
	char			szResult[12];

	pcMemoryFile = MemoryFile();
	pcMemoryFile->Open(EFM_ReadWrite_Create);
	pcMemoryFile->Write(szABC, 1, 12);
	pcMemoryFile->Close();

	pcLogFile = LogFile(pcMemoryFile);
	cFile.Init(pcLogFile);

	pcLogFile->Begin();

	cFile.Open(EFM_ReadWrite_Create);
	AssertLong(12, cFile.GetFileLength());

	iWritten = cFile.Write(sz123, 1, 3);
	AssertSize(3, iWritten);
	iWritten = cFile.Write(sz4, 1, 1);
	AssertSize(1, iWritten);
	cFile.Close();

	cFile.Open(EFM_ReadWrite_Create);
	cFile.Write(szExclamation, 1, 2);
	cFile.Seek(3, EFSO_CURRENT);
	cFile.Write(szQWE, 5, 1);
	cFile.Close();

	cFile.Open(EFM_Read);
	AssertLong(12, cFile.GetFileLength());
	memset(szResult, 0, 12);
	cFile.Read(szResult, 12, 1);
	AssertString("!?34E_QWE_K", szResult);
	cFile.Close();

	bResult = pcLogFile->Commit();
	AssertTrue(bResult);
	AssertFalse(pcMemoryFile->IsOpen());
	AssertSize(12, pcMemoryFile->GetBufferSize());
	AssertString("!?34E_QWE_K", (char*)pcMemoryFile->GetBufferPointer());

	cFile.Kill();
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
	size			iSourcelen;
	char			szResult[50];
	char			szWrite[] = {"Cat Catt ct... "};
	size			iWriteLen;
	char			szA[] = {"A"};
	char			szDirectory[] = "Output" _FS_ "LogFile";
	char			szFileName[] = "Output" _FS_ "LogFile" _FS_ "File.txt";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);
	pcDiskFile = DiskFile(szFileName);
	pcDiskFile->Open(EFM_ReadWrite_Create);
	iSourcelen = strlen(szSource);
	pcDiskFile->Write(szSource, iSourcelen + 1, 1);
	pcDiskFile->Close();
	AssertTrue(cFileUtil.Exists(szFileName));

	pcLogFile = LogFile(pcDiskFile);
	cFile.Init(pcLogFile);
	pcLogFile->Begin();

	AssertTrue(cFile.Open(EFM_Read));
	AssertLong(iSourcelen + 1, cFile.GetFileSize());
	cFile.ReadData(szResult, iSourcelen + 1);
	AssertString(szSource, szResult);
	cFile.Close();

	cFile.Open(EFM_ReadWrite_Create);
	iWriteLen = strlen(szWrite);
	cFile.WriteData(szWrite, iWriteLen);
	AssertLong(iSourcelen + 1, cFile.GetFileSize());
	
	pcLogFile->Close();
	AssertSize(5, pcLogFile->GetNumCommands());
	AssertLong(25, cFile.GetFileSize());

	cFile.Delete();
	AssertTrue(cFileUtil.Exists(szFileName));
	AssertSize(1, pcLogFile->GetNumCommands());
	AssertLong(0, cFile.GetFileSize());

	cFile.Open(EFM_ReadWrite_Create);
	cFile.Write(szA, 2, 1);
	AssertLong(2, cFile.GetFileSize());
	cFile.Close();

	pcLogFile->Commit();
	cFile.Kill();

	AssertTrue(cFileUtil.Exists(szFileName));
	AssertLong(2, cFileUtil.Size(szFileName));

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
	size			iSourcelen;
	char			szResult[50];
	char			szWrite[] = {"Cat Catt ct... "};
	size			iWriteLen;
	char			szA[] = {"A"};
	char			szDirectory[] = "Output" _FS_ "LogFile2";
	char			szFileName[] = "Output" _FS_ "LogFile2" _FS_ "OpenClose.txt";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);
	pcDiskFile = DiskFile(szFileName);
	pcDiskFile->Open(EFM_ReadWrite_Create);
	iSourcelen = strlen(szSource);
	pcDiskFile->Write(szSource, iSourcelen + 1, 1);
	pcDiskFile->Close();
	AssertTrue(cFileUtil.Exists(szFileName));

	pcLogFile = LogFile(pcDiskFile);
	cFile.Init(pcLogFile);
	pcLogFile->Begin();

	AssertTrue(cFile.Open(EFM_Read));
	AssertLong(iSourcelen + 1, cFile.GetFileSize());
	cFile.ReadData(szResult, iSourcelen + 1);
	AssertString(szSource, szResult);
	cFile.Close();

	cFile.Open(EFM_ReadWrite_Create);
	iWriteLen = strlen(szWrite);
	cFile.WriteData(szWrite, iWriteLen);
	AssertLong(iSourcelen + 1, cFile.GetFileSize());
	pcLogFile->Close();

	cFile.Delete();
	AssertTrue(cFileUtil.Exists(szFileName));
	AssertLong(0, cFile.GetFileSize());

	cFile.Open(EFM_ReadWrite_Create);
	cFile.Write(szA, 2, 1);
	AssertLong(2, cFile.GetFileSize());

	cFile.Close();

	pcLogFile->Commit();
	cFile.Kill();

	AssertTrue(cFileUtil.Exists(szFileName));
	AssertLong(2, cFileUtil.Size(szFileName));

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
	TypeConverterInit();
	DataMemoryInit();
	BeginTests();

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

	TestStatistics();
	DataMemoryKill();
	TypeConverterKill();
}

