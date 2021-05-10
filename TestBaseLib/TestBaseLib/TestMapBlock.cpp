#include "BaseLib/MapBlock.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/StdRandom.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/LogString.h"
#include "TestLib/Words.h"
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

	cMapBlock.Init(&CompareInt, TRUE);
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
	cMapBlock.Get(&iKey, sizeof(int), (void**)&piData, NULL);
	AssertNotNull(piData);
	AssertInt(43, *piData);

	iKey = 9; piData = NULL;
	cMapBlock.Get(&iKey, sizeof(int), (void**)&piData, NULL);
	AssertNotNull(piData);
	AssertInt(21, *piData);

	iKey = 3; piData = NULL;
	cMapBlock.Get(&iKey, sizeof(int), (void**)&piData, NULL);
	AssertNull(piData);

	cMapBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL AddToMapBlock(CMapBlock* pcMapBlock, char* szKey, long long int lliData)
{
	int				iStrLen;

	iStrLen = strlen(szKey) + 1;
	return pcMapBlock->Put(szKey, iStrLen, &lliData, sizeof(long long int));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL GetFromMapBlock(CMapBlock* pcMapBlock, char* szKey, long long int** pplli, int* piSize)
{
	int				iStrLen;

	iStrLen = strlen(szKey) + 1;
	return pcMapBlock->Get(szKey, iStrLen, (void**)pplli, piSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertMapBlock(CMapBlock* pcMapBlock, char* szKey, long long int lliData)
{
	long long int*	plli;
	int				iStrLen;

	iStrLen = strlen(szKey) + 1;
	pcMapBlock->Get(szKey, iStrLen, (void**)&plli, NULL);
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

	cMapBlock.Init((CompareFunc)&strcmp, TRUE);
	AddToMapBlock(&cMapBlock, "cocker", llia[0]);
	AddToMapBlock(&cMapBlock, "cock", llia[1]);
	AddToMapBlock(&cMapBlock, "cockerel", llia[2]);

	AssertInt(3, cMapBlock.NumElements());
	AssertTrue(GetFromMapBlock(&cMapBlock, "cocker", &plli, &iSize));
	AssertLongLongInt(llia[0], *plli);
	AssertInt(sizeof(long long int), iSize);

	AssertTrue(GetFromMapBlock(&cMapBlock, "cock", &plli, &iSize));
	AssertLongLongInt(llia[1], *plli);
	AssertInt(sizeof(long long int), iSize);

	AssertTrue(GetFromMapBlock(&cMapBlock, "cockerel", &plli, &iSize));
	AssertLongLongInt(llia[2], *plli);

	AddToMapBlock(&cMapBlock, "vizard", llia[3]);
	AddToMapBlock(&cMapBlock, "visard", llia[4]);
	AddToMapBlock(&cMapBlock, "wizard", llia[5]);
	AssertTrue(GetFromMapBlock(&cMapBlock, "vizard", &plli, &iSize));
	AssertLongLongInt(llia[3], *plli);
	AssertTrue(GetFromMapBlock(&cMapBlock, "visard", &plli, &iSize));
	AssertLongLongInt(llia[4], *plli);
	AssertTrue(GetFromMapBlock(&cMapBlock, "wizard", &plli, &iSize));
	AssertLongLongInt(llia[5], *plli);

	AddToMapBlock(&cMapBlock, "repletion", llia[6]);
	AddToMapBlock(&cMapBlock, "ponderous", llia[7]);
	AddToMapBlock(&cMapBlock, "quondam", llia[8]);
	AddToMapBlock(&cMapBlock, "inimical", llia[9]);
	AddToMapBlock(&cMapBlock, "ignominy", llia[10]);
	AssertTrue(GetFromMapBlock(&cMapBlock, "inimical", &plli, &iSize));
	AssertLongLongInt(llia[9], *plli);
	AssertInt(sizeof(long long int), iSize);
	AssertTrue(GetFromMapBlock(&cMapBlock, "cocker", &plli, &iSize));
	AssertLongLongInt(llia[0], *plli);
	AssertInt(sizeof(long long int), iSize);

	AddToMapBlock(&cMapBlock, "voluble", llia[11]);
	AddToMapBlock(&cMapBlock, "intransigent", llia[12]);
	AddToMapBlock(&cMapBlock, "potentate", llia[13]);
	AddToMapBlock(&cMapBlock, "sophist", llia[14]);
	AddToMapBlock(&cMapBlock, "solicitous", llia[15]);
	AssertInt(16, cMapBlock.NumElements());
	AssertTrue(GetFromMapBlock(&cMapBlock, "solicitous", &plli, &iSize));
	AssertLongLongInt(llia[15], *plli);
	AssertInt(sizeof(long long int), iSize);
	AssertTrue(GetFromMapBlock(&cMapBlock, "cock", &plli, &iSize));
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

	cMapBlock.Init(&CompareInt, TRUE);
	bResult = cMapBlock.Put(&ia, sizeof(int), "Hello", iHelloLen + 1);
	AssertTrue(bResult);
	AssertInt(1, cMapBlock.NumElements());
	AssertString("Hello", (char*)cMapBlock.Get(&ia, sizeof(int)));

	bResult = cMapBlock.Put(&ib, sizeof(int), "World", iWorldLen + 1);
	AssertTrue(bResult);
	AssertInt(1, cMapBlock.NumElements());
	AssertString("World", (char*)cMapBlock.Get(&ia, sizeof(int)));

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

	cMapBlock.Init(&CompareInt, TRUE);
	bResult = cMapBlock.Put(&ia, sizeof(int), "Hello", strlen("Hello") + 1);
	bResult = cMapBlock.Put(&ib, sizeof(int), "World", strlen("World") + 1);
	bResult = cMapBlock.Put(&ic, sizeof(int), "Rogue", strlen("Rogue") + 1);
	AssertInt(3, cMapBlock.NumElements());

	cMapBlock.Remove(&ib, sizeof(int));
	AssertInt(2, cMapBlock.NumElements());
	bResult = cMapBlock.Get(&ia, sizeof(int), (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Hello");
	bResult = cMapBlock.Get(&ic, sizeof(int), (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Rogue");
	bResult = cMapBlock.Get(&ib, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);

	cMapBlock.Remove(&ia, sizeof(int));
	AssertInt(1, cMapBlock.NumElements());
	bResult = cMapBlock.Get(&ia, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cMapBlock.Get(&ic, sizeof(int), (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Rogue");
	bResult = cMapBlock.Get(&ib, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);

	cMapBlock.Remove(&ic, sizeof(int));
	AssertInt(0, cMapBlock.NumElements());
	bResult = cMapBlock.Get(&ia, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cMapBlock.Get(&ic, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cMapBlock.Get(&ib, sizeof(int), (void**)&szData, NULL);
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

	mszsz.Init();

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
void MakeKey(CRandom* cRandom, CArrayChars* aszWords, CChars* sz)
{
	int		iIndex;
	char*	szWord;

	iIndex = cRandom->Next(0, aszWords->NumElements() - 1);
	szWord = aszWords->GetText(iIndex);
	sz->Init(szWord)->Append(" ");
	iIndex = cRandom->Next(0, aszWords->NumElements() - 1);
	szWord = aszWords->GetText(iIndex);
	sz->Append(szWord)->Append(" ");
	iIndex = cRandom->Next(0, aszWords->NumElements() - 1);
	szWord = aszWords->GetText(iIndex);
	sz->Append(szWord);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlockDataMemoryUnchanged(void)
{
	CMapStringString	mszsz;
	int					i;
	CRandom				cRandom;
	CArrayChars			aszWords;
	CChars				sz;
	char*				szData;
	char*				aszData[2048];
	BOOL				bFailed;

	WordsInit();

	mszsz.Init();

	cRandom.Init(2367849);
	aszWords.Init();
	GetCommonWords(&aszWords);

	for (i = 0; i < 2048; i++)
	{
		MakeKey(&cRandom, &aszWords, &sz);

		mszsz.Put(sz.Text(), IntToString(i));
		szData = mszsz.Get(sz.Text());
		aszData[i] = szData;

		sz.Kill();
	}
	cRandom.Kill();

	cRandom.Init(2367849);

	bFailed = FALSE;
	for (i = 0; i < 2048; i++)
	{
		MakeKey(&cRandom, &aszWords, &sz);

		szData = mszsz.Get(sz.Text());
		if (aszData[i] != szData)
		{
			bFailed = TRUE;
		}
		sz.Kill();
	}

	AssertFalse(bFailed);
	
	cRandom.Kill();
	mszsz.Kill();

	aszWords.Kill();
	WordsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlockRemoveHalf(void)
{
	CMapStringString	mszsz;
	int					i;
	CRandom				cRandom;
	CArrayChars			aszWords;
	CChars				sz;
	char*				szData;
	char*				aszData[2048];
	BOOL				bResult;
	BOOL				bFailed;

	WordsInit();

	mszsz.Init();

	cRandom.Init(2367849);
	aszWords.Init();
	GetCommonWords(&aszWords);

	for (i = 0; i < 2048; i++)
	{
		MakeKey(&cRandom, &aszWords, &sz);

		mszsz.Put(sz.Text(), IntToString(i));
		szData = mszsz.Get(sz.Text());
		aszData[i] = szData;

		sz.Kill();
	}
	cRandom.Kill();

	cRandom.Init(2367849);
	bResult = TRUE;
	for (i = 0; i < 2048; i++)
	{
		MakeKey(&cRandom, &aszWords, &sz);
		if (i % 2 == 1)
		{
			bResult &= mszsz.Remove(sz.Text());
		}
		sz.Kill();
	}

	AssertTrue(bResult);
	AssertInt(1024, mszsz.NumElements());
	cRandom.Kill();

	bFailed = FALSE;
	cRandom.Init(2367849);
	for (i = 0; i < 2048; i++)
	{
		MakeKey(&cRandom, &aszWords, &sz);
		szData = mszsz.Get(sz.Text());
		if (i % 2 == 0)
		{
			if (aszData[i] != szData)
			{
				bFailed = TRUE;
			}
		}
		else
		{
			if (szData != NULL)
			{
				bFailed = TRUE;
			}
		}
		sz.Kill();
	}
	AssertFalse(bFailed);
	cRandom.Kill();

	mszsz.Kill();

	aszWords.Kill();
	WordsKill();
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
	TestMapBlockDataMemoryUnchanged();
	TestMapBlockRemoveHalf();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}


