#include "BaseLib/ArrayInt.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayIntAddFind(void)
{
	CArrayInt	cArray;

	cArray.Init();
	cArray.AddList(-1, 1, 2, 3, 4, -1);

	cArray.AddIfUnique(5);

	AssertInt(5, cArray.NumElements());
	AssertInt(1, cArray[0]);
	AssertInt(2, cArray[1]);
	AssertInt(3, cArray[2]);
	AssertInt(4, cArray[3]);
	AssertInt(5, cArray[4]);

	cArray.AddIfUnique(5);

	AssertInt(5, cArray.NumElements());
	AssertInt(1, cArray[0]);
	AssertInt(2, cArray[1]);
	AssertInt(3, cArray[2]);
	AssertInt(4, cArray[3]);
	AssertInt(5, cArray[4]);

	cArray.InsertIntoSorted(2, FALSE);

	AssertInt(6, cArray.NumElements());
	AssertInt(1, cArray[0]);
	AssertInt(2, cArray[1]);
	AssertInt(2, cArray[2]);
	AssertInt(3, cArray[3]);
	AssertInt(4, cArray[4]);
	AssertInt(5, cArray[5]);

	cArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayIntSortingUsingQuickSort(void)
{
	CArrayInt	cArray;

	cArray.Init();
	cArray.AddList(-1, 4, 3, 7, 8, 1, 9, 0, 2, 4, 2, -1);

	cArray.QuickSort();

	AssertInt(10, cArray.NumElements());
	AssertInt(0, cArray[0]);
	AssertInt(1, cArray[1]);
	AssertInt(2, cArray[2]);
	AssertInt(2, cArray[3]);
	AssertInt(3, cArray[4]);
	AssertInt(4, cArray[5]);
	AssertInt(4, cArray[6]);
	AssertInt(7, cArray[7]);
	AssertInt(8, cArray[8]);
	AssertInt(9, cArray[9]);

	cArray.InsertIntoSorted(7, FALSE);
	cArray.InsertIntoSorted(1, TRUE);

	AssertInt(11, cArray.NumElements());
	AssertInt(0, cArray[0]);
	AssertInt(1, cArray[1]);
	AssertInt(2, cArray[2]);
	AssertInt(2, cArray[3]);
	AssertInt(3, cArray[4]);
	AssertInt(4, cArray[5]);
	AssertInt(4, cArray[6]);
	AssertInt(7, cArray[7]);
	AssertInt(7, cArray[8]);
	AssertInt(8, cArray[9]);
	AssertInt(9, cArray[10]);

	cArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayIntSortingUsingBubbleSort(void)
{
	CArrayInt	cArray;

	cArray.Init();
	cArray.AddList(-1, 4, 3, 7, 8, 1, 9, 0, 2, 4, 2, -1);

	cArray.BubbleSort();

	AssertInt(10, cArray.NumElements());
	AssertInt(0, cArray[0]);
	AssertInt(1, cArray[1]);
	AssertInt(2, cArray[2]);
	AssertInt(2, cArray[3]);
	AssertInt(3, cArray[4]);
	AssertInt(4, cArray[5]);
	AssertInt(4, cArray[6]);
	AssertInt(7, cArray[7]);
	AssertInt(8, cArray[8]);
	AssertInt(9, cArray[9]);

	cArray.InsertIntoSorted(7, FALSE);
	cArray.InsertIntoSorted(1, TRUE);

	AssertInt(11, cArray.NumElements());
	AssertInt(0, cArray[0]);
	AssertInt(1, cArray[1]);
	AssertInt(2, cArray[2]);
	AssertInt(2, cArray[3]);
	AssertInt(3, cArray[4]);
	AssertInt(4, cArray[5]);
	AssertInt(4, cArray[6]);
	AssertInt(7, cArray[7]);
	AssertInt(7, cArray[8]);
	AssertInt(8, cArray[9]);
	AssertInt(9, cArray[10]);

	cArray.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayIntRemoveDuplicates(void)
{
	CArrayInt	cArray;

	cArray.Init();
	cArray.AddList(-1, 1, 1, 2, 3, 3, 3, 4, 5, 5, -1);
	cArray.RemoveDuplicatesFromSorted();
	AssertInt(5, cArray.NumElements());
	AssertInt(1, cArray[0]);
	AssertInt(2, cArray[1]);
	AssertInt(3, cArray[2]);
	AssertInt(4, cArray[3]);
	AssertInt(5, cArray[4]);

	cArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayIntRemoveAt(void)
{
	CArrayInt	cArray;
	CArrayInt	cKiller;

	////////////////////////////////////////////////
	cArray.Init();

	//                 0  1  2  3  4  5  6  7  8  9  Stop
	cArray.AddList(-1, 4, 3, 7, 8, 1, 9, 0, 2, 4, 2, -1);

	AssertInt(10, cArray.NumElements());

	cKiller.Init();
	cKiller.AddList(-1, 8, 5, 0, 5, -1);
	cKiller.MakeUnique();

	cArray.RemoveAt(cKiller.GetData(), cKiller.NumElements());

	AssertInt(7, cArray.NumElements());

	AssertInt(3, cArray[0]);
	AssertInt(7, cArray[1]);
	AssertInt(8, cArray[2]);
	AssertInt(1, cArray[3]);
	AssertInt(0, cArray[4]);
	AssertInt(2, cArray[5]);
	AssertInt(2, cArray[6]);

	cKiller.Kill();
	cArray.Kill();

	////////////////////////////////////////////////
	cArray.Init();

	//                 0  1  2  3  4  5  6  7  8  9  Stop
	cArray.AddList(-1, 4, 3, 7, 8, 1, 9, 0, 2, 4, 2, -1);

	AssertInt(10, cArray.NumElements());

	cKiller.Init();
	cKiller.AddList(-1, 8, 5, 2, -1);
	cKiller.MakeUnique();

	cArray.RemoveAt(cKiller.GetData(), cKiller.NumElements());

	AssertInt(7, cArray.NumElements());

	AssertInt(4, cArray[0]);
	AssertInt(3, cArray[1]);
	AssertInt(8, cArray[2]);
	AssertInt(1, cArray[3]);
	AssertInt(0, cArray[4]);
	AssertInt(2, cArray[5]);
	AssertInt(2, cArray[6]);

	cKiller.Kill();
	cArray.Kill();

	////////////////////////////////////////////////
	cArray.Init();

	//                 0  1  2  3  4  5  6  7  8  9  Stop
	cArray.AddList(-1, 4, 3, 7, 8, 1, 9, 0, 2, 4, 2, -1);

	AssertInt(10, cArray.NumElements());

	cKiller.Init();
	cKiller.AddList(-1, 0, 1, 2, 7, 8, 9, -1);
	cKiller.MakeUnique();

	cArray.RemoveAt(cKiller.GetData(), cKiller.NumElements());

	AssertInt(4, cArray.NumElements());

	AssertInt(8, cArray[0]);
	AssertInt(1, cArray[1]);
	AssertInt(9, cArray[2]);
	AssertInt(0, cArray[3]);

	cKiller.Kill();
	cArray.Kill();

	////////////////////////////////////////////////
	cArray.Init();

	//                 0  1  2  3  4  5  6  7  8  9  Stop
	cArray.AddList(-1, 4, 3, 7, 8, 1, 9, 0, 2, 4, 2, -1);

	AssertInt(10, cArray.NumElements());

	cKiller.Init();
	cKiller.AddList(-1, 3, 4, 5, 6, -1);
	cKiller.MakeUnique();

	cArray.RemoveAt(cKiller.GetData(), cKiller.NumElements());

	AssertInt(6, cArray.NumElements());

	AssertInt(4, cArray[0]);
	AssertInt(3, cArray[1]);
	AssertInt(7, cArray[2]);
	AssertInt(2, cArray[3]);
	AssertInt(4, cArray[4]);
	AssertInt(2, cArray[5]);

	cKiller.Kill();
	cArray.Kill();

	////////////////////////////////////////////////
	cArray.Init();

	//                 0  1  2  3  4  5  6  7  8  9  Stop
	cArray.AddList(-1, 4, 3, 7, 8, 1, 9, 0, 2, 4, 2, -1);

	cKiller.Init();
	cKiller.AddList(-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1);
	cKiller.MakeUnique();

	cArray.RemoveAt(cKiller.GetData(), cKiller.NumElements());

	AssertInt(0, cArray.NumElements());

	cKiller.Kill();
	cArray.Kill();


	////////////////////////////////////////////////
	cArray.Init();

	//                 0  1  2  3  4  5  6  7  8  9  Stop
	cArray.AddList(-1, 4, 3, 7, 8, 1, 9, 0, 2, 4, 2, -1);

	cKiller.Init();
	cKiller.AddList(-1, -1);
	cKiller.MakeUnique();

	cArray.RemoveAt(cKiller.GetData(), cKiller.NumElements());

	AssertInt(10, cArray.NumElements());

	AssertInt(4, cArray[0]);
	AssertInt(3, cArray[1]);
	AssertInt(7, cArray[2]);
	AssertInt(8, cArray[3]);
	AssertInt(1, cArray[4]);
	AssertInt(9, cArray[5]);
	AssertInt(0, cArray[6]);
	AssertInt(2, cArray[7]);
	AssertInt(4, cArray[8]);
	AssertInt(2, cArray[9]);

	cKiller.Kill();
	cArray.Kill();

	////////////////////////////////////////////////
	cArray.Init();

	//                 0  1  2  3  4  5  6  7  8  9  Stop
	cArray.AddList(-1, 4, 3, 7, 8, 1, 9, 0, 2, 4, 2, -1);

	cKiller.Init();
	cKiller.AddList(-1, 0, 2, 4, 6, 8, -1);
	cKiller.MakeUnique();

	cArray.RemoveAt(cKiller.GetData(), cKiller.NumElements());

	AssertInt(5, cArray.NumElements());

	AssertInt(3, cArray[0]);
	AssertInt(8, cArray[1]);
	AssertInt(9, cArray[2]);
	AssertInt(2, cArray[3]);
	AssertInt(2, cArray[4]);

	cKiller.Kill();
	cArray.Kill();

	////////////////////////////////////////////////
	cArray.Init();

	//                 0  1  2  3  4  5  6  7  8  9  Stop
	cArray.AddList(-1, 4, 3, 7, 8, 1, 9, 0, 2, 4, 2, -1);

	cKiller.Init();
	cKiller.AddList(-1, 1, 3, 5, 7, 9, -1);
	cKiller.MakeUnique();

	cArray.RemoveAt(cKiller.GetData(), cKiller.NumElements());

	AssertInt(5, cArray.NumElements());

	AssertInt(4, cArray[0]);
	AssertInt(7, cArray[1]);
	AssertInt(1, cArray[2]);
	AssertInt(0, cArray[3]);
	AssertInt(4, cArray[4]);

	cKiller.Kill();
	cArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayInt(void)
{
	BeginTests();
	FastFunctionsInit();

	TestArrayIntAddFind();
	TestArrayIntSortingUsingQuickSort();
	TestArrayIntSortingUsingBubbleSort();
	TestArrayIntRemoveDuplicates();
	TestArrayIntRemoveAt();

	FastFunctionsKill();
	TestStatistics();
}

