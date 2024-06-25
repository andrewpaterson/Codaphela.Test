#include "SupportLib/RectanglePow2Packer.h"
#include "TestLib/Assert.h"
#include "TestRectanglePow2Packer.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRectanglePow2PackerStuff(void)
{
	CRectanglePow2Packer	cPacker;
	CRectangle				cRect1;
	CRectangle				cRect2;
	CRectangle				cRect3;
	char					sz1[] = "1";
	char					sz2[] = "2";
	char					sz3[] = "3";
	CArrayPackedRectangle	macRects;
	CPackedRectangle*		pcPackedRect;
	SInt2					sImageSize;

	cRect1.Init(0, 0, 7, 5);
	cRect2.Init(0, 0, 3, 5);
	cRect3.Init(0, 0, 4, 5);

	cPacker.Init(0, 0);

	cPacker.AddRectangle(&cRect1, sz1);
	cPacker.AddRectangle(&cRect2, sz2);
	cPacker.AddRectangle(&cRect3, sz3);

	cPacker.Pack();

	macRects.Init();
	cPacker.GetPackedRectangles(&macRects);

	AssertInt(3, macRects.NumElements());

	pcPackedRect = macRects.Get(0);
	AssertInt(0, pcPackedRect->miLeft);
	AssertInt(0, pcPackedRect->miTop);
	AssertInt(7, pcPackedRect->miRight);
	AssertInt(5, pcPackedRect->miBottom);

	pcPackedRect = macRects.Get(1);
	AssertInt(7, pcPackedRect->miLeft);
	AssertInt(0, pcPackedRect->miTop);
	AssertInt(11, pcPackedRect->miRight);
	AssertInt(5, pcPackedRect->miBottom);

	pcPackedRect = macRects.Get(2);
	AssertInt(11, pcPackedRect->miLeft);
	AssertInt(0, pcPackedRect->miTop);
	AssertInt(14, pcPackedRect->miRight);
	AssertInt(5, pcPackedRect->miBottom);

	sImageSize = cPacker.GetPackedImageSize();
	AssertInt(16, sImageSize.x);
	AssertInt(8, sImageSize.y);

	macRects.Kill();
	cPacker.Kill();

	/////
	
	cPacker.Init(2, 1);

	cPacker.AddRectangle(&cRect1, sz1);
	cPacker.AddRectangle(&cRect2, sz2);
	cPacker.AddRectangle(&cRect3, sz3);

	cPacker.Pack();

	macRects.Init();
	cPacker.GetPackedRectangles(&macRects);

	AssertInt(3, macRects.NumElements());

	pcPackedRect = macRects.Get(0);
	AssertInt(2, pcPackedRect->miLeft);
	AssertInt(2, pcPackedRect->miTop);
	AssertInt(9, pcPackedRect->miRight);
	AssertInt(7, pcPackedRect->miBottom);

	pcPackedRect = macRects.Get(1);
	AssertInt(10, pcPackedRect->miLeft);
	AssertInt(2, pcPackedRect->miTop);
	AssertInt(14, pcPackedRect->miRight);
	AssertInt(7, pcPackedRect->miBottom);

	pcPackedRect = macRects.Get(2);
	AssertInt(2, pcPackedRect->miLeft);
	AssertInt(8, pcPackedRect->miTop);
	AssertInt(5, pcPackedRect->miRight);
	AssertInt(13, pcPackedRect->miBottom);

	sImageSize = cPacker.GetPackedImageSize();
	AssertInt(16, sImageSize.x);
	AssertInt(16, sImageSize.y);

	macRects.Kill();
	cPacker.Kill();
}




//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRectanglePow2Packer(void)
{
	BeginTests();

	TestRectanglePow2PackerStuff();

	TestStatistics();
}
