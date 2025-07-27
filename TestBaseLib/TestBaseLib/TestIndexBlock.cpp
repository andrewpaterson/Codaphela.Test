#include "BaseLib/IndexBlock.h"
#include "BaseLib/IndexMapAccess.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/CountingAllocator.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/StdRandom.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/LogString.h"
#include "BaseLib/LocalMallocatorConstructors.h"
#include "BaseLib/DataOrderers.h"
#include "TestLib/Words.h"
#include "TestLib/Assert.h"
#include "TestMap.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool AddToIndexBlock(CIndexBlock* pcIndexBlock, char* szKey, int64 lliData)
{
	size				iStrLen;

	iStrLen = strlen(szKey) + 1;
	return pcIndexBlock->Put((uint8*)szKey, iStrLen, &lliData, sizeof(int64));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool GetFromIndexBlock(CIndexBlock* pcIndexBlock, char* szKey, int64** pplli, size* piSize)
{
	size				iStrLen;

	iStrLen = strlen(szKey) + 1;
	return pcIndexBlock->Get((uint8*)szKey, iStrLen, (void**)pplli, piSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertIndexBlock(CIndexBlock* pcIndexBlock, char* szKey, int64 lliData)
{
	int64*	plli;
	size				iStrLen;

	plli = NULL;
	iStrLen = strlen(szKey) + 1;
	pcIndexBlock->Get((uint8*)szKey, iStrLen, (void**)&plli, NULL);
	AssertLong(lliData, *plli);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexBlockGet(void)
{
	CIndexBlock		cIndexBlock;
	int64			llia[64];
	size			i;
	int64			lli;
	int64*			plli;
	size			iSize;

	lli = 0x886c857864030e05;
	for (i = 0; i < 64; i++)
	{
		llia[i] = lli;
		lli = ((lli + 0x336b265cfdd8a7a6) / 2) * 3;
	}

	cIndexBlock.Init();
	AddToIndexBlock(&cIndexBlock, "cocker", llia[0]);
	AddToIndexBlock(&cIndexBlock, "cock", llia[1]);
	AddToIndexBlock(&cIndexBlock, "cockerel", llia[2]);

	AssertInt(3, cIndexBlock.NumElements());
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "cocker", &plli, &iSize));
	AssertLong(llia[0], *plli);
	AssertInt(sizeof(int64), iSize);

	AssertTrue(GetFromIndexBlock(&cIndexBlock, "cock", &plli, &iSize));
	AssertLong(llia[1], *plli);
	AssertInt(sizeof(int64), iSize);

	AssertTrue(GetFromIndexBlock(&cIndexBlock, "cockerel", &plli, &iSize));
	AssertLong(llia[2], *plli);

	AddToIndexBlock(&cIndexBlock, "vizard", llia[3]);
	AddToIndexBlock(&cIndexBlock, "visard", llia[4]);
	AddToIndexBlock(&cIndexBlock, "wizard", llia[5]);
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "vizard", &plli, &iSize));
	AssertLong(llia[3], *plli);
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "visard", &plli, &iSize));
	AssertLong(llia[4], *plli);
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "wizard", &plli, &iSize));
	AssertLong(llia[5], *plli);

	AddToIndexBlock(&cIndexBlock, "repletion", llia[6]);
	AddToIndexBlock(&cIndexBlock, "ponderous", llia[7]);
	AddToIndexBlock(&cIndexBlock, "quondam", llia[8]);
	AddToIndexBlock(&cIndexBlock, "inimical", llia[9]);
	AddToIndexBlock(&cIndexBlock, "ignominy", llia[10]);
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "inimical", &plli, &iSize));
	AssertLong(llia[9], *plli);
	AssertInt(sizeof(int64), iSize);
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "cocker", &plli, &iSize));
	AssertLong(llia[0], *plli);
	AssertInt(sizeof(int64), iSize);

	AddToIndexBlock(&cIndexBlock, "voluble", llia[11]);
	AddToIndexBlock(&cIndexBlock, "intransigent", llia[12]);
	AddToIndexBlock(&cIndexBlock, "potentate", llia[13]);
	AddToIndexBlock(&cIndexBlock, "sophist", llia[14]);
	AddToIndexBlock(&cIndexBlock, "solicitous", llia[15]);
	AssertInt(16, cIndexBlock.NumElements());
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "solicitous", &plli, &iSize));
	AssertLong(llia[15], *plli);
	AssertInt(sizeof(int64), iSize);
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "cock", &plli, &iSize));
	AssertLong(llia[1], *plli);
	AssertInt(sizeof(int64), iSize);

	AddToIndexBlock(&cIndexBlock, "resplendent", llia[16]);
	AssertInt(17, cIndexBlock.NumElements());

	AssertIndexBlock(&cIndexBlock, "cocker", llia[0]);
	AssertIndexBlock(&cIndexBlock, "cock", llia[1]);
	AssertIndexBlock(&cIndexBlock, "cockerel", llia[2]);
	AssertIndexBlock(&cIndexBlock, "vizard", llia[3]);
	AssertIndexBlock(&cIndexBlock, "visard", llia[4]);
	AssertIndexBlock(&cIndexBlock, "wizard", llia[5]);
	AssertIndexBlock(&cIndexBlock, "voluble", llia[11]);
	AssertIndexBlock(&cIndexBlock, "intransigent", llia[12]);
	AssertIndexBlock(&cIndexBlock, "potentate", llia[13]);
	AssertIndexBlock(&cIndexBlock, "sophist", llia[14]);
	AssertIndexBlock(&cIndexBlock, "solicitous", llia[15]);
	AssertIndexBlock(&cIndexBlock, "repletion", llia[6]);
	AssertIndexBlock(&cIndexBlock, "ponderous", llia[7]);
	AssertIndexBlock(&cIndexBlock, "quondam", llia[8]);
	AssertIndexBlock(&cIndexBlock, "inimical", llia[9]);
	AssertIndexBlock(&cIndexBlock, "ignominy", llia[10]);
	AssertIndexBlock(&cIndexBlock, "resplendent", llia[16]);

	cIndexBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexBlockAddDuplicate(void)
{
	CIndexBlock		cIndexBlock;
	size			ia = 'a';
	size			ib = 'a';
	bool			bResult;
	size			iWorldLen;
	size			iHelloLen;

	iWorldLen = strlen("World");
	iHelloLen = strlen("Hello");

	cIndexBlock.Init();
	bResult = cIndexBlock.Put((uint8*)&ia, sizeof(size), "Hello", iHelloLen + 1);
	AssertTrue(bResult);
	AssertInt(1, cIndexBlock.NumElements());
	AssertString("Hello", (char*)cIndexBlock.Get((uint8*)&ia, sizeof(size)));

	bResult = cIndexBlock.Put((uint8*)&ib, sizeof(size), "World", iWorldLen + 1);
	AssertTrue(bResult);
	AssertInt(1, cIndexBlock.NumElements());
	AssertString("World", (char*)cIndexBlock.Get((uint8*)&ia, sizeof(size)));

	cIndexBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexBlockRemove(void)
{
	CIndexBlock		cIndexBlock;
	size			ia = 'a';
	size			ib = 'b';
	size			ic = 'c';
	bool			bResult;
	char*			szData;

	cIndexBlock.Init();
	bResult = cIndexBlock.Put((uint8*)&ia, sizeof(size), "Hello", strlen("Hello") + 1);
	bResult = cIndexBlock.Put((uint8*)&ib, sizeof(size), "World", strlen("World") + 1);
	bResult = cIndexBlock.Put((uint8*)&ic, sizeof(size), "Rogue", strlen("Rogue") + 1);
	AssertInt(3, cIndexBlock.NumElements());

	cIndexBlock.Remove((uint8*)&ib, sizeof(size));
	AssertInt(2, cIndexBlock.NumElements());
	bResult = cIndexBlock.Get((uint8*)&ia, sizeof(size), (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Hello");
	bResult = cIndexBlock.Get((uint8*)&ic, sizeof(size), (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Rogue");
	bResult = cIndexBlock.Get((uint8*)&ib, sizeof(size), (void**)&szData, NULL);
	AssertFalse(bResult);

	cIndexBlock.Remove((uint8*)&ia, sizeof(size));
	AssertInt(1, cIndexBlock.NumElements());
	bResult = cIndexBlock.Get((uint8*)&ia, sizeof(size), (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cIndexBlock.Get((uint8*)&ic, sizeof(size), (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Rogue");
	bResult = cIndexBlock.Get((uint8*)&ib, sizeof(size), (void**)&szData, NULL);
	AssertFalse(bResult);

	cIndexBlock.Remove((uint8*)&ic, sizeof(size));
	AssertInt(0, cIndexBlock.NumElements());
	bResult = cIndexBlock.Get((uint8*)&ia, sizeof(size), (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cIndexBlock.Get((uint8*)&ic, sizeof(size), (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cIndexBlock.Get((uint8*)&ib, sizeof(size), (void**)&szData, NULL);
	AssertFalse(bResult);

	cIndexBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexBlockReadWrite(void)
{
	CIndexMapAccess					cAccess;
	CIndexBlock						cIndex;
	CFileBasic						cFile;
	CIndexBlock						cIndexIn;

	cIndex.Init();
	cAccess.Init(&cIndex);

	cAccess.PutStringString("ABC", "XYZ");
	cAccess.PutStringString("Collision", "Detection");
	cAccess.PutStringString("Retro", "Evolved");
	cAccess.PutStringString("Blame", "Canada");

	AssertString("XYZ", cAccess.GetStringString("ABC"));
	AssertString("Detection", cAccess.GetStringString("Collision"));
	AssertString("Evolved", cAccess.GetStringString("Retro"));
	AssertString("Canada", cAccess.GetStringString("Blame"));

	cFile.Init(MemoryFile());
	cFile.Open(EFM_Write_Create);
	AssertTrue(cIndex.Write(&cFile));

	cAccess.Kill();
	cIndex.Kill();

	cFile.Close();
	cFile.Open(EFM_Read);

	AssertTrue(cIndexIn.Read(&cFile));
	cAccess.Init(&cIndexIn);

	AssertString("XYZ", cAccess.GetStringString("ABC"));
	AssertString("Detection", cAccess.GetStringString("Collision"));
	AssertString("Evolved", cAccess.GetStringString("Retro"));
	AssertString("Canada", cAccess.GetStringString("Blame"));

	cIndexIn.Kill();
	cFile.Close();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexBlockIterate(void)
{
	CIndexMapAccess					cAccess;
	CIndexBlock						cIndex;
	CFileBasic						cFile;
	CIndexBlock						cIndexIn;
	SIndexTreeMemoryUnsafeIterator	sIter;
	char* pvData;
	size							uiDataSize;
	char							szKey[MAX_KEY_SIZE];
	size							uiKeySize;
	bool							bExists;

	cIndex.Init();
	cAccess.Init(&cIndex);

	cAccess.PutStringString("ABC", "XYZ");
	cAccess.PutStringString("Collision", "Detection");
	cAccess.PutStringString("Retro", "Evolved");
	cAccess.PutStringString("Blame", "Canada");

	cFile.Init(MemoryFile());
	cFile.Open(EFM_Write_Create);
	AssertTrue(cIndex.Write(&cFile));

	bExists = cIndex.StartIteration(&sIter, (void**)&pvData, &uiDataSize, szKey, &uiKeySize, MAX_KEY_SIZE);
	AssertTrue(bExists);
	AssertString("ABC", szKey);
	AssertString("XYZ", pvData);
	AssertInt(3, uiKeySize);
	AssertInt(4, uiDataSize);
	bExists = cIndex.Iterate(&sIter, (void**)&pvData, &uiDataSize, szKey, &uiKeySize, MAX_KEY_SIZE);
	AssertTrue(bExists);
	AssertString("Blame", szKey);
	AssertString("Canada", pvData);
	AssertInt(5, uiKeySize);
	AssertInt(7, uiDataSize);
	bExists = cIndex.Iterate(&sIter, (void**)&pvData, &uiDataSize, szKey, &uiKeySize, MAX_KEY_SIZE);
	AssertTrue(bExists);
	AssertString("Collision", szKey);
	AssertString("Detection", pvData);
	AssertInt(9, uiKeySize);
	AssertInt(10, uiDataSize);
	bExists = cIndex.Iterate(&sIter, (void**)&pvData, &uiDataSize, szKey, &uiKeySize, MAX_KEY_SIZE);
	AssertTrue(bExists);
	AssertString("Retro", szKey);
	AssertString("Evolved", pvData);
	AssertInt(5, uiKeySize);
	AssertInt(8, uiDataSize);
	bExists = cIndex.Iterate(&sIter, (void**)&pvData, &uiDataSize, szKey, &uiKeySize, MAX_KEY_SIZE);
	AssertFalse(bExists);

	cAccess.Kill();
	cIndex.Kill();

	cFile.Close();
	cFile.Open(EFM_Read);

	AssertTrue(cIndexIn.Read(&cFile));
	cAccess.Init(&cIndexIn);

	AssertTrue(cIndexIn.ValidateIndexTree());

	bExists = cIndexIn.StartIteration(&sIter, (void**)&pvData, &uiDataSize, szKey, &uiKeySize, MAX_KEY_SIZE);
	AssertTrue(bExists);
	AssertString("ABC", szKey);
	AssertString("XYZ", pvData);
	AssertInt(3, uiKeySize);
	AssertInt(4, uiDataSize);
	bExists = cIndexIn.Iterate(&sIter, (void**)&pvData, &uiDataSize, szKey, &uiKeySize, MAX_KEY_SIZE);
	AssertTrue(bExists);
	AssertString("Blame", szKey);
	AssertString("Canada", pvData);
	AssertInt(5, uiKeySize);
	AssertInt(7, uiDataSize);
	bExists = cIndexIn.Iterate(&sIter, (void**)&pvData, &uiDataSize, szKey, &uiKeySize, MAX_KEY_SIZE);
	AssertTrue(bExists);
	AssertString("Collision", szKey);
	AssertString("Detection", pvData);
	AssertInt(9, uiKeySize);
	AssertInt(10, uiDataSize);
	bExists = cIndexIn.Iterate(&sIter, (void**)&pvData, &uiDataSize, szKey, &uiKeySize, MAX_KEY_SIZE);
	AssertTrue(bExists);
	AssertString("Retro", szKey);
	AssertString("Evolved", pvData);
	AssertInt(5, uiKeySize);
	AssertInt(8, uiDataSize);
	bExists = cIndexIn.Iterate(&sIter, (void**)&pvData, &uiDataSize, szKey, &uiKeySize, MAX_KEY_SIZE);
	AssertFalse(bExists);

	cIndexIn.Kill();
	cFile.Close();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexBlockDataMemoryUnchanged(void)
{
	CIndexBlock			cIndex;
	CIndexMapAccess		cAccess;
	size					i;
	CRandom				cRandom;
	CArrayChars			aszWords;
	CChars				sz;
	char*				szData;
	char*				aszData[2048];
	bool				bFailed;

	WordsInit();

	cIndex.Init();
	cAccess.Init(&cIndex);

	cRandom.Init(2367849);
	aszWords.Init();
	GetCommonWords(&aszWords);

	for (i = 0; i < 2048; i++)
	{
		MakeKey(&cRandom, &aszWords, &sz);

		szData = cAccess.PutStringString(sz.Text(), IntToString(i));
		aszData[i] = szData;

		sz.Kill();
	}
	cRandom.Kill();

	cRandom.Init(2367849);

	bFailed = false;
	for (i = 0; i < 2048; i++)
	{
		MakeKey(&cRandom, &aszWords, &sz);

		szData = cAccess.GetStringString(sz.Text());
		if (aszData[i] != szData)
		{
			bFailed = true;
		}
		sz.Kill();
	}

	AssertFalse(bFailed);

	cRandom.Kill();
	cAccess.Kill();
	cIndex.Kill();

	aszWords.Kill();
	WordsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexBlockRemoveHalf(void)
{
	CIndexBlock			cIndex;
	CIndexMapAccess		cAccess;
	size					i;
	CRandom				cRandom;
	CArrayChars			aszWords;
	CChars				sz;
	char*				szData;
	char*				aszData[2048];
	bool				bResult;
	bool				bFailed;

	WordsInit();

	cIndex.Init();
	cAccess.Init(&cIndex);

	cRandom.Init(2367849);
	aszWords.Init();
	GetCommonWords(&aszWords);

	for (i = 0; i < 2048; i++)
	{
		MakeKey(&cRandom, &aszWords, &sz);

		szData = cAccess.PutStringString(sz.Text(), IntToString(i));
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
			bResult &= cAccess.DeleteString(sz.Text());
		}
		sz.Kill();
	}

	AssertTrue(bResult);
	AssertInt(1024, cIndex.NumElements());
	cRandom.Kill();

	bFailed = false;
	cRandom.Init(2367849);
	for (i = 0; i < 2048; i++)
	{
		MakeKey(&cRandom, &aszWords, &sz);
		szData = cAccess.GetStringString(sz.Text());
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

	cAccess.Kill();
	cIndex.Kill();

	aszWords.Kill();
	WordsKill();
}

char	gszIndexBlockCallbackData[64];

void TestIndexBlockDataFreeCallback(const void* pvData)
{
	memset(gszIndexBlockCallbackData, 0, 64);
	strcpy(gszIndexBlockCallbackData, (char*)pvData);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexBlockDataFree(void)
{
	CIndexBlock			cMap;
	CIndexMapAccess		cAccess;
	CDataFreeCallBack	cDataFree;

	cMap.Init();
	cDataFree.Init(TestIndexBlockDataFreeCallback);
	cMap.SetDataFreeCallback(&cDataFree);
	cAccess.Init(&cMap);

	TestIndexBlockDataFreeCallback("");
	cAccess.PutIntString(7, "Jimmy!");
	AssertString("", gszIndexBlockCallbackData);
	cAccess.DeleteInt(7);
	AssertString("Jimmy!", gszIndexBlockCallbackData);

	memset(gszIndexBlockCallbackData, 0, 64);
	cAccess.PutIntString(7, "Jimmy's not gone.");
	AssertString("", gszIndexBlockCallbackData);
	cAccess.PutIntString(7, "Oh, never mind.");
	AssertString("Jimmy's not gone.", gszIndexBlockCallbackData);

	memset(gszIndexBlockCallbackData, 0, 64);
	cAccess.PutIntString(7, "Jimmy is Back!!");
	AssertString("Oh, never mind.", gszIndexBlockCallbackData);

	cAccess.Kill();
	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexBlock(void)
{
	BeginTests();
	FastFunctionsInit();
	MemoryInit();
	LocalMallocatorsInit(&gcConstructors, &gcMallocators);
	DataOrderersInit(&gcConstructors, &gcDataOrderers);

	TestIndexBlockGet();
	TestIndexBlockAddDuplicate();
	TestIndexBlockRemove();
	TestIndexBlockReadWrite();
	TestIndexBlockDataMemoryUnchanged();
	TestIndexBlockRemoveHalf();
	TestIndexBlockDataFree();
	TestIndexBlockIterate();

	DataOrderersKill();
	MemoryKill();
	FastFunctionsKill();
	TestStatistics();
}

