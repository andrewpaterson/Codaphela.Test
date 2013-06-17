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
	CFileUtil				cFileUtil;
	Ptr<CTestNamedObject>	pNamed1;
	Ptr<CTestNamedObject>	pNamed2;
	Ptr<CTestNamedObject>	pNamed3;
	Ptr<CTestNamedObject>	pResult1;
	Ptr<CTestNamedObject>	pResult2;
	CPointer				pResult3;
	Ptr<CRoot>				pRoot;
	Ptr<CSet>				pSet;
	CSet*					pcSet;
	OIndex					oiSet;
	OIndex					oiNamed3;

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
	oiNamed3 = pNamed3->GetOI();
	
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

	pcSet = pRoot->TestGetSet();
	oiSet = pcSet->GetOI();

	gcObjects.Flush(FALSE, FALSE);
	ObjectsKill();
	pcSet = NULL;

	ObjectsInit("Output/NamedObject");
	TestNamedObjectAddConstructors();

	AssertLongLongInt(3, gcObjects.NumDatabaseNames());
	AssertLongLongInt(5, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumMemoryNames());
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	pSet = gcObjects.Get(oiSet);
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertString("CSet", pSet.ClassName());

	AssertTrue(pSet.IsNotNull());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pSet.DistToRoot());

	AssertInt(1, pSet->NumElements());
	pResult3 = pSet->UnsafeGet(0);
	AssertTrue(pResult3.IsNotNull());
	AssertLongLongInt(oiNamed3, pResult3.GetIndex());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pResult3.DistToRoot());

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

