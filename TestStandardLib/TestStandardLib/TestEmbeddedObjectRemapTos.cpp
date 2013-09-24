#include "StandardLib/Objects.h"
#include "StandardLib/ObjectAllocator.h"
#include "StandardLib/String.h"
#include "StandardLib/PointerContainer.h"
#include "TestLib/Assert.h"


class CTestObjectWithTwoEmbedded : public CNamedObject
{
BASE_FUNCTIONS(CTestObjectWithTwoEmbedded);
public:
	CString		mpString1;
	CString		mpString2;

	void Class(void)
	{
		Embedded(&mpString1);
		Embedded(&mpString2);
	}

	Ptr<CTestObjectWithTwoEmbedded> Init(void) 
	{
		return this;
	}

	void KillData(void)
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
	CObjectAllocator	cAllocator;

	ObjectsInit();
	cAllocator.Init(&gcObjects);

	Ptr<CRoot>	pRoot = ORoot();

	Ptr<CNamedHollowObject>	pHollow = cAllocator.AddHollow("Name", gcObjects.GetIndexGenerator()->PopIndex(), 3);
	AssertInt(3, pHollow.Object()->GetNumEmbedded());

	Ptr<CEmbeddedObject> pEmbedded0 = pHollow.Object()->GetEmbeddedObject(0);
	Ptr<CEmbeddedObject> pEmbedded1 = pHollow.Object()->GetEmbeddedObject(1);
	Ptr<CEmbeddedObject> pEmbedded2 = pHollow.Object()->GetEmbeddedObject(2);
	AssertPointer(pHollow.Object(), pEmbedded0.Object());

	Ptr<CPointerContainer>	pPointerHollow = gcObjects.Add<CPointerContainer>()->Init(pHollow);
	Ptr<CPointerContainer>	pPointerEmbedded1 = gcObjects.Add<CPointerContainer>()->Init(pEmbedded1);
	Ptr<CPointerContainer>	pPointerEmbedded2 = gcObjects.Add<CPointerContainer>()->Init(pEmbedded2);

	pRoot->Add(pHollow);

	Ptr<CTestObjectWithTwoEmbedded> pObject = gcObjects.Add<CTestObjectWithTwoEmbedded>("Name2")->Init();
	AssertInt(3, pObject.Object()->GetNumEmbedded());

	pObject.Remap(pHollow.Object());

	AssertPointer(pObject.Object(), pPointerHollow->mp.Object());
	AssertPointer(pEmbedded1.Object(), pPointerEmbedded1->mp.Object());
	AssertPointer(pEmbedded2.Object(), pPointerEmbedded2->mp.Object());

	cAllocator.Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedObjectRemapTos(void)
{
	BeginTests();

	TestEmbeddedObjectRemapTosActual();

	TestStatistics();
}

