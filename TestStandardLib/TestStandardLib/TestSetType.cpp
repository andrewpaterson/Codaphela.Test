#include "TestLib/Assert.h"
#include "StandardLib/Unknowns.h"
#include "StandardLib/SetType.h"
#include "UnknownTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetTypeInstantiation(void)
{
	UnknownsInit();

	CSetType<CTestUnknown>	cSet;
	CTestUnknown*			pcTest1;
	CTestUnknown*			pcTest2;
	CTestUnknown*			pcTest;
	int						iSize;
	char*					szName;
	SSetIterator			sIter;
	int						iCount;

	cSet.Init();

	pcTest1 = cSet.Add();
	pcTest1->Init();
	pcTest2 = UMalloc(CTestUnknown);
	pcTest2->Init();
	cSet.Add(pcTest2);

	iCount = 0;
	pcTest = cSet.StartIteration(&sIter);
	while (pcTest)
	{
		iCount++;
		pcTest = cSet.Iterate(&sIter);
	}
	AssertInt(2, iCount);
	AssertInt(2, cSet.NumElements());

	//This test is not correct.  The order is not guaranteed.
	//However it necessary to make the template compile.
	AssertTrue(cSet.Contains(pcTest1));
	AssertTrue(cSet.Contains(pcTest2));

	pcTest = cSet.StartIteration(&sIter);
	AssertPointer(pcTest1, pcTest);
	pcTest = cSet.Iterate(&sIter);
	AssertPointer(pcTest2, pcTest);

	pcTest = cSet.StartIteration(&sIter);
	cSet.RemoveDuringIteration(&sIter);
	pcTest = cSet.Iterate(&sIter);
	AssertPointer(pcTest2, pcTest);

	AssertInt(1, cSet.NumElements());

	cSet.Remove(pcTest2);
	AssertInt(0, cSet.NumElements());

	iSize = cSet.ClassSize();
	AssertInt(44, iSize);

	szName = cSet.ClassName();
	AssertString("CSetType", szName);

	cSet.Kill();
	UnknownsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetTypeAddAll(void)
{
	UnknownsInit();

	CSetType<CTestNamedUnknown>	cSet;
	int							i;
	CTestNamedUnknown*			pcTest;
	CSetType<CTestNamedUnknown>	cDest;
	CChars						sz;
	CTestNamedUnknown*			pcTest25;

	cSet.Init();
	pcTest25 = NULL;
	for (i = 0; i < 50; i++)
	{
		pcTest = UMalloc(CTestNamedUnknown);

		sz.Init(":");
		sz.Append(i);
		pcTest->Init(sz.Text());
		sz.Kill();
		cSet.Add(pcTest);
		if (i == 25)
		{
			pcTest25 = pcTest;
		}
	}

	cSet.Remove(pcTest25);

	cDest.Init();
	cDest.AddAll(&cSet);
	cSet.KillElements(FALSE);
	cSet.Kill();

	AssertInt(49, cDest.NumElements());

	for (i = 0; i < 25; i++)
	{
		pcTest = (CTestNamedUnknown*)cDest.UnsafeGet(i);
		sz.Init(":");
		sz.Append(i);
		AssertString(sz.Text(), pcTest->mszName.Text());
		sz.Kill();
	}

	pcTest = (CTestNamedUnknown*)cDest.UnsafeGet(i);
	AssertNull(pcTest);

	for (i = 26; i < 50; i++)
	{
		pcTest = (CTestNamedUnknown*)cDest.UnsafeGet(i);
		sz.Init(":");
		sz.Append(i);
		AssertString(sz.Text(), pcTest->mszName.Text());
		sz.Kill();
	}

	cDest.Kill();
	UnknownsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetType(void)
{
	BeginTests();

	TestSetTypeInstantiation();
	TestSetTypeAddAll();

	TestStatistics();
}

