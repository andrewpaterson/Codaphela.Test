#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/Logger.h"
#include "BaseLib/DebugOutput.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexTreeTemplateFile.h"
#include "CoreLib/IndexTreeFileAccess.h"
#include "TestLib/Assert.h"
#include "IndexTreeFileTestCallback.h"
#include "IndexTreeCallbackTestObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileCallbackWorks(void)
{
	CIndexTreeHelper									cHelper;
	CDurableFileController								cDurableController;
	CIndexTreeTemplateFile<CTestIndexTreeMemoryObject>	cIndexTree;
	CIndexTreeFileAccess								cAccess;
	CIndexTreeFileTestCallback							cDataCallback;
	CTestIndexTreeMemoryObject							cTestObject1;
	char												szKey1[3] = "AB";
	CTestIndexTreeMemoryObject							cTestObject2;
	char												szKey2[3] = "AD";
	CTestIndexTreeMemoryObject							cResult;


	cHelper.Init("Output" _FS_"IndexTreeCallback", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, &cDataCallback, TRUE);
	cAccess.Init(&cIndexTree);

	cTestObject1.Init(1, 2, 3, 4);
	AssertTrue(cAccess.PutStringData(szKey1, &cTestObject1, sizeof(CTestIndexTreeMemoryObject)));

	cDurableController.End();
	cIndexTree.Kill();

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, &cDataCallback, TRUE);

	memset(&cResult, 0, sizeof(CTestIndexTreeMemoryObject));
	AssertTrue(cIndexTree.Get(szKey1, 2, &cResult));
	AssertInt(17, cResult.mi1);
	AssertInt(2, cResult.mi2);
	AssertInt(56, cResult.mi3);
	AssertInt(4, cResult.mi4);

	cDurableController.End();
	cIndexTree.Kill();

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, &cDataCallback, FALSE);

	cTestObject1.Init(5, 6, 7, 8);
	AssertTrue(cAccess.PutStringData(szKey1, &cTestObject1, sizeof(CTestIndexTreeMemoryObject)));
	cTestObject2.Init(9, 10, 11, 12);
	AssertTrue(cAccess.PutStringData(szKey2, &cTestObject2, sizeof(CTestIndexTreeMemoryObject)));
	
	cIndexTree.Flush();
	cDurableController.End();
	cIndexTree.Kill();

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, &cDataCallback, FALSE);

	memset(&cResult, 0, sizeof(CTestIndexTreeMemoryObject));
	AssertTrue(cIndexTree.Get(szKey1, 2, &cResult));
	AssertInt(17, cResult.mi1);
	AssertInt(6, cResult.mi2);
	AssertInt(56, cResult.mi3);
	AssertInt(8, cResult.mi4);

	memset(&cResult, 0, sizeof(CTestIndexTreeMemoryObject));
	AssertTrue(cIndexTree.Get(szKey2, 2, &cResult));
	AssertInt(17, cResult.mi1);
	AssertInt(10, cResult.mi2);
	AssertInt(56, cResult.mi3);
	AssertInt(12, cResult.mi4);

	cDurableController.End();
	cAccess.Kill();
	cIndexTree.Kill();

	cDurableController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileCallback(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	BeginTests();

	TestIndexTreeFileCallbackWorks();

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

