#include "BaseLib/MemoryFile.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/ArrayBlockSorted.h"
#include "TestLib/Assert.h"
#include "SortedTestObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void ListAddInt(CArrayBlockSorted* pcArray, int i)
{
	pcArray->Add(&i);
}


void AssertListInt(CArrayBlockSorted* pcArray, int ai ...)
{
	va_list		vaMarker;
	int			i;
	int			iCount;
	int*		piExpected;

	iCount = 0;
	i = ai;

	va_start(vaMarker, ai);
	while (i != -1)
	{
		piExpected = (int*)pcArray->GetInSorted(iCount);
		AssertNotNull(piExpected);
		AssertInt(i, *piExpected);
		iCount++;
		i = va_arg(vaMarker, int);
	}
	va_end(vaMarker);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedAddBasic(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);
	AssertInt(0, avBlock.NumElements());
	AssertInt(0, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	ListAddInt(&avBlock, 2);
	AssertInt(1, avBlock.NumElements());
	AssertInt(0, avBlock.GetSortedSize());
	AssertInt(1, avBlock.GetHoldingSize());

	ListAddInt(&avBlock, 4);
	AssertInt(2, avBlock.NumElements());
	AssertInt(0, avBlock.GetSortedSize());
	AssertInt(2, avBlock.GetHoldingSize());

	ListAddInt(&avBlock, 8);
	AssertInt(3, avBlock.NumElements());
	AssertInt(0, avBlock.GetSortedSize());
	AssertInt(3, avBlock.GetHoldingSize());

	ListAddInt(&avBlock, 10);
	AssertInt(4, avBlock.NumElements());
	AssertInt(4, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedAdd(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 8);
	ListAddInt(&avBlock, 10);
	AssertInt(4, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedAddAfter(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 8);
	ListAddInt(&avBlock, 10);
	AssertInt(4, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	ListAddInt(&avBlock, 11);
	ListAddInt(&avBlock, 13);
	ListAddInt(&avBlock, 12);
	ListAddInt(&avBlock, 14);
	AssertInt(8, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertListInt(&avBlock, 2, 4, 8, 10, 11, 12, 13, 14, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedAddBefore(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);
	ListAddInt(&avBlock, 5);
	ListAddInt(&avBlock, 6);
	ListAddInt(&avBlock, 7);
	ListAddInt(&avBlock, 8);
	AssertInt(4, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	ListAddInt(&avBlock, 1);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 3);
	ListAddInt(&avBlock, 4);
	AssertInt(8, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertListInt(&avBlock, 1, 2, 3, 4, 5, 6, 7, 8, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedAddAfterAndMiddle(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 8);
	ListAddInt(&avBlock, 10);
	AssertInt(4, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	ListAddInt(&avBlock, 6);
	ListAddInt(&avBlock, 7);
	ListAddInt(&avBlock, 12);
	ListAddInt(&avBlock, 14);
	AssertInt(8, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertListInt(&avBlock, 2, 4, 6, 7, 8, 10, 12, 14, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedAddBeforeAndMiddle(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);
	ListAddInt(&avBlock, 5);
	ListAddInt(&avBlock, 6);
	ListAddInt(&avBlock, 9);
	ListAddInt(&avBlock, 10);
	AssertInt(4, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	ListAddInt(&avBlock, 1);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 7);
	ListAddInt(&avBlock, 8);
	AssertInt(8, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertListInt(&avBlock, 1, 2, 5, 6, 7, 8, 9, 10, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedAddBeforeAndMiddleAndEnd(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);
	ListAddInt(&avBlock, 1);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 5);
	AssertInt(4, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	ListAddInt(&avBlock, 0);
	ListAddInt(&avBlock, 3);
	ListAddInt(&avBlock, 6);
	ListAddInt(&avBlock, 7);
	AssertInt(8, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertListInt(&avBlock, 0, 1, 2, 3, 4, 5, 6, 7, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedAddMiddleAndMiddle(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 6, 1, CompareInt);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 8);
	ListAddInt(&avBlock, 10);
	ListAddInt(&avBlock, 14);
	ListAddInt(&avBlock, 16);
	AssertInt(6, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	ListAddInt(&avBlock, 5);
	ListAddInt(&avBlock, 6);
	ListAddInt(&avBlock, 7);
	ListAddInt(&avBlock, 11);
	ListAddInt(&avBlock, 12);
	ListAddInt(&avBlock, 13);
	AssertInt(12, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertListInt(&avBlock, 2, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 16, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedToListSmallList(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 8);
	AssertInt(0, avBlock.GetSortedSize());
	AssertInt(3, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertInt(3, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	AssertListInt(&avBlock, 2, 4, 8, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedToListBigList1After(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 8);
	ListAddInt(&avBlock, 10);
	ListAddInt(&avBlock, 12);
	ListAddInt(&avBlock, 14);
	ListAddInt(&avBlock, 16);
	AssertInt(4, avBlock.GetSortedSize());
	AssertInt(3, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertInt(7, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	AssertListInt(&avBlock, 2, 4, 8, 10, 12, 14, 16, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedToListBigList2After(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 8);
	ListAddInt(&avBlock, 10);
	ListAddInt(&avBlock, 12);
	ListAddInt(&avBlock, 14);
	AssertInt(4, avBlock.GetSortedSize());
	AssertInt(2, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertInt(6, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	AssertListInt(&avBlock, 2, 4, 8, 10, 12, 14, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedToListBigList3After(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 8);
	ListAddInt(&avBlock, 10);
	ListAddInt(&avBlock, 12);
	AssertInt(4, avBlock.GetSortedSize());
	AssertInt(1, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertInt(5, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	AssertListInt(&avBlock, 2, 4, 8, 10, 12, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedToListBigList1Before(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);
	ListAddInt(&avBlock, 10);
	ListAddInt(&avBlock, 12);
	ListAddInt(&avBlock, 14);
	ListAddInt(&avBlock, 16);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 8);
	AssertInt(4, avBlock.GetSortedSize());
	AssertInt(3, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertInt(7, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	AssertListInt(&avBlock, 2, 4, 8, 10, 12, 14, 16, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedToListBigList2Before(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);
	ListAddInt(&avBlock, 8);
	ListAddInt(&avBlock, 10);
	ListAddInt(&avBlock, 12);
	ListAddInt(&avBlock, 14);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 4);
	AssertInt(4, avBlock.GetSortedSize());
	AssertInt(2, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertInt(6, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	AssertListInt(&avBlock, 2, 4, 8, 10, 12, 14, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedToListBigList3Before(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 8);
	ListAddInt(&avBlock, 10);
	ListAddInt(&avBlock, 12);
	ListAddInt(&avBlock, 2);
	AssertInt(4, avBlock.GetSortedSize());
	AssertInt(1, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertInt(5, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	AssertListInt(&avBlock, 2, 4, 8, 10, 12, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedStaggeredLeftSingle(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);

	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 6);
	ListAddInt(&avBlock, 8);

	ListAddInt(&avBlock, 1);
	ListAddInt(&avBlock, 3);
	ListAddInt(&avBlock, 5);
	ListAddInt(&avBlock, 7);

	AssertInt(8, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertListInt(&avBlock, 1, 2, 3, 4, 5, 6, 7, 8, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedStaggeredRightSingle(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);

	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 6);
	ListAddInt(&avBlock, 8);

	ListAddInt(&avBlock, 3);
	ListAddInt(&avBlock, 5);
	ListAddInt(&avBlock, 7);
	ListAddInt(&avBlock, 9);

	AssertInt(8, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertListInt(&avBlock, 2, 3, 4, 5, 6, 7, 8, 9, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedStaggeredLeftDouble(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);

	ListAddInt(&avBlock, 1);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 5);
	ListAddInt(&avBlock, 6);

	ListAddInt(&avBlock, 3);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 7);
	ListAddInt(&avBlock, 8);

	AssertInt(8, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertListInt(&avBlock, 1, 2, 3, 4, 5, 6, 7, 8, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedStaggeredRightDouble(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 1, CompareInt);

	ListAddInt(&avBlock, 5);
	ListAddInt(&avBlock, 6);
	ListAddInt(&avBlock, 9);
	ListAddInt(&avBlock, 10);

	ListAddInt(&avBlock, 3);
	ListAddInt(&avBlock, 4);
	ListAddInt(&avBlock, 7);
	ListAddInt(&avBlock, 8);

	AssertInt(8, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertListInt(&avBlock, 3, 4, 5, 6, 7, 8, 9, 10, -1);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedMultipleBuffers(void)
{
	CArrayBlockSorted	avBlock;

	avBlock.Init(sizeof(int), 10, 4, 4, CompareInt);

	ListAddInt(&avBlock, 9);
	ListAddInt(&avBlock, 10);
	ListAddInt(&avBlock, 11);
	ListAddInt(&avBlock, 12);

	ListAddInt(&avBlock, 13);
	ListAddInt(&avBlock, 14);
	ListAddInt(&avBlock, 15);
	ListAddInt(&avBlock, 16);

	ListAddInt(&avBlock, 1);
	ListAddInt(&avBlock, 2);
	ListAddInt(&avBlock, 3);
	ListAddInt(&avBlock, 4);

	ListAddInt(&avBlock, 5);
	ListAddInt(&avBlock, 6);
	ListAddInt(&avBlock, 7);

	AssertInt(0, avBlock.GetSortedSize());
	AssertInt(15, avBlock.GetHoldingSize());

	ListAddInt(&avBlock, 8);

	AssertInt(16, avBlock.GetSortedSize());
	AssertInt(0, avBlock.GetHoldingSize());

	avBlock.InsertHoldingIntoSorted();
	AssertListInt(&avBlock, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, -1);

	avBlock.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockReadWrite(void)
{
	CArrayBlockSorted	avBlock;
	CFileBasic			cFile;
	CArrayBlockSorted	avBlockIn;
	int					iKey;
	int*				piData;

	avBlock.Init(sizeof(int), 10, 4, 4, CompareInt);

	ListAddInt(&avBlock, 9);
	ListAddInt(&avBlock, 10);
	ListAddInt(&avBlock, 11);
	ListAddInt(&avBlock, 12);

	iKey = 9; piData = (int*)avBlock.Get(&iKey);  
	AssertNotNull(piData); AssertInt(iKey, *piData);
	iKey = 10; piData = (int*)avBlock.Get(&iKey);  
	AssertNotNull(piData); AssertInt(iKey, *piData);
	iKey = 11; piData = (int*)avBlock.Get(&iKey);  
	AssertNotNull(piData); AssertInt(iKey, *piData);
	iKey = 12; piData = (int*)avBlock.Get(&iKey);  
	AssertNotNull(piData); AssertInt(iKey, *piData);

	cFile.Init(MemoryFile());
	cFile.Open(EFM_Write_Create);
	AssertTrue(avBlock.Write(&cFile));
	avBlock.Kill();

	cFile.Close();
	cFile.Open(EFM_Read);

	AssertTrue(avBlockIn.Read(&cFile, CompareInt));

	iKey = 9; piData = (int*)avBlockIn.Get(&iKey);  
	AssertNotNull(piData); AssertInt(iKey, *piData);
	iKey = 10; piData = (int*)avBlockIn.Get(&iKey);  
	AssertNotNull(piData); AssertInt(iKey, *piData);
	iKey = 11; piData = (int*)avBlockIn.Get(&iKey);  
	AssertNotNull(piData); AssertInt(iKey, *piData);
	iKey = 12; piData = (int*)avBlockIn.Get(&iKey);  
	AssertNotNull(piData); AssertInt(iKey, *piData);

	avBlockIn.Kill();
	cFile.Close();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSortedAddDuplicate(void)
{
	CArrayBlockSorted	avBlock;
	CFileBasic			cFile;
	CSortedTestObject	cObject;
	CSortedTestObject*	pcObject;
	int					i;

	avBlock.Init(&gcSystemAllocator, sizeof(CSortedTestObject), 4, 0, 0, &CompareSortedTestObject);

	cObject.Init(1, "One");
	avBlock.Add(&cObject);

	cObject.Init(2, "Two");
	avBlock.Add(&cObject);

	cObject.Init(3, "Bug");
	avBlock.Add(&cObject);

	cObject.Init(4, "Ger");
	avBlock.Add(&cObject);

	AssertInt(4, avBlock.NumElements());

	i = 3;
	pcObject = (CSortedTestObject*)avBlock.Get(&i);
	AssertInt(3, pcObject->miValue);
	AssertString("Bug", pcObject->mszThreeChars);

	cObject.Init(3, "Tom");
	avBlock.Add(&cObject);

	AssertInt(4, avBlock.NumElements());

	i = 3;
	pcObject = (CSortedTestObject*)avBlock.Get(&i);
	AssertInt(3, pcObject->miValue);
	AssertString("Bug", pcObject->mszThreeChars);

	avBlock.SetOverwrite(TRUE);
	cObject.Init(3, "Tom");
	avBlock.Add(&cObject);

	i = 3;
	pcObject = (CSortedTestObject*)avBlock.Get(&i);
	AssertInt(3, pcObject->miValue);
	AssertString("Tom", pcObject->mszThreeChars);

	avBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBlockSorted(void)
{
	BeginTests();

	TestArrayBlockSortedAddBasic();
	TestArrayBlockSortedAdd();
	TestArrayBlockSortedAddAfter();
	TestArrayBlockSortedAddBefore();
	TestArrayBlockSortedAddAfterAndMiddle();
	TestArrayBlockSortedAddBeforeAndMiddle();
	TestArrayBlockSortedAddBeforeAndMiddleAndEnd();
	TestArrayBlockSortedAddMiddleAndMiddle();
	TestArrayBlockSortedToListSmallList();
	TestArrayBlockSortedToListBigList1After();
	TestArrayBlockSortedToListBigList2After();
	TestArrayBlockSortedToListBigList3After();
	TestArrayBlockSortedToListBigList1Before();
	TestArrayBlockSortedToListBigList2Before();
	TestArrayBlockSortedToListBigList3Before();
	TestArrayBlockSortedStaggeredLeftSingle();
	TestArrayBlockSortedStaggeredRightSingle();
	TestArrayBlockSortedStaggeredLeftDouble();
	TestArrayBlockSortedStaggeredRightDouble();
	TestArrayBlockSortedMultipleBuffers();
	TestArrayBlockSortedAddDuplicate();
	TestArrayBlockReadWrite();

	TestStatistics();
}

