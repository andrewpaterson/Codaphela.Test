#include "BaseLib/TypeConverter.h"
#include "BaseLib/DebugOutput.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/CharsHelper.h"
#include "BaseLib/LogFile.h"
#include "BaseLib/CodabaseFactory.h"
#include "BaseLib/Codabase.h"
#include "TestLib/Words.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCodabaseFactoryCreate(void)
{
	CCodabase*	pcDatabase;
	CFileUtil	cFileUtil;

	cFileUtil.RemoveDir("Output" _FS_ "CodabaseFactory1");

	pcDatabase = CCodabaseFactory::Create("Output" _FS_ "CodabaseFactory1", IWT_No);

	AssertTrue(cFileUtil.Exists("Output" _FS_ "CodabaseFactory1" _FS_ "Primary" _FS_ "Index"));
	AssertTrue(cFileUtil.Exists("Output" _FS_ "CodabaseFactory1" _FS_ "Primary" _FS_ "Names"));
	AssertTrue(pcDatabase->ValidateConfigInitialised());
	Pass();

	pcDatabase->Kill();
	AssertTrue(pcDatabase->ValidateConfigKilled()); 
	Pass();
	
	SafeFree(pcDatabase);
	Pass();

	AssertTrue(cFileUtil.RemoveDir("Output" _FS_ "CodabaseFactory1"));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCodabaseOperations(void)
{
	CCodabase*	pcDatabase;
	CFileUtil	cFileUtil;

	OIndex		oiKey1 = 0x4902385234347LL;
	char		szData1[] = "Village did removed enjoyed explain nor ham saw calling talking. Securing as informed declared or margaret. Joy horrible moreover man feelings own shy. Request norland neither mistake for yet. Between the for morning assured country believe. On even feet time have an no at. Relation so in confined smallest children unpacked delicate. Why sir end believe uncivil respect. Always get adieus nature day course for common. My little garret repair to desire he esteem.";

	OIndex		oiKey2 = 0x4902383278911LL;
	char		szData2[] = "Folly words widow one downs few age every seven. If miss part by fact he park just shew. Discovered had get considered projection who favourable. Necessary up knowledge it tolerably. Unwilling departure education is be dashwoods or an. Use off agreeable law unwilling sir deficient curiosity instantly. Easy mind life fact with see has bore ten. Parish any chatty can elinor direct for former. Up as meant widow equal an share least.";

	OIndex		oiKey3 = 0x4902394579823LL;
	char		szName3[] = "Advanced";
	char		szData3[] = "One advanced diverted domestic sex repeated bringing you old.Possible procured her trifling laughter thoughts property she met way.Companions shy had solicitude favourable own.Which could saw guest man now heard but.Lasted my coming uneasy marked so should.Gravity letters it amongst herself dearest an windows by.Wooded ladies she basket season age her uneasy saw.Discourse unwilling am no described dejection incommode no listening of.Before nature his parish boy.";

	OIndex		oiKey4 = 0x4902393749238LL;
	char		szName4[] = "Article";
	char		szData4[] = "Article nor prepare chicken you him now. Shy merits say advice ten before lovers innate add. She cordially behaviour can attempted estimable. Trees delay fancy noise manor do as an small. Felicity now law securing breeding likewise extended and. Roused either who favour why ham.";

	char		szResult[2 KB];

	cFileUtil.RemoveDir("Output" _FS_ "Codabase1");

	pcDatabase = CCodabaseFactory::Create("Output" _FS_ "Codabase1", IWT_No);
	AssertNotNull(pcDatabase);
	Pass();
	pcDatabase->Open();

	AssertTrue(pcDatabase->Add(oiKey1, szData1, strlen(szData1) + 1));
	AssertTrue(pcDatabase->Add(oiKey2, szData2, strlen(szData2) + 1));

	AssertLongLongInt(2, pcDatabase->NumIndicesCached());
	AssertLongLongInt(0, pcDatabase->NumNamesCached());
	AssertLongLongInt(2, pcDatabase->NumIndices());
	AssertLongLongInt(0, pcDatabase->NumNames());
	Pass();

	pcDatabase->Close();
	SafeKill(pcDatabase);
	Pass();


	pcDatabase = CCodabaseFactory::Create("Output" _FS_ "Codabase1", IWT_No);
	AssertNotNull(pcDatabase);
	Pass();
	pcDatabase->Open();

	memset(szResult, 0, 2 KB);
	AssertTrue(pcDatabase->Get(oiKey1, szResult));
	AssertString(szData1, szResult);

	AssertTrue(pcDatabase->Add(oiKey3, szName3, szData3, strlen(szData3) + 1));

	memset(szResult, 0, 2 KB);
	AssertTrue(pcDatabase->Get(oiKey2, szResult));
	AssertString(szData2, szResult);

	AssertTrue(pcDatabase->Add(oiKey4, szName4, szData4, strlen(szData4) + 1));

	memset(szResult, 0, 2 KB);
	AssertTrue(pcDatabase->Get(oiKey3, szResult));
	AssertString(szData3, szResult);

	memset(szResult, 0, 2 KB);
	AssertTrue(pcDatabase->Get(oiKey4, szResult));
	AssertString(szData4, szResult);

	AssertLongLongInt(4, pcDatabase->NumIndicesCached());
	AssertLongLongInt(2, pcDatabase->NumNamesCached());
	AssertLongLongInt(4, pcDatabase->NumIndices());
	AssertLongLongInt(2, pcDatabase->NumNames());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	Pass();


	pcDatabase = CCodabaseFactory::Create("Output" _FS_ "Codabase1", IWT_No);
	AssertNotNull(pcDatabase);
	Pass();
	pcDatabase->Open();

	AssertLongLongInt(0, pcDatabase->NumIndicesCached());
	AssertLongLongInt(0, pcDatabase->NumNamesCached());
	AssertLongLongInt(4, pcDatabase->NumIndices());
	AssertLongLongInt(2, pcDatabase->NumNames());
	AssertLongLongInt(4, pcDatabase->NumIndicesCached());
	AssertLongLongInt(2, pcDatabase->NumNamesCached());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	Pass();


	AssertTrue(cFileUtil.RemoveDir("Output" _FS_ "Codabase1"));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCodabase(void)
{
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	WordsInit();
	BeginTests();

	TestCodabaseFactoryCreate();
	TestCodabaseOperations();

	TestStatistics();
	WordsKill();
	DataMemoryKill();
	MemoryKill();
	TypeConverterKill();
}

