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

	Ptr<CGameWorld>			pWorld;
	CPointer				pNull = ONull;
	Ptr<CPlayerVehicle>		pVehicle = ONull;
	Ptr<CHarrier>			pHarrier;

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

	pWorld = pHarrier;  //This probably shouldn't compile but it does because pHarrier (Ptr<CHarrier>) extends CPointer.

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUsageDefaultPointer(void)
{
	Ptr<CBaseObject>	pBase;
	Ptr<>				pDefault;
	CPointer			pObject;

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
