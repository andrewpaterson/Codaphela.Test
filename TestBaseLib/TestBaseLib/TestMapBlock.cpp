#include "BaseLib/MapBlock.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/IntegerHelper.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlockSimple(void)
{
	CMapBlock	cMapBlock;
	int			i;
	int			j;
	int			iKey;
	int*		piData;

	cMapBlock.Init(&gcSystemAllocator, 1024, &CompareInt);
	i = 7; j = 43;
	cMapBlock.Put(&i, sizeof(int), &j, sizeof(int));

	i = 9; j = 21;
	cMapBlock.Put(&i, sizeof(int), &j, sizeof(int));
	AssertInt(2, cMapBlock.NumElements());

	iKey = 3; piData = NULL;
	cMapBlock.Get(&iKey, (void**)&piData, NULL);
	AssertNull(piData);

	iKey = 7; piData = NULL;
	cMapBlock.Get(&iKey, (void**)&piData, NULL);
	AssertNotNull(piData);
	AssertInt(43, *piData);

	iKey = 9; piData = NULL;
	cMapBlock.Get(&iKey, (void**)&piData, NULL);
	AssertNotNull(piData);
	AssertInt(21, *piData);

	cMapBlock.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapBlock(void)
{
	BeginTests();

	TestMapBlockSimple();

	TestStatistics();
}


