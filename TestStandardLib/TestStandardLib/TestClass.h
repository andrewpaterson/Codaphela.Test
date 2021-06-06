#ifndef __TEST_CLASS_H__
#define __TEST_CLASS_H__
#include "StandardLib/Object.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Array.h"
#include "StandardLib/Integer.h"
#include "StandardLib/Float.h"


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
		Primitive(&mc, "mc");
	}

	void Free(void)
	{
	}
};


class CTestClass : public CNamedObject
{
CONSTRUCTABLE(CTestClass);
public:
	CPointer					mpObject;
	Ptr<CTestClass>				mpTest;
	Int32						mInt;
	int							miUnmanagedInt;
	CTinyTestClass				mTiny;
	Float64						mDouble;
	unsigned char				mauiData[12];

	Ptr<CTestClass> Init(void)
	{
		PreInit();
		mTiny.Init();
		mInt = 0;
		miUnmanagedInt = 0;
		mDouble = 0;
		memset(mauiData, 0, 12);
		PostInit();
		return this;
	}

	CTestClass::~CTestClass(void)
	{
		Kill();
	}

	void Class(void)
	{
		Pointer(mpObject.This(), "mpObject");
		Pointer(mpTest.This(), "mpTest");
		UnmanagedInt(&miUnmanagedInt, "miUnmanagedInt");
		Primitive(&mInt, "mInt");
		Embedded(&mTiny, "mTiny");
		Primitive(&mDouble, "mDouble");
		UnmanagedData(mauiData, 12, "mauiData");
	}

	void Free(void)
	{
		mInt = -1;
	}
};


#endif // __TEST_CLASS_H__

