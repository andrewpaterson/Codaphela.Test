#include "BaseLib/IndexTreeTemplateMemory.h"
#include "TestLib/Assert.h"
#include "TestIndexTreeObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeTemplatePut(void)
{
	CIndexTreeTemplateMemory<long long int>	cIndex;
	long long int							lliLarry;
	long long int							lliThe;
	long long int							lliLamb;
	long long int*							plliResult;

	cIndex.Init();

	lliLarry = 0x4224f9be509f7b36LL;
	lliThe = 0x392168ee06b4c0d0;
	lliLamb = 0xf855181fab7e51e5;

	AssertTrue(cIndex.Put("Larry", &lliLarry));
	AssertTrue(cIndex.Put("The", &lliThe));
	AssertTrue(cIndex.Put("Lamb", &lliLamb));

	AssertInt(3, cIndex.NumElements());
	AssertInt(3, cIndex.RecurseSize());

	plliResult = cIndex.Get("Lamb");
	AssertLongLongInt(lliLamb, *plliResult);
	plliResult = cIndex.Get("The");
	AssertLongLongInt(lliThe, *plliResult);
	plliResult = cIndex.Get("Larry");
	AssertLongLongInt(lliLarry, *plliResult);

	AssertTrue(cIndex.Remove("The"));
	plliResult = cIndex.Get("The");
	AssertNull(plliResult);

	AssertInt(2, cIndex.NumElements());
	AssertInt(2, cIndex.RecurseSize());

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeTemplate(void)
{
	BeginTests();

	TestIndexTreeTemplatePut();

	TestStatistics();
}


