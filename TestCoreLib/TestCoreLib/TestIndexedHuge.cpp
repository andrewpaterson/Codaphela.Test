#include "BaseLib/FileUtil.h"
#include "CoreLib/IndexedHuge.h"
#include "TestLib/Assert.h"
#include "TestIndexedHuge.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedHugeStuff(void)
{
	CIndexedHuge		cHuge;
	CDurableFile		cDurableFile;  //This is where indices that don't fit in memory go (not the objects that they point too).
	CFileUtil			cFileUtil;
	CChars				szWrite;
	CChars				szRewrite;
	CIndexDescriptor	cIndex1;
	CIndexDescriptor	cTest;
	int					i;
	int					j;
	BOOL				bResult;

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

	AssertLongLongInt(0 * sizeof(CIndexDescriptor), cDurableFile.Size());
	cHuge.UpdateFile();
	AssertLongLongInt(3 * sizeof(CIndexDescriptor), cDurableFile.Size());

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

	AssertLongLongInt(5 * sizeof(CIndexDescriptor), cDurableFile.Size());
	cHuge.Get(&cTest, 12LL);
	AssertInt(12, cTest.GetDataSize());

	cIndex1.Init(13LL, 13);
	cHuge.Set(&cIndex1);

	AssertLongLongInt(5 * sizeof(CIndexDescriptor), cDurableFile.Size());
	cHuge.Get(&cTest, 13LL);
	AssertInt(13, cTest.GetDataSize());
	cHuge.Get(&cTest, 12LL);
	AssertInt(12, cTest.GetDataSize());

	AssertLongLongInt(5 * sizeof(CIndexDescriptor), cDurableFile.Size());
	cHuge.Get(&cTest, 13LL);

	cHuge.Get(&cTest, 4LL);
	AssertInt(4, cTest.GetDataSize());

	AssertLongLongInt(14 * sizeof(CIndexDescriptor), cDurableFile.Size());

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

	for (i = 0; i < 48; i++)
	{
		cIndex1.Init(i, i+100);
		cHuge.Set(&cIndex1);

		for (j = 0; j < 48; j++)
		{
			bResult = cHuge.Get(&cTest, j);
			if (j <= i)
			{
				AssertBool(TRUE, bResult);
				AssertInt(j+100, cTest.GetDataSize());
			}
			else
			{
				AssertBool(FALSE, bResult);
			}
		}
	}

	cHuge.UpdateFile();
	AssertLongLongInt(48 * sizeof(CIndexDescriptor), cDurableFile.Size());

	cDurableFile.Close();
	cDurableFile.Kill();

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

	TestStatistics();
	FastFunctionsKill();
}

