#include "BaseLib/StringHelper.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/Logger.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/AccessDataOrderer.h"
#include "CoreLib/IndexTreeEvicting.h"
#include "CoreLib/IndexTreeEvictedList.h"
#include "CoreLib/IndexedDataEvictedList.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexTreeEvictingAccess.h"
#include "CoreLib/IndexTreeEvictionStrategyRandom.h"
#include "CoreLib/IndexTreeEvictionStrategyDataOrderer.h"
#include "CoreLib/IndexTreeFileDefaultDataCallback.h"
#include "TestLib/Assert.h"
#include "TestIndexTreeEvicting.h"


void AssertTree(char* szExpected, CIndexTreeEvicting* pcTree);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvictingAdd(EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse)
{
	CIndexTreeEvicting			cIndexTree;
	CIndexTreeEvictingAccess	cAccess;
	CDurableFileController		cController;
	CIndexTreeHelper			cHelper;
	int							iData;
	CChars						sz;

	cHelper.Init("Output" _FS_"IndexTreeEvicting0", "primary", "backup", true);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, 8 KB, NULL, LifeNull<CIndexTreeEvictionStrategy>(), NULL, eWriteThrough, eKeyReverse);
	cAccess.Init(&cIndexTree);

	iData = 78;
	cAccess.PutLongData(1LL, &iData, sizeof(int));
	sz.Init();
	cIndexTree.Print(&sz, true, false);
	if (eWriteThrough == IWT_Yes && eKeyReverse == IKR_Yes)
	{
		AssertStringApproximate(
			"= [IndexTreeEvicting]  =============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
			"   Both:   root -> 2:6 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  ()\n"
			"Key: ------------- [0x01 00 00 00 00 00 00 00] -------------\n"
			"   Both:   0    -> 2:5  ()\n"
			"   Both:   0    -> 2:4  ()\n"
			"   Both:   0    -> 2:3  ()\n"
			"   Both:   0    -> 2:2  ()\n"
			"   Both:   0    -> 2:1  ()\n"
			"   Both:   0    -> 2:0  ()\n"
			"   Both:   0    -> 1:0  ()\n"
			"   Both:   1(X) (HAS_DATA, NODES_EMPTY)\n"
			, sz.Text());
		Pass();
	}
	else if (eWriteThrough == IWT_Yes && eKeyReverse == IKR_No)
	{
		AssertStringApproximate(
			"= [IndexTreeEvicting]  =============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
			"   Both:   root -> . 2:6 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  ()\n"
			"Key: ------------- [0x01 00 00 00 00 00 00 00] -------------\n"
			"   Both:   1    -> 2:5  ()\n"
			"   Both:   0    -> 2:4  ()\n"
			"   Both:   0    -> 2:3  ()\n"
			"   Both:   0    -> 2:2  ()\n"
			"   Both:   0    -> 2:1  ()\n"
			"   Both:   0    -> 2:0  ()\n"
			"   Both:   0    -> 1:0  ()\n"
			"   Both:   0(X) (HAS_DATA, NODES_EMPTY)\n"
			, sz.Text());
	}
	else if (eWriteThrough == IWT_No && eKeyReverse == IKR_Yes)
	{
		AssertStringApproximate(
			"= [IndexTreeEvicting]  =============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
			"+Memory:   root -> o . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  (DIRTY_PATH)\n"
			"-  File:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  (DIRTY_PATH)\n"
			"Key: ------------- [0x01 00 00 00 00 00 00 00] -------------\n"
			" Memory:   0    -> o  (DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_PATH)\n"
			" Memory:   1(X) (DIRTY_NODE, DIRTY_PATH, HAS_DATA, NODES_EMPTY)\n"
			, sz.Text());
		Pass();
	}
	else if (eWriteThrough == IWT_No && eKeyReverse == IKR_No)
	{
		AssertStringApproximate(
			"= [IndexTreeEvicting]  =============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
			"+Memory:   root -> . o . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  (DIRTY_PATH)\n"
			"-  File:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  (DIRTY_PATH)\n"
			"Key: ------------- [0x01 00 00 00 00 00 00 00] -------------\n"
			" Memory:   1    -> o  (DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_PATH)\n"
			" Memory:   0(X) (DIRTY_NODE, DIRTY_PATH, HAS_DATA, NODES_EMPTY)\n"
			, sz.Text());
		Pass();
	}
	sz.Kill();

	cAccess.Flush();
	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();
	cHelper.Kill(true);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvictingEvictRandom(EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse)
{
	CTestIndexTreeEvicting				cIndexTree;
	CIndexTreeHelper					cHelper;
	CDurableFileController				cController;
	CIndexTreeEvictingAccess			cAccess;
	CMemoryAllocator					cAllocator;
	CIndexTreeEvictionStrategyRandom	cStrategy;
	CIndexTreeEvictedList				cIndexTreeEvictedList;   // CIndexTreeEvictionCallback
	size_t								sSize;
	CIndexTreeFileDefaultDataCallback	cWriterCallback;

	cHelper.Init("Output" _FS_"IndexTreeEvicting0a", "primary", "backup", true);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cIndexTreeEvictedList.Init();
	cController.Begin();
	cStrategy.Init();
	cIndexTree.Init(&cController, "Sub", 8 KB, &cIndexTreeEvictedList, LifeLocal<CIndexTreeEvictionStrategy>(&cStrategy), &cWriterCallback, eWriteThrough, eKeyReverse);
	cAccess.Init(&cIndexTree);


	sSize = cIndexTree.GetRoot()->CalculateNodeSize();
	AssertLongLongInt(2062LL, sSize);
	sSize = cIndexTree.GetSystemMemorySize();
	AssertLongLongInt(3100LL, sSize);

	cAccess.PutLongInt(1LL, 57);
	sSize = cIndexTree.GetRoot()->CalculateNodeSize();
	AssertLongLongInt(2062LL, sSize);
	sSize = cIndexTree.GetSystemMemorySize();
	AssertLongLongInt(3424LL, sSize);

	cAccess.Flush();
	sSize = cIndexTree.GetRoot()->CalculateNodeSize();
	AssertInt(2062LL, sSize);
	sSize = cIndexTree.GetSystemMemorySize();
	AssertInt(3424LL, sSize);

	cAccess.DeleteLong(1LL);
	cAccess.Flush();
	sSize = cIndexTree.GetRoot()->CalculateNodeSize();
	AssertInt(2062LL, sSize);
	sSize = cIndexTree.GetSystemMemorySize();
	AssertInt(3100LL, sSize);


	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cIndexTreeEvictedList.Kill();
	cController.Kill();
	cStrategy.Kill();
	cHelper.Kill(true);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvictingPut(EIndexWriteThrough eWriteThrough)
{
	CTestIndexTreeEvicting				cIndexTree;
	CIndexTreeEvictedList				cEvictedNodes;
	CIndexTreeHelper					cHelper;
	CDurableFileController				cController;
	CIndexTreeEvictingAccess			cAccess;
	CMemoryAllocator					cAllocator;
	CGeneralMemory*						pcMemory;
	int									x;
	int									y;
	CIndexTreeEvictionStrategyRandom	cStrategy;
	
	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();
	cHelper.Init("Output" _FS_"IndexTreeEvicting1", "primary", "backup", true);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cEvictedNodes.Init();
	cStrategy.Init();
	cIndexTree.Init(&cController, "Here", 3656, &cEvictedNodes, LifeLocal<CIndexTreeEvictionStrategy>(&cStrategy), NULL, LifeLocal<CMallocator>(&cAllocator), eWriteThrough, IKR_No);
	cAccess.Init(&cIndexTree);

	AssertLongLongInt(3096, pcMemory->GetTotalAllocatedMemory());
	x = 1234;
	cAccess.PutStringInt("Tomato", x);
	AssertLongLongInt(3316LL, pcMemory->GetTotalAllocatedMemory());
	AssertInt(1, cIndexTree.NumMemoryElements());
	AssertInt(7, cIndexTree.NumMemoryNodes());
	AssertInt(7, strlen("Tomato") + 1);  //6 nodes for Tomato + the root node.
	AssertInt(0, cEvictedNodes.NumElements());
	cEvictedNodes.Clear();

	y = 567890;
	cAccess.PutStringInt("Plantation", y);

	AssertLongLongInt(3460LL, pcMemory->GetTotalAllocatedMemory());
	AssertInt(1, cEvictedNodes.NumElements());
	AssertString("Tomato", (char*)cEvictedNodes.GetKey(0));
	AssertInt(x, *((int*)cEvictedNodes.GetData(0)));
	AssertInt(1, cIndexTree.NumMemoryElements());
	AssertInt(11, cIndexTree.NumMemoryNodes());
	AssertInt(11, strlen("Plantation") + 1);  //10 nodes for Plantation + the root node.
	cEvictedNodes.Clear();

	AssertInt(1234, cAccess.GetStringInt("Tomato"));

	AssertLongLongInt(3328LL, pcMemory->GetTotalAllocatedMemory());
	AssertInt(1, cEvictedNodes.NumElements());
	AssertString("Plantation", (char*)cEvictedNodes.GetKey(0));
	AssertInt(y, *((int*)cEvictedNodes.GetData(0)));
	AssertInt(1, cIndexTree.NumMemoryElements());
	AssertInt(7, cIndexTree.NumMemoryNodes());

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cEvictedNodes.Kill();
	cStrategy.Kill();
	cController.Kill();
	cHelper.Kill(true);

	cAllocator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvictingEvictWithChildren(void)
{
	CIndexTreeEvictingAccess	cAccess;
	CIndexTreeHelper			cHelper;
	char						szAlbatros[] = "albatros";
	char						szAlba[] = "alba";
	char						szAlbaquerque[] = "albaquerque";
	CGeneralMemory*				pcMemory;
	CMemoryAllocator			cAllocator;
	CDurableFileController		cController;
	CIndexTreeEvicting			cIndexTree;
	SLogConfig					sLogConfig;

	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();
	cHelper.Init("Output" _FS_"IndexTreeEvicting2", "primary", "backup", true);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, 8192, NULL, LifeNull<CIndexTreeEvictionStrategy>(), NULL, LifeLocal<CMallocator>(&cAllocator), IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutStringString(szAlbatros, szAlbatros));
	AssertTrue(cAccess.PutStringString(szAlba, szAlba));
	AssertTrue(cAccess.PutStringString(szAlbaquerque, szAlbaquerque));
	AssertLongLongInt(3710LL, pcMemory->GetTotalAllocatedMemory());

	sLogConfig = gcLogger.SetSilent();
	AssertFalse(cAccess.EvictString(szAlba));
	gcLogger.SetConfig(&sLogConfig);
	AssertLongLongInt(3710LL, pcMemory->GetTotalAllocatedMemory());
	Pass();

	AssertTrue(cAccess.EvictString(szAlbatros));
	AssertLongLongInt(3557LL, pcMemory->GetTotalAllocatedMemory());

	sLogConfig = gcLogger.SetSilent();
	AssertFalse(cAccess.EvictString(szAlba));
	gcLogger.SetConfig(&sLogConfig);
	AssertLongLongInt(3557LL, pcMemory->GetTotalAllocatedMemory());
	Pass();

	AssertTrue(cAccess.EvictString(szAlbaquerque));
	AssertLongLongInt(3293LL, pcMemory->GetTotalAllocatedMemory());
	Pass();

	AssertTrue(cAccess.EvictString(szAlba));
	AssertLongLongInt(3096LL, pcMemory->GetTotalAllocatedMemory());

	cController.End();
	cIndexTree.Kill();
	AssertLongLongInt(0, pcMemory->GetTotalAllocatedMemory());
	cHelper.Kill(true);

	cController.Kill();
	cAllocator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvictingFlushWithChildren(void)
{
	CIndexTreeEvictingAccess	cAccess;
	CIndexTreeHelper			cHelper;
	char						szAlbatros[] = "albatros";
	char						szAlba[] = "alba";
	char						szAlbaquerque[] = "albaquerque";
	CGeneralMemory*				pcMemory;
	CMemoryAllocator			cAllocator;
	CDurableFileController		cController;
	CIndexTreeEvicting			cIndexTree;
	char						szBatmobile[] = "batmobile";
	char						szBatcave[] = "batcave";
	char						szBathroom[] = "bathroom";
	CChars						szResult;

	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();
	cHelper.Init("Output" _FS_"IndexTreeEvicting3", "primary", "backup", true);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, 8192, NULL, LifeNull<CIndexTreeEvictionStrategy>(), NULL, LifeLocal<CMallocator>(&cAllocator), IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);
	AssertLongLongInt(3096LL, pcMemory->GetTotalAllocatedMemory());
	Pass();

	AssertTrue(cAccess.PutStringString(szAlbatros, szAlbatros));
	AssertTrue(cAccess.PutStringString(szAlba, szAlba));
	AssertTrue(cAccess.PutStringString(szAlbaquerque, szAlbaquerque));
	AssertLongLongInt(3710LL, pcMemory->GetTotalAllocatedMemory());
	Pass();

	AssertTree(
		"= [IndexTreeEvicting]  =============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n" 
		"+Memory:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . o . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n" 
		"-  File:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n" 
		"Key: ------------- [alba] -------------\n"
		" Memory:   a    -> o \n"
		" Memory:   l    -> o \n"
		" Memory:   b    -> o \n"
		" Memory:   a(X) -> o . . o\n"
		"Key: ------------- [albaquerque] -------------\n"
		" Memory:   a    -> o \n" 
		" Memory:   l    -> o \n" 
		" Memory:   b    -> o \n" 
		" Memory:   a(X) -> o . . o \n" 
		" Memory:   q    -> o \n" 
		" Memory:   u    -> o \n" 
		" Memory:   e    -> o \n" 
		" Memory:   r    -> o \n" 
		" Memory:   q    -> o \n" 
		" Memory:   u    -> o \n" 
		" Memory:   e(X)\n" 
		"Key: ------------- [albatros] -------------\n" 
		" Memory:   a    -> o \n" 
		" Memory:   l    -> o \n" 
		" Memory:   b    -> o \n" 
		" Memory:   a(X) -> o . . o \n" 
		" Memory:   t    -> o \n" 
		" Memory:   r    -> o \n" 
		" Memory:   o    -> o \n" 
		" Memory:   s(X)", 
		&cIndexTree);
	AssertFalse(cIndexTree.IsFlushed());

	AssertTrue(cAccess.FlushString(szAlba));
	AssertTree(
		"= [IndexTreeEvicting]  =============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
		"   Both:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 2:2 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n"
		"Key: ------------- [alba] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 1:0 \n"
		"+Memory:   a(X) -> o . . o \n"
		"-  File:   a(X) -> . . . . \n"
		"Key: ------------- [albaquerque] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 1:0 \n"
		"+Memory:   a(X) -> o . . o \n"
		"-  File:   a(X) -> . . . . \n"
		" Memory:   q    -> o \n"
		" Memory:   u    -> o \n"
		" Memory:   e    -> o \n"
		" Memory:   r    -> o \n"
		" Memory:   q    -> o \n"
		" Memory:   u    -> o \n"
		" Memory:   e(X)\n"
		"Key: ------------- [albatros] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 1:0 \n"
		"+Memory:   a(X) -> o . . o \n"
		"-  File:   a(X) -> . . . . \n"
		" Memory:   t    -> o \n"
		" Memory:   r    -> o \n"
		" Memory:   o    -> o \n"
		" Memory:   s(X)",
		&cIndexTree);
	AssertFalse(cIndexTree.IsFlushed());

	AssertTrue(cAccess.FlushString(szAlbatros));
	AssertTree(
		"= [IndexTreeEvicting]  =============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
		"   Both:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 2:2 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n"
		"Key: ------------- [alba] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 1:0 \n"
		"+Memory:   a(X) -> o . . 2:5 \n"
		"-  File:   a(X) -> . . . 2:5 \n"
		"Key: ------------- [albaquerque] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 1:0 \n"
		"+Memory:   a(X) -> o . . 2:5 \n"
		"-  File:   a(X) -> . . . 2:5 \n"
		" Memory:   q    -> o \n"
		" Memory:   u    -> o \n"
		" Memory:   e    -> o \n"
		" Memory:   r    -> o \n"
		" Memory:   q    -> o \n"
		" Memory:   u    -> o \n"
		" Memory:   e(X)\n"
		"Key: ------------- [albatros] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 1:0 \n"
		"+Memory:   a(X) -> o . . 2:5 \n"
		"-  File:   a(X) -> . . . 2:5 \n"
		"   Both:   t    -> 2:4 \n"
		"   Both:   r    -> 2:3 \n"
		"   Both:   o    -> 3:0 \n"
		"   Both:   s(X)",
		&cIndexTree);
	AssertFalse(cIndexTree.IsFlushed());

	AssertTrue(cAccess.FlushString(szAlbaquerque));
	AssertTree(
	"= [IndexTreeEvicting]  =============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
		"   Both:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 2:2 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n"
		"Key: ------------- [alba] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 1:0 \n"
		"   Both:   a(X) -> 2:11 . . 2:5 \n"
		"Key: ------------- [albaquerque] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 1:0 \n"
		"   Both:   a(X) -> 2:11 . . 2:5 \n"
		"   Both:   q    -> 2:10 \n"
		"   Both:   u    -> 2:9 \n"
		"   Both:   e    -> 2:8 \n"
		"   Both:   r    -> 2:7 \n"
		"   Both:   q    -> 2:6 \n"
		"   Both:   u    -> 4:0 \n"
		"   Both:   e(X)\n"
		"Key: ------------- [albatros] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 1:0 \n"
		"   Both:   a(X) -> 2:11 . . 2:5 \n"
		"   Both:   t    -> 2:4 \n"
		"   Both:   r    -> 2:3 \n"
		"   Both:   o    -> 3:0 \n"
		"   Both:   s(X)",
		&cIndexTree);
	AssertTrue(cIndexTree.IsFlushed());
	AssertLongLongInt(3710LL, pcMemory->GetTotalAllocatedMemory());

	szResult = cAccess.GetStringString(szAlbatros);
	AssertString(szAlbatros, szResult.Text());	szResult.Kill();
	szResult = cAccess.GetStringString(szAlba);
	AssertString(szAlba, szResult.Text());	szResult.Kill();
	szResult = cAccess.GetStringString(szAlbaquerque);
	AssertString(szAlbaquerque, szResult.Text());	szResult.Kill();
	Pass();

	AssertTrue(cAccess.PutStringString(szAlbatros, szBatcave));
	AssertTrue(cAccess.PutStringString(szAlba, szBathroom));
	AssertLongLongInt(3713LL, pcMemory->GetTotalAllocatedMemory());
	Pass();

	szResult = cAccess.GetStringString(szAlbatros);
	AssertString(szBatcave, szResult.Text());	szResult.Kill();
	szResult = cAccess.GetStringString(szAlba);
	AssertString(szBathroom, szResult.Text());	szResult.Kill();
	AssertTree(
		"= [IndexTreeEvicting]  =============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
		"   Both:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 2:2 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n"
		"Key: ------------- [alba] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 1:0 \n"
		"   Both:   a(X) -> 2:11 . . 2:5 \n"
		"Key: ------------- [albaquerque] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 1:0 \n"
		"   Both:   a(X) -> 2:11 . . 2:5 \n"
		"   Both:   q    -> 2:10 \n"
		"   Both:   u    -> 2:9 \n"
		"   Both:   e    -> 2:8 \n"
		"   Both:   r    -> 2:7 \n"
		"   Both:   q    -> 2:6 \n"
		"   Both:   u    -> 4:0 \n"
		"   Both:   e(X)\n"
		"Key: ------------- [albatros] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 1:0 \n"
		"   Both:   a(X) -> 2:11 . . 2:5 \n"
		"   Both:   t    -> 2:4 \n"
		"   Both:   r    -> 2:3 \n"
		"   Both:   o    -> 3:0 \n"
		"   Both:   s(X)",
		&cIndexTree);

	AssertTrue(cAccess.FlushString(szAlba));
	AssertTrue(cAccess.FlushString(szAlbatros));
	AssertTree(
		"= [IndexTreeEvicting]  =============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
		"   Both:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 2:2 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n"
		"Key: ------------- [alba] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 5:0 \n"
		"   Both:   a(X) -> 2:11 . . 2:5 \n"
		"Key: ------------- [albaquerque] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 5:0 \n"
		"   Both:   a(X) -> 2:11 . . 2:5 \n"
		"   Both:   q    -> 2:10 \n"
		"   Both:   u    -> 2:9 \n"
		"   Both:   e    -> 2:8 \n"
		"   Both:   r    -> 2:7 \n"
		"   Both:   q    -> 2:6 \n"
		"   Both:   u    -> 4:0 \n"
		"   Both:   e(X)\n"
		"Key: ------------- [albatros] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 5:0 \n"
		"   Both:   a(X) -> 2:11 . . 2:5 \n"
		"   Both:   t    -> 2:4 \n"
		"   Both:   r    -> 2:3 \n"
		"   Both:   o    -> 2:12 \n"
		"   Both:   s(X)",
		&cIndexTree);

	AssertTrue(cAccess.PutStringString(szAlbaquerque, szBatmobile));
	AssertTrue(cAccess.FlushString(szAlbaquerque));
	AssertTrue(cIndexTree.IsFlushed());
	AssertTree(
		"= [IndexTreeEvicting]  =============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
		"   Both:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 2:2 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n"
		"Key: ------------- [alba] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 5:0 \n"
		"   Both:   a(X) -> 2:11 . . 2:5 \n"
		"Key: ------------- [albaquerque] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 5:0 \n"
		"   Both:   a(X) -> 2:11 . . 2:5 \n"
		"   Both:   q    -> 2:10 \n"
		"   Both:   u    -> 2:9 \n"
		"   Both:   e    -> 2:8 \n"
		"   Both:   r    -> 2:7 \n"
		"   Both:   q    -> 2:6 \n"
		"   Both:   u    -> 6:0 \n"
		"   Both:   e(X)\n"
		"Key: ------------- [albatros] -------------\n"
		"   Both:   a    -> 2:1 \n"
		"   Both:   l    -> 2:0 \n"
		"   Both:   b    -> 5:0 \n"
		"   Both:   a(X) -> 2:11 . . 2:5 \n"
		"   Both:   t    -> 2:4 \n"
		"   Both:   r    -> 2:3 \n"
		"   Both:   o    -> 2:12 \n"
		"   Both:   s(X)\n",
		&cIndexTree);

	cController.End();
	cIndexTree.Kill();
	cAccess.Kill();
	AssertLongLongInt(0, pcMemory->GetTotalAllocatedMemory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, 8192, NULL, LifeNull<CIndexTreeEvictionStrategy>(), NULL, LifeLocal<CMallocator>(&cAllocator), IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);
	AssertLongLongInt(3120, pcMemory->GetTotalAllocatedMemory());

	szResult = cAccess.GetStringString(szAlbatros);
	AssertString(szBatcave, szResult.Text());	szResult.Kill();
	szResult = cAccess.GetStringString(szAlba);
	AssertString(szBathroom, szResult.Text());	szResult.Kill();
	szResult = cAccess.GetStringString(szAlbaquerque);
	AssertString(szBatmobile, szResult.Text());	szResult.Kill();

	cController.End();
	cIndexTree.Kill();
	cAccess.Kill();
	AssertLongLongInt(0, pcMemory->GetTotalAllocatedMemory());
	cHelper.Kill(true);

	cController.Kill();
	cAllocator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvictingEvictLastAccessed(void)
{
	CTestIndexTreeEvicting					cIndexTree;
	CIndexTreeHelper						cHelper;
	CDurableFileController					cController;
	CIndexTreeEvictingAccess				cAccess;
	CIndexTreeEvictionStrategyDataOrderer	cStrategy;
	CIndexTreeEvictedList					cIndexTreeEvictedList;
	CAccessDataOrderer						cOrderer;
	char									szData[1024];
	int										i;
	size_t									sSize;
	char*									szEvictedKey;

	for (i = 0; i < 1023; i++)
	{
		szData[i] = (char)('A' + i % 26);
	}
	szData[1023] = '\0';

	cHelper.Init("Output" _FS_"IndexTreeEvicting4", "primary", "backup", true);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cIndexTreeEvictedList.Init();
	cController.Begin();
	cOrderer.Init();
	cStrategy.Init(LifeLocal<CIndexTreeDataOrderer>(&cOrderer));
	cIndexTree.Init(&cController, "Sub", 8 KB, &cIndexTreeEvictedList, LifeLocal<CIndexTreeEvictionStrategy>(&cStrategy), NULL, IWT_No, IKR_No, LifeLocal<CIndexTreeDataOrderer>(&cOrderer));
	cAccess.Init(&cIndexTree);

	sSize = cIndexTree.GetSystemMemorySize();
	AssertLongLongInt(3100LL, sSize);
	AssertInt(0, cIndexTreeEvictedList.NumElements());

	cAccess.PutStringString("A0000001", szData);
	sSize = cIndexTree.GetSystemMemorySize();
	AssertLongLongInt(4444LL, sSize);
	AssertInt(0, cIndexTreeEvictedList.NumElements());

	cAccess.PutStringString("B0000002", szData);
	sSize = cIndexTree.GetSystemMemorySize();
	AssertLongLongInt(5788LL, sSize);
	AssertInt(0, cIndexTreeEvictedList.NumElements());

	cAccess.PutStringString("C0000003", szData);
	sSize = cIndexTree.GetSystemMemorySize();
	AssertLongLongInt(7132LL, sSize);
	AssertInt(0, cIndexTreeEvictedList.NumElements());

	cAccess.PutStringString("D0000004", szData);
	sSize = cIndexTree.GetSystemMemorySize();
	AssertLongLongInt(7132LL, sSize);
	AssertInt(1, cIndexTreeEvictedList.NumElements());
	szEvictedKey = (char*)cIndexTreeEvictedList.GetKey(0);
	AssertString("A0000001", szEvictedKey);
	cIndexTreeEvictedList.Clear();

	cAccess.PutStringString("E0000005", szData);
	sSize = cIndexTree.GetSystemMemorySize();
	AssertLongLongInt(7132LL, sSize);
	AssertInt(1, cIndexTreeEvictedList.NumElements());
	szEvictedKey = (char*)cIndexTreeEvictedList.GetKey(0);
	AssertString("B0000002", szEvictedKey);
	cIndexTreeEvictedList.Clear();

	cAccess.PutStringString("G0000006", szData);
	sSize = cIndexTree.GetSystemMemorySize();
	AssertLongLongInt(7132LL, sSize);
	AssertInt(1, cIndexTreeEvictedList.NumElements());
	szEvictedKey = (char*)cIndexTreeEvictedList.GetKey(0);
	AssertString("C0000003", szEvictedKey);

	cAccess.Flush();
	cAccess.ValidateIndex();

	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cIndexTreeEvictedList.Kill();
	cController.Kill();
	cStrategy.Kill();
	cOrderer.Kill();
	cHelper.Kill(true);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvictingEmpty(void)
{
	CIndexTreeEvictingAccess 				cAccess;
	CIndexTreeEvicting						cIndexTree;
	CIndexTreeHelper						cHelper;
	CDurableFileController					cController;
	CIndexTreeEvictionStrategyDataOrderer	cEvictionStrategy;
	CAccessDataOrderer						cDataOrderer;

	cHelper.Init("Output" _FS_ "IndexTreeEvicting5", "primary", "backup", true);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDataOrderer.Init();
	cEvictionStrategy.Init(LifeLocal<CIndexTreeDataOrderer>(&cDataOrderer));

	cController.Begin();
	cIndexTree.Init(&cController, NULL, 8 KB, NULL, LifeLocal<CIndexTreeEvictionStrategy>(&cEvictionStrategy), NULL, IWT_No, IKR_No, LifeLocal<CIndexTreeDataOrderer>(&cDataOrderer));
	cAccess.Init(&cIndexTree);

	cAccess.Flush();
	cAccess.ValidateIndex();

	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();
	cEvictionStrategy.Kill();
	cDataOrderer.Kill();

	cHelper.Kill(true);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertTree(char* szExpected, CIndexTreeEvicting* pcTree)
{
	CChars	sz;

	sz.Init();
	pcTree->Print(&sz, false, false);
	AssertStringApproximate(szExpected, sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvicting(void)
{
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	TestIndexTreeEvictingEmpty();
	TestIndexTreeEvictingAdd(IWT_Yes, IKR_Yes);
	TestIndexTreeEvictingAdd(IWT_Yes, IKR_No);
	TestIndexTreeEvictingAdd(IWT_No, IKR_Yes);
	TestIndexTreeEvictingAdd(IWT_No, IKR_No);
	TestIndexTreeEvictingPut(IWT_Yes);
	TestIndexTreeEvictingPut(IWT_No);
	TestIndexTreeEvictingEvictWithChildren();
	TestIndexTreeEvictingFlushWithChildren();
	TestIndexTreeEvictingEvictRandom(IWT_Yes, IKR_Yes);
	TestIndexTreeEvictingEvictRandom(IWT_Yes, IKR_No);
	TestIndexTreeEvictingEvictRandom(IWT_No, IKR_Yes);
	TestIndexTreeEvictingEvictRandom(IWT_No, IKR_No);
	TestIndexTreeEvictingEvictLastAccessed();
	
	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	TypeConverterKill();
}

