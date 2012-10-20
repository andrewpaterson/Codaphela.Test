#include "BaseLib/TreeInt.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/Numbers.h"
#include "BaseLib/Chars.h"
#include "BaseLib/MapTemplate.h"
#include "BaseLib/MapStringTemplate.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/MapStringInt.h"
#include "TestLib/Assert.h"


typedef CMapTemplate<int, int> CMapIntInt;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringString(void)
{
	CMapStringString	cMapStringSting;
	CChars*				sz1;
	CChars				szKey;
	char*				sz2;

	cMapStringSting.Init(11);

	cMapStringSting.Put("Hello", "World");
	cMapStringSting.Put("Michelle", "Bridget");
	cMapStringSting.Put("Number", "String");
	cMapStringSting.Put("Michelle", "Megan");

	szKey.Init("Michelle");
	sz1 = cMapStringSting.GetWithKey(&szKey);
	AssertString("Megan", sz1->Text());
	szKey.Kill();

	sz2 = cMapStringSting.GetWithKey("Michelle");
	AssertString("Megan", sz2);

	cMapStringSting.Kill();
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringInt(void)
{
	CMapStringInt	cMapStringInt;
	CChars			sz;
	int				x;
	int*			px;

	cMapStringInt.Init(11);

	sz.Init("Hello");  x = 73;
	cMapStringInt.Put(&sz, x);
	sz.Kill();

	sz.Init("World");  x = 12;
	cMapStringInt.Put(&sz, x);
	sz.Kill();

	x = 324;
	cMapStringInt.Put("Hello", x);

	px = cMapStringInt.GetWithKey("Hello");
	px = cMapStringInt.GetWithKey("World");
	px = cMapStringInt.GetWithKey("Miner");

	cMapStringInt.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapIntInt(void)
{
	CMapIntInt	cMapIntInt;
	int			x, y, i;
	int			*px, *py, *pz;

	cMapIntInt.Init(11, CompareInt);

	x = 10; y = 73;
	cMapIntInt.Put(&x, &y);

	x = 5; y = 12;
	cMapIntInt.Put(&x, &y);

	x = 15; y = 139;
	cMapIntInt.Put(&x, &y);

	x = 5; y = 99;
	cMapIntInt.Put(&x, &y);

	for (i = 0; i < cMapIntInt.NumElements(); i++)
	{
		cMapIntInt.GetAtIndex(i, &px, &py);
		pz = cMapIntInt.GetWithKey(px);
		AssertInt(*py, *pz);
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

