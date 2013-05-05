#include "BaseLib/ArrayInt2D.h"
#include "TestLib/Assert.h"
#include "TestArrayInt2D.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayInt2DRemoval(void)
{
	CArrayInt2D		cArray;
	int				iValue;
	int				i;

	cArray.Init(1);
	cArray.SetSize(10, 10);
	cArray.CountFill(0, 0, 10, 10);

	cArray.RemoveRow(0);
	iValue = cArray.Get(0, 0);
	AssertInt(10, iValue);

	cArray.RemoveRow(8);
	AssertInt(8, cArray.miHeight);

	cArray.RemoveRow(4);
	iValue = cArray.Get(0, 4);
	AssertInt(60, iValue);
	cArray.Kill();

	cArray.Init(1);
	cArray.SetSize(10, 10);
	cArray.CountFill(0, 0, 10, 10);

	cArray.RemoveColumn(0);
	iValue = cArray.Get(0, 0);
	AssertInt(1, iValue);

	cArray.RemoveColumn(8);
	AssertInt(8, cArray.miWidth);

	cArray.RemoveColumn(4);
	iValue = cArray.Get(4, 0);
	AssertInt(6, iValue);

	for (i = 0; i < 6; i++)
	{
		cArray.RemoveColumn(1);
	}

	AssertInt(cArray.mcArray.GetValue(0), 1);
	AssertInt(cArray.mcArray.GetValue(1), 11);
	AssertInt(cArray.mcArray.GetValue(2), 21);
	AssertInt(cArray.mcArray.GetValue(3), 31);
	AssertInt(cArray.mcArray.GetValue(4), 41);
	AssertInt(cArray.mcArray.GetValue(5), 51);
	AssertInt(cArray.mcArray.GetValue(6), 61);
	AssertInt(cArray.mcArray.GetValue(7), 71);
	AssertInt(cArray.mcArray.GetValue(8), 81);
	AssertInt(cArray.mcArray.GetValue(9), 91);

	cArray.RemoveColumn(0);
	AssertInt(cArray.mcArray.NumElements(), 0);
	AssertInt(cArray.miWidth, 0);
	AssertInt(cArray.miHeight, 10);

	cArray.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayInt2DInsertion(void)
{
	CArrayInt2D		cArray;
	int				x;
	int				y;
	int				iValue;

	cArray.Init(1);
	cArray.SetSize(10, 10);
	cArray.Fill(0, 0, 10, 10, 0);
	for (y = 0; y < 10; y++)
	{
		for (x = 0; x < 10; x++)
		{
			iValue = cArray.Get(x, y);
			AssertInt(0, iValue);
		}
	}

	cArray.SetSize(20, 20);
	AssertInt(400, cArray.mcArray.NumElements());
	cArray.Fill(0, 0, 20, 20, 0x3e987c34);

	cArray.AddColumn();
	cArray.Set(20, 0, 0);

	for (x = 0; x < 20; x++)
	{
		iValue = cArray.Get(x, 0);
		AssertInt(0x3e987c34, iValue);
	}
	iValue = cArray.Get(20, 0);
	AssertInt(0, iValue);

	cArray.InsertColumn(10);
	cArray.Set(10, 0, 0);

	for (x = 0; x < 21; x++)
	{
		if (x != 10)
		{
			iValue = cArray.Get(x, 0);
			AssertInt(0x3e987c34, iValue);
		}
	}
	iValue = cArray.Get(21, 0);
	AssertInt(0, iValue);
	iValue = cArray.Get(10, 0);
	AssertInt(0, iValue);

	cArray.AddRow();
	cArray.Set(0, 20, 0);

	for (y = 0; y < 20; y++)
	{
		iValue = cArray.Get(0, y);
		AssertInt(0x3e987c34, iValue);
	}
	iValue = cArray.Get(0, 20);
	AssertInt(0, iValue);

	cArray.InsertRow(10);
	cArray.Set(0, 10, 0);

	for (y = 0; y < 21; y++)
	{
		if (y != 10)
		{
			iValue = cArray.Get(0, y);
			AssertInt(0x3e987c34, iValue);
		}
	}
	iValue = cArray.Get(0, 21);
	AssertInt(0, iValue);
	iValue = cArray.Get(0, 10);
	AssertInt(0, iValue);

	cArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayInt2D(void)
{
	BeginTests();

	TestArrayInt2DInsertion();
	TestArrayInt2DRemoval();

	TestStatistics();
}

