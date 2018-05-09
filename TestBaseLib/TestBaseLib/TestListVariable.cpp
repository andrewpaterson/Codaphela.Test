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
	int				i;
	void*			pv;

	cList.Init();
	AssertInt(0, cList.NumElements());

	pszData = (char*)cList.Add(5);
	strcpy(pszData, "Door");

	AssertInt(1, cList.NumElements());
	pszResult = (char*)cList.Get(0);
	AssertString(pszData, pszResult);
	AssertPointer(pszData, pszResult);
	cList.Kill();

	cList.Init();
	for (i = 1; i < 65536; i += 4)
	{
		pv = cList.Add(i);
		memset(pv, i, i);
	}
	
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

