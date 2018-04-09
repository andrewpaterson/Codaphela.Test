#include "BaseLib/GlobalMemory.h"
#include "BaseLib/ListCharsMinimal.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestListCharsMinimalStuff(void)
{
	CListCharsMinimal*	pcListChars;
	char*				sz1 = "Hello";
	char*				sz2 = "3rd";
	char*				sz3 = "World";
	int					iLen1 = strlen(sz1);
	int					iLen2 = strlen(sz2);
	int					iLen3 = strlen(sz3);
	
	pcListChars = NULL;
	pcListChars = (CListCharsMinimal*)malloc(pcListChars->TotalSize(3, iLen1 + iLen2 + iLen3));

	pcListChars->Init(3, iLen1 + iLen2 + iLen3);
	AssertInt(0, pcListChars->NumElements());

	pcListChars->Add(sz1, iLen1);
	AssertInt(1, pcListChars->NumElements());
	AssertString(sz1, pcListChars->Get(0));

	pcListChars->Add(sz2, iLen2);
	AssertInt(2, pcListChars->NumElements());
	AssertString(sz1, pcListChars->Get(0));
	AssertString(sz2, pcListChars->Get(1));

	pcListChars->Add(sz3, iLen3);
	AssertInt(3, pcListChars->NumElements());
	AssertString(sz1, pcListChars->Get(0));
	AssertString(sz2, pcListChars->Get(1));
	AssertString(sz3, pcListChars->Get(2));

	pcListChars->Kill();
	free(pcListChars);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestListCharsMinimal(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestListCharsMinimalStuff();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

