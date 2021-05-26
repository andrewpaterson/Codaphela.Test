#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "StandardLib/Object.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Array.h"
#include "StandardLib/Integer.h"
#include "StandardLib/Float.h"
#include "StandardLib/ObjectSerialiser.h"
#include "StandardLib/ObjectDeserialiser.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"


class CTinyTestClass : public CObject
{
CONSTRUCTABLE(CTinyTestClass);
public:
	Int8						mc;

	Ptr<CTinyTestClass> Init(void)
	{
		PreInit();
		mc = 127;
		PostInit();
		return this;
	}

	void Class(void)
	{
		CObject::Class();
		Primitive(&mc);
	}

	void Free(void)
	{
	}
};


class CTestClass : public CObject
{
CONSTRUCTABLE(CTestClass);
public:
	CPointer					mpObject;
	Ptr<CTestClass>				mpTest;
	Int32						mInt;
	int							miUnmanagedInt;
	CTinyTestClass				mTiny;
	Float64						mDouble;

	Ptr<CTestClass> Init(void)
	{
		PreInit();
		mInt = 0;
		miUnmanagedInt = 0;
		mDouble = 0;
		PostInit();
		return this;
	}

	void Class(void)
	{
		CObject::Class();
		Pointer(mpObject.This());
		Pointer(mpTest.This());
		Primitive(&mInt);
		Embedded(&mTiny);
		Primitive(&mDouble);
	}

	void Free(void)
	{
	}
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClassDefinition(void)
{
	Ptr<CTestClass>		pTestClass;
	CClass*				pcTestClassClass;
	CClass*				pcTinyTestClassClass;
	CClasses*			pcClasses;
	CClass*				pcTemp;

	DataIOInit();
	ObjectsInit();

	pcClasses = gcObjects.GetClasses();

	pTestClass = gcObjects.Malloc<CTestClass>();
	pTestClass->Init();

	pcTestClassClass = pTestClass->GetClass();
	AssertNotNull(pcTestClassClass);
	AssertString("CTestClass", pcTestClassClass->GetName());
	AssertInt(CLASS_TYPES, pcTestClassClass->GetType());
	AssertTrue(pcTestClassClass->IsComplete());

	pcTemp = pcClasses->Get(CLASS_TYPES);
	AssertPointer(pcTestClassClass, pcTemp);
	pcTemp = pcClasses->Get("CTestClass");
	AssertPointer(pcTestClassClass, pcTemp);

	pcTinyTestClassClass = pTestClass->mTiny.GetClass();
	AssertNotNull(pcTinyTestClassClass);
	AssertString("CTinyTestClass", pcTinyTestClassClass->GetName());
	AssertInt(CLASS_TYPES + 1, pcTinyTestClassClass->GetType());
	AssertTrue(pcTinyTestClassClass->IsComplete());

	pcTemp = pcClasses->Get(CLASS_TYPES + 1);
	AssertPointer(pcTinyTestClassClass, pcTemp);
	pcTemp = pcClasses->Get("CTinyTestClass");
	AssertPointer(pcTinyTestClassClass, pcTemp);

	ObjectsKill();
	DataIOKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClass(void)
{
	BeginTests();
	MemoryInit();
	TypesInit();

	TestClassDefinition();

	TypesKill();
	MemoryKill();
	TestStatistics();
}

