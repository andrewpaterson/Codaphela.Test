#include "BaseLib/ListVariable.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestListVariableAdd(void)
{
	CListVariable	cList;
	char*			pszData;
	char*			pszResult;
	size			i;
	void*			pv;
	size			uiMaxSize;
	size			uiSize;
	size			uiExpectedSize;
	size			uiCount;
	void*			pvExpected;
	int				iResult;

	cList.Init();
	AssertInt(0, cList.NumElements());

	pszData = (char*)cList.Add(5);
	strcpy(pszData, "Door");

	AssertInt(1, cList.NumElements());
	pszResult = (char*)cList.Get(0);
	AssertString(pszData, pszResult);
	AssertPointer(pszData, pszResult);
	cList.Kill();

	uiCount = 0;
	uiMaxSize = 8192;
	cList.Init();
	
	for (i = 1; i < uiMaxSize; i += 2)
	{
		pv = cList.Add(i);
		if (pv == NULL)
		{
			AssertNotNull(pv);
		}
		memset(pv, i, i);
		uiCount++;
	}
	AssertSize(uiCount, cList.NumElements());

	pvExpected = malloc(uiMaxSize + 10);
	memset(pvExpected, 0, uiMaxSize + 10);
	uiCount = 0;
	for (i = 0; i < uiMaxSize / 2; i++)
	{
		uiSize = cList.GetSize(i);
		uiExpectedSize = i * 2 + 1;
		AssertSize(uiExpectedSize, uiSize);
		pv = cList.Get(i);
		memset(pvExpected, i * 2 + 1, uiSize);
		iResult = memcmp(pvExpected, pv, uiSize);
		if (iResult != 0)
		{
			AssertInt(0, iResult);
		}
		uiCount++;
	}
	AssertSize(uiCount, cList.NumElements());

	free(pvExpected);
	
	cList.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestListVariable(void)
{
	BeginTests();
	FastFunctionsInit();
	DataMemoryInit();

	TestListVariableAdd();

	DataMemoryKill();
	FastFunctionsKill();
	TestStatistics();
}

