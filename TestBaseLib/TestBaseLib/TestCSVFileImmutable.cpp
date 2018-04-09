#include "BaseLib/FileUtil.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/CSVFileImutable.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCSVFileImmutableRead(void)
{
	CCSVFileImmutable	cCSVFile;
	CMemoryFile*		pcMemoryFile;
	int					iNumRows;
	SCSVRowImmutable*	psRow;
	char*				szCell;
	int					iFileLen;
	char				szFile[] = "\
Header1|Header2\n\
234|7782\n";

	iFileLen = strlen(szFile);
	pcMemoryFile = MemoryFile(szFile, iFileLen);

	cCSVFile.Init('|');
	cCSVFile.Open(pcMemoryFile);

	cCSVFile.ReadAllLines();

	iNumRows = cCSVFile.NumRows();
	AssertInt(2, iNumRows);
	psRow = cCSVFile.Get(0);
	AssertInt(2, psRow->NumElements());

	szCell = psRow->Get(0);
	AssertString("Header1", szCell);
	szCell = psRow->Get(1);
	AssertString("Header2", szCell);

	psRow = cCSVFile.Get(1);
	AssertInt(2, psRow->NumElements());

	szCell = psRow->Get(0);
	AssertString("234", szCell);
	szCell = psRow->Get(1);
	AssertString("7782", szCell);

	cCSVFile.Close();
	cCSVFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCSVFileImmutable(void)
{
	BeginTests();
	FastFunctionsInit();

	TestCSVFileImmutableRead();

	FastFunctionsKill();
	TestStatistics();
}

