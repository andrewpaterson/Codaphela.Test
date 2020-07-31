#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/Logger.h"
#include "BaseLib/GlobalMemory.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexTreeEvicting.h"
#include "CoreLib/IndexTreeEvictingAccess.h"
#include "CoreLib/IndexTreeEvictionStrategyDataOrderer.h"
#include "CoreLib/IndexTreeFileKeyDiagnosticLoggingCallback.h"
#include "TestLib/Assert.h"
#include "TestIndexTreeObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileKeyDiagnosticCallbackStuff(void)
{
	CIndexTreeEvictingAccess 						cAccess;
	CIndexTreeEvicting								cIndexTree;
	CIndexTreeHelper								cHelper;
	CDurableFileController							cController;
	CIndexTreeEvictionStrategyDataOrderer			cEvictionStrategy;
	CAccessDataOrderer								cDataOrderer;
	CIndexTreeFileKeyDiagnosticLoggingCallback		cCallback;
	char											szData[1024];
	int												i;

	for (i = 0; i < 1023; i++)
	{
		szData[i] = (char)('A' + i % 26);
	}
	szData[1023] = '\0';

	cHelper.Init("Output" _FS_ "IndexTreeEvictingDiagnostic", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDataOrderer.Init();
	cEvictionStrategy.Init(&cDataOrderer);
	cController.Begin();
	cCallback.Init();
	cIndexTree.Init(&cController, NULL, 8 KB, NULL, &cEvictionStrategy, NULL, IWT_No, IKR_No, &cDataOrderer);
	cIndexTree.SetDiagnosticCallback(&cCallback);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringString("A0000001", szData);

	cAccess.PutStringString("B0000002", szData);

	cAccess.PutStringString("C0000003", szData);

	cAccess.PutStringString("D0000004", szData);

	cAccess.PutStringString("E0000005", szData);

	cAccess.PutStringString("F0000006", szData);

	cAccess.DeleteString("B0000002");

	cAccess.PutStringString("G0000007", szData);

	cAccess.Flush();
	cAccess.ValidateIndex();


	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	
	cCallback.Dump();
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
void TestIndexTreeFileKeyDiagnosticCallback(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	TestIndexTreeFileKeyDiagnosticCallbackStuff();

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}


