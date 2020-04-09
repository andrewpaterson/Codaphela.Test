#include "BaseLib/TypeConverter.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/Define.h"
#include "BaseLib/GlobalMemory.h"
#include "CoreLib/DurableFileController.h"
#include "CoreLib/NamedIndexes.h"
#include "StandardLib/BaseObject.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexesAdd(void)
{
	CNamedIndexes			cNamedIndexes;
	CDurableFileController	cController;
	CFileUtil				cFileUtil;
	BOOL					bResult;
	char					szDirectory[] = "NamedIndexes" _FS_ "1";
	char					szRewriteDirectory[] = "_NamedIndexes" _FS_ "1";

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewriteDirectory, NULL);

	cController.Init(szDirectory, szRewriteDirectory);
	cController.Begin();
	cNamedIndexes.Init(&cController, 10 MB, IWT_No);

	AssertLongLongInt(0, cNamedIndexes.NumElements());

	cNamedIndexes.Add(45LL, "Berty");
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(1, cNamedIndexes.NumElements());

	cNamedIndexes.Add(73LL, "Alfred");
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex(""));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Ax"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex((char*)NULL));

	cNamedIndexes.Add(19LL, "Camilla");
	cNamedIndexes.Add(20LL, "Wordsworth");
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(4, cNamedIndexes.NumElements());


	cNamedIndexes.Add(66LL, "Alicia");
	AssertLongLongInt(66LL, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(5, cNamedIndexes.NumElements());


	cNamedIndexes.Add(67LL, "Aardvark");
	cNamedIndexes.Add(68LL, "Alfredo");
	bResult = cNamedIndexes.Add(69LL, "Play-dough");
	cNamedIndexes.Add(01LL, "Zynaps");
	AssertTrue(bResult);
	AssertLongLongInt(66LL, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(67LL, cNamedIndexes.GetIndex("Aardvark"));
	AssertLongLongInt(68LL, cNamedIndexes.GetIndex("Alfredo"));
	AssertLongLongInt(69LL, cNamedIndexes.GetIndex("Play-dough"));
	AssertLongLongInt(01LL, cNamedIndexes.GetIndex("Zynaps"));
	AssertLongLongInt(9, cNamedIndexes.NumElements());

	bResult = cNamedIndexes.Add(88LL, "Play-dough");
	AssertFalse(bResult);

	AssertLongLongInt(9, cNamedIndexes.NumElements());

	cNamedIndexes.Flush();
	cController.End();
	cNamedIndexes.Kill();
	cController.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexesRemove(void)
{
	CNamedIndexes			cNamedIndexes;
	CDurableFileController	cController;
	CFileUtil				cFileUtil;
	BOOL					bResult;
	char					szDirectory[] = "NamedIndexes" _FS_ "2";
	char					szRewriteDirectory[] = "_NamedIndexes" _FS_ "2";

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewriteDirectory, NULL);

	cController.Init(szDirectory, szRewriteDirectory);
	cController.Begin();
	cNamedIndexes.Init(&cController, 10 MB, IWT_No);

	cNamedIndexes.Add(45LL, "Berty");
	cNamedIndexes.Add(73LL, "Alfred");
	cNamedIndexes.Add(19LL, "Camilla");
	cNamedIndexes.Add(20LL, "Wordsworth");

	cNamedIndexes.Add(66LL, "Alicia");
	cNamedIndexes.Add(67LL, "Aardvark");
	cNamedIndexes.Add(68LL, "Alfredo");
	cNamedIndexes.Add(69LL, "Play-dough");

	cNamedIndexes.Add(01LL, "Zynaps");

	AssertLongLongInt(9, cNamedIndexes.NumElements());

	bResult = cNamedIndexes.Remove("Aardvark");
	AssertTrue(bResult);

	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Aardvark"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(68LL, cNamedIndexes.GetIndex("Alfredo"));
	AssertLongLongInt(66LL, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(69LL, cNamedIndexes.GetIndex("Play-dough"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(01LL, cNamedIndexes.GetIndex("Zynaps"));

	AssertLongLongInt(8, cNamedIndexes.NumElements());

	bResult = cNamedIndexes.Remove("Aardvark");
	AssertFalse(bResult);
	AssertLongLongInt(8, cNamedIndexes.NumElements());

	AssertTrue(cNamedIndexes.Remove("Alicia"));
	AssertTrue(cNamedIndexes.Remove("Alfredo"));
	AssertLongLongInt(6, cNamedIndexes.NumElements());

	AssertTrue(cNamedIndexes.Remove("Play-dough"));

	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Alfredo"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Play-dough"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(01LL, cNamedIndexes.GetIndex("Zynaps"));
	AssertLongLongInt(5, cNamedIndexes.NumElements());

	AssertTrue(cNamedIndexes.Remove("Alfred"));
	AssertTrue(cNamedIndexes.Remove("Berty"));
	AssertTrue(cNamedIndexes.Remove("Camilla"));
	AssertTrue(cNamedIndexes.Remove("Wordsworth"));
	AssertTrue(cNamedIndexes.Remove("Zynaps"));

	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Zynaps"));
	AssertLongLongInt(0, cNamedIndexes.NumElements());

	cNamedIndexes.Add(45LL, "Berty");
	AssertLongLongInt(1, cNamedIndexes.NumElements());
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertTrue(cNamedIndexes.Remove("Berty"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(0, cNamedIndexes.NumElements());

	cNamedIndexes.Flush();
	AssertTrue(cController.End());
	cNamedIndexes.Kill();
	cController.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexesCacheEviction(void)
{
	CNamedIndexes				cNamedIndexes;
	CDurableFileController		cController;
	CFileUtil					cFileUtil;
	BOOL						bResult;
	char						szDirectory[] = "NamedIndexes" _FS_ "3";
	char						szRewriteDirectory[] = "_NamedIndexes" _FS_ "3";

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewriteDirectory, NULL);

	cController.Init(szDirectory, szRewriteDirectory);
	cController.Begin();
	cNamedIndexes.Init(&cController, 8192, IWT_No);

	AssertLongLongInt(0, cNamedIndexes.NumElements());

	AssertTrue(cNamedIndexes.Add(45LL, "Berty"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(1, cNamedIndexes.NumElements());

	AssertTrue(cNamedIndexes.Add(73LL, "Alfred"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex(""));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Ax"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex((char*)NULL));

	AssertTrue(cNamedIndexes.Add(19LL, "Camilla"));
	AssertTrue(cNamedIndexes.Add(20LL, "Wordsworth"));
	AssertLongLongInt(4, cNamedIndexes.NumElements());
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));


	AssertTrue(cNamedIndexes.Add(66LL, "Alicia"));
	AssertLongLongInt(5, cNamedIndexes.NumElements());

	AssertLongLongInt(66LL, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));

	AssertTrue(cNamedIndexes.Add(67LL, "Aardvark"));
	AssertTrue(cNamedIndexes.Add(68LL, "Alfredo"));
	AssertTrue(cNamedIndexes.Add(69LL, "Play-dough"));
	AssertLongLongInt(67LL, cNamedIndexes.GetIndex("Aardvark"));
	AssertLongLongInt(66LL, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(68LL, cNamedIndexes.GetIndex("Alfredo"));
	AssertLongLongInt(69LL, cNamedIndexes.GetIndex("Play-dough"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));

	AssertTrue(cNamedIndexes.Add(01LL, "Zynaps"));
	AssertLongLongInt(66LL, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(67LL, cNamedIndexes.GetIndex("Aardvark"));
	AssertLongLongInt(68LL, cNamedIndexes.GetIndex("Alfredo"));
	AssertLongLongInt(69LL, cNamedIndexes.GetIndex("Play-dough"));
	AssertLongLongInt(01LL, cNamedIndexes.GetIndex("Zynaps"));
	AssertLongLongInt(9, cNamedIndexes.NumElements());

	bResult = cNamedIndexes.Add(88LL, "Play-dough");
	AssertFalse(bResult);

	AssertLongLongInt(9, cNamedIndexes.NumElements());

	cNamedIndexes.Flush();
	AssertTrue(cController.End());
	cNamedIndexes.Kill();
	cController.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexesLoad(void)
{
	CNamedIndexes			cNamedIndexes;
	CDurableFileController	cController;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "NamedIndexes" _FS_ "4";
	char					szRewriteDirectory[] = "_NamedIndexes" _FS_ "4";

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewriteDirectory, NULL);

	cController.Init(szDirectory, szRewriteDirectory);
	AssertTrue(cController.Begin());
	cNamedIndexes.Init(&cController, 10 MB, IWT_No);

	cNamedIndexes.Add(1LL, "Arthur Miller");
	cNamedIndexes.Add(2LL, "systema skeletale");
	cNamedIndexes.Add(3LL, "roe");
	cNamedIndexes.Add(4LL, "order Plumbaginales Melba aldicarb");
	cNamedIndexes.Add(5LL, "asphyxiate");
	cNamedIndexes.Add(6LL, "Fonseca Bay Piaget Salt tomato plant");
	cNamedIndexes.Add(7LL, "thoracic vertebra");
	cNamedIndexes.Add(8LL, "LL75");
	cNamedIndexes.Add(9LL, "Calendrer");
	cNamedIndexes.Add(10LL, "zone refining refashion butter up");
	cNamedIndexes.Add(11LL, "Chopin Dicranaceae transmountain insentient");
	cNamedIndexes.Add(12LL, "Recipes Kerchiefs 32TX");
	cNamedIndexes.Add(13LL, "factor V domestic relations");
	cNamedIndexes.Add(14LL, "bedum ?");
	cNamedIndexes.Add(15LL, "gauche");
	cNamedIndexes.Add(16LL, "takeoff breakup value Tenuifolious magnitude");
	cNamedIndexes.Add(17LL, "Forisfamiliated");
	cNamedIndexes.Add(18LL, "amphibious bulk liquid transfer system");
	cNamedIndexes.Add(19LL, "otoscope");
	cNamedIndexes.Add(20LL, "impel Christmas");
	cNamedIndexes.Add(21LL, "universalise rose fever IL59 Europe");

	AssertLongLongInt(1LL, cNamedIndexes.GetIndex("Arthur Miller"));
	AssertLongLongInt(2LL, cNamedIndexes.GetIndex("systema skeletale"));
	AssertLongLongInt(3LL, cNamedIndexes.GetIndex("roe"));
	AssertLongLongInt(4LL, cNamedIndexes.GetIndex("order Plumbaginales Melba aldicarb"));
	AssertLongLongInt(5LL, cNamedIndexes.GetIndex("asphyxiate"));
	AssertLongLongInt(6LL, cNamedIndexes.GetIndex("Fonseca Bay Piaget Salt tomato plant"));
	AssertLongLongInt(7LL, cNamedIndexes.GetIndex("thoracic vertebra"));
	AssertLongLongInt(8LL, cNamedIndexes.GetIndex("LL75"));
	AssertLongLongInt(9LL, cNamedIndexes.GetIndex("Calendrer"));
	AssertLongLongInt(10LL, cNamedIndexes.GetIndex("zone refining refashion butter up"));
	AssertLongLongInt(11LL, cNamedIndexes.GetIndex("Chopin Dicranaceae transmountain insentient"));
	AssertLongLongInt(12LL, cNamedIndexes.GetIndex("Recipes Kerchiefs 32TX"));
	AssertLongLongInt(13LL, cNamedIndexes.GetIndex("factor V domestic relations"));
	AssertLongLongInt(14LL, cNamedIndexes.GetIndex("bedum ?"));
	AssertLongLongInt(15LL, cNamedIndexes.GetIndex("gauche"));
	AssertLongLongInt(16LL, cNamedIndexes.GetIndex("takeoff breakup value Tenuifolious magnitude"));
	AssertLongLongInt(17LL, cNamedIndexes.GetIndex("Forisfamiliated"));
	AssertLongLongInt(18LL, cNamedIndexes.GetIndex("amphibious bulk liquid transfer system"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("otoscope"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("impel Christmas"));
	AssertLongLongInt(21LL, cNamedIndexes.GetIndex("universalise rose fever IL59 Europe"));

	cNamedIndexes.Flush();
	AssertTrue(cController.End());
	cNamedIndexes.Kill();
	cController.Kill();

	cController.Init(szDirectory, szRewriteDirectory);
	AssertTrue(cController.Begin());
	cNamedIndexes.Init(&cController, 10 MB, IWT_No);

	AssertLongLongInt(1LL, cNamedIndexes.GetIndex("Arthur Miller"));
	AssertLongLongInt(2LL, cNamedIndexes.GetIndex("systema skeletale"));
	AssertLongLongInt(3LL, cNamedIndexes.GetIndex("roe"));
	AssertLongLongInt(4LL, cNamedIndexes.GetIndex("order Plumbaginales Melba aldicarb"));
	AssertLongLongInt(5LL, cNamedIndexes.GetIndex("asphyxiate"));
	AssertLongLongInt(6LL, cNamedIndexes.GetIndex("Fonseca Bay Piaget Salt tomato plant"));
	AssertLongLongInt(7LL, cNamedIndexes.GetIndex("thoracic vertebra"));
	AssertLongLongInt(8LL, cNamedIndexes.GetIndex("LL75"));
	AssertLongLongInt(9LL, cNamedIndexes.GetIndex("Calendrer"));
	AssertLongLongInt(10LL, cNamedIndexes.GetIndex("zone refining refashion butter up"));
	AssertLongLongInt(11LL, cNamedIndexes.GetIndex("Chopin Dicranaceae transmountain insentient"));
	AssertLongLongInt(12LL, cNamedIndexes.GetIndex("Recipes Kerchiefs 32TX"));
	AssertLongLongInt(13LL, cNamedIndexes.GetIndex("factor V domestic relations"));
	AssertLongLongInt(14LL, cNamedIndexes.GetIndex("bedum ?"));
	AssertLongLongInt(15LL, cNamedIndexes.GetIndex("gauche"));
	AssertLongLongInt(16LL, cNamedIndexes.GetIndex("takeoff breakup value Tenuifolious magnitude"));
	AssertLongLongInt(17LL, cNamedIndexes.GetIndex("Forisfamiliated"));
	AssertLongLongInt(18LL, cNamedIndexes.GetIndex("amphibious bulk liquid transfer system"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("otoscope"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("impel Christmas"));
	AssertLongLongInt(21LL, cNamedIndexes.GetIndex("universalise rose fever IL59 Europe"));

	AssertLongLongInt(1LL, cNamedIndexes.GetIndex("Arthur Miller"));
	AssertLongLongInt(14LL, cNamedIndexes.GetIndex("bedum ?"));
	AssertLongLongInt(21LL, cNamedIndexes.GetIndex("universalise rose fever IL59 Europe"));
	AssertLongLongInt(3LL, cNamedIndexes.GetIndex("roe"));
	AssertLongLongInt(16LL, cNamedIndexes.GetIndex("takeoff breakup value Tenuifolious magnitude"));
	AssertLongLongInt(5LL, cNamedIndexes.GetIndex("asphyxiate"));
	AssertLongLongInt(18LL, cNamedIndexes.GetIndex("amphibious bulk liquid transfer system"));
	AssertLongLongInt(7LL, cNamedIndexes.GetIndex("thoracic vertebra"));
	AssertLongLongInt(9LL, cNamedIndexes.GetIndex("Calendrer"));
	AssertLongLongInt(13LL, cNamedIndexes.GetIndex("factor V domestic relations"));
	AssertLongLongInt(15LL, cNamedIndexes.GetIndex("gauche"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("impel Christmas"));
	AssertLongLongInt(10LL, cNamedIndexes.GetIndex("zone refining refashion butter up"));
	AssertLongLongInt(12LL, cNamedIndexes.GetIndex("Recipes Kerchiefs 32TX"));
	AssertLongLongInt(8LL, cNamedIndexes.GetIndex("LL75"));
	AssertLongLongInt(17LL, cNamedIndexes.GetIndex("Forisfamiliated"));
	AssertLongLongInt(6LL, cNamedIndexes.GetIndex("Fonseca Bay Piaget Salt tomato plant"));
	AssertLongLongInt(4LL, cNamedIndexes.GetIndex("order Plumbaginales Melba aldicarb"));
	AssertLongLongInt(11LL, cNamedIndexes.GetIndex("Chopin Dicranaceae transmountain insentient"));
	AssertLongLongInt(2LL, cNamedIndexes.GetIndex("systema skeletale"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("otoscope"));

	cNamedIndexes.Flush();
	AssertTrue(cController.End());
	cNamedIndexes.Kill();
	cController.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexes(void)
{
	CFileUtil	cFileUtil;

	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	cFileUtil.RemoveDir("NamedIndexes");

	TestNamedIndexesAdd();
	TestNamedIndexesRemove();
	TestNamedIndexesCacheEviction();
	TestNamedIndexesLoad();

	cFileUtil.RemoveDir("NamedIndexes");

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

