#include "BaseLib/ArrayFloat.h"
#include "BaseLib/ArrayDouble.h"
#include "BaseLib/ArrayChar.h"
#include "BaseLib/ArrayLong.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplatePrimitive(void)
{
	CArrayChar		aChars;
	CArrayFloat		aFloats;
	CArrayDouble	aDoubles;
	CArrayLong		aLongs;
	int				iIndex;

	BeginTests();

	aChars.Init();
	aChars.Add('A');
	AssertChar('A', aChars.GetValue(0));
	aChars.Kill();

	aFloats.Init();
	aFloats.InsertAt(5.1f, 0);
	AssertFloat(5.1f, aFloats.GetValue(0), 2);
	AssertInt(1, aFloats.AllocatedElements());
	AssertInt(1, aFloats.ChunkSize());
	AssertInt(1, aFloats.NumElements());
	aFloats.Kill();

	aDoubles.Init();
	aDoubles.Add(0.0);
	aDoubles.Add(0.1);
	aDoubles.Add(0.2);
	aDoubles.Add(0.3);
	aDoubles.Add(0.4);
	AssertTrue(aDoubles.IsSorted());
	aDoubles.InsertAt(0.5, 2);
	AssertFalse(aDoubles.IsSorted());
	aDoubles.Kill();

	aLongs.Init();
	aLongs.AddList(0LL, 4LL, 0x3122345482773411LL, 2LL, 1LL, 0LL);
	iIndex = aLongs.Find(0x3122345482773411LL);
	AssertInt(1, iIndex);
	aLongs.Kill();

	TestStatistics();
}

