#include "BaseLib/GlobalMemory.h"
#include "CoreLib/Codabase.h"
#include "CoreLib/CodabaseFactory.h"
#include "StandardLib/NamedObject.h"
#include "StandardLib/Objects.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Root.h"
#include "StandardLib/ArrayObject.h"
#include "TestLib/Assert.h"
#include "NamedObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedObjectAddConstructors(void)
{
	gcObjects.AddConstructor<CArrayObject>();
	gcObjects.AddConstructor<CSetObject>();
	gcObjects.AddConstructor<CRoot>();
	gcObjects.AddConstructor<CTestNamedObject>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedObjectSize(void)
{
	AssertInt(192, sizeof(CNamedObject));
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
	Ptr<CSetObject>			pSet;
	CSetObject*				pcSet;
	OIndex					oiSet;
	OIndex					oiNamed3;
	CCodabase*				pcDatabase;

	cFileUtil.RemoveDir("Output" _FS_ "NamedObject");
	cFileUtil.TouchDir("Output" _FS_ "NamedObject");

	MemoryInit();
	pcDatabase = CCodabaseFactory::Create("Output" _FS_ "NamedObject", IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);
	TestNamedObjectAddConstructors(); //This is only important if an object is being loaded.

	pNamed1 = ONMalloc(CTestNamedObject, "Frank")->Init(1);

	pNamed2 = ONMalloc(CTestNamedObject, "Zappa")->Init(2);
	pNamed2->mpNamedTest1 = pNamed1;

	pNamed3 = ONMalloc(CTestNamedObject, NULL)->Init(3);
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

	gcObjects.Flush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();

	AssertNull(pNamed1.Object());
	AssertNull(pNamed2.Object());
	AssertNull(pNamed3.Object());
	AssertNull(pRoot.Object());
	AssertNull(pSet.Object());

	pcDatabase = CCodabaseFactory::Create("Output" _FS_ "NamedObject", IWT_Yes);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);
	TestNamedObjectAddConstructors();

	AssertLongLongInt(3, pcDatabase->NumNames());
	AssertLongLongInt(5, pcDatabase->NumIndices());
	AssertLongLongInt(0, gcObjects.NumMemoryNames());
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	pSet = gcObjects.Get(oiSet);
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertString("CSetObject", pSet.ClassName());

	AssertTrue(pSet.IsNotNull());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pSet.GetDistToRoot());

	AssertInt(1, pSet->NumElements());
	pResult3 = pSet->UnsafeGet(0);
	AssertTrue(pResult3.IsNotNull());
	AssertLongLongInt(oiNamed3, pResult3.GetIndex());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pResult3.GetDistToRoot());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedOjectKill(void)
{
	Ptr<CTestNamedObject>	pNamedObject;
	char*					pszName;

	MemoryInit();
	ObjectsInit();

	pNamedObject = ONMalloc(CTestNamedObject, "This is my Name")->Init(7);

	pszName = pNamedObject->GetName();

	//Trying to test that FreeIdentifiers is called and that mon is freed.
	pNamedObject->Kill();

	ObjectsKill();
	MemoryKill();
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
	TestNamedOjectKill();

	TestStatistics();
}

