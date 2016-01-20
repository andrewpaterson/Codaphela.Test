#include "BaseLib/MapBlock.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/GlobalMemory.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlockInternals(void)
{
	CMapBlock			cMapBlock;
	int					i;
	int					j;
	int					iKey;
	int*				piData;
	CArrayBlockSorted*	paBlock;
	SMNode**			psNode1;
	SMNode**			psNode2;
	int*				piKey;

	cMapBlock.Init(1024, &CompareInt, TRUE);
	i = 7; j = 43;
	cMapBlock.Put(&i, sizeof(int), &j, sizeof(int));

	i = 9; j = 21;
	cMapBlock.Put(&i, sizeof(int), &j, sizeof(int));
	AssertInt(2, cMapBlock.NumElements());

	paBlock = cMapBlock.GetArray();
	paBlock->InsertHoldingIntoSorted();
	psNode1 = (SMNode**)paBlock->GetInSorted(0);
	psNode2 = (SMNode**)paBlock->GetInSorted(1);
	AssertInt(sizeof(int), (*psNode1)->iDataSize);
	AssertInt(sizeof(int), (*psNode1)->iKeySize);
	AssertPointer(&cMapBlock, (*psNode1)->pcMapBlock);
	AssertInt(sizeof(int), (*psNode2)->iDataSize);
	AssertInt(sizeof(int), (*psNode2)->iKeySize);
	AssertPointer(&cMapBlock, (*psNode2)->pcMapBlock);
	piKey = (int*)RemapSinglePointer(*psNode1, sizeof(SMNode));
	AssertInt(7, *piKey);
	piData = (int*)RemapSinglePointer(piKey, (int)sizeof(int));
	AssertInt(43, *piData);
	piKey = (int*)RemapSinglePointer(*psNode2, sizeof(SMNode));
	AssertInt(9, *piKey);
	piData = (int*)RemapSinglePointer(piKey, (int)sizeof(int));
	AssertInt(21, *piData);

	iKey = 7; piData = NULL;
	cMapBlock.Get(&iKey, (void**)&piData, NULL);
	AssertNotNull(piData);
	AssertInt(43, *piData);

	iKey = 9; piData = NULL;
	cMapBlock.Get(&iKey, (void**)&piData, NULL);
	AssertNotNull(piData);
	AssertInt(21, *piData);

	iKey = 3; piData = NULL;
	cMapBlock.Get(&iKey, (void**)&piData, NULL);
	AssertNull(piData);

	cMapBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL AddToMapBlock(CMapBlock* pcMapBlock, char* szKey, long long int lliData)
{
	return pcMapBlock->Put(szKey, strlen(szKey) +1 , &lliData, sizeof(long long int));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertMapBlock(CMapBlock* pcMapBlock, char* szKey, long long int lliData)
{
	long long int*	plli;

	pcMapBlock->Get(szKey, (void**)&plli, NULL);
	AssertLongLongInt(lliData, *plli);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlockGet(void)
{
	CMapBlock		cMapBlock;
	long long int	llia[64];
	int				i;
	long long int	lli;
	long long int*	plli;
	int				iSize;

	lli = 0x886c857864030e05;
	for (i = 0; i < 64; i++)
	{
		llia[i] = lli;
		lli = ((lli + 0x336b265cfdd8a7a6) / 2) * 3;
	}

	cMapBlock.Init(16, (CompareFunc)&strcmp, TRUE);
	AddToMapBlock(&cMapBlock, "cocker", llia[0]);
	AddToMapBlock(&cMapBlock, "cock", llia[1]);
	AddToMapBlock(&cMapBlock, "cockerel", llia[2]);

	AssertInt(3, cMapBlock.NumElements());
	AssertTrue(cMapBlock.Get("cocker", (void**)&plli, &iSize));
	AssertLongLongInt(llia[0], *plli);
	AssertInt(sizeof(long long int), iSize);

	AssertTrue(cMapBlock.Get("cock", (void**)&plli, &iSize));
	AssertLongLongInt(llia[1], *plli);
	AssertInt(sizeof(long long int), iSize);

	AssertTrue(cMapBlock.Get("cockerel", (void**)&plli, &iSize));
	AssertLongLongInt(llia[2], *plli);

	AddToMapBlock(&cMapBlock, "vizard", llia[3]);
	AddToMapBlock(&cMapBlock, "visard", llia[4]);
	AddToMapBlock(&cMapBlock, "wizard", llia[5]);
	AssertTrue(cMapBlock.Get("vizard", (void**)&plli, &iSize));
	AssertLongLongInt(llia[3], *plli);
	AssertTrue(cMapBlock.Get("visard", (void**)&plli, &iSize));
	AssertLongLongInt(llia[4], *plli);
	AssertTrue(cMapBlock.Get("wizard", (void**)&plli, &iSize));
	AssertLongLongInt(llia[5], *plli);

	AddToMapBlock(&cMapBlock, "repletion", llia[6]);
	AddToMapBlock(&cMapBlock, "ponderous", llia[7]);
	AddToMapBlock(&cMapBlock, "quondam", llia[8]);
	AddToMapBlock(&cMapBlock, "inimical", llia[9]);
	AddToMapBlock(&cMapBlock, "ignominy", llia[10]);
	AssertTrue(cMapBlock.Get("inimical", (void**)&plli, &iSize));
	AssertLongLongInt(llia[9], *plli);
	AssertInt(sizeof(long long int), iSize);
	AssertTrue(cMapBlock.Get("cocker", (void**)&plli, &iSize));
	AssertLongLongInt(llia[0], *plli);
	AssertInt(sizeof(long long int), iSize);

	AddToMapBlock(&cMapBlock, "voluble", llia[11]);
	AddToMapBlock(&cMapBlock, "intransigent", llia[12]);
	AddToMapBlock(&cMapBlock, "potentate", llia[13]);
	AddToMapBlock(&cMapBlock, "sophist", llia[14]);
	AddToMapBlock(&cMapBlock, "solicitous", llia[15]);
	AssertInt(16, cMapBlock.NumElements());
	AssertTrue(cMapBlock.Get("solicitous", (void**)&plli, &iSize));
	AssertLongLongInt(llia[15], *plli);
	AssertInt(sizeof(long long int), iSize);
	AssertTrue(cMapBlock.Get("cock", (void**)&plli, &iSize));
	AssertLongLongInt(llia[1], *plli);
	AssertInt(sizeof(long long int), iSize);

	AddToMapBlock(&cMapBlock, "resplendent", llia[16]);
	AssertInt(17, cMapBlock.NumElements());

	AssertMapBlock(&cMapBlock, "cocker", llia[0]);
	AssertMapBlock(&cMapBlock, "cock", llia[1]);
	AssertMapBlock(&cMapBlock, "cockerel", llia[2]);
	AssertMapBlock(&cMapBlock, "vizard", llia[3]);
	AssertMapBlock(&cMapBlock, "visard", llia[4]);
	AssertMapBlock(&cMapBlock, "wizard", llia[5]);
	AssertMapBlock(&cMapBlock, "voluble", llia[11]);
	AssertMapBlock(&cMapBlock, "intransigent", llia[12]);
	AssertMapBlock(&cMapBlock, "potentate", llia[13]);
	AssertMapBlock(&cMapBlock, "sophist", llia[14]);
	AssertMapBlock(&cMapBlock, "solicitous", llia[15]);
	AssertMapBlock(&cMapBlock, "repletion", llia[6]);
	AssertMapBlock(&cMapBlock, "ponderous", llia[7]);
	AssertMapBlock(&cMapBlock, "quondam", llia[8]);
	AssertMapBlock(&cMapBlock, "inimical", llia[9]);
	AssertMapBlock(&cMapBlock, "ignominy", llia[10]);
	AssertMapBlock(&cMapBlock, "resplendent", llia[16]);

	cMapBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlockAddDuplicate(void)
{
	CMapBlock	cMapBlock;
	int			ia = 'a';
	int			ib = 'a';
	BOOL		bResult;
	int			iWorldLen;
	int			iHelloLen;

	iWorldLen = strlen("World");
	iHelloLen = strlen("Hello");

	cMapBlock.Init(1024, &CompareInt, TRUE);
	bResult = cMapBlock.Put(&ia, sizeof(int), "Hello", iHelloLen + 1);
	AssertTrue(bResult);
	AssertInt(1, cMapBlock.NumElements());
	AssertString("Hello", (char*)cMapBlock.Get(&ia));

	bResult = cMapBlock.Put(&ib, sizeof(int), "World", iWorldLen + 1);
	AssertTrue(bResult);
	AssertInt(1, cMapBlock.NumElements());
	AssertString("World", (char*)cMapBlock.Get(&ia));

	cMapBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlockRemove(void)
{
	CMapBlock	cMapBlock;
	int			ia = 'a';
	int			ib = 'b';
	int			ic = 'c';
	BOOL		bResult;
	char*		szData;

	cMapBlock.Init(1024, &CompareInt, TRUE);
	bResult = cMapBlock.Put(&ia, sizeof(int), "Hello", strlen("Hello") + 1);
	bResult = cMapBlock.Put(&ib, sizeof(int), "World", strlen("World") + 1);
	bResult = cMapBlock.Put(&ic, sizeof(int), "Rogue", strlen("Rogue") + 1);
	AssertInt(3, cMapBlock.NumElements());

	cMapBlock.Remove(&ib);
	AssertInt(2, cMapBlock.NumElements());
	bResult = cMapBlock.Get(&ia, (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Hello");
	bResult = cMapBlock.Get(&ic, (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Rogue");
	bResult = cMapBlock.Get(&ib, (void**)&szData, NULL);
	AssertFalse(bResult);

	cMapBlock.Remove(&ia);
	AssertInt(1, cMapBlock.NumElements());
	bResult = cMapBlock.Get(&ia, (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cMapBlock.Get(&ic, (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Rogue");
	bResult = cMapBlock.Get(&ib, (void**)&szData, NULL);
	AssertFalse(bResult);

	cMapBlock.Remove(&ic);
	AssertInt(0, cMapBlock.NumElements());
	bResult = cMapBlock.Get(&ia, (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cMapBlock.Get(&ic, (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cMapBlock.Get(&ib, (void**)&szData, NULL);
	AssertFalse(bResult);

	cMapBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlockReadWrite(void)
{
	CMapStringString	mszsz;
	CFileBasic			cFile;
	CMapStringString	mszszIn;

	mszsz.Init(16);

	mszsz.Put("ABC", "XYZ");
	mszsz.Put("Collision", "Detection");
	mszsz.Put("Retro", "Evolved");
	mszsz.Put("Blame", "Canada");

	AssertString("XYZ", mszsz.Get("ABC"));
	AssertString("Detection", mszsz.Get("Collision"));
	AssertString("Evolved", mszsz.Get("Retro"));
	AssertString("Canada", mszsz.Get("Blame"));

	cFile.Init(MemoryFile());
	cFile.Open(EFM_Write_Create);
	AssertTrue(mszsz.Write(&cFile));
	mszsz.Kill();

	cFile.Close();
	cFile.Open(EFM_Read);

	AssertTrue(mszszIn.Read(&cFile));

	AssertString("XYZ", mszszIn.Get("ABC"));
	AssertString("Detection", mszszIn.Get("Collision"));
	AssertString("Evolved", mszszIn.Get("Retro"));
	AssertString("Canada", mszszIn.Get("Blame"));

	mszszIn.Kill();
	cFile.Close();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlock(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestMapBlockInternals();
	TestMapBlockGet();
	TestMapBlockAddDuplicate();
	TestMapBlockRemove();
	TestMapBlockReadWrite();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

