#include "BaseLib/SetBlock.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/CountingAllocator.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/StdRandom.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/LogString.h"
#include "TestLib/Words.h"
#include "TestLib/Assert.h"
#include "WordKey.h"


class CTestSetBlock : public CSetBlock
{
public:
	SSNode* GetNode(void* pvKey, size iKeySize)
	{
		return CSetBlock::GetNode(pvKey, iKeySize);
	}
};


size	giSetBlockCallbackData = 0;


class CTestSetDataFree : public CDataFree
{
protected:
	CSetBlock*	mpcSetBlock;

public:
	void	Init(CSetBlock* pcIndexBlock);
	void	FreeData(void* pvData) override;
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestSetDataFree::Init(CSetBlock* pcSetBlock)
{
	mpcSetBlock = pcSetBlock;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestSetDataFree::FreeData(void* pvData)
{
	SSNode*		psNode;
	void*		pvKey;
	
	psNode = (SSNode*)pvData;
	pvKey = CSetBlock::GetData(psNode);
	giSetBlockCallbackData++;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetBlockInternals(void)
{
	CSetBlock			cSet;
	size				i;
	size				iKey;
	CArrayBlockSorted*	paBlock;
	SSNode**			psNode1;
	SSNode**			psNode2;
	size*				piKey;

	cSet.Init(&CompareInt, true);
	i = 7;
	cSet.Put(&i, sizeof(size));

	i = 9;
	cSet.Put(&i, sizeof(size));
	AssertInt(2, cSet.NumElements());

	paBlock = cSet.GetArray();
	paBlock->InsertHoldingIntoSorted();
	psNode1 = (SSNode**)paBlock->GetInSorted(0);
	psNode2 = (SSNode**)paBlock->GetInSorted(1);
	AssertInt(sizeof(size), (*psNode1)->iDataSize);
	AssertInt(sizeof(size), (*psNode2)->iDataSize);
	piKey = (size*)RemapSinglePointer(*psNode1, sizeof(SSNode));
	AssertInt(7, *piKey);
	piKey = (size*)RemapSinglePointer(*psNode2, sizeof(SSNode));
	AssertInt(9, *piKey);

	iKey = 7;
	piKey = (size*)cSet.Get(&iKey, sizeof(size));
	AssertSize(7, *piKey);

	iKey = 9;
	piKey = (size*)cSet.Get(&iKey, sizeof(size));
	AssertSize(9, *piKey);

	iKey = 3;
	piKey = (size*)cSet.Get(&iKey, sizeof(size));
	AssertNull(piKey);

	cSet.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool AddToSetBlock(CSetBlock* pcSetBlock, char* szKey)
{
	size				iStrLen;

	iStrLen = strlen(szKey) + 1;
	return pcSetBlock->Put(szKey, iStrLen);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* GetFromSetBlock(CSetBlock* pcSetBlock, char* szKey)
{
	size	iStrLen;
	char*	szData;

	iStrLen = strlen(szKey) + 1;
	szData = (char*)pcSetBlock->Get(szKey, iStrLen);
	return szData;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertSetBlock(CSetBlock* pcSetBlock, char* szKey)
{
	size	iStrLen;
	char*	szData;

	iStrLen = strlen(szKey) + 1;
	szData = (char*)pcSetBlock->Get(szKey, iStrLen);
	AssertString(szKey, szData);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetBlockGet(void)
{
	CSetBlock	cSet;

	cSet.Init((DataCompare)&StringCompare, true);
	AddToSetBlock(&cSet, "cocker");
	AddToSetBlock(&cSet, "cock");
	AddToSetBlock(&cSet, "cockerel");

	AssertInt(3, cSet.NumElements());
	AssertString("cocker", GetFromSetBlock(&cSet, "cocker"));

	AssertString("cock", GetFromSetBlock(&cSet, "cock"));

	AssertString("cockerel", GetFromSetBlock(&cSet, "cockerel"));

	AddToSetBlock(&cSet, "vizard");
	AddToSetBlock(&cSet, "visard");
	AddToSetBlock(&cSet, "wizard");
	AssertString("vizard", GetFromSetBlock(&cSet, "vizard"));
	AssertString("visard", GetFromSetBlock(&cSet, "visard"));
	AssertString("wizard", GetFromSetBlock(&cSet, "wizard"));

	AddToSetBlock(&cSet, "repletion");
	AddToSetBlock(&cSet, "ponderous");
	AddToSetBlock(&cSet, "quondam");
	AddToSetBlock(&cSet, "inimical");
	AddToSetBlock(&cSet, "ignominy");
	AssertString("inimical", GetFromSetBlock(&cSet, "inimical"));
	AssertString("cocker", GetFromSetBlock(&cSet, "cocker"));

	AddToSetBlock(&cSet, "voluble");
	AddToSetBlock(&cSet, "intransigent");
	AddToSetBlock(&cSet, "potentate");
	AddToSetBlock(&cSet, "sophist");
	AddToSetBlock(&cSet, "solicitous");
	AssertInt(16, cSet.NumElements());
	AssertString("solicitous", GetFromSetBlock(&cSet, "solicitous"));
	AssertString("cock", GetFromSetBlock(&cSet, "cock"));

	AddToSetBlock(&cSet, "resplendent");
	AssertInt(17, cSet.NumElements());

	AssertSetBlock(&cSet, "cocker");
	AssertSetBlock(&cSet, "cock");
	AssertSetBlock(&cSet, "cockerel");
	AssertSetBlock(&cSet, "vizard");
	AssertSetBlock(&cSet, "visard");
	AssertSetBlock(&cSet, "wizard");
	AssertSetBlock(&cSet, "voluble");
	AssertSetBlock(&cSet, "intransigent");
	AssertSetBlock(&cSet, "potentate");
	AssertSetBlock(&cSet, "sophist");
	AssertSetBlock(&cSet, "solicitous");
	AssertSetBlock(&cSet, "repletion");
	AssertSetBlock(&cSet, "ponderous");
	AssertSetBlock(&cSet, "quondam");
	AssertSetBlock(&cSet, "inimical");
	AssertSetBlock(&cSet, "ignominy");
	AssertSetBlock(&cSet, "resplendent");

	cSet.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetBlockAddDuplicate(void)
{
	CSetBlock	cSet;
	size		ia = 'a';
	size		ib = 'a';
	bool		bResult;
	size		iWorldLen;
	size		iHelloLen;

	iWorldLen = strlen("World");
	iHelloLen = strlen("Hello");

	cSet.Init(&CompareInt, true);
	bResult = cSet.Put(&ia, sizeof(size));
	AssertTrue(bResult);
	AssertInt(1, cSet.NumElements());
	AssertSize('a', *((size*)cSet.Get(&ia, sizeof(size))));

	bResult = cSet.Put(&ib, sizeof(size));
	AssertTrue(bResult);
	AssertInt(1, cSet.NumElements());
	AssertSize('a', *((size*)cSet.Get(&ia, sizeof(size))));

	cSet.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetBlockRemove(void)
{
	CSetBlock	cSet;
	size		ia = 'a';
	size		ib = 'b';
	size		ic = 'c';
	bool		bResult;

	cSet.Init(&CompareInt, true);
	bResult = cSet.Put(&ia, sizeof(size));
	bResult = cSet.Put(&ib, sizeof(size));
	bResult = cSet.Put(&ic, sizeof(size));
	AssertInt(3, cSet.NumElements());

	cSet.Remove(&ib, sizeof(size));
	AssertInt(2, cSet.NumElements());
	bResult = cSet.Get(&ia, sizeof(size));
	AssertTrue(bResult);
	bResult = cSet.Get(&ic, sizeof(size));
	AssertTrue(bResult);
	bResult = cSet.Get(&ib, sizeof(size));
	AssertFalse(bResult);

	cSet.Remove(&ia, sizeof(size));
	AssertInt(1, cSet.NumElements());
	bResult = cSet.Get(&ia, sizeof(size));
	AssertFalse(bResult);
	bResult = cSet.Get(&ic, sizeof(size));
	AssertTrue(bResult);
	bResult = cSet.Get(&ib, sizeof(size));
	AssertFalse(bResult);

	cSet.Remove(&ic, sizeof(size));
	AssertInt(0, cSet.NumElements());
	bResult = cSet.Get(&ia, sizeof(size));
	AssertFalse(bResult);
	bResult = cSet.Get(&ic, sizeof(size));
	AssertFalse(bResult);
	bResult = cSet.Get(&ib, sizeof(size));
	AssertFalse(bResult);

	cSet.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetBlockReadWrite(void)
{
	//CSetString	mszsz;
	//CFileBasic	cFile;
	//CSetString	mszszIn;

	//mszsz.Init();

	//mszsz.Put("ABC", "XYZ");
	//mszsz.Put("Collision", "Detection");
	//mszsz.Put("Retro", "Evolved");
	//mszsz.Put("Blame", "Canada");

	//AssertString("XYZ", mszsz.Get("ABC"));
	//AssertString("Detection", mszsz.Get("Collision"));
	//AssertString("Evolved", mszsz.Get("Retro"));
	//AssertString("Canada", mszsz.Get("Blame"));

	//cFile.Init(MemoryFile());
	//cFile.Open(EFM_Write_Create);
	//AssertTrue(mszsz.Write(&cFile));
	//mszsz.Kill();

	//cFile.Close();
	//cFile.Open(EFM_Read);

	//AssertTrue(mszszIn.Read(&cFile));

	//AssertString("XYZ", mszszIn.Get("ABC"));
	//AssertString("Detection", mszszIn.Get("Collision"));
	//AssertString("Evolved", mszszIn.Get("Retro"));
	//AssertString("Canada", mszszIn.Get("Blame"));

	//mszszIn.Kill();
	//cFile.Close();
	//cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetBlockDataMemoryUnchanged(void)
{
	//CSetString		mszsz;
	//size			i;
	//CRandom			cRandom;
	//CArrayChars		aszWords;
	//CChars			sz;
	//char*			szData;
	//char*			aszData[2048];
	//bool			bFailed;

	//WordsInit();

	//mszsz.Init();

	//cRandom.Init(2367849);
	//aszWords.Init();
	//GetCommonWords(&aszWords);

	//for (i = 0; i < 2048; i++)
	//{
	//	MakeKey(&cRandom, &aszWords, &sz);

	//	mszsz.Put(sz.Text(), IntToString(i));
	//	szData = mszsz.Get(sz.Text());
	//	aszData[i] = szData;

	//	sz.Kill();
	//}
	//cRandom.Kill();

	//cRandom.Init(2367849);

	//bFailed = false;
	//for (i = 0; i < 2048; i++)
	//{
	//	MakeKey(&cRandom, &aszWords, &sz);

	//	szData = mszsz.Get(sz.Text());
	//	if (aszData[i] != szData)
	//	{
	//		bFailed = true;
	//	}
	//	sz.Kill();
	//}

	//AssertFalse(bFailed);
	//
	//cRandom.Kill();
	//mszsz.Kill();

	//aszWords.Kill();
	//WordsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetBlockRemoveHalf(void)
{
	//CSetStringString	mszsz;
	//size				i;
	//CRandom				cRandom;
	//CArrayChars			aszWords;
	//CChars				sz;
	//char*				szData;
	//char*				aszData[2048];
	//bool				bResult;
	//bool				bFailed;

	//WordsInit();

	//mszsz.Init();

	//cRandom.Init(2367849);
	//aszWords.Init();
	//GetCommonWords(&aszWords);

	//for (i = 0; i < 2048; i++)
	//{
	//	MakeKey(&cRandom, &aszWords, &sz);

	//	mszsz.Put(sz.Text(), IntToString(i));
	//	szData = mszsz.Get(sz.Text());
	//	aszData[i] = szData;

	//	sz.Kill();
	//}
	//cRandom.Kill();

	//cRandom.Init(2367849);
	//bResult = true;
	//for (i = 0; i < 2048; i++)
	//{
	//	MakeKey(&cRandom, &aszWords, &sz);
	//	if (i % 2 == 1)
	//	{
	//		bResult &= mszsz.Remove(sz.Text());
	//	}
	//	sz.Kill();
	//}

	//AssertTrue(bResult);
	//AssertInt(1024, mszsz.NumElements());
	//cRandom.Kill();

	//bFailed = false;
	//cRandom.Init(2367849);
	//for (i = 0; i < 2048; i++)
	//{
	//	MakeKey(&cRandom, &aszWords, &sz);
	//	szData = mszsz.Get(sz.Text());
	//	if (i % 2 == 0)
	//	{
	//		if (aszData[i] != szData)
	//		{
	//			bFailed = true;
	//		}
	//	}
	//	else
	//	{
	//		if (szData != NULL)
	//		{
	//			bFailed = true;
	//		}
	//	}
	//	sz.Kill();
	//}
	//AssertFalse(bFailed);
	//cRandom.Kill();

	//mszsz.Kill();

	//aszWords.Kill();
	//WordsKill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetBlock(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestSetBlockInternals();
	TestSetBlockGet();
	TestSetBlockAddDuplicate();
	TestSetBlockRemove();
	TestSetBlockReadWrite();
	TestSetBlockDataMemoryUnchanged();
	TestSetBlockRemoveHalf();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

