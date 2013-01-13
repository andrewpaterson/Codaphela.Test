#include "StandardLib/NamedObject.h"
#include "StandardLib/Objects.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Root.h"
#include "StandardLib/Array.h"
#include "TestLib/Assert.h"
#include "NamedObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedObjectAddConstructors(void)
{
	gcObjects.AddConstructor<CArray>();
	gcObjects.AddConstructor<CSet>();
	gcObjects.AddConstructor<CRoot>();
	gcObjects.AddConstructor<CTestNamedObject>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedObjectSize(void)
{
	AssertInt(128, sizeof(CNamedObject));
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedObjectName(void)
{
	CFileUtil					cFileUtil;
	CPointer<CTestNamedObject>	pNamed1;
	CPointer<CTestNamedObject>	pNamed2;
	CPointer<CTestNamedObject>	pNamed3;
	CPointer<CTestNamedObject>	pResult1;
	CPointer<CTestNamedObject>	pResult2;
	CPointer<CTestNamedObject>	pResult3;
	CPointer<CRoot>				pRoot;
	CSet*						pcSet;


	cFileUtil.RemoveDir("Output/NamedObject");
	cFileUtil.MakeDir("Output/NamedObject");
	ObjectsInit("Output/NamedObject");
	TestNamedObjectAddConstructors(); //This is only important if an object is being loaded.

	pNamed1 = ONMalloc(CTestNamedObject, "Frank");
	pNamed1->Init(1);

	pNamed2 = ONMalloc(CTestNamedObject, "Zappa");
	pNamed2->Init(2);
	pNamed2->mpNamedTest1 = pNamed1;

	pNamed3 = ONMalloc(CTestNamedObject, NULL);
	pNamed3->Init(3);
	pNamed3->mpNamedTest1 = pNamed1;
	pNamed3->mpNamedTest2 = pNamed2;
	
	pRoot = ORoot();
	pRoot->Add(pNamed3);
	
	AssertLongLongInt(3, gcObjects.NumMemoryNames());
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());

	pResult1 = gcObjects.Get("Frank");
	AssertNotNull(pResult1.Object());

	pResult2 = gcObjects.Get("Zappa");
	AssertNotNull(pResult2.Object());

	pResult3 = gcObjects.Get("");
	AssertNull(pResult3.Object());

	gcObjects.Flush(FALSE, FALSE);
	ObjectsKill();

	ObjectsInit("Output/NamedObject");
	TestNamedObjectAddConstructors();
	pRoot = ORoot();

	AssertLongLongInt(3, gcObjects.NumDatabaseNames());
	AssertLongLongInt(4, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	pcSet = pRoot->TestGetSet();
	AssertNotNull(pcSet);
	AssertInt(1, pcSet->NumElements());
	pResult3 = (CTestNamedObject*)pcSet->UnsafeGet(0);
	AssertInt(3, pResult3->miNum);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedObject(void)
{
	BeginTests();

	TestNamedObjectSize();
	TestNamedObjectName();

	TestStatistics();
}

