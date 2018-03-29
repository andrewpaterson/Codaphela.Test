#include "BaseLib/Logger.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/IndexTreeNodeMemory.h"
#include "BaseLib/IndexTreeMemory.h"
#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/PrimitiveTypes.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryComplex(void)
{
	//Most of the tests for IndexTreeMemory are done in the BaseLib.
	//This test just exists to remind me of that fact.

	CMemoryAllocator	cMemoryAllocator;
	CIndexTreeMemory	cIndexTree;
	int64				lliKey1;
	char*				pvData1;
	CMemory*			pcMemory;
	size_t				tRootNodeSize;
	size_t				tNodeSize;
	size_t				tNoDataSize;

	cMemoryAllocator.Init(16);
	pcMemory = cMemoryAllocator.GetMemory();
	AssertLongLongInt(0, pcMemory->GetTotalAllocatedMemory());
	AssertLongLongInt(0, pcMemory->GetTotalAllocations());

	cIndexTree.Init(&cMemoryAllocator);
	tRootNodeSize = cIndexTree.CalculateRootNodeSize();
	tNodeSize = cIndexTree.SizeofNode();
	tNoDataSize = cIndexTree.SizeofNodePtr();

	AssertLongLongInt(1 /* root node (256 children) */, pcMemory->GetTotalAllocations());
	AssertLongLongInt(tRootNodeSize, pcMemory->GetTotalAllocatedMemory());
	
	lliKey1 = 1;
	pvData1 = (char*)cIndexTree.Put(&lliKey1, sizeof(int64), 103);
	AssertLongLongInt(1 /* root node (256 children) */ + 7 /* empty nodes with child */ + 1 /* node with no children but with data */, pcMemory->GetTotalAllocations());
	AssertLongLongInt(tRootNodeSize + (tNodeSize + tNoDataSize) * 7 + (tNodeSize + 103), pcMemory->GetTotalAllocatedMemory());

	AssertInt(tNodeSize + 103, pcMemory->GetSize(cIndexTree.GetNodeForData(pvData1)));

	cIndexTree.Kill();
	AssertLongLongInt(0, pcMemory->GetTotalAllocations());
	AssertLongLongInt(0, pcMemory->GetTotalAllocatedMemory());

	cMemoryAllocator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemory(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	BeginTests();

	TestIndexTreeMemoryComplex();

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

