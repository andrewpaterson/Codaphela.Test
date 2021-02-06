#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/Logger.h"
#include "BaseLib/GlobalMemory.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexTreeEvicting.h"
#include "CoreLib/IndexTreeEvictingAccess.h"
#include "CoreLib/IndexTreeEvictionStrategyDataOrderer.h"
#include "CoreLib/IndexTreeFileDiagnosticLoggingCallback.h"
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
	CAccessDataOrderer								cOrderer;
	CIndexTreeFileDiagnosticLoggingCallback			cCallback;
	char											szData[1024];
	int												i;
	CChars											sz;

	for (i = 0; i < 1023; i++)
	{
		szData[i] = (char)('A' + i % 26);
	}
	szData[1023] = '\0';

	cHelper.Init("Output" _FS_ "IndexTreeEvictingDiagnostic", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cOrderer.Init();
	cEvictionStrategy.Init(LifeLocal<CIndexTreeDataOrderer>(&cOrderer));
	cController.Begin();
	cCallback.Init();
	cIndexTree.Init(&cController, NULL, 8 KB, NULL, LifeLocal<CIndexTreeEvictionStrategy>(&cEvictionStrategy), NULL, IWT_No, IKR_No, LifeLocal<CIndexTreeDataOrderer>(&cOrderer));
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

	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	
	sz.Init();
	cCallback.Print(&sz);
	AssertString(
		"Put:    A0000001 [1024]\n" 
		"Put:    B0000002 [1024]\n" 
		"Put:    C0000003 [1024]\n" 
		"Put:    D0000004 [1024]\n" 
		"Flush:  A0000001 [1024]\n" 
		"Evict:  A0000001 [1024]\n" 
		"Put:    E0000005 [1024]\n" 
		"Flush:  B0000002 [1024]\n" 
		"Evict:  B0000002 [1024]\n" 
		"Put:    F0000006 [1024]\n" 
		"Flush:  C0000003 [1024]\n" 
		"Evict:  C0000003 [1024]\n" 
		"Remove: B0000002 [1024]\n" 
		"Flush:  D0000004 [1024]\n" 
		"Evict:  D0000004 [1024]\n" 
		"Put:    G0000007 [1024]\n" 
		"Flush:  E0000005 [1024]\n" 
		"Evict:  E0000005 [1024]\n" 
		"Flush:  B0000002 [0]\n" 
		"Flush:  F0000006 [1024]\n" 
		"Flush:  G0000007 [1024]\n" 
		"Evict:  F0000006 [1024]\n" 
		"Evict:  G0000007 [1024]\n", 
		sz.Text());

	cCallback.Kill();
	cController.Kill();
	cEvictionStrategy.Kill();
	cOrderer.Kill();

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


