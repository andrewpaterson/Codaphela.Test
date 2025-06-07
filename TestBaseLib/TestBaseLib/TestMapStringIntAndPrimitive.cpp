#include "BaseLib/MapStringIntAndPointer.h"
#include "BaseLib/StdRandom.h"
#include "BaseLIb/Number.h"
#include "BaseLIb/FreeList.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringIntAndPrimitivePut(void)
{
	CMapStringIntAndPointer		cMap;
	bool						bBool;
	char						szWord[] = "Words are Cool";
	uint						uiType;
	bool*						pbBool;
	char*						pszWord;
	size						uiSize;

	cMap.Init(true, true);

	bBool = true;
	cMap.Put("Hello", PT_bool, &bBool);
	cMap.Put("Word", PT_char8Pointer, szWord);

	pbBool = (bool*)cMap.Get("Hello", &uiType);
	AssertBool(true, *pbBool);
	AssertInt(PT_bool, uiType);
	
	pszWord = (char*)cMap.Get("Word", &uiType);
	AssertString("Words are Cool", pszWord);
	AssertInt(PT_char8Pointer, uiType);
	
	uiSize = cMap.NumElements();
	AssertSize(2, uiSize);

	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool TestNumberMatchesIndex(CMapStringIntAndPointer* pcMap, CArrayInt* paiKeys)
{
	size						ui;
	char						szKey[5];
	CRandom						cRandom;
	uint						uiKey;
	CNumber*					pcNumber;
	uint						uiType;
	int32						iValue;
	bool						bPass;
	size						uiNumElements;

	bPass = true;
	uiNumElements = paiKeys->NumElements();

	if (uiNumElements != pcMap->NumElements())
	{
		return false;
	}

	for (ui = 0; ui < uiNumElements; ui++)
	{
		uiKey = paiKeys->GetValue(ui);
		IntToString(szKey, 5, uiKey, 10);
		pcNumber = (CNumber*)pcMap->Get(szKey, &uiType);
		iValue = pcNumber->IntValue();
		if (iValue != uiKey)
		{
			bPass = false;
			break;
		}
	}

	return bPass;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringIntAndPrimitiveRemove(void)
{
	CMapStringIntAndPointer		cMap;
	size						uiSize;
	size						ui;
	char						szKey[5];
	CArrayInt					aiKeys;
	CRandom						cRandom;
	uint						uiKey;
	CFreeList					cFreeNumbers;
	CNumber*					pcNumber;
	size						uiNumberSize;
	bool						bPass;
	size						uiNumElements;
	bool						bRemoved;

	aiKeys.Init();
	for (ui = 0; ui < 1024 + 128; ui++)
	{
		aiKeys.Add(ui);
	}

	cRandom.Init(89743636);
	aiKeys.Shuffle(&cRandom);

	cMap.Init(true, true);

	uiNumberSize = NUMBER_SIZE(DEFAULT_WHOLE_NUMBERS, DEFAULT_DECIMALS);
	cFreeNumbers.Init(uiNumberSize);
	for (ui = 0; ui < 1152; ui++)
	{
		uiKey = aiKeys.GetValue(ui);
		IntToString(szKey, 5, uiKey, 10);
		pcNumber = (CNumber*)cFreeNumbers.Add();
		pcNumber->Init((int)uiKey);
		cMap.Put(szKey, PT_Number, pcNumber);
	}


	uiSize = cMap.NumElements();
	AssertSize(1152, uiSize);

	aiKeys.Shuffle(&cRandom);

	bPass = TestNumberMatchesIndex(&cMap, &aiKeys);
	AssertTrue(bPass);

	uiNumElements = aiKeys.NumElements();
	ui = uiNumElements - 1;
	do
	{
		uiKey = aiKeys.GetValue(ui);
		IntToString(szKey, 5, uiKey, 10);

		bRemoved = cMap.Remove(szKey);
		AssertTrue(bRemoved);
		aiKeys.RemoveAt(ui);

		bPass = TestNumberMatchesIndex(&cMap, &aiKeys);
		AssertTrue(bPass);
		ui--;
	} while (ui != SIZE_MAX);

	uiSize = cMap.NumElements();
	AssertSize(0, uiSize);

	aiKeys.Kill();
	cRandom.Kill();

	cMap.Kill();

	cFreeNumbers.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringIntAndPrimitive(void)
{
	BeginTests();

	TestMapStringIntAndPrimitivePut();
	TestMapStringIntAndPrimitiveRemove();

	TestStatistics();
}

