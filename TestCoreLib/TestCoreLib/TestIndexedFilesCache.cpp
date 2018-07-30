#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexedFilesEvictedDescriptorList.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesEvictingFlush(BOOL bWriteThrough)
{
	CDurableFileController					cDurableController;
	CIndexTreeHelper						cHelper;
	CIndexedFilesEvictedDescriptorList		cCallback;
	char									szMoreover[] = "Although moreover mistaken kindness me feelings do be marianne.  Cordial village and settled she ability law herself.";
	char									sz[200];
	int										iLenMoreover;
	OIndex									oi;
	CIndexedDataDescriptor					cDescriptor;
	unsigned int							uiSize;

	cHelper.Init("Output" _FS_ "Test1", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 1024, bWriteThrough);

	AssertTrue(cDurableController.Begin());
	iLenMoreover = strlen(szMoreover) + 1;
	oi = 45;
	AssertInt(0, cCallback.NumCached());

	AssertTrue(cCallback.Add(oi, szMoreover, iLenMoreover, 0));
	AssertTrue(cCallback.TestGetDescriptor(oi, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertTrue(cCallback.Get(oi, &uiSize, sz, 200));
	AssertInt(iLenMoreover, uiSize);
	AssertString(szMoreover, sz);
	AssertInt(1, cCallback.NumCached());
	AssertTrue(cCallback.Flush(TRUE));

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());

	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 1024, bWriteThrough);
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cDurableController.Begin());

	AssertTrue(cCallback.TestGetDescriptor(oi, &cDescriptor));
	AssertFalse(cDescriptor.IsCached());
	AssertTrue(cDescriptor.HasFile());
	AssertTrue(cCallback.Get(oi, &uiSize, sz, 200));
	AssertInt(iLenMoreover, uiSize);
	AssertString(szMoreover, sz);

	AssertTrue(cDurableController.End());

	AssertTrue(cCallback.Kill());

	cDurableController.Kill();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
//void TestIndexedFilesEvictingEviction(BOOL bWriteThrough)
//{
//	CDurableFileController					cDurableController;
//	CIndexTreeHelper						cHelper;
//	CIndexedFilesEvictedDescriptorList		cCallback;
//	char									szMoreover[] = "Although moreover mistaken kindness me feelings do be marianne.  Cordial village and settled she ability law herself.";
//	char									szIndulged[] = "Concerns greatest margaret him absolute entrance nay.  Door neat week do find past he.Be no surprise he honoured indulged.";
//	char									szSeparate[] = "To they four in love.  Settling you has separate supplied bed.  Concluded resembled suspected his resources curiosity joy.";
//	char									sz[200];
//	int										iLenMoreover;
//	int										iLenIndulged;
//	int										iLenSeparate;
//	OIndex									oi;
//	CIndexedDataDescriptor*					pcDescriptor;
//
//	cHelper.Init("Output" _FS_ "Test2", "primary", "backup", TRUE);
//	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
//
//	cCallback.Init();
//
//	cDurableController.Begin();
//	mcFileCache.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 1024, bWriteThrough, &cCallback);
//	cDurableController.End();
//	cDurableController.Begin();
//
//	iLenMoreover = strlen(szMoreover) + 1;
//	oi = 45;
//
//	pcDescriptor = cCallback.AddDescriptor(oi, iLenMoreover);
//	AssertTrue(cCallback.GetDescriptor(oi, NULL));
//
//	AssertTrue(mcFileCache.SetData(oi, pcDescriptor, szMoreover, 0));
//	AssertTrue(mcFileCache.GetData(oi, pcDescriptor, sz));
//	AssertString(szMoreover, sz);
//	AssertTrue(mcFileCache.Flush(TRUE));
//
//	cDurableController.End();
//	mcFileCache.Kill();
//
//	cDurableController.Begin();
//	mcFileCache.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 1024, bWriteThrough, &cCallback);
//	cDurableController.End();
//	cDurableController.Begin();
//
//	AssertTrue(cCallback.GetDescriptor(oi, pcDescriptor));
//	AssertTrue(mcFileCache.GetData(oi, pcDescriptor, sz));
//	AssertString(szMoreover, sz);
//
//	cDurableController.End();
//	mcFileCache.Kill();
//
//	cCallback.Kill();
//
//	cDurableController.Kill();
//	cHelper.Kill(TRUE);
//}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesEvicting(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	TestIndexedFilesEvictingFlush(FALSE);
	//TestIndexedFilesEvictingEviction(TRUE);

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

