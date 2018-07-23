#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/IndexedFilesEvicting.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexedFilesEvictedDescriptorList.h"
#include "TestLib/Assert.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesEvictingSomething(BOOL bWriteThrough)
{
	CIndexedFilesEvicting						mcFileCache;
	CDurableFileController					cDurableController;
	CIndexTreeHelper						cHelper;
	CIndexedFilesEvictedDescriptorList		cCallback;
	char									szMoreover[] = "Although moreover mistaken kindness me feelings do be marianne.  Cordial village and settled she ability law herself.";
	char									sz[200];
	int										iLenMoreover;
	OIndex									oi;
	CIndexedDataDescriptor*					pcDescriptor;

	cHelper.Init("Output" _FS_ "Test1", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cCallback.Init();

	cDurableController.Begin();
	mcFileCache.Init(&cDurableController, "DAT", "Test1.IDX", "_TestIDX", 1024, bWriteThrough, &cCallback);
	cDurableController.End();
	cDurableController.Begin();

	iLenMoreover = strlen(szMoreover) + 1;
	oi = 45;

	pcDescriptor = cCallback.AddDescriptor(oi, iLenMoreover);
	AssertTrue(cCallback.GetDescriptor(oi, NULL));

	AssertTrue(mcFileCache.SetData(oi, pcDescriptor, szMoreover, 0));
	AssertTrue(mcFileCache.GetData(oi, pcDescriptor, sz));
	AssertString(szMoreover, sz);
	AssertTrue(mcFileCache.Flush(TRUE));

	cDurableController.End();
	mcFileCache.Kill();

	cDurableController.Begin();
	mcFileCache.Init(&cDurableController, "DAT", "Test1.IDX", "_TestIDX", 1024, bWriteThrough, &cCallback);
	cDurableController.End();
	cDurableController.Begin();

	AssertTrue(cCallback.GetDescriptor(oi, pcDescriptor));
	AssertTrue(mcFileCache.GetData(oi, pcDescriptor, sz));
	AssertString(szMoreover, sz);

	cDurableController.End();
	mcFileCache.Kill();

	cCallback.Kill();

	cDurableController.Kill();
	cHelper.Kill(TRUE);

	// Actually test shit for eviction.
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesEvicting(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	BeginTests();

	TestIndexedFilesEvictingSomething(FALSE);
	TestIndexedFilesEvictingSomething(TRUE);

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

