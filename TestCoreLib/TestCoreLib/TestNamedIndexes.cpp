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
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(1, cNamedIndexes.NumElements());

	cNamedIndexes.Put("Alfred", 73LL);
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get(""));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Ax"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get((char*)NULL));

	cNamedIndexes.Put("Camilla", 19LL);
	cNamedIndexes.Put("Wordsworth", 20LL);
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("Wordsworth"));
	AssertLongLongInt(4, cNamedIndexes.NumElements());


	cNamedIndexes.Put("Alicia", 66LL);
	AssertLongLongInt(66LL, cNamedIndexes.Get("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("Wordsworth"));
	AssertLongLongInt(5, cNamedIndexes.NumElements());


	cNamedIndexes.Put("Aardvark", 67LL);
	cNamedIndexes.Put("Alfredo", 68LL);
	bResult = cNamedIndexes.Put("Play-dough", 69LL);
	cNamedIndexes.Put("Zynaps", 01LL);
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

	cNamedIndexes.Put("Berty", 45LL);
	AssertLongLongInt(1, cNamedIndexes.NumElements());
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertTrue(cNamedIndexes.Remove("Berty"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Berty"));
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
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(1, cNamedIndexes.NumElements());

	AssertTrue(cNamedIndexes.Put("Alfred", 73LL));
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get(""));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get("Ax"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.Get((char*)NULL));

	AssertTrue(cNamedIndexes.Put("Camilla", 19LL));
	AssertTrue(cNamedIndexes.Put("Wordsworth", 20LL));
	AssertLongLongInt(4, cNamedIndexes.NumElements());
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("Wordsworth"));


	AssertTrue(cNamedIndexes.Put("Alicia", 66LL));
	AssertLongLongInt(5, cNamedIndexes.NumElements());

	AssertLongLongInt(66LL, cNamedIndexes.Get("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("Wordsworth"));

	AssertTrue(cNamedIndexes.Put("Aardvark", 67LL));
	AssertTrue(cNamedIndexes.Put("Alfredo", 68LL));
	AssertTrue(cNamedIndexes.Put("Play-dough", 69LL));
	AssertLongLongInt(67LL, cNamedIndexes.Get("Aardvark"));
	AssertLongLongInt(66LL, cNamedIndexes.Get("Alicia"));
	AssertLongLongInt(68LL, cNamedIndexes.Get("Alfredo"));
	AssertLongLongInt(69LL, cNamedIndexes.Get("Play-dough"));
	AssertLongLongInt(73LL, cNamedIndexes.Get("Alfred"));
	AssertLongLongInt(45LL, cNamedIndexes.Get("Berty"));
	AssertLongLongInt(19LL, cNamedIndexes.Get("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.Get("Wordsworth"));

	AssertTrue(cNamedIndexes.Put("Zynaps", 01LL));
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

	cController.Init(szDirectory, szRewriteDirectory);
	AssertTrue(cController.Begin());
	cNamedIndexes.Init(&cController, 10 MB, IWT_No);

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

