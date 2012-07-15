#include "CoreLib/DurableFileController.h"
#include "StandardLib/NamedIndexes.h"
#include "StandardLib/BaseObject.h"
#include "TestLib/Assert.h"
#include "TestNamedIndexes.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAdd(void)
{
	CNamedIndexes			cNamedIndexes;
	CDurableFileController	cController;
	CFileUtil				cFileUtil;
	BOOL					bResult;

	cFileUtil.MakeDir("NamedIndexes/1");
	cController.Init("NamedIndexes/1", TRUE);
	cNamedIndexes.Init(&cController, 10 MB, 4);

	AssertInt(0, cNamedIndexes.NumNames());

	cNamedIndexes.Add(45LL, "Berty");
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertInt(1, cNamedIndexes.NumNames());

	cNamedIndexes.Add(73LL, "Alfred");
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex(""));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Ax"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex((char*)NULL));

	cNamedIndexes.Add(19LL, "Camilla");
	cNamedIndexes.Add(20LL, "Wordsworth");
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertInt(4, cNamedIndexes.NumNames());


	cNamedIndexes.Add(66LL, "Alicia");
	AssertLongLongInt(66LL, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertInt(5, cNamedIndexes.NumNames());


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
	AssertInt(9, cNamedIndexes.NumNames());

	bResult = cNamedIndexes.Add(88LL, "Play-dough");
	AssertFalse(bResult);

	AssertInt(9, cNamedIndexes.NumNames());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRemove(void)
{
	CNamedIndexes			cNamedIndexes;
	CDurableFileController	cController;
	CFileUtil				cFileUtil;
	BOOL					bResult;

	cFileUtil.MakeDir("NamedIndexes/2");
	cController.Init("NamedIndexes/2", TRUE);
	cNamedIndexes.Init(&cController, 10 MB, 4);

	cNamedIndexes.Add(45LL, "Berty");
	cNamedIndexes.Add(73LL, "Alfred");
	cNamedIndexes.Add(19LL, "Camilla");
	cNamedIndexes.Add(20LL, "Wordsworth");

	cNamedIndexes.Add(66LL, "Alicia");
	cNamedIndexes.Add(67LL, "Aardvark");
	cNamedIndexes.Add(68LL, "Alfredo");
	cNamedIndexes.Add(69LL, "Play-dough");

	cNamedIndexes.Add(01LL, "Zynaps");

	AssertInt(9, cNamedIndexes.NumNames());

	bResult = cNamedIndexes.Remove("Aardvark");
	AssertTrue(bResult);

	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Aardvark"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(68LL, cNamedIndexes.GetIndex("Alfredo"));
	AssertLongLongInt(66LL, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(69LL, cNamedIndexes.GetIndex("Play-dough"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(01LL, cNamedIndexes.GetIndex("Zynaps"));

	AssertInt(8, cNamedIndexes.NumNames());

	bResult = cNamedIndexes.Remove("Aardvark");
	AssertFalse(bResult);
	AssertInt(8, cNamedIndexes.NumNames());

	AssertTrue(cNamedIndexes.Remove("Alicia"));
	AssertTrue(cNamedIndexes.Remove("Alfredo"));
	AssertInt(6, cNamedIndexes.NumNames());

	AssertTrue(cNamedIndexes.Remove("Play-dough"));

	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Alfredo"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Play-dough"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(01LL, cNamedIndexes.GetIndex("Zynaps"));
	AssertInt(5, cNamedIndexes.NumNames());

	AssertTrue(cNamedIndexes.Remove("Alfred"));
	AssertTrue(cNamedIndexes.Remove("Berty"));
	AssertTrue(cNamedIndexes.Remove("Camilla"));
	AssertTrue(cNamedIndexes.Remove("Wordsworth"));
	AssertTrue(cNamedIndexes.Remove("Zynaps"));

	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Zynaps"));
	AssertInt(0, cNamedIndexes.NumNames());

	cNamedIndexes.Add(45LL, "Berty");
	AssertInt(1, cNamedIndexes.NumNames());
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertTrue(cNamedIndexes.Remove("Berty"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Berty"));
	AssertInt(0, cNamedIndexes.NumNames());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCacheEviction(void)
{
	CNamedIndexes				cNamedIndexes;
	CDurableFileController		cController;
	CFileUtil					cFileUtil;
	BOOL						bResult;
	CArrayNamedIndexesBlockPtr	cBlockPtrs;

	cFileUtil.MakeDir("NamedIndexes/3");
	cController.Init("NamedIndexes/3", TRUE);
	cNamedIndexes.Init(&cController, 256, 4);
	cController.Begin();

	AssertInt(0, cNamedIndexes.NumNames());

	cNamedIndexes.Add(45LL, "Berty");
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertInt(1, cNamedIndexes.NumNames());

	cNamedIndexes.Add(73LL, "Alfred");
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex(""));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Ax"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex((char*)NULL));

	cNamedIndexes.Add(19LL, "Camilla");
	cNamedIndexes.Add(20LL, "Wordsworth");
	AssertInt(4, cNamedIndexes.NumNames());
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));

	cBlockPtrs.Init(4);
	cNamedIndexes.TestGetPotentialContainingBlocks("Berty", &cBlockPtrs);
	AssertInt(1, cBlockPtrs.NumElements());
	AssertString("Alfred", (*cBlockPtrs.Get(0))->GetFirst());
	AssertString("Wordsworth", (*cBlockPtrs.Get(0))->GetLast());
	AssertTrue((*cBlockPtrs.Get(0))->IsCached());
	cBlockPtrs.Kill();

	cNamedIndexes.Add(66LL, "Alicia");
	AssertInt(5, cNamedIndexes.NumNames());

	cBlockPtrs.Init(4);
	cNamedIndexes.TestGetPotentialContainingBlocks("Alicia", &cBlockPtrs);
	AssertInt(2, cBlockPtrs.NumElements());
	AssertString("Alfred", (*cBlockPtrs.Get(0))->GetFirst());
	AssertString("Wordsworth", (*cBlockPtrs.Get(0))->GetLast());
	AssertFalse((*cBlockPtrs.Get(0))->IsCached());
	AssertString("Alicia", (*cBlockPtrs.Get(1))->GetFirst());
	AssertString("Alicia", (*cBlockPtrs.Get(1))->GetLast());
	AssertTrue((*cBlockPtrs.Get(1))->IsCached());
	cBlockPtrs.Kill();

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
	AssertInt(9, cNamedIndexes.NumNames());

	bResult = cNamedIndexes.Add(88LL, "Play-dough");
	AssertFalse(bResult);

	AssertInt(9, cNamedIndexes.NumNames());

	cController.End();
	cNamedIndexes.Kill();
	cController.Kill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLoad(void)
{
	CNamedIndexes				cNamedIndexes;
	CDurableFileController		cController;
	CFileUtil					cFileUtil;
	CNamedIndexesBlocks*		pcBlock32;
	CNamedIndexesBlocks*		pcBlock64;

	cFileUtil.MakeDir("NamedIndexes/4");
	cController.Init("NamedIndexes/4", TRUE);
	cNamedIndexes.Init(&cController, 512, 6);
	cController.Begin();

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

	pcBlock32 = cNamedIndexes.TestGetBlock(32);
	pcBlock64 = cNamedIndexes.TestGetBlock(64);

	cController.End();
	cNamedIndexes.Kill();

	
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexes(void)
{
	CFileUtil	cFileUtil;

	BeginTests();

	cFileUtil.RemoveDir("NamedIndexes");

	TestAdd();
	TestRemove();
	TestCacheEviction();
	//TestLoad();

	cFileUtil.RemoveDir("NamedIndexes");

	TestStatistics();
}

