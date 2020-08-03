#include "BaseLib/TypeConverter.h"
#include "BaseLib/DebugOutput.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/IndexTreeMemoryAccess.h"
#include "BaseLib/CharsHelper.h"
#include "CoreLib/LogFile.h"
#include "CoreLib/IndexTreeFileAccess.h"
#include "CoreLib/IndexTreeEvictingAccess.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexTreeEvictionStrategyRandom.h"
#include "CoreLib/IndexTreeFileKeyDiagnosticCountingCallback.h"
#include "TestLib/Words.h"
#include "TestLib/Assert.h"
#include "TestIndexTreeFile.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void Flush(CIndexTreeAccess* pcAccess, int iFlushFrequency, int* piCurrent)
{
	if (iFlushFrequency != -1)
	{
		(*piCurrent)++;

		if (*piCurrent == iFlushFrequency)
		{
			pcAccess->Flush();
			*piCurrent = 0;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeAccessString(CIndexTreeAccess* pcAccess, int iFlushFrequency)
{
	int64					lliData;
	int						iData;
	char*					pszData;
	char					szData[256];
	char*					pszKey;
	int						i;
	CChars*					pszKey2;
	CChars*					pszData2;
	BOOL					bPassed;
	int						iArchaicIndex;
	int						iFlush;
	CIndexTreeIterator*		pcIter;
	BOOL					bHasData;
	CArrayChars				aszKeys;
	CArrayChars				aszExpected;
	CArrayChars				aszIntersection;

	iFlush = 0;
	for (i = 0; i < gaszCommonWords.NumElements(); i++)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		iData = i;
		pcAccess->PutStringInt(pszKey, iData);
		Flush(pcAccess, iFlushFrequency, &iFlush);
	}
	AssertLongLongInt(1000, pcAccess->NumElements());
	Pass();
	AssertTrue(pcAccess->ValidateIndex());
	Pass();

	bPassed = TRUE;
	for (i = 0; i < gaszCommonWords.NumElements(); i++)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		iData = pcAccess->GetStringInt(pszKey);
		if (iData != i)
		{
			bPassed = FALSE;
			break;
		}
		Flush(pcAccess, iFlushFrequency, &iFlush);
	}
	AssertTrue(bPassed);
	Pass();
	AssertTrue(pcAccess->ValidateIndex());
	Pass();

	aszExpected.Init();
	iArchaicIndex = 0;
	for (i = 0; i < gaszCommonWords.NumElements(); i++)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();

		if (i % 2 == 1)
		{
			pcAccess->DeleteString(pszKey);
		}
		else
		{
			pszData2 = gaszArchaicDefinitions.Get(iArchaicIndex);
			pszData = pszData2->Text();

			iArchaicIndex++;
			if (iArchaicIndex >= gaszArchaicDefinitions.NumElements())
			{
				iArchaicIndex = 0;
			}

			pcAccess->PutStringString(pszKey, pszData);
			aszExpected.Add(pszKey);
		}
		Flush(pcAccess, iFlushFrequency, &iFlush);
	}

	aszKeys.Init();
	pcIter = pcAccess->CreateIterator();
	bHasData = pcIter->Iterate();
	while (bHasData)
	{
		pszKey = pcIter->GetKey();
		aszKeys.Add(pszKey);
		bHasData = pcIter->Iterate();
	}

	aszIntersection.Init();
	CCharsHelper::InverseIntersect(&aszIntersection, &aszExpected, &aszKeys);
	if (aszIntersection.NumElements() > 0)
	{
		aszIntersection.Dump();
		pcAccess->Dump();
	}
	aszIntersection.Kill();
	aszKeys.Kill();

	AssertLongLongInt(500, pcAccess->NumElements());
	Pass();
	AssertTrue(pcAccess->ValidateIndex());
	Pass();

	iArchaicIndex = 0;
	bPassed = TRUE;
	for (i = 0; i < gaszCommonWords.NumElements(); i += 2)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();

		pszData2 = gaszArchaicDefinitions.Get(iArchaicIndex);
		pszData = pszData2->Text();

		iArchaicIndex++;
		if (iArchaicIndex >= gaszArchaicDefinitions.NumElements())
		{
			iArchaicIndex = 0;
		}

		pszData = pcAccess->GetStringString(pszKey, szData);
		pszData2 = gaszArchaicDefinitions.Get(iArchaicIndex);

		if (pszData2->Equals(pszData))
		{
			bPassed = FALSE;
			break;
		}
		Flush(pcAccess, iFlushFrequency, &iFlush);
	}
	AssertTrue(bPassed);
	Pass();
	AssertTrue(pcAccess->ValidateIndex());
	Pass();

	for (i = gaszCommonWords.NumElements() - 1; i >= 0; i--)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		lliData = ((int64)1000 - i) * 86509465456456LL;
		pcAccess->PutStringLong(pszKey, lliData);
		Flush(pcAccess, iFlushFrequency, &iFlush);
	}
	AssertLongLongInt(1000, pcAccess->NumElements());
	Pass();
	AssertTrue(pcAccess->ValidateIndex());
	Pass();

	bPassed = TRUE;
	for (i = 0; i < gaszCommonWords.NumElements(); i++)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		lliData = pcAccess->GetStringLong(pszKey);
		if (lliData != ((int64)1000 - i) * 86509465456456LL)
		{
			bPassed = FALSE;
			break;
		}
		Flush(pcAccess, iFlushFrequency, &iFlush);
	}
	AssertTrue(bPassed);
	Pass();
	AssertTrue(pcAccess->ValidateIndex());
	Pass();

	for (i = 0; i < gaszCommonWords.NumElements(); i += 3)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		pcAccess->DeleteString(pszKey);
		Flush(pcAccess, iFlushFrequency, &iFlush);
	}
	AssertLongLongInt(666, pcAccess->NumElements());
	Pass();
	AssertTrue(pcAccess->ValidateIndex());
	Pass();

	for (i = 1; i < gaszCommonWords.NumElements(); i += 3)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		pcAccess->DeleteString(pszKey);
		Flush(pcAccess, iFlushFrequency, &iFlush);
	}
	AssertLongLongInt(333, pcAccess->NumElements());
	Pass();
	AssertTrue(pcAccess->ValidateIndex());
	Pass();

	for (i = 2; i < gaszCommonWords.NumElements(); i += 3)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		pcAccess->PutStringInt(pszKey, i);
		Flush(pcAccess, iFlushFrequency, &iFlush);
	}
	Pass();
	AssertTrue(pcAccess->ValidateIndex());
	Pass();

	bPassed = TRUE;
	for (i = 2; i < gaszCommonWords.NumElements(); i += 3)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		iData = pcAccess->GetStringInt(pszKey);
		if (iData != i)
		{
			bPassed = FALSE;
			break;
		}

		Flush(pcAccess, iFlushFrequency, &iFlush);
	}
	AssertTrue(bPassed);
	Pass();
	AssertTrue(pcAccess->ValidateIndex());
	Pass();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryAccess(EIndexKeyReverse eKeyReverse)
{
	CIndexTreeMemoryAccess	cAccess;
	CIndexTreeMemory		cIndexTree;

	cIndexTree.Init(eKeyReverse);
	cAccess.Init(&cIndexTree);

	TestIndexTreeAccessString(&cAccess, -1);

	cAccess.Kill();
	cIndexTree.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileAccessFlushEvictBug(void)
{
	CIndexTreeFileAccess	cAccess;
	CTestIndexTreeFile		cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cController;
	int						iFlushFrequency;
	BOOL					bResult;

	iFlushFrequency = -1;

	cHelper.Init("Output" _FS_ "IndexTreeFileAccessFlushEvictBug", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutStringLong("clearly", 0x7486498577436958LL));
	AssertTrue(cAccess.PutStringLong("clear", 0x9234794843954732LL));

	bResult = cAccess.Flush();
	AssertTrue(bResult);

	cIndexTree.ValidateParentIndex();
	 
	AssertTrue(cAccess.DeleteString("clear"));
	Pass();

	bResult = cAccess.EvictString("clearly");
	AssertTrue(bResult);
	Pass();

	bResult = cAccess.FlushString("clear");
	AssertTrue(bResult);
	Pass();

	AssertFalse(cAccess.HasString("clear"));
	Pass();
	AssertTrue(cAccess.HasString("clearly"));
	Pass();

	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileAccessRemoveEvictBug(void)
{
	CIndexTreeFileAccess	cAccess;
	CTestIndexTreeFile		cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cController;
	int						iFlushFrequency;

	iFlushFrequency = -1;

	cHelper.Init("Output" _FS_ "TestIndexTreeFileAccessRemoveEvictBug", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);
	
	AssertTrue(cAccess.PutStringInt("any", 0x03));
	AssertTrue(cAccess.PutStringInt("anyone", 0x04));
	AssertTrue(cAccess.PutStringInt("anything", 0x05));

	AssertLongLongInt(3, cAccess.NumElements());
	Pass();
	AssertTrue(cAccess.ValidateIndex());
	Pass();

	AssertInt(0x03, cAccess.GetStringInt("any"));
	AssertInt(0x04, cAccess.GetStringInt("anyone"));
	AssertInt(0x05, cAccess.GetStringInt("anything"));
	Pass();
	AssertTrue(cAccess.ValidateIndex());
	Pass();

	AssertTrue(cAccess.DeleteString("any"));
	AssertTrue(cAccess.DeleteString("anyone"));
	//AssertTrue(cAccess.DeleteString("anything"));
	Pass();

	AssertFalse(cAccess.HasString("any"));
	cAccess.EvictString("anything");
	AssertFalse(cAccess.HasString("any"));
	Pass();
	cAccess.EvictString("anyone");
	AssertFalse(cAccess.HasString("any"));
	Pass();

	AssertLongLongInt(1, cAccess.NumElements());
	Pass();
	AssertTrue(cAccess.ValidateIndex());
	Pass();

	cAccess.Flush();
	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileAccessEvictBug()
{
	CIndexTreeFileAccess	cAccess;
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cController;
	int						iFlushFrequency;
	BOOL					bResult;

	iFlushFrequency = -1;

	cHelper.Init("Output" _FS_ "IndexTreeFileAccessEvictBug", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutStringLong("nonen", 0x7486498577436958LL));
	AssertTrue(cAccess.PutStringLong("non",   0x9234794843954732LL));

	bResult = cAccess.Flush();
	AssertTrue(bResult);

	cIndexTree.ValidateParentIndex();

	AssertTrue(cAccess.PutStringLong("nonen", 0x5708237808346701LL));
	AssertTrue(cAccess.DeleteString("non"));
	Pass();

	cIndexTree.ValidateParentIndex();

	bResult = cAccess.EvictString("nonen");
	AssertTrue(bResult);
	Pass();

	cAccess.Flush();
	cIndexTree.ValidateIndexTree();

	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileAccessFlushBug()
{
	CIndexTreeFileAccess	cAccess;
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cController;
	int						iData;
	char*					pszData;
	char*					pszKey;
	int						i;
	CChars*					pszKey2;
	CChars*					pszData2;
	int						iArchaicIndex;
	int						iFlush;
	int						iFlushFrequency;
	int						iCount;

	iFlushFrequency = -1;

	cHelper.Init("Output" _FS_ "IndexTreeFileAccessFlushBug", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_No, IKR_Yes);
	cAccess.Init(&cIndexTree);

	iFlush = 0;
	iCount = 230;  //Lowest value causing Kill(void) Flush must called before Kill. bug.
	for (i = 0; i < iCount; i++)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		iData = i;
		cAccess.PutStringInt(pszKey, iData);
		Flush(&cAccess, iFlushFrequency, &iFlush);
	}
	AssertLongLongInt(iCount, cAccess.NumElements());

	iArchaicIndex = 0;
	for (i = 0; i < iCount; i++)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();

		if (i % 2 == 1)
		{
			cAccess.DeleteString(pszKey);
		}
		else
		{
			pszData2 = gaszArchaicDefinitions.Get(iArchaicIndex);
			pszData = pszData2->Text();

			iArchaicIndex++;
			if (iArchaicIndex >= gaszArchaicDefinitions.NumElements())
			{
				iArchaicIndex = 0;
			}

			cAccess.PutStringString(pszKey, pszData);
		}
		Flush(&cAccess, iFlushFrequency, &iFlush);
	}
	AssertLongLongInt(iCount / 2, cAccess.NumElements());
	Pass();

	cAccess.Flush();
	cIndexTree.ValidateIndexTree();

	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileAccess(char* szSubirectory, EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse, int iFlushFrequency)
{
	CIndexTreeFileAccess	cAccess;
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cController;

	cHelper.Init("Output" _FS_ "IndexTreeFileAccess", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, szSubirectory, eWriteThrough, eKeyReverse);
	cAccess.Init(&cIndexTree);

	TestIndexTreeAccessString(&cAccess, iFlushFrequency);

	cAccess.Flush();
	cIndexTree.ValidateIndexTree();

	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeEvictingAccess(char* szSubirectory, size_t sCacheSize, EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse, int iFlushFrequency)
{
	CIndexTreeEvictingAccess 			cAccess;
	CIndexTreeEvicting					cIndexTree;
	CIndexTreeHelper					cHelper;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	CIndexTreeFileKeyDiagnosticCountingCallback			cCallback;

	cHelper.Init("Output" _FS_ "IndexTreeEvictingAccess", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cEvictionStrategy.Init();
	cController.Begin();
	cCallback.Init("any");
	cIndexTree.Init(&cController, szSubirectory, sCacheSize, NULL, &cEvictionStrategy, NULL,  eWriteThrough, eKeyReverse);
	cIndexTree.SetDiagnosticCallback(&cCallback);
	cAccess.Init(&cIndexTree);

	TestIndexTreeAccessString(&cAccess, iFlushFrequency);

	cAccess.Flush();
	cIndexTree.ValidateIndexTree();

	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cCallback.Kill();
	cController.Kill();
	cEvictionStrategy.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeAccess(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	WordsInit();
	BeginTests();

	TestIndexTreeFileAccessFlushBug();
	TestIndexTreeFileAccessEvictBug();
	TestIndexTreeFileAccessFlushEvictBug();
	TestIndexTreeFileAccessRemoveEvictBug();

	TestIndexTreeMemoryAccess(IKR_No);
	TestIndexTreeMemoryAccess(IKR_Yes);

	TestIndexTreeFileAccess(NULL, IWT_Yes, IKR_No, -1);
	TestIndexTreeFileAccess("Sub", IWT_Yes, IKR_No, -1);
	TestIndexTreeFileAccess(NULL, IWT_No, IKR_No, -1);
	TestIndexTreeFileAccess(NULL, IWT_Yes, IKR_Yes, -1);
	TestIndexTreeFileAccess(NULL, IWT_No, IKR_Yes, -1);
	TestIndexTreeFileAccess("Sub", IWT_No, IKR_Yes, -1);

	TestIndexTreeFileAccess(NULL, IWT_No, IKR_No, 1);

	TestIndexTreeFileAccess(NULL, IWT_Yes, IKR_No, 100);
	TestIndexTreeFileAccess(NULL, IWT_No, IKR_No, 100);
	TestIndexTreeFileAccess(NULL, IWT_Yes, IKR_Yes, 100);
	TestIndexTreeFileAccess(NULL, IWT_No, IKR_Yes, 100);

	TestIndexTreeEvictingAccess(NULL, 64 KB, IWT_Yes, IKR_No, -1);
	TestIndexTreeEvictingAccess("Sub", 64 KB, IWT_Yes, IKR_No, -1);
	TestIndexTreeEvictingAccess(NULL, 64 KB, IWT_No, IKR_No, -1);
	TestIndexTreeEvictingAccess(NULL, 64 KB, IWT_Yes, IKR_Yes, -1);
	TestIndexTreeEvictingAccess(NULL, 64 KB, IWT_No, IKR_Yes, -1);
	TestIndexTreeEvictingAccess("Sub", 64 KB, IWT_No, IKR_Yes, -1);

	TestIndexTreeEvictingAccess(NULL, 64 KB, IWT_No, IKR_No, 1);

	TestIndexTreeEvictingAccess(NULL, 64 KB, IWT_Yes, IKR_No, 100);
	TestIndexTreeEvictingAccess(NULL, 64 KB, IWT_No, IKR_No, 100);
	TestIndexTreeEvictingAccess(NULL, 64 KB, IWT_Yes, IKR_Yes, 100);
	TestIndexTreeEvictingAccess(NULL, 64 KB, IWT_No, IKR_Yes, 100);

	TestStatistics();
	WordsKill();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

