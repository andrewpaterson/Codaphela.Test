#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestSetup.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedObject(void)
{
	ObjectsInit();

	Ptr<CGameWorld>			pWorld = OMalloc(CGameWorld)->Init();
	Ptr<CClusterMissile>	pMissile = ONMalloc(CClusterMissile, "Frank")->Init(pWorld);
	Ptr<CRoot>				pRoot = ORoot();
	
	pRoot->Add(pMissile);


	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbedded(void)
{
	BeginTests();

	TestEmbeddedObject();

	TestStatistics();
}

