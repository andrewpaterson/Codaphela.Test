#include "BaseLib/TypeConverter.h"
#include "BaseLib/DebugOutput.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/IndexTreeMemory.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/IndexTreeMemoryIterator.h"
#include "BaseLib/IndexTreeMemoryAccess.h"
#include "TestLib/Words.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeIteratorUnsafeIterate(void)
{
	SIndexTreeMemoryIterator	sIter;
	char*						pvData;
	char*						pvKey;
	int							iDataSize;
	BOOL						bExists;
	char						pacKey[9+1];
	int							iKeyLength;
	CIndexTreeMemory			cIndexTree;
	CMapStringString			cMap;
	SMapIterator				sMapIter;
	char*						pacData;
	int							iResult;
	int							iMapDataSize;

	cMap.Init(3);
	cMap.Put("AA", "nutritious");
	cMap.Put("AAA", "follow");
	cMap.Put("AB", "lighten");
	cMap.Put("BAAB", "ear");
	cMap.Put("BB", "spotted");
	cMap.Put("AAAAAAAAA", "hanging");
	cMap.Put("ABBA", "mate");
	cMap.Put("ABA", "blot");
	cMap.Put("BCD", "smash");
	cMap.Put("BBC", "cycle");
	cMap.Put("BBB", "waggish");
	cMap.Put("BBA", "debt");

	AssertInt(12, cMap.NumElements());

	cIndexTree.Init();

	bExists = cMap.StartIteration(&sMapIter, (void**)&pvKey, (void**)&pvData);
	while (bExists)
	{
		iKeyLength = strlen((char*)pvKey);
		iDataSize = strlen((char*)pvData);
		cIndexTree.Put(pvKey, iKeyLength, pvData, (unsigned char)iDataSize);

		bExists = cMap.Iterate(&sMapIter, (void**)&pvKey, (void**)&pvData);
	}

	AssertInt(12, cIndexTree.NumElements());

	bExists = cIndexTree.StartUnsafeIteration(&sIter, (void**)&pvData, &iDataSize);
	while (bExists)
	{
		iKeyLength = cIndexTree.GetKey(pvData, pacKey, 9+1);

		pacData = cMap.Get(pacKey);
		iMapDataSize = strlen(pacData);
		AssertInt(iMapDataSize, iDataSize);

		iResult = memcmp_fast(pacData, pvData, iDataSize);
		AssertInt(0, iResult);

		bExists = cIndexTree.UnsafeIterate(&sIter, (void**)&pvData, &iDataSize);
	}

	cIndexTree.Kill();
	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeIteratorIterate(void)
{
	int						iData;
	char*					pszKey;
	int						i;
	CChars*					pszKey2;
	CIndexTreeMemory		cIndex;
	CIndexTreeMemoryAccess	cAccess;
	CIndexTreeIterator*		pcIter;
	BOOL					bExists;

	cIndex.Init();
	cAccess.Init(&cIndex);

	for (i = 0; i < gaszCommonWords.NumElements(); i++)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		iData = i;

		cAccess.PutStringInt(pszKey, iData);
	}

	AssertLongLongInt(1000, cAccess.NumElements());

	pcIter = cAccess.CreateIterator();

	for (i = 0; i < gaszCommonWords.NumElements(); i++)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();

		bExists = pcIter->Iterate();
		AssertString(pszKey, pcIter->GetKey());
	}
	bExists = pcIter->Iterate();
	AssertFalse(bExists);

	cAccess.FreeIterator(pcIter);

	cIndex.Kill();
	cAccess.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeIterator(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	WordsInit();
	BeginTests();


	TestIndexTreeIteratorUnsafeIterate();
	TestIndexTreeIteratorIterate();

	TestStatistics();
	WordsKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}


