#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "StandardLib/IndexObject.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexObjectPut(void)
{
	Ptr<CRoot>					pRoot;
	
	ObjectsInit();

	pRoot = ORoot();


	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexObject(void)
{
	BeginTests();
	MemoryInit();
	TypesInit();
	DataIOInit();

	TestIndexObjectPut();

	DataIOKill();
	TypesKill();
	MemoryKill();
	TestStatistics();
}

