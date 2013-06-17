#include "BaseLib/FileUtil.h"
#include "CoreLib/IndexedHuge.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedHugeStuff(void)
{
	CIndexedHuge			cHuge;
	CDurableFile			cDurableFile;  //This is where indices that don't fit in memory go (not the objects that they point too).
	CFileUtil				cFileUtil;
	CChars					szWrite;
	CChars					szRewrite;
	CIndexedDataDescriptor	cIndex1;
	CIndexedDataDescriptor	cTest;
	int						i;
	int						j;
	BOOL					bResult;

	cFileUtil.RemoveDir("IndexedHuge");
	cFileUtil.MakeDir("IndexedHuge");

	szWrite.Init("IndexedHuge");
	szWrite.Append(FILE_SEPARATOR[0]);
	szWrite.Append("Indices.DAT");
	szRewrite.Init("IndexedHuge");
	szRewrite.Append(FILE_SEPARATOR[0]);
	szRewrite.Append("_Indices.DAT");

	cDurableFile.Init(FALSE, szWrite.Text(), szRewrite.Text());
	cDurableFile.Open();

	szWrite.Kill();
	szRewrite.Kill();

	cHuge.Init(&cDurableFile, FALSE, NULL, 12, 4, 1, 3);
	AssertInt(12, cHuge.NumPossibleInMemoryIndexDescriptors());
	AssertInt(528, cHuge.GetThirdLevelCacheByteSize());
	AssertInt(72, cHuge.GetSecondLevelCacheByteSize());

	cIndex1.Init(1LL, 1);
	cHuge.Set(&cIndex1);

	cHuge.Get(&cTest, 1LL);
	AssertInt(1, cTest.GetDataSize());

	cIndex1.Init(2LL, 2);
	cHuge.Set(&cIndex1);

	cHuge.Get(&cTest, 2LL);
	AssertInt(2, cTest.GetDataSize());

	AssertLongLongInt(0 * sizeof(CIndexedDataDescriptor), cDurableFile.Size());
	cHuge.UpdateFile();
	AssertLongLongInt(3 * sizeof(CIndexedDataDescriptor), cDurableFile.Size());

	cIndex1.Init(4LL, 4);
	cHuge.Set(&cIndex1);

	cHuge.Get(&cTest, 4LL);
	AssertInt(4, cTest.GetDataSize());
	cHuge.Get(&cTest, 2LL);
	AssertInt(2, cTest.GetDataSize());
	cHuge.Get(&cTest, 1LL);
	AssertInt(1, cTest.GetDataSize());

	cIndex1.Init(12LL, 12);
	cHuge.Set(&cIndex1);

	AssertLongLongInt(5 * sizeof(CIndexedDataDescriptor), cDurableFile.Size());
	cHuge.Get(&cTest, 12LL);
	AssertInt(12, cTest.GetDataSize());

	cIndex1.Init(13LL, 13);
	cHuge.Set(&cIndex1);

	AssertLongLongInt(5 * sizeof(CIndexedDataDescriptor), cDurableFile.Size());
	cHuge.Get(&cTest, 13LL);
	AssertInt(13, cTest.GetDataSize());
	cHuge.Get(&cTest, 12LL);
	AssertInt(12, cTest.GetDataSize());

	AssertLongLongInt(5 * sizeof(CIndexedDataDescriptor), cDurableFile.Size());
	cHuge.Get(&cTest, 13LL);

	cHuge.Get(&cTest, 4LL);
	AssertInt(4, cTest.GetDataSize());

	AssertLongLongInt(14 * sizeof(CIndexedDataDescriptor), cDurableFile.Size());

	cHuge.Get(&cTest, 2LL);
	AssertInt(2, cTest.GetDataSize());
	cHuge.Get(&cTest, 1LL);
	AssertInt(1, cTest.GetDataSize());

	cHuge.Kill();
	cDurableFile.Close();

	cDurableFile.Open();

	cHuge.Init(&cDurableFile, FALSE, NULL, 12, 4, 2, 2);
	AssertInt(8, cHuge.NumPossibleInMemoryIndexDescriptors());
	AssertInt(352, cHuge.GetThirdLevelCacheByteSize());
	AssertInt(144, cHuge.GetSecondLevelCacheByteSize());

	BOOL bJLessThanI = TRUE;
	BOOL bJGreaterThanI = FALSE;
	BOOL bJEqualsDataSize = TRUE;

	for (i = 0; i < 48; i++)
	{
		cIndex1.Init(i, i+100);
		cHuge.Set(&cIndex1);

		for (j = 0; j < 48; j++)
		{
			bResult = cHuge.Get(&cTest, j);
			if (j <= i)
			{
				bJLessThanI &= bResult;
				if (j+100 != cTest.GetDataSize())
				{
					bJEqualsDataSize = FALSE;
				}
			}
			else
			{
				bJGreaterThanI |= bResult;
			}
		}
	}

	AssertTrue(bJLessThanI);
	AssertFalse(bJGreaterThanI);
	AssertTrue(bJEqualsDataSize);

	cHuge.UpdateFile();
	AssertLongLongInt(48 * sizeof(CIndexedDataDescriptor), cDurableFile.Size());

	cDurableFile.Close();
	cDurableFile.Kill();

	cFileUtil.RemoveDir("IndexedHuge");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedHugeSmallCacheFailure(void)
{
	CIndexedHuge		cHuge;
	CDurableFile		cDurableFile;
	CFileUtil			cFileUtil;
	CChars				szWrite;
	CChars				szRewrite;
	CChars				szResult;

	cFileUtil.RemoveDir("IndexedHuge");
	cFileUtil.MakeDir("IndexedHuge");
	szWrite.InitList("IndexedHuge", FILE_SEPARATOR, "Indices.DAT", NULL);
	szRewrite.InitList("IndexedHuge", FILE_SEPARATOR, "_Indices.DAT", NULL);

	cDurableFile.Init(FALSE, szWrite.Text(), szRewrite.Text());
	cDurableFile.Open();

	cHuge.Init(&cDurableFile, FALSE, NULL, 6, 3, 4, 2);
	AssertInt(6, cHuge.NumPossibleInMemoryIndexDescriptors());
	AssertInt(192, cHuge.GetSecondLevelCacheByteSize()); // 4 * (SIndexedSecondLevelSearch + (SIndexedThirdLevelSearch * 6));
	AssertInt(272, cHuge.GetThirdLevelCacheByteSize()); // 2 * (SIndexedThirdLevelSearch + (CIndexedDataDescriptor * 3))

	cHuge.Set(3LL, 68);
	cHuge.Set(4LL, 80);
	cHuge.Set(5LL, 81);

	cHuge.Set(6LL, 82);
	cHuge.Set(7LL, 30);
	cHuge.Set(8LL, 29);

	AssertInt(0, cHuge.GetThirdLevelEvictions());

	szResult.Init();
	cHuge.DumpThirdLevelCache(&szResult);
	AssertString("\
Third Level Cache (272 bytes)\n\
--------------------\n\
Chunk Width: 3\n\
Chunk Count: 2\n\
Chunk Size: 136\n\
Valid: 1\n\
Parent: 0 - 5 (3)\n\
    OI: 3\n\
    OI: 4\n\
    OI: 5\n\
\n\
Valid: 1\n\
Parent: 6 - 11 (0)\n\
    OI: 6\n\
    OI: 7\n\
    OI: 8\n\
\n"
	, szResult.Text());
	szResult.Kill();

	cHuge.Set(9LL, 28);
	AssertInt(3, cHuge.GetThirdLevelEvictions());
	cHuge.Set(10LL, 50);
	cHuge.Set(11LL, 51);

		szResult.Init();
	cHuge.DumpThirdLevelCache(&szResult);
	AssertString("\
Third Level Cache (272 bytes)\n\
--------------------\n\
Chunk Width: 3\n\
Chunk Count: 2\n\
Chunk Size: 136\n\
Valid: 1\n\
Parent: 6 - 11 (3)\n\
    OI: 9\n\
    OI: 10\n\
    OI: 11\n\
\n\
Valid: 1\n\
Parent: 6 - 11 (0)\n\
    OI: 6\n\
    OI: 7\n\
    OI: 8\n\
\n"
	, szResult.Text());
	szResult.Kill();

	cHuge.Set(12LL, 52);
	cHuge.Set(13LL, 90);
	cHuge.Set(14LL, 91);

	cHuge.Save();
	cHuge.Kill();
	cDurableFile.Close();
	cDurableFile.Kill();

	CIndexedDataDescriptor	cIndex;

	cDurableFile.Init(FALSE, szWrite.Text(), szRewrite.Text());
	cDurableFile.Open();

	cHuge.Init(&cDurableFile, FALSE, NULL, 4, 2, 4, 2);
	cHuge.Load();

	AssertFalse(cHuge.Get(&cIndex, 0LL));
	AssertFalse(cHuge.Get(&cIndex, 1LL));
	AssertFalse(cHuge.Get(&cIndex, 2LL));

	AssertTrue(cHuge.Get(&cIndex, 3LL));
	AssertInt(68, cIndex.GetDataSize());
	AssertNull(cIndex.GetCache());
	AssertTrue(cHuge.Get(&cIndex, 4LL));
	AssertInt(80, cIndex.GetDataSize());
	AssertNull(cIndex.GetCache());
	AssertTrue(cHuge.Get(&cIndex, 5LL));
	AssertInt(81, cIndex.GetDataSize());
	AssertNull(cIndex.GetCache());

	AssertTrue(cHuge.Get(&cIndex, 6LL));
	AssertInt(82, cIndex.GetDataSize());
	AssertNull(cIndex.GetCache());
	AssertTrue(cHuge.Get(&cIndex, 7LL));
	AssertInt(30, cIndex.GetDataSize());
	AssertNull(cIndex.GetCache());
	AssertTrue(cHuge.Get(&cIndex, 8LL));
	AssertInt(29, cIndex.GetDataSize());
	AssertNull(cIndex.GetCache());

	AssertTrue(cHuge.Get(&cIndex, 9LL));
	AssertInt(28, cIndex.GetDataSize());
	AssertNull(cIndex.GetCache());
	AssertTrue(cHuge.Get(&cIndex, 10LL));
	AssertInt(50, cIndex.GetDataSize());
	AssertNull(cIndex.GetCache());
	AssertTrue(cHuge.Get(&cIndex, 11LL));
	AssertInt(51, cIndex.GetDataSize());
	AssertNull(cIndex.GetCache());

	AssertTrue(cHuge.Get(&cIndex, 12LL));
	AssertInt(52, cIndex.GetDataSize());
	AssertNull(cIndex.GetCache());
	AssertTrue(cHuge.Get(&cIndex, 13LL));
	AssertInt(90, cIndex.GetDataSize());
	AssertNull(cIndex.GetCache());
	AssertTrue(cHuge.Get(&cIndex, 14LL));
	AssertInt(91, cIndex.GetDataSize());
	AssertNull(cIndex.GetCache());

	AssertFalse(cHuge.Get(&cIndex, 15LL));
	AssertFalse(cHuge.Get(&cIndex, 16LL));
	AssertFalse(cHuge.Get(&cIndex, 17LL));

	cHuge.Save();
	cHuge.Kill();
	cDurableFile.Close();
	cDurableFile.Kill();

	szWrite.Kill();
	szRewrite.Kill();
	cFileUtil.RemoveDir("IndexedHuge");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedHuge(void)
{
	FastFunctionsInit();
	BeginTests();

	TestIndexedHugeStuff();
	TestIndexedHugeSmallCacheFailure();

	TestStatistics();
	FastFunctionsKill();
}

