#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestSetup.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUsageNullPointers(void)
{
	ObjectsInit();

	CPointer<CGameWorld>		pWorld;
	CPointerObject				pNull = ONull;
	CPointer<CPlayerVehicle>	pVehicle = ONull;
	CPointer<CHarrier>			pHarrier;

	pWorld = pNull;
	pWorld->AddTickable(pNull);
	pWorld->AddTickable(pVehicle);
	pWorld->AddTickable(ONull);

	pVehicle = pNull;
	pWorld->AddPlayer(pVehicle);
	pWorld->AddPlayer(pNull);
	pWorld->AddPlayer(ONull);

	pVehicle = pHarrier;

	AssertString("This code must compile", "This code must compile");

	pWorld = pHarrier;  //This probably shouldn't compile but it does because pHarrier (CPointer<CHarrier>) extends CPointerObject.

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUsageDefaultPointer(void)
{
	CPointer<CBaseObject>	pBase;
	CPointer<>				pDefault;
	CPointerObject			pObject;

	AssertString("This code must compile", "This code must compile");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUsage(void)
{
	BeginTests();

	TestUsageNullPointers();
	TestUsageDefaultPointer();

	TestStatistics();
}


