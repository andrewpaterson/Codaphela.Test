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
void TestIndexTreeAccessComplex(void)
{
	CIndexTreeFileAccess	cAccess;
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cController;
	//int64					lliKey;
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

	cHelper.Init("Output" _FS_"IndexTreeAccess", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_Yes, IKR_No);
	cAccess.Init(&cIndexTree);

	for (i = 0; i < gaszCommonWords.NumElements(); i++)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		iData = i;
		cAccess.PutStringInt(pszKey, iData);
	}
	AssertInt(1000, cIndexTree.NumElements());

	bPassed = TRUE;
	for (i = 0; i < gaszCommonWords.NumElements(); i++)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		iData = cAccess.GetStringInt(pszKey);
		if (iData != i)
		{
			bPassed = FALSE;
			break;
		}
	}
	AssertTrue(bPassed);

	iArchaicIndex = 0;
	for (i = 0; i < gaszCommonWords.NumElements(); i++)
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
	}
	AssertInt(500, cIndexTree.NumElements());

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

		pszData = cAccess.GetStringString(pszKey, szData);
		pszData2 = gaszArchaicDefinitions.Get(iArchaicIndex);

		if (pszData2->Equals(pszData))
		{
			bPassed = FALSE;
			break;
		}
	}
	AssertTrue(bPassed);

	for (i = gaszCommonWords.NumElements()-1; i >= 0; i--)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		lliData = (1000 - i) * 86509465456456LL;
		cAccess.PutStringLong(pszKey, lliData);
	}
	AssertInt(1000, cIndexTree.NumElements());

	bPassed = TRUE;
	for (i = 0; i < gaszCommonWords.NumElements(); i++)
	{
		pszKey2 = gaszCommonWords.Get(i);
		pszKey = pszKey2->Text();
		lliData = cAccess.GetStringLong(pszKey);
		if (lliData != (1000 - i) * 86509465456456LL)
		{
			bPassed = FALSE;
			break;
		}
	}
	AssertTrue(bPassed);

	//cAccess.PutLongInt(lliKey, iData);
	//cAccess.PutLongString(lliKey, pszData);

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

	TestIndexTreeAccessComplex();

	TestStatistics();
	WordsKill();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

