#include "BaseLib/IndexTreeMemory.h"
#include "BaseLib/MapStringString.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeIteratorIterate(void)
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

	bExists = cIndexTree.StartIteration(&sIter, (void**)&pvData, &iDataSize);
	while (bExists)
	{
		iKeyLength = cIndexTree.GetKey(pacKey, pvData, TRUE);

		pacData = cMap.Get(pacKey);
		iMapDataSize = strlen(pacData);
		AssertInt(iMapDataSize, iDataSize);

		iResult = memcmp_fast(pacData, pvData, iDataSize);
		AssertInt(0, iResult);

		bExists = cIndexTree.Iterate(&sIter, (void**)&pvData, &iDataSize);
	}

	cIndexTree.Kill();
	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeIterator(void)
{
	BeginTests();

	TestIndexTreeIteratorIterate();

	TestStatistics();
}


