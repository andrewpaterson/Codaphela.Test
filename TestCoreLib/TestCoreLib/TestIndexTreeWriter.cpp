#include "BaseLib/IndexTreeMemory.h"
#include "BaseLib/IndexTreeMemoryAccess.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalMemory.h"
#include "TestLib/Assert.h"
#include "CoreLib/IndexTreeWriter.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeWriterWrite(void)
{
	char*					pvData;
	char*					pvKey;
	int						iDataSize;
	BOOL					bExists;
	int						iKeyLength;
	CIndexTreeMemory		cIndexTree;
	CIndexTreeMemoryAccess	cAccess;
	CMapStringString		cMap;
	SMapIterator			sMapIter;
	CIndexTreeWriter		cWriter;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "IndexTreeMemoryWriter";

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
	cAccess.Init(&cIndexTree);

	bExists = cMap.StartIteration(&sMapIter, (void**)&pvKey, (void**)&pvData);
	while (bExists)
	{
		iKeyLength = strlen((char*)pvKey);
		iDataSize = strlen((char*)pvData);
		cAccess.PutKeyData(pvKey, iKeyLength, pvData, iDataSize);

		bExists = cMap.Iterate(&sMapIter, (void**)&pvKey, (void**)&pvData);
	}

	AssertInt(12, cIndexTree.NumElements());
	Pass();
	AssertTrue(cIndexTree.ValidateIndexTree());

	cFileUtil.RemoveDir(szDirectory);

	cWriter.Write(&cIndexTree, szDirectory);

	cAccess.Kill();
	cIndexTree.Kill();
	cMap.Kill();

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeWriter(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	TestIndexTreeWriterWrite();

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

