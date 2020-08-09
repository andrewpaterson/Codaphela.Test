#include "BaseLib/IndexTreeMemory.h"
#include "BaseLib/IndexTreeMemoryAccess.h"
#include "BaseLib/IndexTreeConfig.h"
#include "BaseLib/CreationDataOrderer.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryAllocator.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeConfigReading(void)
{
	CIndexTreeMemory			cIndexTree;
	CIndexTreeConfig			cConfig;
	CIndexTreeMemoryAccess		cAccess;
	CCreationDataOrderer		cOrderer;
	CMemoryAllocator			mcLocalMallocator;

	cOrderer.Init();
	cIndexTree.Init(&mcLocalMallocator, IKR_Yes, 512, 8, &cOrderer);
	cAccess.Init(&cIndexTree);

	cConfig

	cAccess.PutStringChar("0000", 'a');
	cAccess.PutStringChar("0100", 'b');
	cAccess.PutStringChar("0010", 'c');
	cAccess.PutStringChar("0110", 'd');


	cIndexTree.Kill();
	cAccess.Kill();
	cOrderer.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeConfig(void)
{
	BeginTests();
	FastFunctionsInit();
	MemoryInit();

	TestIndexTreeConfigReading();

	MemoryKill();
	FastFunctionsKill();
	TestStatistics();
}

