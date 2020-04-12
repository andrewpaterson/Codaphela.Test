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

	cNamedIndexes.Put("Berty", 45LL);
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(1, cNamedIndexes.NumElements());

	cNamedIndexes.Put("Alfred", 73LL);
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex(""));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Ax"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex((char*)NULL));

	cNamedIndexes.Put("Camilla", 19LL);
	cNamedIndexes.Put("Wordsworth", 20LL);
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(4, cNamedIndexes.NumElements());


	cNamedIndexes.Put("Alicia", 66LL);
	AssertLongLongInt(66LL, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(5, cNamedIndexes.NumElements());


	cNamedIndexes.Put("Aardvark", 67LL);
	cNamedIndexes.Put("Alfredo", 68LL);
	bResult = cNamedIndexes.Put("Play-dough", 69LL);
	cNamedIndexes.Put("Zynaps", 01LL);
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

	bResult = cNamedIndexes.Put("Play-dough", 88LL);
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

	cNamedIndexes.Put("Berty", 45LL);
	cNamedIndexes.Put("Alfred", 73LL);
	cNamedIndexes.Put("Camilla", 19LL);
	cNamedIndexes.Put("Wordsworth", 20LL);

	cNamedIndexes.Put("Alicia", 66LL);
	cNamedIndexes.Put("Aardvark", 67LL);
	cNamedIndexes.Put("Alfredo", 68LL);
	cNamedIndexes.Put("Play-dough", 69LL);

	cNamedIndexes.Put("Zynaps", 01LL);

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

	cNamedIndexes.Put("Berty", 45LL);
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

	AssertTrue(cNamedIndexes.Put("Berty", 45LL));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(1, cNamedIndexes.NumElements());

	AssertTrue(cNamedIndexes.Put("Alfred", 73LL));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex(""));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Ax"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex((char*)NULL));

	AssertTrue(cNamedIndexes.Put("Camilla", 19LL));
	AssertTrue(cNamedIndexes.Put("Wordsworth", 20LL));
	AssertLongLongInt(4, cNamedIndexes.NumElements());
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));


	AssertTrue(cNamedIndexes.Put("Alicia", 66LL));
	AssertLongLongInt(5, cNamedIndexes.NumElements());

	AssertLongLongInt(66LL, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));

	AssertTrue(cNamedIndexes.Put("Aardvark", 67LL));
	AssertTrue(cNamedIndexes.Put("Alfredo", 68LL));
	AssertTrue(cNamedIndexes.Put("Play-dough", 69LL));
	AssertLongLongInt(67LL, cNamedIndexes.GetIndex("Aardvark"));
	AssertLongLongInt(66LL, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(68LL, cNamedIndexes.GetIndex("Alfredo"));
	AssertLongLongInt(69LL, cNamedIndexes.GetIndex("Play-dough"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));

	AssertTrue(cNamedIndexes.Put("Zynaps", 01LL));
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

	bResult = cNamedIndexes.Put("Play-dough", 88LL);
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

	cNamedIndexes.Put("Arthur Miller", 1LL);
	cNamedIndexes.Put("systema skeletale", 2LL);
	cNamedIndexes.Put("roe", 3LL);
	cNamedIndexes.Put("order Plumbaginales Melba aldicarb", 4LL);
	cNamedIndexes.Put("asphyxiate", 5LL);
	cNamedIndexes.Put("Fonseca Bay Piaget Salt tomato plant", 6LL);
	cNamedIndexes.Put("thoracic vertebra", 7LL);
	cNamedIndexes.Put("LL75", 8LL);
	cNamedIndexes.Put("Calendrer", 9LL);
	cNamedIndexes.Put("zone refining refashion butter up", 10LL);
	cNamedIndexes.Put("Chopin Dicranaceae transmountain insentient", 11LL);
	cNamedIndexes.Put("Recipes Kerchiefs 32TX", 12LL);
	cNamedIndexes.Put("factor V domestic relations", 13LL);
	cNamedIndexes.Put("bedum ?", 14LL);
	cNamedIndexes.Put("gauche", 15LL);
	cNamedIndexes.Put("takeoff breakup value Tenuifolious magnitude", 16LL);
	cNamedIndexes.Put("Forisfamiliated", 17LL);
	cNamedIndexes.Put("amphibious bulk liquid transfer system", 18LL);
	cNamedIndexes.Put("otoscope", 19LL);
	cNamedIndexes.Put("impel Christmas", 20LL);
	cNamedIndexes.Put("universalise rose fever IL59 Europe", 21LL);

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

