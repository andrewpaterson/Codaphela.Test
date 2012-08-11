#include "CoreLib/FunctionCaller.h"
#include "StandardLib/Parameters.h"
#include "StandardLib/Object.h"
#include "StandardLib/Objects.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Root.h"
#include "TestLib/Assert.h"
#include "TestObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectSize(void)
{
	AssertInt(12, sizeof(CUnknown));
	AssertInt(96, sizeof(CObject));
	AssertInt(128, sizeof(CRoot));
	AssertInt(112, sizeof(CSet));
	AssertInt(8, sizeof(CPointerObject));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObject(void)
{
	BeginTests();
	ObjectsInit(NULL);

	TestObjectSize();

	ObjectsKill();
	TestStatistics();
}

