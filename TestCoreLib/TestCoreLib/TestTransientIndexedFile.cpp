#include "TestTransientIndexedFile.h"
#include "TestLib/Assert.h"
#include "CoreLib/TransientIndexedFile.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "CoreLib/TypeConverter.h"


#define AssertCacheConsistency(t)	EmbreakFailure(PrivateAssertCacheConsistency(t, __LINE__, __FILE__))


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL PrivateAssertCacheConsistency(CTransientIndexedFile* pcTransientIndexedFile, int iLine, char* szFile)
{
	SOIndexIndexCacheDescriptor*	psCache;
	SOIndexIndexCacheDescriptor*	psInitial;
	BOOL							bResult;
	int								iIndex;
	CChars							szExpected;
	CChars							szActual;

	psCache = (SOIndexIndexCacheDescriptor*)pcTransientIndexedFile->mcCache.GetFirst();
	psInitial = psCache;
	if (psInitial)
	{
		for (;;)
		{
			bResult = pcTransientIndexedFile->mcPointers.FindInSorted((STransientIndexedPointer*)&psCache->sIndex.oi, CompareOIndexToTransientIndexedPointer, &iIndex);
			if (psCache->sIndex.iIndex != iIndex)
			{
				szExpected.Init();
				szExpected.Append(iIndex);
				szActual.Init();
				szActual.Append(iIndex);
				Fail(szExpected.Text(), szActual.Text(), iLine, szFile);
				szExpected.Kill();
				szActual.Kill();
				return FALSE;
			}
			else
			{
				Pass();
			}

			psCache = (SOIndexIndexCacheDescriptor*)pcTransientIndexedFile->mcCache.GetNext(psCache);
			if (psCache == psInitial)
			{
				break;
			}
		}
	}
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTransientIndexedFilePointerOrdering(void)
{
	FastFunctionsInit();
	TypeConverterInit();

	CFileUtil				cFileUtil;
	CTransientIndexedFile	cTransientIndexedFile;
	BOOL					bResult;
	char					szDelete[] = "Delete";
	char					szFreeStateApples[] = "Free State Apples";
	char					szAtari[] = "Atari";
	char					szHomeWorld[] = "Home World";
	char					szTypek[] = "Typek";
	char					szMoreBloodyWords[] = "More Bloody Words";
	char					szTest[18];

	cFileUtil.RemoveDir("Transient1");

	cTransientIndexedFile.Init("Transient1", 90);

	bResult = cTransientIndexedFile.Add(0LL, szDelete, 7);
	AssertBool(TRUE, bResult);
	AssertCacheConsistency(&cTransientIndexedFile);
	bResult = cTransientIndexedFile.Add(7LL, szFreeStateApples, 18);
	AssertBool(TRUE, bResult);
	AssertCacheConsistency(&cTransientIndexedFile);

	AssertInt(0, cTransientIndexedFile.mcFiles.NumElements());
	bResult = cTransientIndexedFile.Get(0LL, szTest);
	AssertBool(TRUE, bResult);
	AssertString(szDelete, szTest);
	AssertCacheConsistency(&cTransientIndexedFile);
	bResult = cTransientIndexedFile.Get(7LL, szTest);
	AssertString(szFreeStateApples, szTest);
	AssertCacheConsistency(&cTransientIndexedFile);

	bResult = cTransientIndexedFile.Add(5LL, szAtari, 6);
	AssertCacheConsistency(&cTransientIndexedFile);

	AssertInt(1, cTransientIndexedFile.mcFiles.NumElements());
	bResult = cTransientIndexedFile.Get(5LL, szTest);
	AssertString(szAtari, szTest);
	AssertInt(3, cTransientIndexedFile.mcPointers.NumElements());
	AssertCacheConsistency(&cTransientIndexedFile);

	bResult = cTransientIndexedFile.Add(3LL, szHomeWorld, 11);
	AssertBool(TRUE, bResult);
	AssertCacheConsistency(&cTransientIndexedFile);
	bResult = cTransientIndexedFile.Add(6LL, szTypek, 6);
	AssertBool(TRUE, bResult);
	AssertCacheConsistency(&cTransientIndexedFile);
	bResult = cTransientIndexedFile.Add(1LL, szMoreBloodyWords, 18);
	AssertBool(TRUE, bResult);
	AssertCacheConsistency(&cTransientIndexedFile);

	AssertInt(6, cTransientIndexedFile.mcPointers.NumElements());

	bResult = cTransientIndexedFile.TestOrder();
	AssertBool(TRUE, bResult);

	bResult = cTransientIndexedFile.Get(0LL, szTest);
	AssertBool(TRUE, bResult);
	AssertString(szDelete, szTest);
	AssertCacheConsistency(&cTransientIndexedFile);
	bResult = cTransientIndexedFile.Get(1LL, szTest);
	AssertBool(TRUE, bResult);
	AssertString(szMoreBloodyWords, szTest);
	AssertCacheConsistency(&cTransientIndexedFile);
	memset(szTest, 0, 18);
	bResult = cTransientIndexedFile.Get(3LL, szTest);
	AssertBool(TRUE, bResult);
	AssertString(szHomeWorld, szTest);
	AssertCacheConsistency(&cTransientIndexedFile);
	bResult = cTransientIndexedFile.Get(5LL, szTest);
	AssertString(szAtari, szTest);
	AssertCacheConsistency(&cTransientIndexedFile);
	bResult = cTransientIndexedFile.Get(6LL, szTest);
	AssertString(szTypek, szTest);
	AssertCacheConsistency(&cTransientIndexedFile);
	bResult = cTransientIndexedFile.Get(7LL, szTest);
	AssertString(szFreeStateApples, szTest);
	AssertCacheConsistency(&cTransientIndexedFile);

	cTransientIndexedFile.Kill();
	bResult = cFileUtil.Exists("Transient1");
	AssertBool(FALSE, bResult);

	if (bResult)
	{
		cFileUtil.RemoveDir("Transient1");
	}

	FastFunctionsKill();
	TypeConverterKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTransientIndexedFile(void)
{
	BeginTests();

	TestTransientIndexedFilePointerOrdering();

	TestStatistics();
}

