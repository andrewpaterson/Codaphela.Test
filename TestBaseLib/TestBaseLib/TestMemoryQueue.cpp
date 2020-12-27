#include "BaseLib/MemoryQueue.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void FillQueueElement(void* pvData, size_t uiSize, char c)
{
	if (pvData && uiSize > 1)
	{
		memset_fast(pvData, c, uiSize - 1);
		((char*)pvData)[uiSize - 1] = '\0';
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertQueueElement(CMemoryQueue* pcQueue, void* pvData, int iDataSize, char cExpected)
{
	char*						szData;
	CChars						szExpected;
	SMemoryCacheDescriptor*		psDescriptor;

	psDescriptor = pcQueue->GetDescriptor(pvData);

	AssertInt(iDataSize, psDescriptor->uiSize);

	szData = (char*)pvData;
	szExpected.Init();
	szExpected.Append(cExpected, iDataSize - 1);
	AssertString(szExpected.Text(), szData);
	szExpected.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void* PushElement(CMemoryQueue* pcQueue, size_t uiSize, char c)
{
	void*	pv;

	pv = pcQueue->Push(uiSize);
	FillQueueElement(pv, uiSize, c);
	return pv;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryQueuePush(void)
{
	CMemoryQueue	cQueue;
	void*			pvQueue;
	void*			pvTemp;
	void*			pvA;
	void*			pvB;
	void*			pvC;
	void*			pvD;
	void*			pvE;
	void*			pvF;
	size_t			uiDataSize;
	void*			pv;
	char			c;

	pvQueue = malloc(128);
	cQueue.Init(pvQueue, 128);

	AssertInt(0, cQueue.NumElements());

	pvA = PushElement(&cQueue, 24, 'A');
	pvB = PushElement(&cQueue, 20, 'B');
	AssertInt(2, cQueue.NumElements());
	AssertInt(68, cQueue.GetAllocatedSize());

	pv = cQueue.Peek(&uiDataSize);
	AssertQueueElement(&cQueue, pv, 24, 'A');
	cQueue.Drop(pv);

	AssertInt(1, cQueue.NumElements());

	pv = cQueue.Peek(&uiDataSize);
	AssertQueueElement(&cQueue, pv, 20, 'B');
	cQueue.Drop(pv);

	AssertTrue(cQueue.IsEmpty());
	Pass();

	pvA = PushElement(&cQueue, 32, 'A');
	pvB = PushElement(&cQueue, 32, 'B');
	AssertInt(2, cQueue.NumElements());
	AssertInt(88, cQueue.GetAllocatedSize());

	pvC = PushElement(&cQueue, 32, 'C');
	AssertNull(pvC);
	AssertInt(2, cQueue.NumElements());
	AssertInt(88, cQueue.GetAllocatedSize());
	Pass();

	cQueue.ValidateCache();

	pvTemp = malloc(256);
	cQueue.Remap(pvTemp, 256);
	free(pvQueue);
	pvQueue = pvTemp;

	cQueue.ValidateCache();

	pvC = PushElement(&cQueue, 32, 'C');
	AssertNotNull(pvC);
	AssertInt(3, cQueue.NumElements());
	AssertInt(132, cQueue.GetAllocatedSize());
	Pass();

	pvD = PushElement(&cQueue, 32, 'D');
	pvE = PushElement(&cQueue, 32, 'E');
	AssertNotNull(pvE);
	AssertInt(5, cQueue.NumElements());
	AssertInt(220, cQueue.GetAllocatedSize());
	Pass();

	pvF = PushElement(&cQueue, 32, 'F');
	AssertNull(pvF);
	AssertInt(5, cQueue.NumElements());
	AssertInt(220, cQueue.GetAllocatedSize());
	Pass();

	cQueue.ValidateCache();

	for (c = 'A'; c < 'F'; c++)
	{
		pv = cQueue.Peek(&uiDataSize);
		AssertQueueElement(&cQueue, pv, 32, c);
		cQueue.Drop(pv);

		cQueue.ValidateCache();
	}
	pv = cQueue.Peek(&uiDataSize);
	AssertNull(pv);

	AssertInt(0, cQueue.NumElements());
	AssertInt(0, cQueue.GetAllocatedSize());
	AssertNull(cQueue.GetFirst());
	AssertNull(cQueue.GetLast());

	cQueue.Kill();
	free(pvQueue);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryQueuePeek(void)
{
	CMemoryQueue	cQueue;
	void*			pvQueue;
	void*			pvA;
	void*			pvB;
	char			c;
	void*			pvNext;
	void*			pv;
	size_t			uiDataSize;

	pvQueue = malloc(128);
	cQueue.Init(pvQueue, 128);

	AssertInt(0, cQueue.NumElements());

	pvA = PushElement(&cQueue, 28, 'A');
	pvB = PushElement(&cQueue, 20, 'B');

	for (c = 'C'; c <= 'Z'; c++)
	{
		pvNext = PushElement(&cQueue, 20 + (c % 3) * 4, c);

		pv = cQueue.Peek(&uiDataSize);
		AssertQueueElement(&cQueue, pv, 20 + ((c-2) % 3) * 4, c-2);
		cQueue.Drop(pv);

		cQueue.ValidateCache();
	}

	AssertInt(2, cQueue.NumElements());

	cQueue.Kill();
	free(pvQueue);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryQueue(void)
{
	BeginTests();
	FastFunctionsInit();

	TestMemoryQueuePush();
	TestMemoryQueuePeek();

	FastFunctionsKill();
	TestStatistics();
}

