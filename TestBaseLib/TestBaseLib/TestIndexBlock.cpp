#include "BaseLib/IndexBlock.h"
#include "BaseLib/IndexMapAccess.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/CountingAllocator.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/StdRandom.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/LogString.h"
#include "TestLib/Words.h"
#include "TestLib/Assert.h"
#include "TestMap.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL AddToIndexBlock(CIndexBlock* pcIndexBlock, char* szKey, long long int lliData)
{
	int				iStrLen;

	iStrLen = strlen(szKey) + 1;
	return pcIndexBlock->Put(szKey, iStrLen, &lliData, sizeof(long long int));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL GetFromIndexBlock(CIndexBlock* pcIndexBlock, char* szKey, long long int** pplli, int* piSize)
{
	int				iStrLen;

	iStrLen = strlen(szKey) + 1;
	return pcIndexBlock->Get(szKey, iStrLen, (void**)pplli, piSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertIndexBlock(CIndexBlock* pcIndexBlock, char* szKey, long long int lliData)
{
	long long int* plli;
	int				iStrLen;

	iStrLen = strlen(szKey) + 1;
	pcIndexBlock->Get(szKey, iStrLen, (void**)&plli, NULL);
	AssertLongLongInt(lliData, *plli);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexBlockGet(void)
{
	CIndexBlock		cIndexBlock;
	long long int	llia[64];
	int				i;
	long long int	lli;
	long long int* plli;
	int				iSize;

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
	AssertLongLongInt(llia[0], *plli);
	AssertInt(sizeof(long long int), iSize);

	AssertTrue(GetFromIndexBlock(&cIndexBlock, "cock", &plli, &iSize));
	AssertLongLongInt(llia[1], *plli);
	AssertInt(sizeof(long long int), iSize);

	AssertTrue(GetFromIndexBlock(&cIndexBlock, "cockerel", &plli, &iSize));
	AssertLongLongInt(llia[2], *plli);

	AddToIndexBlock(&cIndexBlock, "vizard", llia[3]);
	AddToIndexBlock(&cIndexBlock, "visard", llia[4]);
	AddToIndexBlock(&cIndexBlock, "wizard", llia[5]);
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "vizard", &plli, &iSize));
	AssertLongLongInt(llia[3], *plli);
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "visard", &plli, &iSize));
	AssertLongLongInt(llia[4], *plli);
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "wizard", &plli, &iSize));
	AssertLongLongInt(llia[5], *plli);

	AddToIndexBlock(&cIndexBlock, "repletion", llia[6]);
	AddToIndexBlock(&cIndexBlock, "ponderous", llia[7]);
	AddToIndexBlock(&cIndexBlock, "quondam", llia[8]);
	AddToIndexBlock(&cIndexBlock, "inimical", llia[9]);
	AddToIndexBlock(&cIndexBlock, "ignominy", llia[10]);
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "inimical", &plli, &iSize));
	AssertLongLongInt(llia[9], *plli);
	AssertInt(sizeof(long long int), iSize);
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "cocker", &plli, &iSize));
	AssertLongLongInt(llia[0], *plli);
	AssertInt(sizeof(long long int), iSize);

	AddToIndexBlock(&cIndexBlock, "voluble", llia[11]);
	AddToIndexBlock(&cIndexBlock, "intransigent", llia[12]);
	AddToIndexBlock(&cIndexBlock, "potentate", llia[13]);
	AddToIndexBlock(&cIndexBlock, "sophist", llia[14]);
	AddToIndexBlock(&cIndexBlock, "solicitous", llia[15]);
	AssertInt(16, cIndexBlock.NumElements());
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "solicitous", &plli, &iSize));
	AssertLongLongInt(llia[15], *plli);
	AssertInt(sizeof(long long int), iSize);
	AssertTrue(GetFromIndexBlock(&cIndexBlock, "cock", &plli, &iSize));
	AssertLongLongInt(llia[1], *plli);
	AssertInt(sizeof(long long int), iSize);

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
	CIndexBlock	cIndexBlock;
	int			ia = 'a';
	int			ib = 'a';
	BOOL		bResult;
	int			iWorldLen;
	int			iHelloLen;

	iWorldLen = strlen("World");
	iHelloLen = strlen("Hello");

	cIndexBlock.Init();
	bResult = cIndexBlock.Put(&ia, sizeof(int), "Hello", iHelloLen + 1);
	AssertTrue(bResult);
	AssertInt(1, cIndexBlock.NumElements());
	AssertString("Hello", (char*)cIndexBlock.Get(&ia, sizeof(int)));

	bResult = cIndexBlock.Put(&ib, sizeof(int), "World", iWorldLen + 1);
	AssertTrue(bResult);
	AssertInt(1, cIndexBlock.NumElements());
	AssertString("World", (char*)cIndexBlock.Get(&ia, sizeof(int)));

	cIndexBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexBlockRemove(void)
{
	CIndexBlock	cIndexBlock;
	int			ia = 'a';
	int			ib = 'b';
	int			ic = 'c';
	BOOL		bResult;
	char* szData;

	cIndexBlock.Init();
	bResult = cIndexBlock.Put(&ia, sizeof(int), "Hello", strlen("Hello") + 1);
	bResult = cIndexBlock.Put(&ib, sizeof(int), "World", strlen("World") + 1);
	bResult = cIndexBlock.Put(&ic, sizeof(int), "Rogue", strlen("Rogue") + 1);
	AssertInt(3, cIndexBlock.NumElements());

	cIndexBlock.Remove(&ib, sizeof(int));
	AssertInt(2, cIndexBlock.NumElements());
	bResult = cIndexBlock.Get(&ia, sizeof(int), (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Hello");
	bResult = cIndexBlock.Get(&ic, sizeof(int), (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Rogue");
	bResult = cIndexBlock.Get(&ib, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);

	cIndexBlock.Remove(&ia, sizeof(int));
	AssertInt(1, cIndexBlock.NumElements());
	bResult = cIndexBlock.Get(&ia, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cIndexBlock.Get(&ic, sizeof(int), (void**)&szData, NULL);
	AssertTrue(bResult);
	AssertString(szData, "Rogue");
	bResult = cIndexBlock.Get(&ib, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);

	cIndexBlock.Remove(&ic, sizeof(int));
	AssertInt(0, cIndexBlock.NumElements());
	bResult = cIndexBlock.Get(&ia, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cIndexBlock.Get(&ic, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);
	bResult = cIndexBlock.Get(&ib, sizeof(int), (void**)&szData, NULL);
	AssertFalse(bResult);

	cIndexBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexBlockReadWrite(void)
{
	CIndexMapAccess		cAccess;
	CIndexBlock			cIndex;
	CFileBasic			cFile;
	CIndexBlock			cIndexIn;

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
void TestIndexBlockDataMemoryUnchanged(void)
{
	CIndexBlock			cIndex;
	CIndexMapAccess		cAccess;
	int					i;
	CRandom				cRandom;
	CArrayChars			aszWords;
	CChars				sz;
	char*				szData;
	char*				aszData[2048];
	BOOL				bFailed;

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

	bFailed = FALSE;
	for (i = 0; i < 2048; i++)
	{
		MakeKey(&cRandom, &aszWords, &sz);

		szData = cAccess.GetStringString(sz.Text());
		if (aszData[i] != szData)
		{
			bFailed = TRUE;
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
	int					i;
	CRandom				cRandom;
	CArrayChars			aszWords;
	CChars				sz;
	char*				szData;
	char*				aszData[2048];
	BOOL				bResult;
	BOOL				bFailed;

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
	bResult = TRUE;
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

	bFailed = FALSE;
	cRandom.Init(2367849);
	for (i = 0; i < 2048; i++)
	{
		MakeKey(&cRandom, &aszWords, &sz);
		szData = cAccess.GetStringString(sz.Text());
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

	cAccess.Kill();
	cIndex.Kill();

	aszWords.Kill();
	WordsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexBlock(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestIndexBlockGet();
	TestIndexBlockAddDuplicate();
	TestIndexBlockRemove();
	TestIndexBlockReadWrite();
	TestIndexBlockDataMemoryUnchanged();
	TestIndexBlockRemoveHalf();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

