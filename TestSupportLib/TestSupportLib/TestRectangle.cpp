#include "SupportLib/Rectangle.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertRectangle(int32 iLeft, int32 iTop, int32 iRight, int32 iBottom, CRectangle* pcRectangle)
{
	AssertInt(iLeft, pcRectangle->GetLeft());
	AssertInt(iTop, pcRectangle->GetTop());
	AssertInt(iRight, pcRectangle->GetRight());
	AssertInt(iBottom, pcRectangle->GetBottom());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRectangleClipTo(void)
{
	CRectangle	cBounds;
	CRectangle	cRectangle;

	cBounds.Init(0, 0, 10, 10);

	//A rectangle already inside its bounds is not changed.
	cRectangle.Init(2, 3, 8, 9);
	cRectangle.ClipTo(&cBounds);
	AssertRectangle(2, 3, 8, 9, &cRectangle);

	//Overhanging every side it is cut back to the bounds.
	cRectangle.Init(-5, -4, 15, 14);
	cRectangle.ClipTo(&cBounds);
	AssertRectangle(0, 0, 10, 10, &cRectangle);

	//Only the sides that overhang are cut back.
	cRectangle.Init(-3, 2, 6, 12);
	cRectangle.ClipTo(&cBounds);
	AssertRectangle(0, 2, 6, 10, &cRectangle);

	//Bounds smaller than the rectangle leave just the bounds.
	cRectangle.Init(0, 0, 20, 20);
	cBounds.Init(5, 6, 7, 8);
	cRectangle.ClipTo(&cBounds);
	AssertRectangle(5, 6, 7, 8, &cRectangle);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRectangleGetArea(void)
{
	CRectangle	cRect;

	cRect.Init(2, 3, 12, 8);
	AssertLong(50, cRect.GetArea());

	//A 50mm square in micrometres is more than 32 bits hold.
	cRect.Init(0, 0, 50000, 50000);
	AssertLong(2500000000LL, cRect.GetArea());

	cRect.Init(-60000, -70000, 60000, 70000);
	AssertLong(16800000000LL, cRect.GetArea());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRectangle(void)
{
	BeginTests();

	TestRectangleClipTo();
	TestRectangleGetArea();

	TestStatistics();
}

