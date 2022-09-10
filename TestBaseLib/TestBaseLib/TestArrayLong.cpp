#include "BaseLib/ArrayLong.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayLongRemoveDuplicates(void)
{
	CArrayLong	cArray;
	bool		bRemoved;

	cArray.Init();
	cArray.AddList(0LL, 1LL, 2LL, 3LL, 4LL, 5LL, 6LL, 0LL);
	bRemoved = cArray.RemoveDuplicatesFromSorted();
	AssertInt(6, cArray.NumElements());
	AssertInt(8, cArray.AllocatedElements());
	AssertInt(4, cArray.ChunkSize());
	AssertInt(sizeof(long long int), cArray.ElementSize());
	AssertFalse(bRemoved);
	cArray.Kill();

	cArray.Init();
	cArray.AddList(0LL, 1LL, 2LL, 3LL, 4LL, 5LL, 5LL, 0LL);
	bRemoved = cArray.RemoveDuplicatesFromSorted();
	AssertInt(5, cArray.NumElements());
	AssertInt(8, cArray.AllocatedElements());
	AssertInt(4, cArray.ChunkSize());
	AssertTrue(bRemoved);
	cArray.Kill();

	cArray.Init();
	cArray.AddList(0LL, 2LL, 2LL, 3LL, 4LL, 5LL, 6LL, 0LL);
	bRemoved = cArray.RemoveDuplicatesFromSorted();
	AssertInt(5, cArray.NumElements());
	AssertInt(8, cArray.AllocatedElements());
	AssertInt(4, cArray.ChunkSize());
	AssertTrue(bRemoved);
	cArray.Kill();

	cArray.Init();
	cArray.AddList(0LL, 2LL, 2LL, 3LL, 4LL, 5LL, 5LL, 0LL);
	bRemoved = cArray.RemoveDuplicatesFromSorted();
	AssertInt(4, cArray.NumElements());
	AssertInt(4, cArray.AllocatedElements());
	AssertTrue(bRemoved);
	cArray.Kill();

	cArray.Init();
	cArray.AddList(0LL, 1LL, 1LL, 3LL, 3LL, 3LL, 3LL, 0LL);
	bRemoved = cArray.RemoveDuplicatesFromSorted();
	AssertInt(2, cArray.NumElements());
	AssertInt(4, cArray.AllocatedElements());
	AssertInt(4, cArray.ChunkSize());
	AssertTrue(bRemoved);
	cArray.Kill();

	cArray.Init();
	cArray.AddList(0LL, 1LL, 1LL, 1LL, 1LL, 1LL, 1LL, 0LL);
	bRemoved = cArray.RemoveDuplicatesFromSorted();
	AssertInt(1, cArray.NumElements());
	AssertInt(4, cArray.AllocatedElements());
	AssertInt(4, cArray.ChunkSize());
	AssertTrue(bRemoved);
	cArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayLong(void)
{
	BeginTests();

	TestArrayLongRemoveDuplicates();

	TestStatistics();

}

