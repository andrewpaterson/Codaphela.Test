#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "StandardLib/MapObject.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObjectPut(void)
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
void TestMapObject(void)
{
	BeginTests();
	MemoryInit();
	TypesInit();
	DataIOInit();

	TestMapObjectPut();

	DataIOKill();
	TypesKill();
	MemoryKill();
	TestStatistics();
}

