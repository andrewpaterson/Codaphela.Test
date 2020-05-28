#include "BaseLib/TypeConverter.h"
#include "BaseLib/DebugOutput.h"
#include "BaseLib/GlobalMemory.h"
#include "CoreLib/LogFile.h"
#include "CoreLib/IndexTreeFileAccess.h"
#include "CoreLib/IndexTreeHelper.h"
#include "TestLib/Words.h"
#include "TestLib/Assert.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void Flush(CIndexTreeFileAccess* pcAccess, CDurableFileController* pcController, int iFlushFrequency, int* piCurrent)
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
void TestIndexTreeAccessString(CIndexTreeFileAccess* pcAccess, CDurableFileController* pcController, int iFlushFrequency)
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

	iFlush = 0;
	for (i = 0; i < gaszCommonWords.NumElements(); i++)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		iData = i;
		pcAccess->PutStringInt(pszKey, iData);
		Flush(pcAccess, pcController, iFlushFrequency, &iFlush);
	}
	AssertLongLongInt(1000, pcAccess->NumElements());

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
		Flush(pcAccess, pcController, iFlushFrequency, &iFlush);
	}
	AssertTrue(bPassed);

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
		}
		Flush(pcAccess, pcController, iFlushFrequency, &iFlush);
	}
	AssertLongLongInt(500, pcAccess->NumElements());

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
		Flush(pcAccess, pcController, iFlushFrequency, &iFlush);
	}
	AssertTrue(bPassed);

	for (i = gaszCommonWords.NumElements() - 1; i >= 0; i--)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		lliData = ((int64)1000 - i) * 86509465456456LL;
		pcAccess->PutStringLong(pszKey, lliData);
		Flush(pcAccess, pcController, iFlushFrequency, &iFlush);
	}
	AssertLongLongInt(1000, pcAccess->NumElements());

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
		Flush(pcAccess, pcController, iFlushFrequency, &iFlush);
	}
	AssertTrue(bPassed);

	for (i = 0; i < gaszCommonWords.NumElements(); i += 3)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		pcAccess->DeleteString(pszKey);
		Flush(pcAccess, pcController, iFlushFrequency, &iFlush);
	}
	AssertLongLongInt(666, pcAccess->NumElements());

	for (i = 1; i < gaszCommonWords.NumElements(); i += 3)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		pcAccess->DeleteString(pszKey);
		Flush(pcAccess, pcController, iFlushFrequency, &iFlush);
	}
	AssertLongLongInt(333, pcAccess->NumElements());

	for (i = 2; i < gaszCommonWords.NumElements(); i += 3)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		pcAccess->PutStringInt(pszKey, i);
		Flush(pcAccess, pcController, iFlushFrequency, &iFlush);
	}

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

		Flush(pcAccess, pcController, iFlushFrequency, &iFlush);
	}
	AssertTrue(bPassed);

	//cAccess.PutLongInt(lliKey, iData);
	//cAccess.PutLongString(lliKey, pszData);
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

	cHelper.Init("Output" _FS_ "IndexTreeAccess", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, szSubirectory, eWriteThrough, eKeyReverse);
	cAccess.Init(&cIndexTree);

	TestIndexTreeAccessString(&cAccess, &cController, iFlushFrequency);

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
void TestIndexTreeAccess(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	WordsInit();
	BeginTests();

	TestIndexTreeFileAccess(NULL, IWT_Yes, IKR_No, -1);
	TestIndexTreeFileAccess("Sub", IWT_Yes, IKR_No, -1);
	TestIndexTreeFileAccess(NULL, IWT_No, IKR_No, -1);
	TestIndexTreeFileAccess(NULL, IWT_Yes, IKR_Yes, -1);
	TestIndexTreeFileAccess(NULL, IWT_No, IKR_Yes, -1);
	TestIndexTreeFileAccess("Sub", IWT_No, IKR_Yes, -1);

	TestIndexTreeFileAccess(NULL, IWT_No, IKR_No, 1);

	TestIndexTreeFileAccess(NULL, IWT_Yes, IKR_No, 100);
	TestIndexTreeFileAccess("Sub", IWT_Yes, IKR_No, 100);
	TestIndexTreeFileAccess(NULL, IWT_No, IKR_No, 100);
	TestIndexTreeFileAccess(NULL, IWT_Yes, IKR_Yes, 100);
	TestIndexTreeFileAccess(NULL, IWT_No, IKR_Yes, 100);
	TestIndexTreeFileAccess("Sub", IWT_No, IKR_Yes, 100);

	TestStatistics();
	WordsKill();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

