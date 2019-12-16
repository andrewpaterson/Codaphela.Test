#include "BaseLib/StringHelper.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/MemoryAllocator.h"
#include "CoreLib/IndexTreeEvicting.h"
#include "CoreLib/EvictedList.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexTreeEvictingAccess.h"
#include "CoreLib/IndexTreeEvictionStrategyRandom.h"
#include "CoreLib/IndexTreeFileDefaultCallback.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvictingPut(EIndexWriteThrough eWriteThrough)
{
	CIndexTreeEvicting					cIndexTree;
	CEvictedList						cEvictedNodes;
	CIndexTreeHelper					cHelper;
	CDurableFileController				cDurableController;
	CIndexTreeEvictingAccess			cAccess;
	CMemoryAllocator					cAllocator;
	CGeneralMemory*						pcMemory;
	int									x;
	int									y;
	CIndexTreeEvictionStrategyRandom	cStrategy;
	
	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();
	cHelper.Init("Output" _FS_"IndexTreeEvicting1", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cEvictedNodes.Init();
	cStrategy.Init();
	cIndexTree.Init(&cDurableController, 3656, &cEvictedNodes, &cStrategy, &gcIndexTreeFileDefaultCallback, &cAllocator, eWriteThrough, IKR_No);
	cAccess.Init(&cIndexTree);

	AssertLongLongInt(3096, pcMemory->GetTotalAllocatedMemory());
	x = 1234;
	cAccess.PutStringInt("Tomato", x);
	AssertLongLongInt(3304, pcMemory->GetTotalAllocatedMemory());
	AssertInt(1, cIndexTree.NumMemoryElements());
	AssertInt(7, cIndexTree.NumMemoryNodes());
	AssertInt(7, strlen("Tomato") + 1);  //6 nodes for Tomato + the root node.
	AssertInt(0, cEvictedNodes.NumElements());
	cEvictedNodes.Clear();

	y = 567890;
	cAccess.PutStringInt("Plantation", y);

	AssertLongLongInt(3448, pcMemory->GetTotalAllocatedMemory());
	AssertInt(1, cEvictedNodes.NumElements());
	AssertString("Tomato", (char*)cEvictedNodes.GetKey(0));
	AssertInt(x, *((int*)cEvictedNodes.GetData(0)));
	AssertInt(1, cIndexTree.NumMemoryElements());
	AssertInt(11, cIndexTree.NumMemoryNodes());
	AssertInt(11, strlen("Plantation") + 1);  //10 nodes for Plantation + the root node.
	cEvictedNodes.Clear();

	AssertInt(1234, cAccess.GetStringInt("Tomato"));

	AssertLongLongInt(3316, pcMemory->GetTotalAllocatedMemory());
	AssertInt(1, cEvictedNodes.NumElements());
	AssertString("Plantation", (char*)cEvictedNodes.GetKey(0));
	AssertInt(y, *((int*)cEvictedNodes.GetData(0)));
	AssertInt(1, cIndexTree.NumMemoryElements());
	AssertInt(7, cIndexTree.NumMemoryNodes());

	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cEvictedNodes.Kill();
	cStrategy.Kill();
	cDurableController.Kill();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvicting(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	BeginTests();

	TestIndexTreeEvictingPut(IWT_Yes);
	TestIndexTreeEvictingPut(IWT_No);

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

