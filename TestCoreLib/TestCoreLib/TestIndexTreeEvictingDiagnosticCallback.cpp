#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/Logger.h"
#include "BaseLib/GlobalMemory.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexTreeEvicting.h"
#include "CoreLib/IndexTreeEvictingAccess.h"
#include "CoreLib/IndexTreeEvictionStrategyDataOrderer.h"
#include "TestLib/Assert.h"
#include "TestIndexTreeObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvictingDiagnosticCallbackStuff(void)
{
	CIndexTreeEvictingAccess 				cAccess;
	CIndexTreeEvicting						cIndexTree;
	CIndexTreeHelper						cHelper;
	CDurableFileController					cController;
	CIndexTreeEvictionStrategyDataOrderer	cEvictionStrategy;
	CAccessDataOrderer						cDataOrderer;
	CIndexTreeFileKeyDiagnosticCallback		cCallback;

	cHelper.Init("Output" _FS_ "IndexTreeEvictingDiagnostic", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDataOrderer.Init();
	cEvictionStrategy.Init(&cDataOrderer);
	cController.Begin();
	cCallback.Init("any");
	cIndexTree.Init(&cController, NULL, 8 KB, NULL, &cEvictionStrategy, NULL, IWT_No, IKR_No, &cDataOrderer);
	cIndexTree.SetDiagnosticCallback(&cCallback);
	cAccess.Init(&cIndexTree);



	cAccess.Flush();
	cAccess.ValidateIndex();

	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cCallback.Kill();
	cController.Kill();
	cEvictionStrategy.Kill();
	cDataOrderer.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvictingDiagnosticCallback(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	TestIndexTreeEvictingDiagnosticCallbackStuff();

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}


