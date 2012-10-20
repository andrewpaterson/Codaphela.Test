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
void TestLogFile(void)
{
	BeginTests();

	FastFunctionsInit();
	TypeConverterInit();

	TestLogFileOpen();
	TestLogFileRead();

	FastFunctionsKill();
	TypeConverterKill();

	TestStatistics();
}
