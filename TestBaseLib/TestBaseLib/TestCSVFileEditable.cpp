#include "BaseLib/FileUtil.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/CSVFileEditable.h"
#include "TestLib/Assert.h"
#include "TestCSVFileEditable.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCSVFileEditableRead(void)
{
	CCSVFileEditable	cCSVFile;
	CMemoryFile*		pcMemoryFile;
	int					iNumRows;
	SCSVRowEditable*	psRow;
	CChars*				pszCell;
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
	AssertInt(2, psRow->NumCells());

	pszCell = psRow->Get(0);
	AssertString("Header1", pszCell->Text());
	pszCell = psRow->Get(1);
	AssertString("Header2", pszCell->Text());

	psRow = cCSVFile.Get(1);
	AssertInt(2, psRow->NumCells());

	pszCell = psRow->Get(0);
	AssertString("234", pszCell->Text());
	pszCell = psRow->Get(1);
	AssertString("7782", pszCell->Text());

	cCSVFile.Close();
	cCSVFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCSVFileEditable(void)
{
	BeginTests();
	FastFunctionsInit();

	TestCSVFileEditableRead();

	FastFunctionsKill();
	TestStatistics();
}

