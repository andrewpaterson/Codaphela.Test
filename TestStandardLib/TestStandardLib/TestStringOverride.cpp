#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/LogToMemory.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "CoreLib/CodabaseFactory.h"
#include "CoreLib/SequenceFactory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/String.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStringOverrideCharPointerPlusDeconstructor(void)
{
	Ptr<CString>	pString1 = OMalloc<CString>("Hello ");
	Ptr<CString>	pString3 = NULL;
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	pString3 = pString1 + " World";
	AssertLongLongInt(3, gcObjects.NumMemoryIndexes());

	AssertString("Hello  World", pString3->Text());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStringOverrideCharPointerPlus(void)
{
	MemoryInit();
	TypesInit();
	DataIOInit();
	ObjectsInit();

	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
	TestStringOverrideCharPointerPlusDeconstructor();
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	ObjectsKill();
	DataIOKill();
	TypesKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStringOverrideStringPlusDeconstructor(void)
{
	Ptr<CString>	pString1 = OMalloc<CString>("Hello ");
	Ptr<CString>	pString2 = OMalloc<CString>(" World");
	Ptr<CString>	pString3 = NULL;
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	pString3 = pString1 + pString2;
	AssertLongLongInt(3, gcObjects.NumMemoryIndexes());

	AssertString("Hello  World", pString3->Text());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStringOverrideStringPlus(void)
{
	MemoryInit();
	TypesInit();
	DataIOInit();
	ObjectsInit();

	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
	TestStringOverrideStringPlusDeconstructor();
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	ObjectsKill();
	DataIOKill();
	TypesKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStringOverride(void)
{
	BeginTests();

	TestStringOverrideStringPlus();

	TestStatistics();
}

