#include "BaseLib/TypeConverter.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/Define.h"
#include "BaseLib/Logger.h"
#include "BaseLib/GlobalMemory.h"
#include "CoreLib/IndexTreeEvictionCounter.h"
#include "CoreLib/DurableFileController.h"
#include "CoreLib/NamedIndexes.h"
#include "CoreLib/ValueNamedIndexesConfig.h"
#include "StandardLib/BaseObject.h"
#include "TestLib/Words.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexesAdd(void)
{
	CNamedIndexes						cNamedIndexes;
	CDurableFileController				cController;
	CFileUtil							cFileUtil;
	BOOL								bResult;
	char								szDirectory[] = "Output" _FS_ "NamedIndexes" _FS_ "1";
	char								szRewriteDirectory[] = "Output" _FS_ "_NamedIndexes" _FS_ "1";
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	CLifeInit<CNamedIndexesConfig>		cConfig;
	SLogConfig							sLogConfig;

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewriteDirectory, NULL);

	cController.Init(szDirectory, szRewriteDirectory);
	cController.Begin();

	cEvictionStrategy.Init();
	cConfig = CValueNamedIndexesConfig::Create(NULL, 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cEvictionStrategy), IWT_No);
	cNamedIndexes.Init(&cController, cConfig);

	AssertLongLongInt(0, cNamedIndexes.NumElements());

	cNamedIndexes.Add("Berty", 45LL);
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(1, cNamedIndexes.NumElements());

	cNamedIndexes.Add("Alfred", 73LL);
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get(""));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Ax"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get((char*)NULL));

	cNamedIndexes.Add("Camilla", 19LL);
	cNamedIndexes.Add("Wordsworth", 20LL);
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("Wordsworth"));
	AssertLongLongInt(4, cNamedIndexes.NumElements());


	cNamedIndexes.Add("Alicia", 66LL);
	AssertLongLongInt(66LL, cNamedIndexes.Get("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("Wordsworth"));
	AssertLongLongInt(5, cNamedIndexes.NumElements());


	cNamedIndexes.Add("Aardvark", 67LL);
	cNamedIndexes.Add("Alfredo", 68LL);
	bResult = cNamedIndexes.Add("Play-dough", 69LL);
	cNamedIndexes.Add("Zynaps", 01LL);
	AssertTrue(bResult);
	AssertLongLongInt(66LL, cNamedIndexes.Get("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("Wordsworth"));
	AssertLongLongInt(67LL, cNamedIndexes.Get("Aardvark"));
	AssertLongLongInt(68LL, cNamedIndexes.Get("Alfredo"));
	AssertLongLongInt(69LL, cNamedIndexes.Get("Play-dough"));
	AssertLongLongInt(01LL, cNamedIndexes.Get("Zynaps"));
	AssertLongLongInt(9, cNamedIndexes.NumElements());

	sLogConfig = gcLogger.SetSilent();
	bResult = cNamedIndexes.Add("Play-dough", 88LL);
	AssertFalse(bResult);
	gcLogger.SetConfig(&sLogConfig);

	AssertLongLongInt(9, cNamedIndexes.NumElements());

	cNamedIndexes.Flush();
	cController.End();
	cNamedIndexes.Kill();
	cEvictionStrategy.Kill();
	cController.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexesRemove(void)
{
	CNamedIndexes						cNamedIndexes;
	CDurableFileController				cController;
	CFileUtil							cFileUtil;
	BOOL								bResult;
	char								szDirectory[] = "Output" _FS_ "NamedIndexes" _FS_ "2";
	char								szRewriteDirectory[] = "Output" _FS_ "_NamedIndexes" _FS_ "2";
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	CLifeInit<CNamedIndexesConfig>		cConfig;

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewriteDirectory, NULL);

	cController.Init(szDirectory, szRewriteDirectory);
	cController.Begin();
	
	cEvictionStrategy.Init();
	cConfig = CValueNamedIndexesConfig::Create(NULL, 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cEvictionStrategy), IWT_No);
	cNamedIndexes.Init(&cController, cConfig);

	cNamedIndexes.Add("Berty", 45LL);
	cNamedIndexes.Add("Alfred", 73LL);
	cNamedIndexes.Add("Camilla", 19LL);
	cNamedIndexes.Add("Wordsworth", 20LL);

	cNamedIndexes.Add("Alicia", 66LL);
	cNamedIndexes.Add("Aardvark", 67LL);
	cNamedIndexes.Add("Alfredo", 68LL);
	cNamedIndexes.Add("Play-dough", 69LL);

	cNamedIndexes.Add("Zynaps", 01LL);

	AssertLongLongInt(9, cNamedIndexes.NumElements());

	bResult = cNamedIndexes.Remove("Aardvark");
	AssertTrue(bResult);

	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Aardvark"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(68LL, cNamedIndexes.Get("Alfredo"));
	AssertLongLongInt(66LL, cNamedIndexes.Get("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(69LL, cNamedIndexes.Get("Play-dough"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("Wordsworth"));
	AssertLongLongInt(01LL, cNamedIndexes.Get("Zynaps"));

	AssertLongLongInt(8, cNamedIndexes.NumElements());

	bResult = cNamedIndexes.Remove("Aardvark");
	AssertFalse(bResult);
	AssertLongLongInt(8, cNamedIndexes.NumElements());

	AssertTrue(cNamedIndexes.Remove("Alicia"));
	AssertTrue(cNamedIndexes.Remove("Alfredo"));
	AssertLongLongInt(6, cNamedIndexes.NumElements());

	AssertTrue(cNamedIndexes.Remove("Play-dough"));

	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Alfredo"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Play-dough"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("Wordsworth"));
	AssertLongLongInt(01LL, cNamedIndexes.Get("Zynaps"));
	AssertLongLongInt(5, cNamedIndexes.NumElements());

	AssertTrue(cNamedIndexes.Remove("Alfred"));
	AssertTrue(cNamedIndexes.Remove("Berty"));
	AssertTrue(cNamedIndexes.Remove("Camilla"));
	AssertTrue(cNamedIndexes.Remove("Wordsworth"));
	AssertTrue(cNamedIndexes.Remove("Zynaps"));

	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Wordsworth"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Zynaps"));
	AssertLongLongInt(0, cNamedIndexes.NumElements());

	cNamedIndexes.Add("Berty", 45LL);
	AssertLongLongInt(1, cNamedIndexes.NumElements());
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertTrue(cNamedIndexes.Remove("Berty"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(0, cNamedIndexes.NumElements());

	cNamedIndexes.Flush();
	AssertTrue(cController.End());
	cNamedIndexes.Kill();
	cEvictionStrategy.Kill();
	cController.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexesCacheEviction(void)
{
	CNamedIndexes						cNamedIndexes;
	CDurableFileController				cController;
	CFileUtil							cFileUtil;
	BOOL								bResult;
	char								szDirectory[] = "Output" _FS_ "NamedIndexes" _FS_ "3";
	char								szRewriteDirectory[] = "Output" _FS_ "_NamedIndexes" _FS_ "3";
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	CLifeInit<CNamedIndexesConfig>		cConfig;
	SLogConfig							sLogConfig;

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewriteDirectory, NULL);

	cController.Init(szDirectory, szRewriteDirectory);
	cController.Begin();

	cEvictionStrategy.Init();
	cConfig = CValueNamedIndexesConfig::Create(NULL, 8192, LifeLocal<CIndexTreeEvictionStrategy>(&cEvictionStrategy), IWT_No);
	cNamedIndexes.Init(&cController, cConfig);


	AssertLongLongInt(0, cNamedIndexes.NumElements());

	AssertTrue(cNamedIndexes.Add("Berty", 45LL));
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(1, cNamedIndexes.NumElements());

	AssertTrue(cNamedIndexes.Add("Alfred", 73LL));
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get(""));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Ax"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get((char*)NULL));

	AssertTrue(cNamedIndexes.Add("Camilla", 19LL));
	AssertTrue(cNamedIndexes.Add("Wordsworth", 20LL));
	AssertLongLongInt(4, cNamedIndexes.NumElements());
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("Wordsworth"));


	AssertTrue(cNamedIndexes.Add("Alicia", 66LL));
	AssertLongLongInt(5, cNamedIndexes.NumElements());

	AssertLongLongInt(66LL, cNamedIndexes.Get("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("Wordsworth"));

	AssertTrue(cNamedIndexes.Add("Aardvark", 67LL));
	AssertTrue(cNamedIndexes.Add("Alfredo", 68LL));
	AssertTrue(cNamedIndexes.Add("Play-dough", 69LL));
	AssertLongLongInt(67LL, cNamedIndexes.Get("Aardvark"));
	AssertLongLongInt(66LL, cNamedIndexes.Get("Alicia"));
	AssertLongLongInt(68LL, cNamedIndexes.Get("Alfredo"));
	AssertLongLongInt(69LL, cNamedIndexes.Get("Play-dough"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("Wordsworth"));

	AssertTrue(cNamedIndexes.Add("Zynaps", 01LL));
	AssertLongLongInt(66LL, cNamedIndexes.Get("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("Wordsworth"));
	AssertLongLongInt(67LL, cNamedIndexes.Get("Aardvark"));
	AssertLongLongInt(68LL, cNamedIndexes.Get("Alfredo"));
	AssertLongLongInt(69LL, cNamedIndexes.Get("Play-dough"));
	AssertLongLongInt(01LL, cNamedIndexes.Get("Zynaps"));
	AssertLongLongInt(9, cNamedIndexes.NumElements());

	sLogConfig = gcLogger.SetSilent();
	bResult = cNamedIndexes.Add("Play-dough", 88LL);
	AssertFalse(bResult);
	gcLogger.SetConfig(&sLogConfig);

	AssertLongLongInt(9, cNamedIndexes.NumElements());

	cNamedIndexes.Flush();
	AssertTrue(cController.End());
	cNamedIndexes.Kill();
	cEvictionStrategy.Kill();
	cController.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexesLoad(void)
{
	CNamedIndexes						cNamedIndexes;
	CDurableFileController				cController;
	CFileUtil							cFileUtil;
	char								szDirectory[] = "Output" _FS_ "NamedIndexes" _FS_ "4";
	char								szRewriteDirectory[] = "Output" _FS_"_NamedIndexes" _FS_ "4";
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	CLifeInit<CNamedIndexesConfig>		cConfig;

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewriteDirectory, NULL);

	cController.Init(szDirectory, szRewriteDirectory);
	AssertTrue(cController.Begin());

	cEvictionStrategy.Init();
	cConfig = CValueNamedIndexesConfig::Create(NULL, 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cEvictionStrategy), IWT_No);
	cNamedIndexes.Init(&cController, cConfig);

	cNamedIndexes.Add("Arthur Miller", 1LL);
	cNamedIndexes.Add("systema skeletale", 2LL);
	cNamedIndexes.Add("roe", 3LL);
	cNamedIndexes.Add("order Plumbaginales Melba aldicarb", 4LL);
	cNamedIndexes.Add("asphyxiate", 5LL);
	cNamedIndexes.Add("Fonseca Bay Piaget Salt tomato plant", 6LL);
	cNamedIndexes.Add("thoracic vertebra", 7LL);
	cNamedIndexes.Add("LL75", 8LL);
	cNamedIndexes.Add("Calendrer", 9LL);
	cNamedIndexes.Add("zone refining refashion butter up", 10LL);
	cNamedIndexes.Add("Chopin Dicranaceae transmountain insentient", 11LL);
	cNamedIndexes.Add("Recipes Kerchiefs 32TX", 12LL);
	cNamedIndexes.Add("factor V domestic relations", 13LL);
	cNamedIndexes.Add("bedum ?", 14LL);
	cNamedIndexes.Add("gauche", 15LL);
	cNamedIndexes.Add("takeoff breakup value Tenuifolious magnitude", 16LL);
	cNamedIndexes.Add("Forisfamiliated", 17LL);
	cNamedIndexes.Add("amphibious bulk liquid transfer system", 18LL);
	cNamedIndexes.Add("otoscope", 19LL);
	cNamedIndexes.Add("impel Christmas", 20LL);
	cNamedIndexes.Add("universalise rose fever IL59 Europe", 21LL);

	AssertLongLongInt(1LL, cNamedIndexes.Get("Arthur Miller"));
	AssertLongLongInt(2LL, cNamedIndexes.Get("systema skeletale"));
	AssertLongLongInt(3LL, cNamedIndexes.Get("roe"));
	AssertLongLongInt(4LL, cNamedIndexes.Get("order Plumbaginales Melba aldicarb"));
	AssertLongLongInt(5LL, cNamedIndexes.Get("asphyxiate"));
	AssertLongLongInt(6LL, cNamedIndexes.Get("Fonseca Bay Piaget Salt tomato plant"));
	AssertLongLongInt(7LL, cNamedIndexes.Get("thoracic vertebra"));
	AssertLongLongInt(8LL, cNamedIndexes.Get("LL75"));
	AssertLongLongInt(9LL, cNamedIndexes.Get("Calendrer"));
	AssertLongLongInt(10LL, cNamedIndexes.Get("zone refining refashion butter up"));
	AssertLongLongInt(11LL, cNamedIndexes.Get("Chopin Dicranaceae transmountain insentient"));
	AssertLongLongInt(12LL, cNamedIndexes.Get("Recipes Kerchiefs 32TX"));
	AssertLongLongInt(13LL, cNamedIndexes.Get("factor V domestic relations"));
	AssertLongLongInt(14LL, cNamedIndexes.Get("bedum ?"));
	AssertLongLongInt(15LL, cNamedIndexes.Get("gauche"));
	AssertLongLongInt(16LL, cNamedIndexes.Get("takeoff breakup value Tenuifolious magnitude"));
	AssertLongLongInt(17LL, cNamedIndexes.Get("Forisfamiliated"));
	AssertLongLongInt(18LL, cNamedIndexes.Get("amphibious bulk liquid transfer system"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("otoscope"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("impel Christmas"));
	AssertLongLongInt(21LL, cNamedIndexes.Get("universalise rose fever IL59 Europe"));

	cNamedIndexes.Flush();
	AssertTrue(cController.End());
	cNamedIndexes.Kill();
	cController.Kill();
	cEvictionStrategy.Kill();


	cEvictionStrategy.Init();
	cController.Init(szDirectory, szRewriteDirectory);
	AssertTrue(cController.Begin());
	cConfig = CValueNamedIndexesConfig::Create(NULL, 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cEvictionStrategy), IWT_No);
	cNamedIndexes.Init(&cController, cConfig);

	AssertLongLongInt(1LL, cNamedIndexes.Get("Arthur Miller"));
	AssertLongLongInt(2LL, cNamedIndexes.Get("systema skeletale"));
	AssertLongLongInt(3LL, cNamedIndexes.Get("roe"));
	AssertLongLongInt(4LL, cNamedIndexes.Get("order Plumbaginales Melba aldicarb"));
	AssertLongLongInt(5LL, cNamedIndexes.Get("asphyxiate"));
	AssertLongLongInt(6LL, cNamedIndexes.Get("Fonseca Bay Piaget Salt tomato plant"));
	AssertLongLongInt(7LL, cNamedIndexes.Get("thoracic vertebra"));
	AssertLongLongInt(8LL, cNamedIndexes.Get("LL75"));
	AssertLongLongInt(9LL, cNamedIndexes.Get("Calendrer"));
	AssertLongLongInt(10LL, cNamedIndexes.Get("zone refining refashion butter up"));
	AssertLongLongInt(11LL, cNamedIndexes.Get("Chopin Dicranaceae transmountain insentient"));
	AssertLongLongInt(12LL, cNamedIndexes.Get("Recipes Kerchiefs 32TX"));
	AssertLongLongInt(13LL, cNamedIndexes.Get("factor V domestic relations"));
	AssertLongLongInt(14LL, cNamedIndexes.Get("bedum ?"));
	AssertLongLongInt(15LL, cNamedIndexes.Get("gauche"));
	AssertLongLongInt(16LL, cNamedIndexes.Get("takeoff breakup value Tenuifolious magnitude"));
	AssertLongLongInt(17LL, cNamedIndexes.Get("Forisfamiliated"));
	AssertLongLongInt(18LL, cNamedIndexes.Get("amphibious bulk liquid transfer system"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("otoscope"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("impel Christmas"));
	AssertLongLongInt(21LL, cNamedIndexes.Get("universalise rose fever IL59 Europe"));

	AssertLongLongInt(1LL, cNamedIndexes.Get("Arthur Miller"));
	AssertLongLongInt(14LL, cNamedIndexes.Get("bedum ?"));
	AssertLongLongInt(21LL, cNamedIndexes.Get("universalise rose fever IL59 Europe"));
	AssertLongLongInt(3LL, cNamedIndexes.Get("roe"));
	AssertLongLongInt(16LL, cNamedIndexes.Get("takeoff breakup value Tenuifolious magnitude"));
	AssertLongLongInt(5LL, cNamedIndexes.Get("asphyxiate"));
	AssertLongLongInt(18LL, cNamedIndexes.Get("amphibious bulk liquid transfer system"));
	AssertLongLongInt(7LL, cNamedIndexes.Get("thoracic vertebra"));
	AssertLongLongInt(9LL, cNamedIndexes.Get("Calendrer"));
	AssertLongLongInt(13LL, cNamedIndexes.Get("factor V domestic relations"));
	AssertLongLongInt(15LL, cNamedIndexes.Get("gauche"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("impel Christmas"));
	AssertLongLongInt(10LL, cNamedIndexes.Get("zone refining refashion butter up"));
	AssertLongLongInt(12LL, cNamedIndexes.Get("Recipes Kerchiefs 32TX"));
	AssertLongLongInt(8LL, cNamedIndexes.Get("LL75"));
	AssertLongLongInt(17LL, cNamedIndexes.Get("Forisfamiliated"));
	AssertLongLongInt(6LL, cNamedIndexes.Get("Fonseca Bay Piaget Salt tomato plant"));
	AssertLongLongInt(4LL, cNamedIndexes.Get("order Plumbaginales Melba aldicarb"));
	AssertLongLongInt(11LL, cNamedIndexes.Get("Chopin Dicranaceae transmountain insentient"));
	AssertLongLongInt(2LL, cNamedIndexes.Get("systema skeletale"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("otoscope"));
	
	cNamedIndexes.Flush();
	AssertTrue(cController.End());
	Pass();

	cNamedIndexes.Kill();
	cEvictionStrategy.Kill();
	cController.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexesMoreCacheEviction(void)
{
	CNamedIndexes						cNamedIndexes;
	CDurableFileController				cController;
	CFileUtil							cFileUtil;
	char								szDirectory[] = "Output" _FS_ "NamedIndexes" _FS_ "5";
	char								szRewriteDirectory[] = "Output" _FS_"_NamedIndexes" _FS_ "5";
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	CLifeInit<CNamedIndexesConfig>		cConfig;
	CIndexTreeEvictionCounter			cEvictionCounter;
	CArrayChars							aszWords;
	int									iNumWords;
	CRandom								cRandom;
	OIndex								oi;
	CChars								sz;
	int									iWord;
	int									iIndex;
	CArrayChars							aszNames;
	size_t								uiCacheSize;
	CChars*								psz;

	aszWords.Init();
	GetCommonWords(&aszWords);
	iNumWords = aszWords.NumElements();
	cRandom.Init(9824375);
	aszNames.Init();

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewriteDirectory, NULL);

	cEvictionStrategy.Init(67);
	cEvictionCounter.Init();

	cController.Init(szDirectory, szRewriteDirectory);
	AssertTrue(cController.Begin());

	uiCacheSize = 16 KB;
	cConfig = CValueNamedIndexesConfig::Create(NULL, uiCacheSize, LifeLocal<CIndexTreeEvictionStrategy>(&cEvictionStrategy), IWT_No, &cEvictionCounter);
	cNamedIndexes.Init(&cController, cConfig);

	for (oi = 1; oi < 1024; oi++)
	{
		sz.Init();
		for (iWord = 0; iWord < 3; iWord++)
		{
			if (iWord != 0)
			{
				sz.Append(" ");
			}
			iIndex = cRandom.Next(0, iNumWords - 1);
			sz.Append(aszWords.Get(iIndex));
		}
		cNamedIndexes.Add(sz.Text(), oi);
		aszNames.Add(sz.Text());
		sz.Kill();
	}

	AssertLongLongInt(1015, cEvictionCounter.EvictionCount());
	AssertLongLongInt(15692, cNamedIndexes.GetSystemMemorySize());
	AssertTrue(cNamedIndexes.GetSystemMemorySize() < uiCacheSize);

	cNamedIndexes.Flush();
	AssertTrue(cController.End());
	cNamedIndexes.Kill();
	cEvictionStrategy.Kill();
	cController.Kill();
	Pass();

	cEvictionStrategy.Init(67);
	cEvictionCounter.Init();
	cController.Init(szDirectory, szRewriteDirectory);
	AssertTrue(cController.Begin());
	cConfig = CValueNamedIndexesConfig::Create(NULL, uiCacheSize, LifeLocal<CIndexTreeEvictionStrategy>(&cEvictionStrategy), IWT_No, &cEvictionCounter);
	cNamedIndexes.Init(&cController, cConfig);
	Pass();

	aszNames.Shuffle(cEvictionStrategy.GetRandom());
	for (iIndex = 0; iIndex < aszNames.NumElements(); iIndex++)
	{
		psz = aszNames.Get(iIndex);
		oi = cNamedIndexes.Get(psz);
	}

	AssertLongLongInt(1014, cEvictionCounter.EvictionCount());
	AssertLongLongInt(15564, cNamedIndexes.GetSystemMemorySize());
	AssertTrue(cNamedIndexes.GetSystemMemorySize() < uiCacheSize);

	cNamedIndexes.Flush();
	AssertTrue(cController.End());
	Pass();

	cNamedIndexes.Kill();
	cEvictionStrategy.Kill();
	cController.Kill();

	aszWords.Kill();
	aszNames.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexes(void)
{
	CFileUtil	cFileUtil;

	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	TestNamedIndexesAdd();
	TestNamedIndexesRemove();
	TestNamedIndexesCacheEviction();
	TestNamedIndexesLoad();
	TestNamedIndexesMoreCacheEviction();

	cFileUtil.RemoveDirs("Output" _FS_ "NamedIndexes", "Output" _FS_ "_NamedIndexes", NULL);

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	TypeConverterKill();
}

