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
void TestLogFile(void)
{
	BeginTests();

	FastFunctionsInit();
	TypeConverterInit();

	TestLogFileOpen();

	FastFunctionsKill();
	TypeConverterKill();

	TestStatistics();
}
