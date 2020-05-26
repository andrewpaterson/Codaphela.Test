#include "BaseLib/StringHelper.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/Logger.h"
#include "BaseLib/GlobalMemory.h"
#include "CoreLib/IndexTreeEvicting.h"
#include "CoreLib/IndexTreeEvictedList.h"
#include "CoreLib/IndexedDataEvictedList.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexTreeEvictingAccess.h"
#include "CoreLib/IndexTreeEvictionStrategyRandom.h"
#include "CoreLib/IndexTreeFileDefaultCallback.h"
#include "TestLib/Assert.h"


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

	cHelper.Init("Output" _FS_"IndexTreeEvicting0", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, 8 KB, NULL, NULL, &gcIndexTreeFileDefaultCallback, eWriteThrough, eKeyReverse);
	cAccess.Init(&cIndexTree);

	iData = 78;
	cAccess.PutLongData(1LL, &iData, sizeof(int));
	sz.Init();
	cIndexTree.Print(&sz, TRUE);
	if (eWriteThrough == IWT_Yes && eKeyReverse == IKR_Yes)
	{
		AssertStringApproximate(
			"= [IndexTreeFile]  ===============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
			"   Both:   root -> 1:6 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  ()\n"
			"Key: ------------- [0x01 00 00 00 00 00 00 00] -------------\n"
			"   Both:   0    -> 1:5  ()\n"
			"   Both:   0    -> 1:4  ()\n"
			"   Both:   0    -> 1:3  ()\n"
			"   Both:   0    -> 1:2  ()\n"
			"   Both:   0    -> 1:1  ()\n"
			"   Both:   0    -> 1:0  ()\n"
			"   Both:   0    -> 0:0  ()\n"
			"   Both:   1(X) (HAS_DATA, NODES_EMPTY)\n"
			, sz.Text());
	}
	else if (eWriteThrough == IWT_Yes && eKeyReverse == IKR_No)
	{
		AssertStringApproximate(
			"= [IndexTreeFile]  ===============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
			"   Both:   root -> . 1:6 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  ()\n"
			"Key: ------------- [0x01 00 00 00 00 00 00 00] -------------\n"
			"   Both:   1    -> 1:5  ()\n"
			"   Both:   0    -> 1:4  ()\n"
			"   Both:   0    -> 1:3  ()\n"
			"   Both:   0    -> 1:2  ()\n"
			"   Both:   0    -> 1:1  ()\n"
			"   Both:   0    -> 1:0  ()\n"
			"   Both:   0    -> 0:0  ()\n"
			"   Both:   0(X) (HAS_DATA, NODES_EMPTY)\n"
			, sz.Text());
	}
	else if (eWriteThrough == IWT_No && eKeyReverse == IKR_Yes)
	{
		AssertStringApproximate(
			"= [IndexTreeFile]  ===============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
			" Memory:   root -> o . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  (DIRTY_NODE, DIRTY_PATH)\n"
			"Key: ------------- [0x01 00 00 00 00 00 00 00] -------------\n"
			" Memory:   0    -> o  (DIRTY_NODE, DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_NODE, DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_NODE, DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_NODE, DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_NODE, DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_NODE, DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_NODE, DIRTY_PATH)\n"
			" Memory:   1(X) (DIRTY_NODE, DIRTY_PATH, HAS_DATA, NODES_EMPTY)\n"
			, sz.Text());
	}
	else if (eWriteThrough == IWT_No && eKeyReverse == IKR_No)
	{
		AssertStringApproximate(
			"= [IndexTreeFile]  ===============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
			" Memory:   root -> . o . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  (DIRTY_NODE, DIRTY_PATH)\n"
			"Key: ------------- [0x01 00 00 00 00 00 00 00] -------------\n"
			" Memory:   1    -> o  (DIRTY_NODE, DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_NODE, DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_NODE, DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_NODE, DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_NODE, DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_NODE, DIRTY_PATH)\n"
			" Memory:   0    -> o  (DIRTY_NODE, DIRTY_PATH)\n"
			" Memory:   0(X) (DIRTY_NODE, DIRTY_PATH, HAS_DATA, NODES_EMPTY)\n"
			, sz.Text());
	}
	sz.Kill();

	cAccess.Flush();
	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvictingEvict(EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse)
{
	CIndexTreeEvicting					cIndexTree;
	CIndexTreeHelper					cHelper;
	CDurableFileController				cController;
	CIndexTreeEvictingAccess			cAccess;
	CMemoryAllocator					cAllocator;
	CIndexTreeEvictionStrategyRandom	cStrategy;
	CIndexTreeEvictedList				cIndexTreeEvictedList;   // CIndexTreeEvictionCallback
	size_t								sSize;
	CIndexTreeFileDefaultCallback		cWriterCallback;

	cHelper.Init("Output" _FS_"IndexTreeEvicting0a", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cIndexTreeEvictedList.Init();
	cController.Begin();
	cStrategy.Init();
	cIndexTree.Init(&cController, "Sub", 8 KB, &cIndexTreeEvictedList, &cStrategy, &cWriterCallback, eWriteThrough, eKeyReverse);
	cAccess.Init(&cIndexTree);


	sSize = cIndexTree.GetRoot()->CalculateNodeSize();
	AssertInt(2062, sSize);
	sSize = cIndexTree.GetSystemMemorySize();
	AssertInt(3100, sSize);

	cAccess.PutLongInt(1LL, 57);
	sSize = cIndexTree.GetRoot()->CalculateNodeSize();
	AssertInt(2062, sSize);
	sSize = cIndexTree.GetSystemMemorySize();
	AssertInt(3412, sSize);

	cAccess.Flush();
	sSize = cIndexTree.GetRoot()->CalculateNodeSize();
	AssertInt(2062, sSize);
	sSize = cIndexTree.GetSystemMemorySize();
	AssertInt(3412, sSize);

	cAccess.DeleteLong(1LL);
	cAccess.Flush();
	sSize = cIndexTree.GetRoot()->CalculateNodeSize();
	AssertInt(2062, sSize);
	sSize = cIndexTree.GetSystemMemorySize();
	AssertInt(3100, sSize);


	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cIndexTreeEvictedList.Kill();
	cController.Kill();
	cStrategy.Kill();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvictingPut(EIndexWriteThrough eWriteThrough)
{
	CIndexTreeEvicting					cIndexTree;
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
	cHelper.Init("Output" _FS_"IndexTreeEvicting1", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cEvictedNodes.Init();
	cStrategy.Init();
	cIndexTree.Init(&cController, "Here", 3656, &cEvictedNodes, &cStrategy, &gcIndexTreeFileDefaultCallback, &cAllocator, eWriteThrough, IKR_No);
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

	AssertLongLongInt(3316, pcMemory->GetTotalAllocatedMemory());
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
	cHelper.Kill(TRUE);
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
	cHelper.Init("Output" _FS_"IndexTreeEvicting2", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, 8192, NULL, NULL, &gcIndexTreeFileDefaultCallback, &cAllocator, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutStringString(szAlbatros, szAlbatros));
	AssertTrue(cAccess.PutStringString(szAlba, szAlba));
	AssertTrue(cAccess.PutStringString(szAlbaquerque, szAlbaquerque));
	AssertLongLongInt(3674, pcMemory->GetTotalAllocatedMemory());

	sLogConfig = gcLogger.SetSilent();
	AssertFalse(cAccess.EvictString(szAlba));
	gcLogger.SetConfig(&sLogConfig);
	AssertLongLongInt(3674, pcMemory->GetTotalAllocatedMemory());

	AssertTrue(cAccess.EvictString(szAlbatros));
	AssertLongLongInt(3533, pcMemory->GetTotalAllocatedMemory());

	sLogConfig = gcLogger.SetSilent();
	AssertFalse(cAccess.EvictString(szAlba));
	gcLogger.SetConfig(&sLogConfig);
	AssertLongLongInt(3533, pcMemory->GetTotalAllocatedMemory());

	AssertTrue(cAccess.EvictString(szAlbaquerque));
	AssertLongLongInt(3281, pcMemory->GetTotalAllocatedMemory());

	AssertTrue(cAccess.EvictString(szAlba));
	AssertLongLongInt(3096, pcMemory->GetTotalAllocatedMemory());

	cController.End();
	cIndexTree.Kill();
	AssertLongLongInt(0, pcMemory->GetTotalAllocatedMemory());
	cHelper.Kill(TRUE);
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
	cHelper.Init("Output" _FS_"IndexTreeEvicting3", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, 8192, NULL, NULL, &gcIndexTreeFileDefaultCallback, &cAllocator, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);
	AssertLongLongInt(3096, pcMemory->GetTotalAllocatedMemory());

	AssertTrue(cAccess.PutStringString(szAlbatros, szAlbatros));
	AssertTrue(cAccess.PutStringString(szAlba, szAlba));
	AssertTrue(cAccess.PutStringString(szAlbaquerque, szAlbaquerque));
	AssertLongLongInt(3674, pcMemory->GetTotalAllocatedMemory());

	AssertTree(
		"= [IndexTreeFile]  ===============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n" 
		" Memory:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . o . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n" 
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
		"= [IndexTreeFile]  ===============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
		"   Both:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 1:2 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n"
		"Key: ------------- [alba] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 0:0 \n"
		"+Memory:   a(X) -> o . . o \n"
		"-  File:   a(X) -> . . . . \n"
		"Key: ------------- [albaquerque] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 0:0 \n"
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
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 0:0 \n"
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
		"= [IndexTreeFile]  ===============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
		"   Both:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 1:2 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n"
		"Key: ------------- [alba] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 0:0 \n"
		"+Memory:   a(X) -> o . . 1:5 \n"
		"-  File:   a(X) -> . . . 1:5 \n"
		"Key: ------------- [albaquerque] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 0:0 \n"
		"+Memory:   a(X) -> o . . 1:5 \n"
		"-  File:   a(X) -> . . . 1:5 \n"
		" Memory:   q    -> o \n"
		" Memory:   u    -> o \n"
		" Memory:   e    -> o \n"
		" Memory:   r    -> o \n"
		" Memory:   q    -> o \n"
		" Memory:   u    -> o \n"
		" Memory:   e(X)\n"
		"Key: ------------- [albatros] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 0:0 \n"
		"+Memory:   a(X) -> o . . 1:5 \n"
		"-  File:   a(X) -> . . . 1:5 \n"
		"   Both:   t    -> 1:4 \n"
		"   Both:   r    -> 1:3 \n"
		"   Both:   o    -> 3:0 \n"
		"   Both:   s(X)",
		&cIndexTree);
	AssertFalse(cIndexTree.IsFlushed());

	AssertTrue(cAccess.FlushString(szAlbaquerque));
	AssertTree(
	"= [IndexTreeFile]  ===============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
		"   Both:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 1:2 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n"
		"Key: ------------- [alba] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 0:0 \n"
		"   Both:   a(X) -> 1:11 . . 1:5 \n"
		"Key: ------------- [albaquerque] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 0:0 \n"
		"   Both:   a(X) -> 1:11 . . 1:5 \n"
		"   Both:   q    -> 1:10 \n"
		"   Both:   u    -> 1:9 \n"
		"   Both:   e    -> 1:8 \n"
		"   Both:   r    -> 1:7 \n"
		"   Both:   q    -> 1:6 \n"
		"   Both:   u    -> 4:0 \n"
		"   Both:   e(X)\n"
		"Key: ------------- [albatros] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 0:0 \n"
		"   Both:   a(X) -> 1:11 . . 1:5 \n"
		"   Both:   t    -> 1:4 \n"
		"   Both:   r    -> 1:3 \n"
		"   Both:   o    -> 3:0 \n"
		"   Both:   s(X)",
		&cIndexTree);
	AssertTrue(cIndexTree.IsFlushed());
	AssertLongLongInt(3674, pcMemory->GetTotalAllocatedMemory());

	szResult = cAccess.GetStringString(szAlbatros);
	AssertString(szAlbatros, szResult.Text());	szResult.Kill();
	szResult = cAccess.GetStringString(szAlba);
	AssertString(szAlba, szResult.Text());	szResult.Kill();
	szResult = cAccess.GetStringString(szAlbaquerque);
	AssertString(szAlbaquerque, szResult.Text());	szResult.Kill();

	AssertTrue(cAccess.PutStringString(szAlbatros, szBatcave));
	AssertTrue(cAccess.PutStringString(szAlba, szBathroom));
	AssertLongLongInt(3677, pcMemory->GetTotalAllocatedMemory());

	szResult = cAccess.GetStringString(szAlbatros);
	AssertString(szBatcave, szResult.Text());	szResult.Kill();
	szResult = cAccess.GetStringString(szAlba);
	AssertString(szBathroom, szResult.Text());	szResult.Kill();
	AssertTree(
		"= [IndexTreeFile]  ===============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
		"   Both:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 1:2 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n"
		"Key: ------------- [alba] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 0:0 \n"
		"   Both:   a(X) -> 1:11 . . 1:5 \n"
		"Key: ------------- [albaquerque] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 0:0 \n"
		"   Both:   a(X) -> 1:11 . . 1:5 \n"
		"   Both:   q    -> 1:10 \n"
		"   Both:   u    -> 1:9 \n"
		"   Both:   e    -> 1:8 \n"
		"   Both:   r    -> 1:7 \n"
		"   Both:   q    -> 1:6 \n"
		"   Both:   u    -> 4:0 \n"
		"   Both:   e(X)\n"
		"Key: ------------- [albatros] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 0:0 \n"
		"   Both:   a(X) -> 1:11 . . 1:5 \n"
		"   Both:   t    -> 1:4 \n"
		"   Both:   r    -> 1:3 \n"
		"   Both:   o    -> 3:0 \n"
		"   Both:   s(X)",
		&cIndexTree);

	AssertTrue(cAccess.FlushString(szAlba));
	AssertTrue(cAccess.FlushString(szAlbatros));
	AssertTree(
		"= [IndexTreeFile]  ===============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
		"   Both:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 1:2 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n"
		"Key: ------------- [alba] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 5:0 \n"
		"   Both:   a(X) -> 1:11 . . 1:5 \n"
		"Key: ------------- [albaquerque] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 5:0 \n"
		"   Both:   a(X) -> 1:11 . . 1:5 \n"
		"   Both:   q    -> 1:10 \n"
		"   Both:   u    -> 1:9 \n"
		"   Both:   e    -> 1:8 \n"
		"   Both:   r    -> 1:7 \n"
		"   Both:   q    -> 1:6 \n"
		"   Both:   u    -> 4:0 \n"
		"   Both:   e(X)\n"
		"Key: ------------- [albatros] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 5:0 \n"
		"   Both:   a(X) -> 1:11 . . 1:5 \n"
		"   Both:   t    -> 1:4 \n"
		"   Both:   r    -> 1:3 \n"
		"   Both:   o    -> 1:12 \n"
		"   Both:   s(X)",
		&cIndexTree);

	AssertTrue(cAccess.PutStringString(szAlbaquerque, szBatmobile));
	AssertTrue(cAccess.FlushString(szAlbaquerque));
	AssertTrue(cIndexTree.IsFlushed());
	AssertTree(
		"= [IndexTreeFile]  ===============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n"
		"   Both:   root -> . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 1:2 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n"
		"Key: ------------- [alba] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 5:0 \n"
		"   Both:   a(X) -> 1:11 . . 1:5 \n"
		"Key: ------------- [albaquerque] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 5:0 \n"
		"   Both:   a(X) -> 1:11 . . 1:5 \n"
		"   Both:   q    -> 1:10 \n"
		"   Both:   u    -> 1:9 \n"
		"   Both:   e    -> 1:8 \n"
		"   Both:   r    -> 1:7 \n"
		"   Both:   q    -> 1:6 \n"
		"   Both:   u    -> 6:0 \n"
		"   Both:   e(X)\n"
		"Key: ------------- [albatros] -------------\n"
		"   Both:   a    -> 1:1 \n"
		"   Both:   l    -> 1:0 \n"
		"   Both:   b    -> 5:0 \n"
		"   Both:   a(X) -> 1:11 . . 1:5 \n"
		"   Both:   t    -> 1:4 \n"
		"   Both:   r    -> 1:3 \n"
		"   Both:   o    -> 1:12 \n"
		"   Both:   s(X)\n",
		&cIndexTree);

	cController.End();
	cIndexTree.Kill();
	cAccess.Kill();
	AssertLongLongInt(0, pcMemory->GetTotalAllocatedMemory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, 8192, NULL, NULL, &gcIndexTreeFileDefaultCallback, &cAllocator, IWT_No, IKR_No);
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
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertTree(char* szExpected, CIndexTreeEvicting* pcTree)
{
	CChars	sz;

	sz.Init();
	pcTree->Print(&sz, FALSE);
	AssertStringApproximate(szExpected, sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvicting(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	TestIndexTreeEvictingAdd(IWT_Yes, IKR_Yes);
	TestIndexTreeEvictingAdd(IWT_Yes, IKR_No);
	TestIndexTreeEvictingAdd(IWT_No, IKR_Yes);
	TestIndexTreeEvictingAdd(IWT_No, IKR_No);
	TestIndexTreeEvictingPut(IWT_Yes);
	TestIndexTreeEvictingPut(IWT_No);
	TestIndexTreeEvictingEvictWithChildren();
	TestIndexTreeEvictingFlushWithChildren();
	TestIndexTreeEvictingEvict(IWT_Yes, IKR_Yes);
	TestIndexTreeEvictingEvict(IWT_Yes, IKR_No);
	TestIndexTreeEvictingEvict(IWT_No, IKR_Yes);
	TestIndexTreeEvictingEvict(IWT_No, IKR_No);
	
	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

