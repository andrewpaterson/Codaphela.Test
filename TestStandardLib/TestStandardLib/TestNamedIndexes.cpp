#include "CoreLib/DurableFileController.h"
#include "StandardLib/NamedIndexesFileDumper.h"
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
	cController.Begin();
	cNamedIndexes.Load();

	AssertLongLongInt(0, cNamedIndexes.NumNames());

	cNamedIndexes.Add(45LL, "Berty");
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(1, cNamedIndexes.NumNames());

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
	AssertLongLongInt(4, cNamedIndexes.NumNames());


	cNamedIndexes.Add(66LL, "Alicia");
	AssertLongLongInt(66LL, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(5, cNamedIndexes.NumNames());


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
	AssertLongLongInt(9, cNamedIndexes.NumNames());

	bResult = cNamedIndexes.Add(88LL, "Play-dough");
	AssertFalse(bResult);

	AssertLongLongInt(9, cNamedIndexes.NumNames());

	cNamedIndexes.Save();
	cController.End();
	cNamedIndexes.Kill();
	cController.Kill();
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
	cController.Begin();
	cNamedIndexes.Load();

	cNamedIndexes.Add(45LL, "Berty");
	cNamedIndexes.Add(73LL, "Alfred");
	cNamedIndexes.Add(19LL, "Camilla");
	cNamedIndexes.Add(20LL, "Wordsworth");

	cNamedIndexes.Add(66LL, "Alicia");
	cNamedIndexes.Add(67LL, "Aardvark");
	cNamedIndexes.Add(68LL, "Alfredo");
	cNamedIndexes.Add(69LL, "Play-dough");

	cNamedIndexes.Add(01LL, "Zynaps");

	AssertLongLongInt(9, cNamedIndexes.NumNames());

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

	AssertLongLongInt(8, cNamedIndexes.NumNames());

	bResult = cNamedIndexes.Remove("Aardvark");
	AssertFalse(bResult);
	AssertLongLongInt(8, cNamedIndexes.NumNames());

	AssertTrue(cNamedIndexes.Remove("Alicia"));
	AssertTrue(cNamedIndexes.Remove("Alfredo"));
	AssertLongLongInt(6, cNamedIndexes.NumNames());

	AssertTrue(cNamedIndexes.Remove("Play-dough"));

	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Alfredo"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Play-dough"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(01LL, cNamedIndexes.GetIndex("Zynaps"));
	AssertLongLongInt(5, cNamedIndexes.NumNames());

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
	AssertLongLongInt(0, cNamedIndexes.NumNames());

	cNamedIndexes.Add(45LL, "Berty");
	AssertLongLongInt(1, cNamedIndexes.NumNames());
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertTrue(cNamedIndexes.Remove("Berty"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(0, cNamedIndexes.NumNames());

	cNamedIndexes.Save();
	cController.End();
	cNamedIndexes.Kill();
	cController.Kill();
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
	cNamedIndexes.Load();

	AssertLongLongInt(0, cNamedIndexes.NumNames());

	cNamedIndexes.Add(45LL, "Berty");
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(1, cNamedIndexes.NumNames());

	cNamedIndexes.Add(73LL, "Alfred");
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex(""));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Ax"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex((char*)NULL));

	cNamedIndexes.Add(19LL, "Camilla");
	cNamedIndexes.Add(20LL, "Wordsworth");
	AssertLongLongInt(4, cNamedIndexes.NumNames());
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));

	cBlockPtrs.Init(4);
	cNamedIndexes.TestGetPotentialContainingBlocks("Berty", &cBlockPtrs);
	AssertLongLongInt(1, cBlockPtrs.NumElements());
	AssertString("Alfred", (*cBlockPtrs.Get(0))->GetFirst());
	AssertString("Wordsworth", (*cBlockPtrs.Get(0))->GetLast());
	AssertTrue((*cBlockPtrs.Get(0))->IsCached());
	cBlockPtrs.Kill();

	cNamedIndexes.Add(66LL, "Alicia");
	AssertLongLongInt(5, cNamedIndexes.NumNames());

	cBlockPtrs.Init(4);
	cNamedIndexes.TestGetPotentialContainingBlocks("Alicia", &cBlockPtrs);
	AssertLongLongInt(2, cBlockPtrs.NumElements());
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
	AssertLongLongInt(9, cNamedIndexes.NumNames());

	bResult = cNamedIndexes.Add(88LL, "Play-dough");
	AssertFalse(bResult);

	AssertLongLongInt(9, cNamedIndexes.NumNames());

	cNamedIndexes.Save();
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
	cNamedIndexes.Load();

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

	cNamedIndexes.Save();
	cController.End();
	cNamedIndexes.Kill();
	cController.Kill();


	//Make sure the files appear on disk as expected.

	CChars	sz;

	sz.Init();
	DumpNamedIndexesFile(&sz, "NamedIndexes/4/32_0.NAM", 32, 6);
	AssertString("\
NamedIndexes/4/32_0.NAM\n\
-----------------------\n\
   0:      1 -> Arthur Miller\n\
   1:      5 -> asphyxiate\n\
   2:      8 -> LL75\n\
   3:      3 -> roe\n\
   4:      2 -> systema skeletale\n\
   5:      7 -> thoracic vertebra\n\
\n\
   6:     14 -> bedum ?\n\
   7:      9 -> Calendrer\n\
   8:     17 -> Forisfamiliated\n\
   9:     15 -> gauche\n\
  10:     19 -> otoscope\n\
  11:     12 -> Recipes Kerchiefs 32TX\n\
\n\
  12:     20 -> impel Christmas\n\
  13:      0 -> \n\
  14:      0 -> \n\
  15:      0 -> \n\
  16:      0 -> \n\
  17:      0 -> \n\
-----------------------\n", sz.Text());
	sz.Kill();

	sz.Init();
	DumpNamedIndexesFile(&sz, "NamedIndexes/4/64_0.NAM", 64, 6);

	AssertString("\
NamedIndexes/4/64_0.NAM\n\
-----------------------\n\
   0:     11 -> Chopin Dicranaceae transmountain insentient\n\
   1:     13 -> factor V domestic relations\n\
   2:      6 -> Fonseca Bay Piaget Salt tomato plant\n\
   3:      4 -> order Plumbaginales Melba aldicarb\n\
   4:     16 -> takeoff breakup value Tenuifolious magnitude\n\
   5:     10 -> zone refining refashion butter up\n\
\n\
   6:     18 -> amphibious bulk liquid transfer system\n\
   7:     21 -> universalise rose fever IL59 Europe\n\
   8:      0 -> \n\
   9:      0 -> \n\
  10:      0 -> \n\
  11:      0 -> \n\
-----------------------\n", sz.Text());
	sz.Kill();

	cController.Init("NamedIndexes/4", TRUE);
	cNamedIndexes.Init(&cController, 512, 6);
	cController.Begin();
	cNamedIndexes.Load();
	
	AssertLongLongInt(1LL, cNamedIndexes.GetIndex("Arthur Miller"));

	cNamedIndexes.Save();
	cController.End();
	cNamedIndexes.Kill();
	cController.Kill();
}

/*

NamedIndexes/4/32_0.NAM
-----------------------
 0:      1 -> Arthur Miller
 1:      5 -> asphyxiate
 2:      8 -> LL75
 3:      3 -> roe
 4:      2 -> systema skeletale
 5:      7 -> thoracic vertebra
 
 6:     14 -> bedum ?
 7:      9 -> Calendrer
 8:     17 -> Forisfamiliated
 9:     15 -> gauche
10:     19 -> otoscope
11:     12 -> Recipes Kerchiefs 32TX

12:     20 -> impel Christmas
13:      0 -> 
14:      0 -> 
15:      0 -> 
16:      0 -> 
17:      0 -> 
-----------------------

NamedIndexes/4/64_0.NAM
-----------------------
 0:     11 -> Chopin Dicranaceae transmountain insentient
 1:     13 -> factor V domestic relations
 2:      6 -> Fonseca Bay Piaget Salt tomato plant
 3:      4 -> order Plumbaginales Melba aldicarb
 4:     16 -> takeoff breakup value Tenuifolious magnitude
 5:     10 -> zone refining refashion butter up
 
 6:     18 -> amphibious bulk liquid transfer system
 7:     21 -> universalise rose fever IL59 Europe
 8:      0 -> 
 9:      0 -> 
10:      0 -> 
11:      0 -> 
-----------------------

*/


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
	TestLoad();

	cFileUtil.RemoveDir("NamedIndexes");

	TestStatistics();
}

