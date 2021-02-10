#include "BaseLib/TypeConverter.h"
#include "BaseLib/DebugOutput.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MapStringString.h"
#include "CoreLib/IndexTreeFile.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexTreeFileIterator.h"
#include "CoreLib/IndexTreeFileAccess.h"
#include "TestLib/Words.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileIteratorUnsafeIterate(void)
{
	SIndexTreeFileUnsafeIterator	sIter;
	char*					pvData;
	char*					pvKey;
	size_t					iDataSize;
	BOOL					bExists;
	char					pacKey[9 + 1];
	int						iKeyLength;
	CIndexTreeFile			cIndexTree;
	CMapStringString		cMap;
	SMapIterator			sMapIter;
	char*					pacData;
	int						iResult;
	int						iMapDataSize;
	CIndexTreeFileAccess	cAccess;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cController;

	cHelper.Init("Output" _FS_ "IndexTreeIterator1", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);

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

	bExists = cMap.StartIteration(&sMapIter, (void**)&pvKey, (void**)&pvData);
	while (bExists)
	{
		iKeyLength = strlen((char*)pvKey);
		iDataSize = strlen((char*)pvData);
		cIndexTree.Put(pvKey, iKeyLength, pvData, (unsigned char)iDataSize);

		bExists = cMap.Iterate(&sMapIter, (void**)&pvKey, (void**)&pvData);
	}

	AssertInt(12, cIndexTree.NumElements());

	bExists = cIndexTree.StartUnsafeIteration(&sIter, pacKey, &iKeyLength, (void**)&pvData, &iDataSize);
	while (bExists)
	{
		pacData = cMap.Get(pacKey);
		iMapDataSize = strlen(pacData);
		AssertInt(iMapDataSize, iDataSize);

		iResult = memcmp_fast(pacData, pvData, iDataSize);
		AssertInt(0, iResult);

		bExists = cIndexTree.UnsafeIterate(&sIter, pacKey, &iKeyLength, (void**)&pvData, &iDataSize);
	}

	cIndexTree.Flush();
	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileIteratorIterate(void)
{
	size_t					iData;
	char*					pszKey;
	int						i;
	CChars*					pszKey2;
	CIndexTreeFile			cIndexTree;
	CIndexTreeFileAccess	cAccess;
	CIndexTreeIterator*		pcIter;
	BOOL					bExists;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cController;

	cHelper.Init("Output" _FS_ "IndexTreeIterator2", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);

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

	cIndexTree.Flush();
	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileIterator(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	WordsInit();
	DataMemoryInit();
	BeginTests();

	TestIndexTreeFileIteratorUnsafeIterate();
	TestIndexTreeFileIteratorIterate();

	TestStatistics();
	DataMemoryKill();
	WordsKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}


