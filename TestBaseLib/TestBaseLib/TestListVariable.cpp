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
	CChars			sz;

	cList.Init(32);
	AssertInt(0, cList.NumElements());

	pszData = (char*)cList.Add(5);
	strcpy(pszData, "Door");

	AssertInt(1, cList.NumElements());
	pszResult = (char*)cList.Get(0);
	AssertString(pszData, pszResult);
	AssertPointer(pszData, pszResult);
	cList.Kill();

	cList.Init(32);
	sz.Init();
	//for (i = 1; i < 10000; i++)
	//{
	//	sz.Append(i);
	//	sz.Append(" -> ");
	//	sz.AppendNewLine();
	//	sz.Dump();
	//	sz.Clear();

	//	pv = cList.Add(i);
	//	memset(pv, i, i);
	//}
	sz.Kill();
	
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

	TestListVariableAdd();

	FastFunctionsKill();
	TestStatistics();
}

