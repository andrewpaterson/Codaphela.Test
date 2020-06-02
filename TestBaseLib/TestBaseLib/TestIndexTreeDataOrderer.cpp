#include "BaseLib/IndexTreeMemory.h"
#include "BaseLib/IndexTreeMemoryAccess.h"
#include "BaseLib/AccessDataOrderer.h"
#include "BaseLib/GlobalMemory.h"
#include "TestLib/Assert.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertIndexTreeDataOrdererString(CAccessDataOrderer* pcOrderer, char* szExpected)
{
	SDataOrderIterator	sIter;
	char* pc;
	int					iSize;
	BOOL				bExists;
	CChars				sz;

	sz.Init();
	bExists = pcOrderer->StartIteration(&sIter, (void**)&pc, &iSize);
	while (bExists)
	{
		sz.Append(*pc);
		bExists = pcOrderer->Iterate(&sIter, (void**)&pc, &iSize);
	}

	AssertString(szExpected, sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeDataOrdererAccess(void)
{
	CIndexTreeMemory			cIndexTree;
	CIndexTreeMemoryAccess		cAccess;
	CAccessDataOrderer			cOrderer;
	char						c;
	SIndexTreeMemoryIterator	sIter;
	BOOL						bExists;

	cOrderer.Init();
	cIndexTree.Init(IKR_No, &cOrderer);
	cAccess.Init(&cIndexTree);

	AssertIndexTreeDataOrdererString(&cOrderer, "");

	cAccess.PutStringChar("0000", 'a');
	cAccess.PutStringChar("0100", 'b');
	cAccess.PutStringChar("0010", 'c');
	cAccess.PutStringChar("0110", 'd');
	AssertIndexTreeDataOrdererString(&cOrderer, "dcba");

	c = cAccess.GetStringChar("0000");
	AssertIndexTreeDataOrdererString(&cOrderer, "adcb");

	c = cAccess.GetStringChar("0010");
	AssertIndexTreeDataOrdererString(&cOrderer, "cadb");

	cAccess.DeleteString("0100");
	cAccess.DeleteString("0110");
	AssertIndexTreeDataOrdererString(&cOrderer, "ca");

	cAccess.DeleteString("0010");
	cAccess.DeleteString("0000");
	AssertIndexTreeDataOrdererString(&cOrderer, "");

	cAccess.PutStringChar("0000", 'a');
	cAccess.PutStringChar("0100", 'b');
	cAccess.PutStringChar("0010", 'c');
	cAccess.PutStringChar("0110", 'd');
	AssertIndexTreeDataOrdererString(&cOrderer, "dcba");

	cAccess.HasString("0100");
	AssertIndexTreeDataOrdererString(&cOrderer, "bdca");

	cAccess.HasString("0100");
	AssertIndexTreeDataOrdererString(&cOrderer, "bdca");

	cAccess.HasString("0110");
	AssertIndexTreeDataOrdererString(&cOrderer, "dbca");

	bExists = cIndexTree.StartIteration(&sIter, NULL, NULL);
	AssertTrue(bExists);
	AssertIndexTreeDataOrdererString(&cOrderer, "adbc");
	bExists = cIndexTree.Iterate(&sIter, NULL, NULL);
	AssertTrue(bExists);
	AssertIndexTreeDataOrdererString(&cOrderer, "cadb");
	bExists = cIndexTree.Iterate(&sIter, NULL, NULL);
	AssertTrue(bExists);
	AssertIndexTreeDataOrdererString(&cOrderer, "bcad");
	bExists = cIndexTree.Iterate(&sIter, NULL, NULL);
	AssertTrue(bExists);
	AssertIndexTreeDataOrdererString(&cOrderer, "dbca");
	bExists = cIndexTree.Iterate(&sIter, NULL, NULL);
	AssertFalse(bExists);

	cIndexTree.Kill();
	cAccess.Kill();
	cOrderer.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeDataOrderer(void)
{
	BeginTests();
	FastFunctionsInit();
	MemoryInit();

	TestIndexTreeDataOrdererAccess();

	MemoryKill();
	FastFunctionsKill();
	TestStatistics();
}

