#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/MemoryFile.h"
#include "CoreLib/TypeConverter.h"
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
	BOOL			bResult;

	pcMemoryFile = MemoryFile();
	pcLogFile = LogFile(pcMemoryFile);
	AssertNotNull(pcLogFile);

	cFile.Init(pcLogFile);

	bResult = cFile.Open(EFM_ReadWrite_Create);
	AssertTrue(bResult);

	bResult = cFile.Close();
	AssertTrue(bResult);

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

	pcMemoryFile = MemoryFile();
	cFile.Init(pcMemoryFile);
	cFile.Open(EFM_Write_Create);
	cFile.WriteString("The suspense is killing me!");
	cFile.Close();

	pcLogFile = LogFile(pcMemoryFile);
	cFile.Init(pcLogFile);

	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);

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
void TestLogFileWrite(void)
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

	bResult = pcLogFile->CommitWrites();
	AssertTrue(bResult);
	AssertString("The camisole is killing me!", (char*)RemapSinglePointer(pcMemoryFile->GetBufferPointer(), sizeof(int)));

	bResult = cFile.Close();  //This should go before CommitWrites and CommitWrites should be renamed to just Commit.
	AssertTrue(bResult);

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
	AssertString("Dog camisole is plurgle me!", sz);
	AssertTrue(cFile.IsEndOfFile());

	bResult = pcLogFile->CommitWrites();
	AssertTrue(bResult);
	AssertString("Dog camisole is plurgle me!", (char*)RemapSinglePointer(pcMemoryFile->GetBufferPointer(), sizeof(int)));

	bResult = cFile.Close();
	AssertTrue(bResult);

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

	bResult = pcLogFile->CommitWrites();
	AssertTrue(bResult);
	AssertString("XYZ camisole is plurgle ABC", (char*)RemapSinglePointer(pcMemoryFile->GetBufferPointer(), sizeof(int)));

	bResult = cFile.Close();
	AssertTrue(bResult);

	cFile.Kill();
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
	TestLogFileWrite();

	FastFunctionsKill();
	TypeConverterKill();

	TestStatistics();
}
