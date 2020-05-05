#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/Logger.h"
#include "BaseLib/DebugOutput.h"
#include "BaseLib/GlobalMemory.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexTreeFile.h"
#include "CoreLib/IndexTreeFileAccess.h"
#include "TestLib/Assert.h"
#include "TestIndexTreeObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeTemplateFileStuff(void)
{
	CIndexTreeHelper								cHelper;
	CDurableFileController							cController;
	CIndexTreeFile									cIndexTree;
	CIndexTreeFileAccess							cAccess;
	CTestIndexTreeObject							cObject1;
	CTestIndexTreeObject							cObject2;
	CTestIndexTreeObject							cResult;

	cHelper.Init("Output" _FS_"IndexTree0", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL);
	cAccess.Init(&cIndexTree);
	
	cObject1.Init("Hello");
	cObject2.Init("Haplo");

	AssertTrue(cAccess.PutKeyData(cObject1.GetName(), cObject1.NameLength(), &cObject1, sizeof(CTestIndexTreeObject)));
	AssertTrue(cAccess.PutKeyData(cObject2.GetName(), cObject2.NameLength(), &cObject2, sizeof(CTestIndexTreeObject)));
	AssertInt(2, cIndexTree.NumElements());
		
	AssertTrue(cIndexTree.Get(cObject1.GetName(), cObject1.NameLength(), &cResult, NULL));
	AssertString("Hello", cResult.GetName());
	AssertTrue(cIndexTree.Get(cObject2.GetName(), cObject2.NameLength(), &cResult, NULL));
	AssertString("Haplo", cResult.GetName());
	AssertFalse(cIndexTree.Get("Help", 4, &cResult, NULL));

	AssertTrue(cIndexTree.Remove(cObject1.GetName(), cObject1.NameLength()));
	AssertTrue(cIndexTree.Get(cObject2.GetName(), cObject2.NameLength(), &cResult, NULL));
	AssertString("Haplo", cResult.GetName());
	AssertFalse(cIndexTree.Get(cObject1.GetName(), cObject1.NameLength(), &cResult, NULL));
	AssertFalse(cIndexTree.Get("Hap", 3, &cResult, NULL));
	AssertInt(1, cIndexTree.NumElements());

	AssertTrue(cIndexTree.Remove(cObject2.GetName(), cObject2.NameLength()));
	AssertFalse(cIndexTree.Get(cObject2.GetName(), cObject2.NameLength(), &cResult, NULL));
	AssertFalse(cIndexTree.Get(cObject1.GetName(), cObject1.NameLength(), &cResult, NULL));
	AssertInt(0, cIndexTree.NumElements());

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
void TestIndexTreeTemplateFile(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	TestIndexTreeTemplateFileStuff();

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

