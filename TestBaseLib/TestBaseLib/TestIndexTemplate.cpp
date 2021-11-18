#include "BaseLib/GlobalMemory.h"
#include "BaseLib/LogString.h"
#include "BaseLib/LocalMallocatorConstructors.h"
#include "BaseLib/DataOrderers.h"
#include "BaseLib/IndexTemplate.h"
#include "TestLib/Assert.h"


struct SIndexTemplateKey
{
	double	f;
	char	c;
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTemplateStuff(void)
{
	CIndexTemplate<SIndexTemplateKey, int64>	cIndex;

	cIndex.Init();

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTemplate(void)
{
	BeginTests();
	FastFunctionsInit();
	MemoryInit();
	LocalMallocatorsInit(&gcConstructors, &gcMallocators);
	DataOrderersInit(&gcConstructors, &gcDataOrderers);

	TestIndexTemplateStuff();

	DataOrderersKill();
	MemoryKill();
	FastFunctionsKill();
	TestStatistics();
}

