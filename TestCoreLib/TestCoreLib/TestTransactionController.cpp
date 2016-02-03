#include "CoreLib/TransactionController.h"
#include "BaseLib/FastFunctions.h"
#include "TestLib/Assert.h"
#include "BaseLib/FileUtil.h"
#include "CoreLib/TypeConverter.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTransactionControllerWithDurableFile(char* szDirectory, BOOL bDurable)
{
	CFileUtil cFileUtil;
	cFileUtil.RemoveDir(szDirectory);

	CTransactionController	cTransactionController;
	CTransaction*			pcTransaction1;
	CTransaction*			pcTransaction2;
	char					szFourth[7] = "Fourth";
	char					szBlackJack[11] = "Black Jack";
	char					szMuckPuppy[11] = "Muck Puppy";
	char					szHenry[6] = "Henry";
	char					szBerty[6] = "Berty";
	char					szPalmer[7] = "Palmer";
	BOOL					bResult;
	char					szDest[11];

	cTransactionController.Init(szDirectory, 100, bDurable);
	pcTransaction1 = cTransactionController.BeginTransaction(TRUE);

	pcTransaction1->Add(4LL, szFourth, 7);
	pcTransaction1->Add(32LL, szBlackJack, 11);
	pcTransaction1->Add(6LL, szHenry, 6);
	pcTransaction1->Add(12LL, szPalmer, 7);
	AssertInt(0, (int)cTransactionController.NumElements());
	bResult = cTransactionController.EndTransaction(pcTransaction1, TRUE);
	AssertBool(TRUE, bResult);
	AssertInt(4, (int)cTransactionController.NumElements());
	AssertInt(2, (int)cTransactionController.mcIndexedData.TestNumCachedIndexes());
	cTransactionController.Kill();

	cTransactionController.Init(szDirectory, 128, bDurable);
	AssertInt(0, (int)cTransactionController.mcIndexedData.TestNumCachedIndexes());
	cTransactionController.Kill();

	cTransactionController.Init(szDirectory, 128, bDurable);
	AssertInt(4, (int)cTransactionController.mcIndexedData.NumElements());

	pcTransaction1 = cTransactionController.BeginTransaction(TRUE);  //Tx1 Start
	pcTransaction1->Set(32LL, szMuckPuppy, 11);

	pcTransaction2 = cTransactionController.BeginTransaction(TRUE);  //Tx2 Start
	pcTransaction2->Set(6LL, szBerty, 6);
	bResult = cTransactionController.EndTransaction(pcTransaction2, TRUE);  //Tx2 End
	AssertBool(TRUE, bResult);

	bResult = pcTransaction1->Get(12LL, szDest);
	AssertBool(TRUE, bResult);
	AssertString(szPalmer, szDest);

	bResult = cTransactionController.EndTransaction(pcTransaction1, TRUE);  //Tx1 End
	AssertBool(TRUE, bResult);

	cTransactionController.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTransactionControllerCommit(char* szDirectory, BOOL bDurable)
{
	CFileUtil cFileUtil;

	cFileUtil.RemoveDir(szDirectory);

	CTransactionController	cTransactionController;
	CTransaction*			pcTransaction2;
	CTransaction*			pcTransaction1;
	char					szABCDE[] = "ABCDE";
	char					szFGHIJ[] = "FGHIJ";
	char					szKLNOP[] = "KLNOP";
	char					szQRSTU[] = "QRSTU";

	char					szFZZZJ[] = "FZZZJ";

	char					szDest[6];
	BOOL					bResult;

	cTransactionController.Init(szDirectory, 100, bDurable);  //Used to descriptor cache
	pcTransaction2 = cTransactionController.BeginTransaction();

	pcTransaction2->Add(0LL, szABCDE, 6);
	pcTransaction2->Add(1LL, szFGHIJ, 6);
	pcTransaction2->Add(2LL, szKLNOP, 6);
	pcTransaction2->Add(3LL, szQRSTU, 6);
	cTransactionController.EndTransaction(pcTransaction2, TRUE);
	cTransactionController.Kill();

	cTransactionController.Init(szDirectory, 100, bDurable);  //Used to descriptor cache
	pcTransaction1 = cTransactionController.BeginTransaction();

	bResult = pcTransaction1->Get(1LL, szDest);
	AssertBool(TRUE, bResult);
	AssertString(szFGHIJ, szDest);
	bResult = pcTransaction1->Set(1LL, szFZZZJ, 6);
	AssertBool(TRUE, bResult);
	bResult = pcTransaction1->Get(1LL, szDest);
	AssertBool(TRUE, bResult);
	AssertString(szFZZZJ, szDest);
	bResult = pcTransaction1->Remove(2LL);
	AssertBool(TRUE, bResult);
	bResult = pcTransaction1->Get(2LL, szDest);
	AssertBool(FALSE, bResult);
	cTransactionController.EndTransaction(pcTransaction1, FALSE);  //Don't commit.  The database must be left unchanged.

	bResult = cTransactionController.mcIndexedData.Get(1LL, szDest);
	AssertBool(TRUE, bResult);
	AssertString(szFGHIJ, szDest);

	bResult = cTransactionController.mcIndexedData.Get(2LL, szDest);
	AssertBool(TRUE, bResult);
	AssertString(szKLNOP, szDest);

	pcTransaction1 = cTransactionController.BeginTransaction();
	pcTransaction1->Set(1LL, szFZZZJ, 6);
	pcTransaction1->Remove(2LL);
	bResult = pcTransaction1->Get(2LL, szDest);
	AssertBool(FALSE, bResult);
	cTransactionController.EndTransaction(pcTransaction1, TRUE);  //Do commit.  The database must be updated.

	bResult = cTransactionController.mcIndexedData.Get(1LL, szDest);
	AssertBool(TRUE, bResult);
	AssertString(szFZZZJ, szDest);

	bResult = cTransactionController.mcIndexedData.Get(2LL, szDest);
	AssertBool(FALSE, bResult);

	cTransactionController.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTransactionControllerSubTransactions(char* szDirectory, BOOL bDurable)
{
	CFileUtil cFileUtil;

	cFileUtil.RemoveDir(szDirectory);

	CTransactionController	cTransactionController;
	CTransaction*			pcTransaction;
	char					szFourth[7] = "Fourth";
	char					szBlackJack[11] = "Black Jack";
	char					szMuckPuppy[11] = "Muck Puppy";
	char					szElvenLong[11] = "Elven Long";
	char					szHenry[6] = "Henry";
	char					szDeath[6] = "Death";
	char					szBerty[6] = "Berty";
	char					szPalmer[7] = "Palmer";
	char					szDest[11];
	BOOL					bResult;

	cTransactionController.Init(szDirectory, 40, bDurable);
	pcTransaction = cTransactionController.BeginTransaction(TRUE);

	pcTransaction->BeginSubTransaction();
	pcTransaction->BeginSubTransaction();

	AssertInt(3, pcTransaction->mcSubTransactions.NumElements());

	pcTransaction->Add(4LL, szFourth, 7);
	pcTransaction->Add(32LL, szBlackJack, 11);
	pcTransaction->Add(6LL, szHenry, 6);
	pcTransaction->Add(12LL, szPalmer, 7);

	bResult = pcTransaction->Get(6LL, szDest);
	AssertString(szDest, szHenry);
	bResult = pcTransaction->Get(4LL, szDest);
	AssertString(szDest, szFourth);
	bResult = pcTransaction->Get(32LL, szDest);
	AssertString(szDest, szBlackJack);
	bResult = pcTransaction->Get(12LL, szDest);
	AssertString(szDest, szPalmer);

	bResult = pcTransaction->EndSubTransaction(TRUE); //<-- End Sub Transaction
	AssertBool(TRUE, bResult);
	AssertInt(2, pcTransaction->mcSubTransactions.NumElements());

	bResult = pcTransaction->Get(6LL, szDest);
	AssertString(szDest, szHenry);
	bResult = pcTransaction->Get(4LL, szDest);
	AssertBool(TRUE, bResult);
	AssertString(szDest, szFourth);
	bResult = pcTransaction->Get(32LL, szDest);
	AssertString(szDest, szBlackJack);
	bResult = pcTransaction->Get(12LL, szDest);
	AssertString(szDest, szPalmer);

	pcTransaction->Add(5LL, szBerty, 7);
	pcTransaction->Add(1LL, szMuckPuppy, 11);
	bResult = pcTransaction->Remove(4LL);
	AssertBool(TRUE, bResult);
	memset(szDest, 9, 11);
	bResult = pcTransaction->Get(4LL, szDest);
	AssertBool(FALSE, bResult);

	bResult = pcTransaction->EndSubTransaction(TRUE);  //<-- End Sub Transaction
	AssertBool(TRUE, bResult);
	AssertInt(1, pcTransaction->mcSubTransactions.NumElements());

	bResult = pcTransaction->Get(6LL, szDest);
	AssertString(szDest, szHenry);
	bResult = pcTransaction->Get(4LL, szDest);
	AssertBool(FALSE, bResult);
	bResult = pcTransaction->Get(32LL, szDest);
	AssertString(szDest, szBlackJack);
	bResult = pcTransaction->Get(12LL, szDest);
	AssertString(szDest, szPalmer);
	bResult = pcTransaction->Get(5LL, szDest);
	AssertString(szDest, szBerty);
	bResult = pcTransaction->Get(1LL, szDest);
	AssertString(szDest, szMuckPuppy);

	bResult = cTransactionController.EndTransaction(pcTransaction, TRUE);
	AssertBool(TRUE, bResult);

	//Starting second transaction here.
	pcTransaction = cTransactionController.BeginTransaction();
	bResult = pcTransaction->Get(4LL, szDest);
	AssertBool(FALSE, bResult);

	pcTransaction->BeginSubTransaction();
	pcTransaction->Set(6LL, szDeath, 6);
	pcTransaction->Set(32LL, szElvenLong, 11);
	pcTransaction->EndSubTransaction(FALSE);

	bResult = pcTransaction->Get(6LL, szDest);
	AssertString(szHenry, szDest);
	bResult = pcTransaction->Get(32LL, szDest);
	AssertString(szBlackJack, szDest);

	cTransactionController.EndTransaction(pcTransaction, TRUE);

	cTransactionController.mcIndexedData.Get(6LL, szDest);
	AssertString(szHenry, szDest);
	cTransactionController.mcIndexedData.Get(32LL, szDest);
	AssertString(szBlackJack, szDest);
	bResult = cTransactionController.mcIndexedData.Get(4LL, szDest);
	AssertBool(FALSE, bResult);

	cTransactionController.Kill();

	cFileUtil.RemoveDir(szDirectory);

	AssertBool(FALSE, cFileUtil.Exists(szDirectory));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTransactionControllerAddAndRemove(char* szDirectory, BOOL bDurable)
{
	CFileUtil cFileUtil;

	cFileUtil.RemoveDir(szDirectory);

	CTransactionController	cTransactionController;
	CTransaction*			pcTransaction;

	char					szFour[] = "Four";
	char					szTwelve[] = "Twelve";
	char					szDest[7];
	BOOL					bResult;

	cTransactionController.Init(szDirectory, 100, bDurable);  //Used to descriptor cache

	pcTransaction = cTransactionController.BeginTransaction();
	bResult = pcTransaction->Add(0LL, szFour, 5);
	AssertBool(TRUE, bResult);
	bResult = pcTransaction->Remove(0LL);
	AssertBool(TRUE, bResult);
	bResult = pcTransaction->Add(0LL, szTwelve, 7);
	AssertBool(TRUE, bResult);
	memset(szDest, 0, 7);
	bResult = pcTransaction->Get(0LL, szDest);
	AssertBool(TRUE, bResult);
	AssertString(szTwelve, szDest);
	cTransactionController.EndTransaction(pcTransaction, TRUE);

	bResult = cTransactionController.mcIndexedData.Get(0LL, &szDest);
	AssertBool(TRUE, bResult);
	AssertString(szTwelve, szDest);

	pcTransaction = cTransactionController.BeginTransaction();
	pcTransaction->Remove(0LL);
	pcTransaction->Add(0LL, szFour, 5);
	bResult = pcTransaction->Get(0LL, szDest);
	AssertString(szFour, szDest);
	cTransactionController.EndTransaction(pcTransaction, TRUE);

	bResult = cTransactionController.mcIndexedData.Get(0LL, &szDest);
	AssertBool(TRUE, bResult);
	AssertString(szFour, szDest);

	pcTransaction = cTransactionController.BeginTransaction();
	pcTransaction->Remove(0LL);
	bResult = pcTransaction->Get(0LL, szDest);
	AssertBool(FALSE, bResult);
	cTransactionController.EndTransaction(pcTransaction, TRUE);

	bResult = cTransactionController.mcIndexedData.Get(0LL, &szDest);
	AssertBool(FALSE, bResult);

	cTransactionController.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTransactionControllerTimestampFail(char* szDirectory, BOOL bDurable)
{
	CFileUtil cFileUtil;

	cFileUtil.RemoveDir(szDirectory);

	CTransactionController	cTransactionController;
	CTransaction*			pcTransaction1;
	CTransaction*			pcTransaction2;

	char					szFoo[] = "Foo";
	char					szDog[] = "Dog";
	char					szDest[4];
	BOOL					bResult;

	cTransactionController.Init(szDirectory, 100, bDurable);  //Used to descriptor cache

	pcTransaction1 = cTransactionController.BeginTransaction();

	pcTransaction1->Add(17LL, szFoo, 4);

	pcTransaction2 = cTransactionController.BeginTransaction();
	pcTransaction2->Add(17LL, szDog, 4);
	bResult = cTransactionController.EndTransaction(pcTransaction2, TRUE);
	AssertBool(TRUE, bResult);

	bResult = cTransactionController.EndTransaction(pcTransaction1, TRUE);
	AssertBool(FALSE, bResult);

	bResult = cTransactionController.mcIndexedData.Get(17LL, szDest);
	AssertBool(TRUE, bResult);
	AssertString(szDog, szDest);

	cTransactionController.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTransactionController(void)
{
	BeginTests();

	FastFunctionsInit();
	TypeConverterInit();

	TestTransactionControllerWithDurableFile(	"TransactionDatabase1a", TRUE);
	TestTransactionControllerCommit(			"TransactionDatabase2a", TRUE);
	TestTransactionControllerSubTransactions(	"TransactionDatabase3a", TRUE);
	TestTransactionControllerAddAndRemove(		"TransactionDatabase4a", TRUE);
	TestTransactionControllerTimestampFail(		"TransactionDatabase5a", TRUE);

	TestTransactionControllerWithDurableFile(	"TransactionDatabase1b", TRUE);
	TestTransactionControllerCommit(			"TransactionDatabase2b", TRUE);
	TestTransactionControllerSubTransactions(	"TransactionDatabase3b", TRUE);
	TestTransactionControllerAddAndRemove(		"TransactionDatabase4b", TRUE);
	TestTransactionControllerTimestampFail(		"TransactionDatabase5b", TRUE);

	TestTransactionControllerWithDurableFile(	"TransactionDatabase1c", FALSE);
	TestTransactionControllerCommit(			"TransactionDatabase2c", FALSE);
	TestTransactionControllerSubTransactions(	"TransactionDatabase3c", FALSE);
	TestTransactionControllerAddAndRemove(		"TransactionDatabase4c", FALSE);
	TestTransactionControllerTimestampFail(		"TransactionDatabase5c", FALSE);

	FastFunctionsKill();
	TypeConverterKill();

	TestStatistics();
}

