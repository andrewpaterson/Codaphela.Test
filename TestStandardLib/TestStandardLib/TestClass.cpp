#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
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
	Ptr<CTestClass>	pTestClass;
	CClass*			pcClass;

	DataIOInit();
	ObjectsInit();

	pTestClass = gcObjects.Malloc<CTestClass>();
	pTestClass->Init();

	pcClass = pTestClass->GetClass();


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

	TestClassDefinition();

	MemoryKill();
	TestStatistics();
}

