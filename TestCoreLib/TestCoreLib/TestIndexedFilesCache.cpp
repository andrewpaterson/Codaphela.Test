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
void TestIndexedFilesEvictingFlush(BOOL bWriteThrough, BOOL bClearCache)
{
	CDurableFileController					cDurableController;
	CIndexTreeHelper						cHelper;
	CIndexedFilesEvictedDescriptorList		cCallback;
	char									szMoreover[] = "Although moreover mistaken kindness me feelings do be marianne.  Cordial village and settled she ability law herself.";
	char									szMudpuppy[] = "Although mudpuppy mistaken kindness me feelings do be marianne.  Cordial village and settled she ability law herself.";
	char									szForsaken[] = "Although mudpuppy forsaken kindness me feelings do be marianne.  Cordial village and settled she ability law herself.";
	char									sz[200];
	int										iLenMoreover;
	OIndex									oi;
	CIndexedDataDescriptor					cDescriptor;
	unsigned int							uiSize;

	cHelper.Init("Output" _FS_ "TestEvicting1", "primary", "backup", TRUE);
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
	AssertTrue(cCallback.Flush(bClearCache));
	AssertInt(bClearCache ? 0 : 1, cCallback.NumCached());

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


	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 1024, bWriteThrough);
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cDurableController.Begin());

	AssertTrue(cCallback.Set(oi, szMudpuppy, 0));
	AssertTrue(cCallback.TestGetDescriptor(oi, &cDescriptor));
	AssertTrue(cDescriptor.IsCached());
	AssertInt(1, cCallback.NumCached());
	AssertTrue(cCallback.Get(oi, &uiSize, sz, 200));
	AssertString(szMudpuppy, sz);
	AssertTrue(cCallback.TestGetDescriptor(oi, &cDescriptor));
	AssertTrue(cDescriptor.IsCached());
	AssertTrue(cDescriptor.HasFile());
 	AssertInt(1, cCallback.NumCached());
	AssertTrue(cCallback.Flush(bClearCache));
	AssertInt(bClearCache ? 0 : 1, cCallback.NumCached());
	AssertTrue(cCallback.Get(oi, &uiSize, sz, 200));
	AssertString(szMudpuppy, sz);

	AssertTrue(cDurableController.End());

	AssertTrue(cCallback.Kill());


	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 1024, bWriteThrough);
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cDurableController.Begin());

	AssertTrue(cCallback.Get(oi, &uiSize, sz, 200));
	AssertTrue(cCallback.TestGetDescriptor(oi, &cDescriptor));
	AssertTrue(cDescriptor.IsCached());
	AssertTrue(cDescriptor.HasFile());
	AssertInt(1, cCallback.NumCached());
	AssertTrue(cCallback.Set(oi, szForsaken, 0));
	AssertInt(1, cCallback.NumCached());
	AssertTrue(cCallback.Flush(bClearCache));
	AssertInt(bClearCache ? 0 : 1, cCallback.NumCached());
	AssertTrue(cCallback.Get(oi, &uiSize, sz, 200));
	AssertString(szForsaken, sz);

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

	cHelper.Init("Output" _FS_ "TestEvicting2", "primary", "backup", TRUE);
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
	AssertInt(2, cCallback.NumEvicted());  //Two were evicted because eviction wrapped back to the start of the cache
	                                       //and the first element size szMoreover is smaller than szSeparate size
										   //which means that the second element szIndulged needed to be evicted too
										   //to ensure there was enough contiguous space in the cache.
	AssertString(szMoreover, (char*)cCallback.GetEvicted(0));
	AssertString(szIndulged, (char*)cCallback.GetEvicted(1));

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
	AssertTrue(cCallback.Get(oiIndulged, &uiSize, sz, 200));
	AssertFalse(cCallback.IsDirty(oiMoreover));
	AssertFalse(cCallback.IsDirty(oiSeparate));
	AssertFalse(cCallback.IsDirty(oiMoreover));

	AssertTrue(cCallback.Get(oiSeparate, &uiSize, sz, 200));
	AssertInt(iLenSeparate, uiSize);
	AssertString(szSeparate, sz);
	AssertInt(2, cCallback.NumCached());
	AssertInt(0, cCallback.NumEvicted());
	AssertFalse(cCallback.IsDirty(oiMoreover));
	AssertFalse(cCallback.IsDirty(oiSeparate));
	AssertFalse(cCallback.IsDirty(oiMoreover));
	cCallback.ClearEvicted();

	AssertTrue(cCallback.Get(oiMoreover, &uiSize, sz, 200));
	AssertInt(iLenMoreover, uiSize);
	AssertString(szMoreover, sz);
	AssertInt(2, cCallback.NumCached());
	AssertInt(1, cCallback.NumEvicted());
	AssertFalse(cCallback.IsDirty(oiMoreover));
	AssertFalse(cCallback.IsDirty(oiSeparate));
	AssertFalse(cCallback.IsDirty(oiMoreover));
	AssertString(szIndulged, (char*)cCallback.GetEvicted(0));
	cCallback.ClearEvicted();

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertTrue(cDurableController.Begin());
	AssertInt(3, (int)cCallback.NumElements());

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
	AssertTrue(cCallback.Get(oiIndulged, &uiSize, sz, 200));
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
	AssertFalse(cCallback.IsDirty(oiMoreover));
	AssertFalse(cCallback.IsDirty(oiSeparate));
	AssertFalse(cCallback.IsDirty(oiIndulged));
	AssertTrue(cCallback.TestGetDescriptor(oiMoreover, &cDescriptor));
	AssertNotNull(cDescriptor.GetCache());
	AssertString(szMoreover, (char*)cDescriptor.GetCache());
	AssertTrue(cCallback.TestGetDescriptor(oiSeparate, &cDescriptor));
	AssertNotNull(cDescriptor.GetCache());
	AssertString(szSeparate, (char*)cDescriptor.GetCache());
	AssertTrue(cCallback.TestGetDescriptor(oiIndulged, &cDescriptor));
	AssertNull(cDescriptor.GetCache());
	AssertString(szIndulged, (char*)cCallback.GetEvicted(0));
	cCallback.ClearEvicted();

	AssertTrue(cCallback.Get(oiIndulged, &uiSize, sz, 200));
	AssertInt(iLenIndulged, uiSize);
	AssertString(szIndulged, sz);
	AssertInt(2, cCallback.NumCached());
	AssertInt(1, cCallback.NumEvicted());
	AssertString(szSeparate, (char*)cCallback.GetEvicted(0));
	cCallback.ClearEvicted();

	AssertTrue(cCallback.Get(oiIndulged, &uiSize, sz, 200));
	AssertInt(2, cCallback.NumCached());
	AssertInt(0, cCallback.NumEvicted());

	AssertTrue(cCallback.Get(oiSeparate, &uiSize, sz, 200));
	AssertInt(iLenSeparate, uiSize);
	AssertString(szSeparate, sz);
	AssertInt(1, cCallback.NumCached());
	AssertInt(2, cCallback.NumEvicted());
	AssertString(szMoreover, (char*)cCallback.GetEvicted(0));
	AssertString(szIndulged, (char*)cCallback.GetEvicted(1));
	cCallback.ClearEvicted();

	AssertTrue(cCallback.Get(oiSeparate, &uiSize, sz, 200));
	AssertInt(1, cCallback.NumCached());
	AssertInt(0, cCallback.NumEvicted());

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesEvictingSetDataNoCacheNoFile(void)
{
	CDurableFileController					cDurableController;
	CIndexTreeHelper						cHelper;
	CIndexedFilesEvictedDescriptorList		cCallback;
	char									sz[200];
	char									sz6[] = "6Six6\0";
	BOOL									bWriteThrough;

	bWriteThrough = FALSE;
	cHelper.Init("Output" _FS_ "TestEvicting3", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);

	AssertTrue(cDurableController.Begin());
	AssertInt(0, cCallback.NumCached());

	AssertTrue(cCallback.SetOrAdd(0LL, sz6, 6, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertInt(0, cCallback.NumFiles());
	AssertTrue(cCallback.Flush(TRUE));

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertTrue(cDurableController.Begin());
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cCallback.Get(0LL, sz));
	AssertString(sz6, sz);

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesEvictingSetDataCacheSameSizeNoFile(void)
{
	CDurableFileController					cDurableController;
	CIndexTreeHelper						cHelper;
	CIndexedFilesEvictedDescriptorList		cCallback;
	char									sz[200];
	char									sz6a[] = "6Six6\0";
	char									sz6b[] = "xisix\0";
	BOOL									bWriteThrough;

	bWriteThrough = FALSE;
	cHelper.Init("Output" _FS_ "TestEvicting4", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);

	AssertTrue(cDurableController.Begin());
	AssertInt(0, cCallback.NumCached());

	AssertTrue(cCallback.SetOrAdd(0LL, sz6a, 6, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertTrue(cCallback.SetOrAdd(0LL, sz6b, 6, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertInt(0, cCallback.NumFiles());
	AssertTrue(cCallback.Flush(TRUE));

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertTrue(cDurableController.Begin());
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cCallback.Get(0LL, sz));
	AssertString(sz6b, sz);

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesEvictingSetDataCacheDiffSizeNoFile(void)
{
	CDurableFileController					cDurableController;
	CIndexTreeHelper						cHelper;
	CIndexedFilesEvictedDescriptorList		cCallback;
	char									sz[200];
	char									sz6[] = "6Six6\0";
	char									sz5[] = "5ive\0";
	BOOL									bWriteThrough;

	bWriteThrough = FALSE;
	cHelper.Init("Output" _FS_ "TestEvicting5", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);

	AssertTrue(cDurableController.Begin());
	AssertInt(0, cCallback.NumCached());

	AssertTrue(cCallback.SetOrAdd(0LL, sz6, 6, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertTrue(cCallback.SetOrAdd(0LL, sz5, 5, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertInt(0, cCallback.NumFiles());
	AssertTrue(cCallback.Flush(TRUE));

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertTrue(cDurableController.Begin());
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cCallback.Get(0LL, sz));
	AssertString(sz5, sz);

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesEvictingSetDataNoCacheFileSameSize(void)
{
	CDurableFileController					cDurableController;
	CIndexTreeHelper						cHelper;
	CIndexedFilesEvictedDescriptorList		cCallback;
	char									sz[200];
	char									sz6a[] = "6Six6\0";
	char									sz6b[] = "xisix\0";
	BOOL									bWriteThrough;

	bWriteThrough = FALSE;
	cHelper.Init("Output" _FS_ "TestEvicting6", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);

	AssertTrue(cDurableController.Begin());
	AssertInt(0, cCallback.NumCached());

	AssertTrue(cCallback.SetOrAdd(0LL, sz6a, 6, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertInt(0, cCallback.NumFiles());
	AssertTrue(cCallback.Flush(TRUE));

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertTrue(cDurableController.Begin());
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cCallback.SetOrAdd(0LL, sz6b, 6, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertTrue(cCallback.Flush(TRUE));
	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertTrue(cDurableController.Begin());
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cCallback.Get(0LL, sz));
	AssertString(sz6b, sz);

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesEvictingSetDataNoCacheFileDiffSize(void)
{
	CDurableFileController					cDurableController;
	CIndexTreeHelper						cHelper;
	CIndexedFilesEvictedDescriptorList		cCallback;
	char									sz[200];
	char									sz6[] = "6Six6\0";
	char									sz5[] = "5ive\0";
	BOOL									bWriteThrough;

	bWriteThrough = FALSE;
	cHelper.Init("Output" _FS_ "TestEvicting7", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);

	AssertTrue(cDurableController.Begin());
	AssertInt(0, cCallback.NumCached());

	AssertTrue(cCallback.SetOrAdd(0LL, sz6, 6, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertInt(0, cCallback.NumFiles());
	AssertTrue(cCallback.Flush(TRUE));

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertTrue(cDurableController.Begin());
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cCallback.SetOrAdd(0LL, sz5, 5, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertTrue(cCallback.Flush(TRUE));
	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertTrue(cDurableController.Begin());
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cCallback.Get(0LL, sz));
	AssertString(sz5, sz);

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();
	cHelper.Kill(TRUE);
}

  
//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesEvictingSetDataCacheSameSizeFile(void)
{
	CDurableFileController					cDurableController;
	CIndexTreeHelper						cHelper;
	CIndexedFilesEvictedDescriptorList		cCallback;
	char									sz[200];
	char									sz6a[] = "6Six6\0";
	char									sz6b[] = "xisix\0";
	char									sz5[] = "5ive\0";
	BOOL									bWriteThrough;

	bWriteThrough = FALSE;
	cHelper.Init("Output" _FS_ "TestEvicting8", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);

	AssertTrue(cDurableController.Begin());
	AssertInt(0, cCallback.NumCached());

	AssertTrue(cCallback.SetOrAdd(0LL, sz6a, 6, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertInt(0, cCallback.NumFiles());
	AssertTrue(cCallback.Flush(TRUE));

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertTrue(cDurableController.Begin());
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cCallback.SetOrAdd(0LL, sz6b, 6, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertTrue(cCallback.Flush(TRUE));
	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertTrue(cDurableController.Begin());
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cCallback.SetOrAdd(0LL, sz5, 5, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertTrue(cCallback.Flush(TRUE));
	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertTrue(cDurableController.Begin());
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cCallback.Get(0LL, sz));
	AssertString(sz5, sz);

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedFilesEvictingSetDataCacheDiffSizeFile(void)
{
	CDurableFileController					cDurableController;
	CIndexTreeHelper						cHelper;
	CIndexedFilesEvictedDescriptorList		cCallback;
	char									sz[200];
	char									sz6[] = "6Six6\0";
	char									sz5[] = "5ive\0";
	char									sz4[] = "4or\0";
	BOOL									bWriteThrough;

	bWriteThrough = FALSE;
	cHelper.Init("Output" _FS_ "TestEvicting8", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);

	AssertTrue(cDurableController.Begin());
	AssertInt(0, cCallback.NumCached());

	AssertTrue(cCallback.SetOrAdd(0LL, sz6, 6, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertInt(0, cCallback.NumFiles());
	AssertTrue(cCallback.Flush(TRUE));

	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertTrue(cDurableController.Begin());
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cCallback.SetOrAdd(0LL, sz5, 5, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertTrue(cCallback.Flush(TRUE));
	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertTrue(cDurableController.Begin());
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cCallback.SetOrAdd(0LL, sz4, 4, 0));
	AssertTrue(cCallback.TestGetDescriptor(0LL, NULL));
	AssertInt(1, cCallback.NumCached());

	AssertTrue(cCallback.Flush(TRUE));
	AssertTrue(cDurableController.End());
	AssertTrue(cCallback.Kill());
	cDurableController.Kill();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cCallback.Init(&cDurableController, "DAT", "Files.IDX", "_Files.IDX", 320, bWriteThrough);
	AssertTrue(cDurableController.Begin());
	AssertInt(1, (int)cCallback.NumElements());

	AssertTrue(cCallback.Get(0LL, sz));
	AssertString(sz4, sz);

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

	TestIndexedFilesEvictingSetDataNoCacheNoFile();
	TestIndexedFilesEvictingSetDataCacheSameSizeNoFile();
	TestIndexedFilesEvictingSetDataCacheDiffSizeNoFile();
	TestIndexedFilesEvictingSetDataNoCacheFileSameSize();
	TestIndexedFilesEvictingSetDataNoCacheFileDiffSize();
	TestIndexedFilesEvictingSetDataCacheSameSizeFile();
	TestIndexedFilesEvictingSetDataCacheDiffSizeFile();

	TestIndexedFilesEvictingFlush(FALSE, TRUE);
	TestIndexedFilesEvictingFlush(TRUE, TRUE);
	TestIndexedFilesEvictingFlush(FALSE, FALSE);
	TestIndexedFilesEvictingFlush(TRUE, FALSE);
	TestIndexedFilesEvictingEviction(FALSE);
	TestIndexedFilesEvictingEviction(TRUE);

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

