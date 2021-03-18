#include "BaseLib/GlobalMemory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/String.h"
#include "StandardLib/PointerContainer.h"
#include "TestLib/Assert.h"


class CTestObjectWithTwoEmbedded : public CNamedObject
{
CONSTRUCTABLE(CTestObjectWithTwoEmbedded);
public:
	CString		mString1;
	CString		mString2;

	void Class(void)
	{
		Embedded(&mString1);
		Embedded(&mString2);
	}

	Ptr<CTestObjectWithTwoEmbedded> Init(void) 
	{
		mString1.Init("String1");
		mString2.Init("String2");
		return this;
	}

	void Free(void)
	{
	}

	BOOL Save(CObjectSerialiser* pcFile)
	{
		return FALSE;
	}

	BOOL Load(CObjectDeserialiser* pcFile)
	{
		return FALSE;
	}
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedObjectRemapTosActual(void)
{

	ObjectsInit();

	Ptr<CRoot>	pRoot = ORoot();

	Ptr<CNamedHollowObject>	pHollow = gcObjects.AllocateExistingHollowFromMemoryOrMaybeANewNamedHollow("Name", gcObjects.GetIndexGenerator()->GetNext(), 3);
	AssertInt(3, pHollow.Object()->GetNumEmbedded());

	Ptr<CEmbeddedObject> pHollowEmbedded1 = pHollow.Object()->GetEmbeddedObject(1);
	Ptr<CEmbeddedObject> pHollowEmbedded2 = pHollow.Object()->GetEmbeddedObject(2);
	AssertPointer(pHollow.Object(), pHollow.Object()->GetEmbeddedObject(0));
	AssertInt(3, pHollow.Object()->GetNumEmbedded());

	Ptr<CPointerContainer>	pPointerHollow = gcObjects.Add<CPointerContainer>()->Init(pHollow);
	Ptr<CPointerContainer>	pPointerHollowEmbedded1 = gcObjects.Add<CPointerContainer>()->Init(pHollowEmbedded1);
	Ptr<CPointerContainer>	pPointerHollowEmbedded2 = gcObjects.Add<CPointerContainer>()->Init(pHollowEmbedded2);

	AssertInt(3, pHollow.Object()->NumHeapFroms());
	AssertInt(1, pHollow.Object()->CEmbeddedObject::NumHeapFroms());
	AssertInt(1, pHollowEmbedded1.Object()->CEmbeddedObject::NumHeapFroms());
	AssertInt(1, pHollowEmbedded2.Object()->CEmbeddedObject::NumHeapFroms());

	AssertInt(3, pHollow.Object()->NumStackFroms());
	AssertInt(1, pHollow.Object()->CEmbeddedObject::NumStackFroms());
	AssertInt(1, pHollowEmbedded1.Object()->CEmbeddedObject::NumStackFroms());
	AssertInt(1, pHollowEmbedded2.Object()->CEmbeddedObject::NumStackFroms());

	pRoot->Add(pHollow);

	Ptr<CTestObjectWithTwoEmbedded> pObject = gcObjects.Add<CTestObjectWithTwoEmbedded>("Name2")->Init();
	AssertInt(3, pObject.Object()->GetNumEmbedded());

	AssertString("CNamedHollowObject", pHollow.ClassName());
	AssertString("CHollowEmbeddedObject", pHollowEmbedded1.ClassName());
	AssertString("CHollowEmbeddedObject", pHollowEmbedded2.ClassName());

	AssertString("CNamedHollowObject", pPointerHollow->mp.ClassName());
	AssertString("CHollowEmbeddedObject", pPointerHollowEmbedded1->mp.ClassName());
	AssertString("CHollowEmbeddedObject", pPointerHollowEmbedded2->mp.ClassName());

	Ptr<CPointerContainer>	pPointerObject = gcObjects.Add<CPointerContainer>()->Init(pObject);

	pHollow.MorphInto(&pObject);

	AssertString("CTestObjectWithTwoEmbedded", pHollow.ClassName());
	AssertString("CString", pHollowEmbedded1.ClassName());
	AssertString("CString", pHollowEmbedded2.ClassName());

	AssertString("CTestObjectWithTwoEmbedded", pPointerHollow->mp.ClassName());
	AssertString("CString", pPointerHollowEmbedded1->mp.ClassName());
	AssertString("CString", pPointerHollowEmbedded2->mp.ClassName());

	AssertPointer(pObject.Object(), pHollow.Object());
	AssertPointer(pObject.Object(), pPointerHollow->mp.Object());
	AssertPointer(pObject.Object(), pPointerObject->mp.Object());
	AssertPointer(pHollowEmbedded1.Object(), pPointerHollowEmbedded1->mp.Object());
	AssertPointer(pHollowEmbedded2.Object(), pPointerHollowEmbedded2->mp.Object());

	AssertInt(5, pHollow.Object()->NumHeapFroms());  //pPointerObject and pPointerHollow now both point to the same object.  pRoot.Set is the fifth.
	AssertInt(3, pHollow.Object()->CEmbeddedObject::NumHeapFroms());
	AssertInt(1, pHollowEmbedded1.Object()->CEmbeddedObject::NumHeapFroms());
	AssertInt(1, pHollowEmbedded2.Object()->CEmbeddedObject::NumHeapFroms());

	AssertInt(4, pHollow.Object()->NumStackFroms());  //pObject and pHollow now both point to the same object.
	AssertInt(2, pHollow.Object()->CEmbeddedObject::NumStackFroms());
	AssertInt(1, pHollowEmbedded1.Object()->CEmbeddedObject::NumStackFroms());
	AssertInt(1, pHollowEmbedded2.Object()->CEmbeddedObject::NumStackFroms());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedObjectRemapTos(void)
{
	BeginTests();
	MemoryInit();

	TestEmbeddedObjectRemapTosActual();

	MemoryKill();
	TestStatistics();
}

