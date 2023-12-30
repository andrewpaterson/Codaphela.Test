#include "BaseLib/MapBlock.h"
#include "BaseLib/MapIndexAccess.h"
#include "BaseLib/MapMapAccess.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/CountingAllocator.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/StdRandom.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/LogString.h"
#include "TestLib/Words.h"
#include "TestLib/Assert.h"
#include "TestMap.h"


class CTestMapBlock : public CMapBlock
{
public:
	SMNode* GetNode(void* pvKey, int iKeySize)
	{
		return CMapBlock::GetNode(pvKey, iKeySize);
	}
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlockInternals(void)
{
	CMapBlock			cMap;
	int					i;
	int					j;
	int					iKey;
	int*				piData;
	CArrayBlockSorted*	paBlock;
	SMNode**			psNode1;
	SMNode**			psNode2;
	int*				piKey;

	cMap.Init(&CompareInt, true);
	i = 7; j = 43;
	cMap.Put(&i, sizeof(int), &j, sizeof(int));

	i = 9; j = 21;
	cMap.Put(&i, sizeof(int), &j, sizeof(int));
	AssertInt(2, cMap.NumElements());

	paBlock = cMap.GetArray();
	paBlock->InsertHoldingIntoSorted();
	psNode1 = (SMNode**)paBlock->GetInSorted(0);
	psNode2 = (SMNode**)paBlock->GetInSorted(1);
	AssertInt(sizeof(int), (*psNode1)->iDataSize);
	AssertInt(sizeof(int), (*psNode1)->iKeySize);
	AssertInt(sizeof(int), (*psNode2)->iDataSize);
	AssertInt(sizeof(int), (*psNode2)->iKeySize);
	piKey = (int*)RemapSinglePointer(*psNode1, sizeof(SMNode));
	AssertInt(7, *piKey);
	piData = (int*)RemapSinglePointer(piKey, (int)sizeof(int));
	AssertInt(43, *piData);
	piKey = (int*)RemapSinglePointer(*psNode2, sizeof(SMNode));
	AssertInt(9, *piKey);
	piData = (int*)RemapSinglePointer(piKey, (int)sizeof(int));
	AssertInt(21, *piData);

	iKey = 7; piData = NULL;
	cMap.Get(&iKey, sizeof(int), (void**)&piData, NULL);
	AssertNotNull(piData);
	AssertInt(43, *piData);

	iKey = 9; piData = NULL;
	cMap.Get(&iKey, sizeof(int), (void**)&piData, NULL);
	AssertNotNull(piData);
	AssertInt(21, *piData);

	iKey = 3; piData = NULL;
	cMap.Get(&iKey, sizeof(int), (void**)&piData, NULL);
	AssertNull(piData);

	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool AddToMapBlock(CMapBlock* pcMapBlock, char* szKey, int64_t lliData)
{
	int				iStrLen;

	iStrLen = strlen(szKey) + 1;
	return pcMapBlock->Put(szKey, iStrLen, &lliData, sizeof(int64_t));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool GetFromMapBlock(CMapBlock* pcMapBlock, char* szKey, int64_t** pplli, int* piSize)
{
	int				iStrLen;

	iStrLen = strlen(szKey) + 1;
	return pcMapBlock->Get(szKey, iStrLen, (void**)pplli, piSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertMapBlock(CMapBlock* pcMapBlock, char* szKey, int64_t lliData)
{
	int64_t*	plli;
	int				iStrLen;

	plli = NULL;
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
	CMapBlock		cMap;
	int64_t	llia[64];
	int				i;
	int64_t	lli;
	int64_t*	plli;
	int				iSize;

	lli = 0x886c857864030e05;
	for (i = 0; i < 64; i++)
	{
		llia[i] = lli;
		lli = ((lli + 0x336b265cfdd8a7a6) / 2) * 3;
	}

	cMap.Init((DataCompare)&StringCompare, true);
	AddToMapBlock(&cMap, "cocker", llia[0]);
	AddToMapBlock(&cMap, "cock", llia[1]);
	AddToMapBlock(&cMap, "cockerel", llia[2]);

	AssertInt(3, cMap.NumElements());
	AssertTrue(GetFromMapBlock(&cMap, "cocker", &plli, &iSize));
	AssertLongLongInt(llia[0], *plli);
	AssertInt(sizeof(int64_t), iSize);

	AssertTrue(GetFromMapBlock(&cMap, "cock", &plli, &iSize));
	AssertLongLongInt(llia[1], *plli);
	AssertInt(sizeof(int64_t), iSize);

	AssertTrue(GetFromMapBlock(&cMap, "cockerel", &plli, &iSize));
	AssertLongLongInt(llia[2], *plli);

	AddToMapBlock(&cMap, "vizard", llia[3]);
	AddToMapBlock(&cMap, "visard", llia[4]);
	AddToMapBlock(&cMap, "wizard", llia[5]);
	AssertTrue(GetFromMapBlock(&cMap, "vizard", &plli, &iSize));
	AssertLongLongInt(llia[3], *plli);
	AssertTrue(GetFromMapBlock(&cMap, "visard", &plli, &iSize));
	AssertLongLongInt(llia[4], *plli);
	AssertTrue(GetFromMapBlock(&cMap, "wizard", &plli, &iSize));
	AssertLongLongInt(llia[5], *plli);

	AddToMapBlock(&cMap, "repletion", llia[6]);
	AddToMapBlock(&cMap, "ponderous", llia[7]);
	AddToMapBlock(&cMap, "quondam", llia[8]);
	AddToMapBlock(&cMap, "inimical", llia[9]);
	AddToMapBlock(&cMap, "ignominy", llia[10]);
	AssertTrue(GetFromMapBlock(&cMap, "inimical", &plli, &iSize));
	AssertLongLongInt(llia[9], *plli);
	AssertInt(sizeof(int64_t), iSize);
	AssertTrue(GetFromMapBlock(&cMap, "cocker", &plli, &iSize));
	AssertLongLongInt(llia[0], *plli);
	AssertInt(sizeof(int64_t), iSize);

	AddToMapBlock(&cMap, "voluble", llia[11]);
	AddToMapBlock(&cMap, "intransigent", llia[12]);
	AddToMapBlock(&cMap, "potentate", llia[13]);
	AddToMapBlock(&cMap, "sophist", llia[14]);
	AddToMapBlock(&cMap, "solicitous", llia[15]);
	AssertInt(16, cMap.NumElements());
	AssertTrue(GetFromMapBlock(&cMap, "solicitous", &plli, &iSize));
	AssertLongLongInt(llia[15], *plli);
	AssertInt(sizeof(int64_t), iSize);
	AssertTrue(GetFromMapBlock(&cMap, "cock", &plli, &iSize));
	AssertLongLongInt(llia[1], *plli);
	AssertInt(sizeof(int64_t), iSize);

	AddToMapBlock(&cMap, "resplendent", llia[16]);
	AssertInt(17, cMap.NumElements());

	AssertMapBlock(&cMap, "cocker", llia[0]);
	AssertMapBlock(&cMap, "cock", llia[1]);
	AssertMapBlock(&cMap, "cockerel", llia[2]);
	AssertMapBlock(&cMap, "vizard", llia[3]);
	AssertMapBlock(&cMap, "visard", llia[4]);
	AssertMapBlock(&cMap, "wizard", llia[5]);
	AssertMapBlock(&cMap, "voluble", llia[11]);
	AssertMapBlock(&cMap, "intransigent", llia[12]);
	AssertMapBlock(&cMap, "potentate", llia[13]);
	AssertMapBlock(&cMap, "sophist", llia[14]);
	AssertMapBlock(&cMap, "solicitous", llia[15]);
	AssertMapBlock(&cMap, "repletion", llia[6]);
	AssertMapBlock(&cMap, "ponderous", llia[7]);
	AssertMapBlock(&cMap, "quondam", llia[8]);
	AssertMapBlock(&cMap, "inimical", llia[9]);
	AssertMapBlock(&cMap, "ignominy", llia[10]);
	AssertMapBlock(&cMap, "resplendent", llia[16]);

	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlockAddDuplicate(void)
{
	CMapBlock	cMap;
	int			ia = 'a';
	int			ib = 'a';
	bool		bResult;
	int			iWorldLen;
	int			iHelloLen;

	iWorldLen = strlen("World");
	iHelloLen = strlen("Hello");

	cMap.Init(&CompareInt, true);
	bResult = cMap.Put(&ia, sizeof(int), "Hello", iHelloLen + 1);
	AssertTrue(bResult);
	AssertInt(1, cMap.NumElements());
	AssertString("Hello", (char*)cMap.Get(&ia, sizeof(int)));

	bResult = cMap.Put(&ib, sizeof(int), "World", iWorldLen + 1);
	AssertTrue(bResult);
	AssertInt(1, cMap.NumElements());
	AssertString("World", (char*)cMap.Get(&ia, sizeof(int)));

	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlockRemove(void)
{
	CMapBlock	cMap;
	int			ia = 'a';
	int			ib = 'b';
	int			ic = 'c';
	bool		bResult;
	char*		szData;

	cMap.Init(&CompareInt, true);
	bResult = cMap.Put(&ia, sizeof(int), "Hello", strlen("Hello") + 1);
	bResult = cMap.Put(&ib, sizeof(int), "World", strlen("World") + 1);
	bResult = cMap.Put(&ic, sizeof(int), "Rogue", strlen("Rogue") + 1);
	AssertInt(3, cMap.NumElements());

	cMap.Remove(&ib, sizeof(int));
	AssertInt(2, cMap.NumElements());
	bResult = cMap.Get(&ia, sizeof(int), (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Hello");
	bResult = cMap.Get(&ic, sizeof(int), (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Rogue");
	bResult = cMap.Get(&ib, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);

	cMap.Remove(&ia, sizeof(int));
	AssertInt(1, cMap.NumElements());
	bResult = cMap.Get(&ia, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cMap.Get(&ic, sizeof(int), (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Rogue");
	bResult = cMap.Get(&ib, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);

	cMap.Remove(&ic, sizeof(int));
	AssertInt(0, cMap.NumElements());
	bResult = cMap.Get(&ia, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cMap.Get(&ic, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cMap.Get(&ib, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);

	cMap.Kill();
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
void TestMapBlockDataMemoryUnchanged(void)
{
	CMapStringString	mszsz;
	int					i;
	CRandom				cRandom;
	CArrayChars			aszWords;
	CChars				sz;
	char*				szData;
	char*				aszData[2048];
	bool				bFailed;

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

	bFailed = false;
	for (i = 0; i < 2048; i++)
	{
		MakeKey(&cRandom, &aszWords, &sz);

		szData = mszsz.Get(sz.Text());
		if (aszData[i] != szData)
		{
			bFailed = true;
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
	bool				bResult;
	bool				bFailed;

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
	bResult = true;
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

	bFailed = false;
	cRandom.Init(2367849);
	for (i = 0; i < 2048; i++)
	{
		MakeKey(&cRandom, &aszWords, &sz);
		szData = mszsz.Get(sz.Text());
		if (i % 2 == 0)
		{
			if (aszData[i] != szData)
			{
				bFailed = true;
			}
		}
		else
		{
			if (szData != NULL)
			{
				bFailed = true;
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
void TestMapBlockPutDifferenceSizeDuplicates(void)
{
	CTestMapBlock			cIndex;
	CMapIndexAccess			cAccess;
	char					szOne[] = "1";
	char					szTwo[] = "22";
	char					szOtherTwo[] = "OT";
	char					szThree[] = "333";
	char					szKerfuffle[] = "kerfuffle";
	CCountingAllocator		cAllocator;
	int						iKeyLength;
	char					szResult[256];
	SMNode*					pcNode;

	cAllocator.Init(&gcSystemAllocator);
	AssertInt(0, cAllocator.AllocatedUserSize());

	cIndex.Init(&cAllocator);
	cAccess.Init(&cIndex);
	AssertInt(0, cIndex.NumElements());
	AssertInt(cAllocator.AllocatedUserSize(), cIndex.ByteSize());

	iKeyLength = strlen("Spoedling");
	AssertNull(cIndex.GetNode("Spoedling", iKeyLength));

	AssertTrue(cAccess.PutStringData("SpoedlingZ", szKerfuffle, 10));
	AssertInt(1, cIndex.NumElements());

	//AssertInt(cAllocator.AllocatedUserSize(), cIndex.ByteSize());
	pcNode = cIndex.GetNode("Spoedling", iKeyLength);
	AssertNull(pcNode);
	pcNode = cIndex.GetNode("SpoedlingZ", iKeyLength + 1);
	AssertNotNull(pcNode);

	AssertTrue(cAccess.PutStringData("Spoedling", szTwo, 3));
	AssertInt(2, cIndex.NumElements());
	//AssertInt(cAllocator.AllocatedUserSize(), cIndex.ByteSize());
	AssertString("kerfuffle", cAccess.GetStringString("SpoedlingZ", szResult));
	AssertString("22", cAccess.GetStringString("Spoedling", szResult));

	pcNode = cIndex.GetNode("Spoedling", iKeyLength);
	AssertNotNull(pcNode);

	AssertTrue(cAccess.PutStringData("Spoedling", szOtherTwo, 3));
	AssertInt(2, cIndex.NumElements());
	//AssertInt(cAllocator.AllocatedUserSize(), cIndex.ByteSize());
	AssertString("kerfuffle", cAccess.GetStringString("SpoedlingZ", szResult));
	AssertString("OT", cAccess.GetStringString("Spoedling", szResult));

	pcNode = cIndex.GetNode("Spoedling", iKeyLength);
	AssertNotNull(pcNode);

	AssertTrue(cAccess.PutStringData("Spoedling", szThree, 4));
	AssertInt(2, cIndex.NumElements());
	//AssertInt(cAllocator.AllocatedUserSize(), cIndex.ByteSize());
	AssertString("kerfuffle", cAccess.GetStringString("SpoedlingZ", szResult));
	AssertString("333", cAccess.GetStringString("Spoedling", szResult));

	pcNode = cIndex.GetNode("Spoedling", iKeyLength);
	AssertNotNull(pcNode);

	AssertTrue(cAccess.PutStringData("Spoedling", szOne, 2));
	AssertInt(2, cIndex.NumElements());
	//AssertInt(cAllocator.AllocatedUserSize(), cIndex.ByteSize());
	AssertString("kerfuffle", cAccess.GetStringString("SpoedlingZ", szResult));
	AssertString("1", cAccess.GetStringString("Spoedling", szResult));

	pcNode = cIndex.GetNode("Spoedling", iKeyLength);
	AssertNotNull(pcNode);

	cAccess.Kill();
	cIndex.Kill();
	AssertInt(0, cAllocator.AllocatedUserSize());
}


char	gszMapBlockCallbackData[64];
int		giMapBlockCallbackData = 0;

void TestMapBlockDataFreeCallback(const void* pvData)
{
	memset(gszMapBlockCallbackData, 0, 64);
	strcpy(gszMapBlockCallbackData, (char*)pvData);
	giMapBlockCallbackData++;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlockDataFree(void)
{
	CMapBlock			cMap;
	CMapMapAccess		cAccess;
	CDataFreeCallBack	cDataFree;

	giMapBlockCallbackData = 0;

	cMap.Init(&CompareInt, true);
	cDataFree.Init(TestMapBlockDataFreeCallback);
	cMap.SetDataFreeCallback(&cDataFree);
	cAccess.Init(&cMap);

	TestMapBlockDataFreeCallback("");
	AssertInt(1, giMapBlockCallbackData);
	cAccess.PutIntString(7, "Jimmy!");
	AssertString("", gszMapBlockCallbackData);
	AssertInt(1, giMapBlockCallbackData);
	cAccess.DeleteInt(7);
	AssertString("Jimmy!", gszMapBlockCallbackData);
	AssertInt(2, giMapBlockCallbackData);

	memset(gszMapBlockCallbackData, 0, 64);
	cAccess.PutIntString(7, "Jimmy's not gone.");
	AssertString("", gszMapBlockCallbackData);
	cAccess.PutIntString(7, "Oh, never mind.");
	AssertString("Jimmy's not gone.", gszMapBlockCallbackData);
	AssertInt(3, giMapBlockCallbackData);

	memset(gszMapBlockCallbackData, 0, 64);
	cAccess.PutIntString(7, "Jimmy is Back!!");
	AssertString("Oh, never mind.", gszMapBlockCallbackData);     
	AssertInt(4, giMapBlockCallbackData);

	cAccess.Kill();
	cMap.Kill();

	AssertInt(5, giMapBlockCallbackData);
	AssertString("Jimmy is Back!!", gszMapBlockCallbackData);
}


char* TestMapCopyKey(char* szDest, char* pvKey, int iKeySize)
{
	memcpy(szDest, pvKey, iKeySize);
	szDest[iKeySize] = '\0';
	return szDest;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlockIterate(void)
{
	CMapMapAccess		cAccess;
	CMapBlock			cMap;
	CFileBasic			cFile;
	CMapBlock			cMapIn;
	SMapIterator		sIter;
	char*				pvData;
	int					iDataSize;
	char*				pvKey;
	int					iKeySize;
	bool				bExists;
	char				acKey[MAX_KEY_SIZE];

	cMap.Init();
	cAccess.Init(&cMap);

	cAccess.PutStringString("ABC", "XYZ");
	cAccess.PutStringString("Collision", "Detection");
	cAccess.PutStringString("Retro", "Evolved");
	cAccess.PutStringString("Blame", "Canada");

	cFile.Init(MemoryFile());
	cFile.Open(EFM_Write_Create);
	AssertTrue(cMap.Write(&cFile));

	bExists = cMap.StartIteration(&sIter, (void**)&pvKey, &iKeySize, (void**)&pvData, &iDataSize);
	AssertTrue(bExists);
	TestMapCopyKey(acKey, pvKey, iKeySize);
	AssertString("ABC", acKey);
	AssertString("XYZ", pvData);
	AssertInt(3, iKeySize);
	AssertInt(4, iDataSize);
	bExists = cMap.Iterate(&sIter, (void**)&pvKey, &iKeySize, (void**)&pvData, &iDataSize);
	AssertTrue(bExists);
	TestMapCopyKey(acKey, pvKey, iKeySize);
	AssertString("Blame", acKey);
	AssertString("Canada", pvData);
	AssertInt(5, iKeySize);
	AssertInt(7, iDataSize);
	bExists = cMap.Iterate(&sIter, (void**)&pvKey, &iKeySize, (void**)&pvData, &iDataSize);
	AssertTrue(bExists);
	TestMapCopyKey(acKey, pvKey, iKeySize);
	AssertString("Collision", acKey);
	AssertString("Detection", pvData);
	AssertInt(9, iKeySize);
	AssertInt(10, iDataSize);
	bExists = cMap.Iterate(&sIter, (void**)&pvKey, &iKeySize, (void**)&pvData, &iDataSize);
	AssertTrue(bExists);
	TestMapCopyKey(acKey, pvKey, iKeySize);
	AssertString("Retro", acKey);
	AssertString("Evolved", pvData);
	AssertInt(5, iKeySize);
	AssertInt(8, iDataSize);
	bExists = cMap.Iterate(&sIter, (void**)&pvKey, &iKeySize, (void**)&pvData, &iDataSize);
	AssertFalse(bExists);

	cAccess.Kill();
	cMap.Kill();

	cFile.Close();
	cFile.Open(EFM_Read);

	AssertTrue(cMapIn.Read(&cFile));
	cAccess.Init(&cMapIn);

	bExists = cMapIn.StartIteration(&sIter, (void**)&pvKey, &iKeySize, (void**)&pvData, &iDataSize);
	AssertTrue(bExists);
	TestMapCopyKey(acKey, pvKey, iKeySize);
	AssertString("ABC", acKey);
	AssertString("XYZ", pvData);
	AssertInt(3, iKeySize);
	AssertInt(4, iDataSize);
	bExists = cMapIn.Iterate(&sIter, (void**)&pvKey, &iKeySize, (void**)&pvData, &iDataSize);
	AssertTrue(bExists);
	TestMapCopyKey(acKey, pvKey, iKeySize);
	AssertString("Blame", acKey);
	AssertString("Canada", pvData);
	AssertInt(5, iKeySize);
	AssertInt(7, iDataSize);
	bExists = cMapIn.Iterate(&sIter, (void**)&pvKey, &iKeySize, (void**)&pvData, &iDataSize);
	AssertTrue(bExists);
	TestMapCopyKey(acKey, pvKey, iKeySize);
	AssertString("Collision", acKey);
	AssertString("Detection", pvData);
	AssertInt(9, iKeySize);
	AssertInt(10, iDataSize);
	bExists = cMapIn.Iterate(&sIter, (void**)&pvKey, &iKeySize, (void**)&pvData, &iDataSize);
	AssertTrue(bExists);
	TestMapCopyKey(acKey, pvKey, iKeySize);
	AssertString("Retro", acKey);
	AssertString("Evolved", pvData);
	AssertInt(5, iKeySize);
	AssertInt(8, iDataSize);
	bExists = cMapIn.Iterate(&sIter, (void**)&pvKey, &iKeySize, (void**)&pvData, &iDataSize);
	AssertFalse(bExists);

	cMapIn.Kill();
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
	TestMapBlockDataMemoryUnchanged();
	TestMapBlockRemoveHalf();
	TestMapBlockPutDifferenceSizeDuplicates();
	TestMapBlockDataFree();
	TestMapBlockIterate();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

