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
void TestIndexedFilesEvictingEviction(BOOL bWriteThrough)
{
	CDurableFileController					cDurableController;
	CIndexTreeHelper						cHelper;
	CIndexedFilesEvictedDescriptorList		cCallback;
	char									szMoreover[] = "Although moreover mistaken kindness me feelings do be marianne.  Cordial village and settled she ability law herself.";
	char									szIndulged[] = "Concerns greatest margaret him absolute entrance nay.  Door neat week do find past he.Be no surprise he honoured indulged.";
	char									szSeparate[] = "To they four in love.  Settling you has separate supplied bed.  Concluded resembled suspected his resources curiosity joy.";
	char									sz[200];
	int										iLenMoreover;
	int										iLenIndulged;
	int										iLenSeparate;
	OIndex									oiMoreover;
	OIndex									oiIndulged;
	OIndex									oiSeparate;
	CIndexedDataDescriptor					cDescriptor;
	unsigned int							uiSize;

	cHelper.Init("Output" _FS_ "Test1", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);

	AssertTrue(cDurableController.Begin());
	iLenMoreover = strlen(szMoreover) + 1;
	iLenIndulged = strlen(szIndulged) + 1;
	iLenSeparate = strlen(szSeparate) + 1;
	oiMoreover = 45;
	oiIndulged = 346;
	oiSeparate = 12;
	AssertInt(0, cCallback.NumCached());

	AssertTrue(cCallback.Add(oiMoreover, szMoreover, iLenMoreover, 0));
	AssertTrue(cCallback.TestGetDescriptor(oiMoreover, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertTrue(cCallback.Get(oiMoreover, &uiSize, sz, 200));
	AssertInt(iLenMoreover, uiSize);
	AssertString(szMoreover, sz);
	AssertInt(1, cCallback.NumCached());
	AssertInt(0, cCallback.NumEvicted());

	AssertTrue(cCallback.Add(oiIndulged, szIndulged, iLenIndulged, 0));
	AssertTrue(cCallback.TestGetDescriptor(oiIndulged, NULL));
	AssertInt(2, cCallback.NumCached());
	AssertInt(0, cCallback.NumEvicted());

	AssertTrue(cCallback.Add(oiSeparate, szSeparate, iLenSeparate, 0));
	AssertTrue(cCallback.TestGetDescriptor(oiSeparate, NULL));
	AssertInt(1, cCallback.NumCached());
	AssertInt(2, cCallback.NumEvicted());  //Two were evicted because eviction wrapped back to the start of th cache
	                                       //and the first element size szMoreover is smaller than szSeparate size
										   //which means that the second element szIndulged needed to be evicted too
										   //to ensure there was enough contiguous space in the cache.

	AssertTrue(cCallback.TestGetDescriptor(oiMoreover, NULL));
	AssertTrue(cCallback.TestGetDescriptor(oiIndulged, NULL));
	AssertTrue(cCallback.TestGetDescriptor(oiSeparate, NULL));
	AssertInt(0, cCallback.TestGetCachedObjectSize(oiMoreover));
	AssertInt(0, cCallback.TestGetCachedObjectSize(oiIndulged));
	AssertInt(iLenSeparate + sizeof(SIndexedCacheDescriptor), cCallback.TestGetCachedObjectSize(oiSeparate));
	cCallback.ClearEvicted();

	AssertTrue(cCallback.Flush(TRUE));

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());

	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertInt(3, (int)cCallback.NumElements());

	AssertTrue(cDurableController.Begin());

	XXX //You didn't clear the CACHE_DESCRIPTOR_FLAG_DIRTY on SIndexedCacheDescriptor.iFlags when you wrote them above.
	AssertTrue(cCallback.TestGetDescriptor(oiMoreover, &cDescriptor));
	AssertFalse(cDescriptor.IsCached());
	AssertTrue(cDescriptor.HasFile());
	AssertInt(0, cCallback.TestGetCachedObjectSize(oiMoreover));
	AssertTrue(cCallback.TestGetDescriptor(oiIndulged, &cDescriptor));
	AssertFalse(cDescriptor.IsCached());
	AssertTrue(cDescriptor.HasFile());
	AssertInt(0, cCallback.TestGetCachedObjectSize(oiIndulged));
	AssertTrue(cCallback.TestGetDescriptor(oiSeparate, &cDescriptor));
	AssertFalse(cDescriptor.IsCached());
	AssertTrue(cDescriptor.HasFile());
	AssertInt(0, cCallback.TestGetCachedObjectSize(oiSeparate));

	AssertInt(0, cCallback.NumCached());
	AssertInt(0, cCallback.NumEvicted());

	AssertTrue(cCallback.Get(oiIndulged, &uiSize, sz, 200));
	AssertInt(iLenIndulged, uiSize);
	AssertString(szIndulged, sz);
	AssertInt(1, cCallback.NumCached());
	AssertInt(0, cCallback.NumEvicted());

	AssertTrue(cCallback.Get(oiSeparate, &uiSize, sz, 200));
	AssertInt(iLenSeparate, uiSize);
	AssertString(szSeparate, sz);
	AssertInt(2, cCallback.NumCached());
	AssertInt(0, cCallback.NumEvicted());

	AssertTrue(cCallback.Get(oiMoreover, &uiSize, sz, 200));
	AssertInt(iLenMoreover, uiSize);
	AssertString(szMoreover, sz);
	AssertInt(2, cCallback.NumCached());
	AssertInt(1, cCallback.NumEvicted());

	AssertTrue(cDurableController.End());

	AssertTrue(cCallback.Kill());

	cDurableController.Kill();
	cHelper.Kill(TRUE);
}


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
	TestIndexedFilesEvictingFlush(TRUE);
	TestIndexedFilesEvictingEviction(FALSE);
	TestIndexedFilesEvictingEviction(TRUE);

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

