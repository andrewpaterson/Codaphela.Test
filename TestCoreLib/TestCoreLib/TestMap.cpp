#include "BaseLib/IntegerHelper.h"
#include "BaseLib/Numbers.h"
#include "BaseLib/Chars.h"
#include "BaseLib/MapTemplate.h"
#include "BaseLib/MapStringTemplate.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/MapStringInt.h"
#include "BaseLib/TreeTemplate.h"
#include "TestLib/Assert.h"


typedef CMapTemplate<int, int> CMapIntInt;
typedef CTreeTemplate<int> CTreeInt;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringString(void)
{
	CMapStringString	cMapStringSting;
	char*				sz1;

	cMapStringSting.Init(11);

	cMapStringSting.Put("Hello", "World");
	cMapStringSting.Put("Michelle", "Bridget");
	cMapStringSting.Put("Number", "String");
	cMapStringSting.Put("Michelle", "Megan");

	sz1 = cMapStringSting.Get("Michelle");
	//AssertString("Megan", sz1);  //Should have overwritten.
	AssertString("Bridget", sz1);

	cMapStringSting.Kill();
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringInt(void)
{
	CMapStringInt	cMapStringInt;
	int*			px;

	cMapStringInt.Init(11);
	cMapStringInt.Put("Hello", 73);
	cMapStringInt.Put("World", 12);
	cMapStringInt.Put("Hello", 324);

	px = cMapStringInt.Get("Hello");
	AssertInt(73, *px);
	px = cMapStringInt.Get("World");
	AssertInt(12, *px);
	px = cMapStringInt.Get("Miner");
	AssertNull(px);

	cMapStringInt.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapIntInt(void)
{
	CMapIntInt		cMapIntInt;
	int				*px, *py, *pz;
	SMapIterator	sIter;
	BOOL			bResult;
	int				x, y;

	cMapIntInt.Init(&gcSystemAllocator, 11, CompareInt);

	x = 10; y = 73;
	cMapIntInt.Put(&x, &y);

	x = 5; y = 12;
	cMapIntInt.Put(&x, &y);

	x = 15; y = 139;
	cMapIntInt.Put(&x, &y);

	x = 5; y = 99;
	cMapIntInt.Put(&x, &y);

	bResult = cMapIntInt.StartIteration(&sIter, (void**)&px, (void**)&py);
	while (bResult)
	{
		pz = cMapIntInt.Get(px);
		AssertInt(*py, *pz);
		bResult = cMapIntInt.Iterate(&sIter, (void**)&px, (void**)&py);
	}

	cMapIntInt.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMap(void)
{
	BeginTests();

	TestMapStringString();
	TestMapStringInt();
	TestMapIntInt();

	TestStatistics();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void DumpTree(CTreeInt* pcTree)
{
	int*		pi;
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

