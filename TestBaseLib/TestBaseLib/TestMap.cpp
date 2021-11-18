#include "BaseLib/IntegerHelper.h"
#include "BaseLib/Numbers.h"
#include "BaseLib/Chars.h"
#include "BaseLib/MapTemplate.h"
#include "BaseLib/MapStringTemplate.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/MapStringInt.h"
#include "BaseLib/TreeTemplate.h"
#include "TestLib/Assert.h"
#include "TestMap.h"


typedef CMapTemplate<int, int> CMapIntInt;
typedef CTreeTemplate<int> CTreeInt;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringString2(void)
{
	CMapStringString	cMapStringSting;
	char*				sz1;

	cMapStringSting.Init();

	cMapStringSting.Put("Hello", "World");
	cMapStringSting.Put("Michelle", "Bridget");
	cMapStringSting.Put("Number", "String");
	cMapStringSting.Put("Michelle", "Megan");

	sz1 = cMapStringSting.Get("Michelle");
	AssertString("Megan", sz1);

	cMapStringSting.Kill();
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringInt2(void)
{
	CMapStringInt	cMapStringInt;
	int				x;

	cMapStringInt.Init();
	cMapStringInt.Put("Hello", 73);
	cMapStringInt.Put("World", 12);
	cMapStringInt.Put("Hello", 324);

	x = cMapStringInt.Get("Hello");
	AssertInt(324, x);
	x = cMapStringInt.Get("World");
	AssertInt(12, x);
	x = cMapStringInt.Get("Miner");
	AssertInt(-1, x);

	cMapStringInt.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapIntInt2(void)
{
	CMapIntInt		cMapIntInt;
	int				*px, *py, *pz;
	SMapIterator	sIter;
	BOOL			bResult;
	int				x, y;

	cMapIntInt.Init(CompareInt, TRUE);

	x = 10; y = 73;
	cMapIntInt.Put(&x, &y);

	x = 5; y = 12;
	cMapIntInt.Put(&x, &y);

	x = 15; y = 139;
	cMapIntInt.Put(&x, &y);

	x = 5; y = 99;
	cMapIntInt.Put(&x, &y);

	bResult = cMapIntInt.StartIteration(&sIter, (void**)&px, NULL, (void**)&py, NULL);
	while (bResult)
	{
		pz = cMapIntInt.Get(px);
		AssertInt(*py, *pz);
		bResult = cMapIntInt.Iterate(&sIter, (void**)&px, NULL, (void**)&py, NULL);
	}

	cMapIntInt.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void DumpTree(CTreeInt* pcTree)
{
	int* pi;
	CChars c;

	pi = pcTree->StartTraversal();
	c.Init("-----------------\n");
	while (pi)
	{
		c.Append(' ', pcTree->miLevel);
		c.Append(*pi);
		c.AppendNewLine();

		pi = pcTree->TraverseFrom(pi);
	}
	c.Append("\n\n");
	c.Dump();
	c.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void MakeKey(CRandom* cRandom, CArrayChars* aszWords, CChars* sz)
{
	int		iIndex;
	char* szWord;

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
void TestMap(void)
{
	BeginTests();

	TestMapStringString2();
	TestMapStringInt2();
	TestMapIntInt2();

	TestStatistics();
}

