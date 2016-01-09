#include "BaseLib/Define.h"
#include "CoreLib/DurableFileController.h"
#include "StandardLib/NamedIndexesFileDumper.h"
#include "StandardLib/NamedIndexes.h"
#include "StandardLib/BaseObject.h"
#include "StandardLib/NamedIndexesOptimiser.h"
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
	char					szDirectory[] = "NamedIndexes"_FS_"1";

	cFileUtil.MakeDir(szDirectory);

	cController.Init(szDirectory, szDirectory, TRUE);
	cNamedIndexes.Init(&cController, 10 MB, 4);
	cController.Begin();
	cNamedIndexes.Open();

	AssertLongLongInt(0, cNamedIndexes.NumNames());

	cNamedIndexes.Add(45LL, "Berty");
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(1, cNamedIndexes.NumNames());

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

	cController.End();
	cNamedIndexes.Close();
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
	char					szDirectory[] = "NamedIndexes"_FS_"2";

	cFileUtil.MakeDir(szDirectory);

	cController.Init(szDirectory, szDirectory, TRUE);
	cNamedIndexes.Init(&cController, 10 MB, 4);
	cController.Begin();
	cNamedIndexes.Open();

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

	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Aardvark"));
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
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Alfredo"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Alicia"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(19LL, cNamedIndexes.GetIndex("Camilla"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Play-dough"));
	AssertLongLongInt(20LL, cNamedIndexes.GetIndex("Wordsworth"));
	AssertLongLongInt(01LL, cNamedIndexes.GetIndex("Zynaps"));
	AssertLongLongInt(5, cNamedIndexes.NumNames());

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
	AssertLongLongInt(0, cNamedIndexes.NumNames());

	cNamedIndexes.Add(45LL, "Berty");
	AssertLongLongInt(1, cNamedIndexes.NumNames());
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertTrue(cNamedIndexes.Remove("Berty"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(0, cNamedIndexes.NumNames());

	cController.End();
	cNamedIndexes.Close();
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
	CArrayNamedIndexesBlockPtr	cBlockPtrs;
	char						szDirectory[] = "NamedIndexes"_FS_"3";

	cFileUtil.MakeDir(szDirectory);
	cController.Init(szDirectory, szDirectory, TRUE);
	cNamedIndexes.Init(&cController, 256, 4);
	cController.Begin();
	cNamedIndexes.Open();

	AssertLongLongInt(0, cNamedIndexes.NumNames());

	AssertTrue(cNamedIndexes.Add(45LL, "Berty"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(1, cNamedIndexes.NumNames());

	AssertTrue(cNamedIndexes.Add(73LL, "Alfred"));
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex(""));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex("Ax"));
	AssertLongLongInt(INVALID_O_INDEX, cNamedIndexes.GetIndex((char*)NULL));

	AssertTrue(cNamedIndexes.Add(19LL, "Camilla"));
	AssertTrue(cNamedIndexes.Add(20LL, "Wordsworth"));
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

	AssertTrue(cNamedIndexes.Add(66LL, "Alicia"));
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

	cController.End();
	cNamedIndexes.Close();
	cNamedIndexes.Kill();
	cController.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexesLoad(void)
{
	CNamedIndexes				cNamedIndexes;
	CDurableFileController		cController;
	CFileUtil					cFileUtil;
	CNamedIndexesBlocks*		pcBlock32;
	CNamedIndexesBlocks*		pcBlock64;
	CNamedIndexesBlock*			pcBlock;
	char						szDirectory[] = "NamedIndexes"_FS_"4";

	cFileUtil.MakeDir(szDirectory);

	cController.Init(szDirectory, szDirectory, TRUE);
	cNamedIndexes.Init(&cController, 512, 6);

	AssertTrue(cController.Begin());
	AssertTrue(cNamedIndexes.Open());

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

	pcBlock32 = cNamedIndexes.GetBlockWithDataSize(32);
	AssertInt(32, pcBlock32->GetDataSize())
	pcBlock64 = cNamedIndexes.GetBlockWithDataSize(64);
	AssertInt(64, pcBlock64->GetDataSize())

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

	AssertTrue(cNamedIndexes.Save());
	AssertTrue(cController.End());
	AssertTrue(cNamedIndexes.Close());

	cNamedIndexes.Kill();
	cController.Kill();


	//Make sure the files appear on disk as expected.

	CChars	sz;

	sz.Init();
	DumpNamedIndexesFile(&sz, "NamedIndexes"_FS_"4"_FS_"32_0.NAM", 32, 6);
	AssertString("\
NamedIndexes"_FS_"4"_FS_"32_0.NAM\n\
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
	DumpNamedIndexesFile(&sz, "NamedIndexes"_FS_"4"_FS_"64_0.NAM", 64, 6);

	AssertString("\
NamedIndexes"_FS_"4"_FS_"64_0.NAM\n\
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

	cController.Init(szDirectory, szDirectory, TRUE);
	cNamedIndexes.Init(&cController, 512, 6);

	AssertTrue(cController.Begin());
	AssertTrue(cNamedIndexes.Open());

	pcBlock32 = cNamedIndexes.GetBlockWithDataSize(32);
	pcBlock = pcBlock32->GetBlock(0);
	AssertString("Arthur Miller", pcBlock->GetFirst());
	AssertString("thoracic vertebra", pcBlock->GetLast());
	pcBlock = pcBlock32->GetBlock(1);
	AssertString("bedum ?", pcBlock->GetFirst());
	AssertString("Recipes Kerchiefs 32TX", pcBlock->GetLast());
	pcBlock = pcBlock32->GetBlock(2);
	AssertString("impel Christmas", pcBlock->GetFirst());
	AssertString("impel Christmas", pcBlock->GetLast());

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

	AssertTrue(cNamedIndexes.Save());
	AssertTrue(cController.End());
	AssertTrue(cNamedIndexes.Close());

	cNamedIndexes.Kill();
	cController.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexesOptimise(void)
{
	CNamedIndexes				cNamedIndexes;
	CDurableFileController		cController;
	CFileUtil					cFileUtil;
	BOOL						bResult;
	CNamedIndexesOptimiser		cOptimiser;
	char						szDirectory[] = "NamedIndexes"_FS_"5";

	cFileUtil.MakeDir(szDirectory);

	cController.Init(szDirectory, szDirectory, TRUE);
	cNamedIndexes.Init(&cController, 20 MB, 4);
	
	AssertTrue(cController.Begin());
	AssertTrue(cNamedIndexes.Open());

	cNamedIndexes.Add(7498273948792334521LL, "Vux/spaceships/Intruder");
	cNamedIndexes.Add(8974598758345774533LL, "Vux/spaceships/Globule");
	cNamedIndexes.Add(9223372036854775807LL, "Vux/spaceships/mega-watt Laser Cannon");
	cNamedIndexes.Add(4376423847623874680LL, "Vux/spaceships/admiral Zex/menagarie-transport-ship");
	cNamedIndexes.Add(5265267321786128702LL, "beast");
	cNamedIndexes.Add(9213567356457326474LL, "Lunar Base");
	cNamedIndexes.Add(1532564672346590234LL, "Earthling/spaceships/Cruiser");
	cNamedIndexes.Add(8465236728346532649LL, "Earthling/spaceships/Dominator");
	cNamedIndexes.Add(3749816364128750931LL, "Earthling/spaceships/surplus cold war nuclear war-heads");
	cNamedIndexes.Add(1532564672346590234LL, "Earthling/spaceships/Point defense Laser system");
	cNamedIndexes.Add(8352145325252165435LL, "Earthling/portraits/Captain Zelnick");
	cNamedIndexes.Add(4678979686897958483LL, "Earthling/slave-shield");
	cNamedIndexes.Add(3576898544356890986LL, "Ur-Quan/Kzer-za/spaceships/Dreadnought/hull");
	cNamedIndexes.Add(7935687324790713849LL, "Ur-Quan/Kzer-za/spaceships/Dreadnought/launch figters/weapons/auto-targetting laser");
	cNamedIndexes.Add(2536710003746523782LL, "Ur-Quan/Kzer-za/spaceships/Dreadnought/launch figters/HierachyCrew");
	cNamedIndexes.Add(4368570346902094536LL, "Ur-Quan/kohr-Ah/spaceships/Marauder/hull");
	cNamedIndexes.Add(8765325424368900113LL, "Ur-Quan/kohr-Ah/spaceships/spinning disk");
	cNamedIndexes.Add(8334658173689122135LL, "Ur-Quan/kohr-Ah/spaceships/ring-of-flames");
	cNamedIndexes.Add(1136946723821981232LL, "Zoq");
	cNamedIndexes.Add(3476827346812023123LL, "Fot");
	cNamedIndexes.Add(6513451892183782132LL, "Pik");
	cNamedIndexes.Add(2384789236478123123LL, "Zoq Fot Pik/Sports/Frungy!");
	cNamedIndexes.Add(5451523689723469328LL, "Spathi/Discriminator");
	cNamedIndexes.Add(3214004623467012364LL, "Spathi/Eluder");
	cNamedIndexes.Add(2841213793444383464LL, "Spathi/characters/captain/Fwiffo");
	cNamedIndexes.Add(4012756480145431273LL, "Spathi/characters/captain/Fwiffo-on-the-moon");
	
	AssertLongLongInt(26, cNamedIndexes.NumNames());

	AssertTrue(cNamedIndexes.Save());
	AssertTrue(cController.End());
	AssertTrue(cNamedIndexes.Close());

	cNamedIndexes.Kill();
	cController.Kill();


	cController.Init(szDirectory, szDirectory, FALSE);  //Not being durable during optimisation is important
	cNamedIndexes.Init(&cController, 20 MB, 4);
	cOptimiser.Init(&cNamedIndexes);
	bResult = cOptimiser.Optimise();
	AssertTrue(bResult);
	cOptimiser.Kill();
	cNamedIndexes.Kill();
	cController.Kill();

	CChars sz;

	sz.Init(); 
	DumpNamedIndexesFile(&sz, "NamedIndexes"_FS_"5"_FS_"32_0.NAM", 32, 4); 
	AssertString("\
NamedIndexes"_FS_"5"_FS_"32_0.NAM\n\
-----------------------\n\
   0: 5265267321786128702 -> beast\n\
   1: 4678979686897958483 -> Earthling/slave-shield\n\
   2: 3476827346812023123 -> Fot\n\
   3: 9213567356457326474 -> Lunar Base\n\
\n\
   4: 6513451892183782132 -> Pik\n\
   5: 5451523689723469328 -> Spathi/Discriminator\n\
   6: 3214004623467012364 -> Spathi/Eluder\n\
   7: 8974598758345774533 -> Vux/spaceships/Globule\n\
\n\
   8: 1136946723821981232 -> Zoq\n\
   9:      0 -> \n\
  10:      0 -> \n\
  11:      0 -> \n\
-----------------------\n", sz.Text());
	sz.Kill();

	sz.Init(); 
	DumpNamedIndexesFile(&sz, "NamedIndexes"_FS_"5"_FS_"64_0.NAM", 64, 4); 
	AssertString("\
NamedIndexes"_FS_"5"_FS_"64_0.NAM\n\
-----------------------\n\
   0: 8352145325252165435 -> Earthling/portraits/Captain Zelnick\n\
   1: 1532564672346590234 -> Earthling/spaceships/Cruiser\n\
   2: 8465236728346532649 -> Earthling/spaceships/Dominator\n\
   3: 1532564672346590234 -> Earthling/spaceships/Point defense Laser system\n\
\n\
   4: 2841213793444383464 -> Spathi/characters/captain/Fwiffo\n\
   5: 4012756480145431273 -> Spathi/characters/captain/Fwiffo-on-the-moon\n\
   6: 4368570346902094536 -> Ur-Quan/kohr-Ah/spaceships/Marauder/hull\n\
   7: 8334658173689122135 -> Ur-Quan/kohr-Ah/spaceships/ring-of-flames\n\
\n\
   8: 8765325424368900113 -> Ur-Quan/kohr-Ah/spaceships/spinning disk\n\
   9: 3576898544356890986 -> Ur-Quan/Kzer-za/spaceships/Dreadnought/hull\n\
  10: 4376423847623874680 -> Vux/spaceships/admiral Zex/menagarie-transport-ship\n\
  11: 7498273948792334521 -> Vux/spaceships/Intruder\n\
\n\
  12: 9223372036854775807 -> Vux/spaceships/mega-watt Laser Cannon\n\
  13: 2384789236478123123 -> Zoq Fot Pik/Sports/Frungy!\n\
  14:      0 -> \n\
  15:      0 -> \n\
-----------------------\n", sz.Text());
	sz.Kill();

	sz.Init(); 
	DumpNamedIndexesFile(&sz, "NamedIndexes"_FS_""_FS_"96_0.NAM", 96, 4); 
	AssertString("\
NamedIndexes"_FS_"5"_FS_"96_0.NAM\n\
-----------------------\n\
   0: 3749816364128750931 -> Earthling/spaceships/surplus cold war nuclear war-heads\n\
   1: 2536710003746523782 -> Ur-Quan/Kzer-za/spaceships/Dreadnought/launch figters/HierachyCrew\n\
   2: 7935687324790713849 -> Ur-Quan/Kzer-za/spaceships/Dreadnought/launch figters/weapons/auto-targetting laser\n\
   3:      0 -> \n\
-----------------------\n", sz.Text());
	sz.Kill();

	AssertFalse(cFileUtil.Exists("NamedIndexes"_FS_"5"_FS_"32_0.NAM.TMP"));
	AssertFalse(cFileUtil.Exists("NamedIndexes"_FS_"5"_FS_"64_0.NAM.TMP"));
	AssertFalse(cFileUtil.Exists("NamedIndexes"_FS_"5"_FS_"96_0.NAM.TMP"));


	cController.Init(szDirectory, szDirectory, TRUE);
	AssertTrue(cController.Begin());
	cNamedIndexes.Init(&cController, 20 MB, 4);
	AssertLongLongInt(26, cNamedIndexes.NumNames());

	AssertLongLongInt(5265267321786128702LL, cNamedIndexes.GetIndex("beast"));
	AssertLongLongInt(9213567356457326474LL, cNamedIndexes.GetIndex("Lunar Base"));
	AssertLongLongInt(1532564672346590234LL, cNamedIndexes.GetIndex("Earthling/spaceships/Cruiser"));
	AssertLongLongInt(8465236728346532649LL, cNamedIndexes.GetIndex("Earthling/spaceships/Dominator"));
	AssertLongLongInt(3749816364128750931LL, cNamedIndexes.GetIndex("Earthling/spaceships/surplus cold war nuclear war-heads"));
	AssertLongLongInt(1532564672346590234LL, cNamedIndexes.GetIndex("Earthling/spaceships/Point defense Laser system"));
	AssertLongLongInt(8352145325252165435LL, cNamedIndexes.GetIndex("Earthling/portraits/Captain Zelnick"));
	AssertLongLongInt(4678979686897958483LL, cNamedIndexes.GetIndex("Earthling/slave-shield"));
	AssertLongLongInt(3476827346812023123LL, cNamedIndexes.GetIndex("Fot"));
	AssertLongLongInt(6513451892183782132LL, cNamedIndexes.GetIndex("Pik"));
	AssertLongLongInt(5451523689723469328LL, cNamedIndexes.GetIndex("Spathi/Discriminator"));
	AssertLongLongInt(3214004623467012364LL, cNamedIndexes.GetIndex("Spathi/Eluder"));
	AssertLongLongInt(2841213793444383464LL, cNamedIndexes.GetIndex("Spathi/characters/captain/Fwiffo"));
	AssertLongLongInt(4012756480145431273LL, cNamedIndexes.GetIndex("Spathi/characters/captain/Fwiffo-on-the-moon"));
	AssertLongLongInt(3576898544356890986LL, cNamedIndexes.GetIndex("Ur-Quan/Kzer-za/spaceships/Dreadnought/hull"));
	AssertLongLongInt(7935687324790713849LL, cNamedIndexes.GetIndex("Ur-Quan/Kzer-za/spaceships/Dreadnought/launch figters/weapons/auto-targetting laser"));
	AssertLongLongInt(2536710003746523782LL, cNamedIndexes.GetIndex("Ur-Quan/Kzer-za/spaceships/Dreadnought/launch figters/HierachyCrew"));
	AssertLongLongInt(4368570346902094536LL, cNamedIndexes.GetIndex("Ur-Quan/kohr-Ah/spaceships/Marauder/hull"));
	AssertLongLongInt(8765325424368900113LL, cNamedIndexes.GetIndex("Ur-Quan/kohr-Ah/spaceships/spinning disk"));
	AssertLongLongInt(8334658173689122135LL, cNamedIndexes.GetIndex("Ur-Quan/kohr-Ah/spaceships/ring-of-flames"));
	AssertLongLongInt(7498273948792334521LL, cNamedIndexes.GetIndex("Vux/spaceships/Intruder"));
	AssertLongLongInt(8974598758345774533LL, cNamedIndexes.GetIndex("Vux/spaceships/Globule"));
	AssertLongLongInt(9223372036854775807LL, cNamedIndexes.GetIndex("Vux/spaceships/mega-watt Laser Cannon"));
	AssertLongLongInt(4376423847623874680LL, cNamedIndexes.GetIndex("Vux/spaceships/admiral Zex/menagarie-transport-ship"));
	AssertLongLongInt(1136946723821981232LL, cNamedIndexes.GetIndex("Zoq"));
	AssertLongLongInt(2384789236478123123LL, cNamedIndexes.GetIndex("Zoq Fot Pik/Sports/Frungy!"));
	
	cNamedIndexes.Add(7234982374982126710LL, "Earthling/Quorum/Slave Shielded");
	AssertLongLongInt(7234982374982126710LL, cNamedIndexes.GetIndex("Earthling/Quorum/Slave Shielded"));

	AssertTrue(cNamedIndexes.Save());
	AssertTrue(cController.End());
	AssertTrue(cNamedIndexes.Close());

	cNamedIndexes.Kill();
	cController.Kill();

	sz.Init(); 
	DumpNamedIndexesFile(&sz, "NamedIndexes"_FS_"5"_FS_"64_0.NAM", 64, 4); 
	AssertString("\
NamedIndexes"_FS_"5"_FS_"64_0.NAM\n\
-----------------------\n\
   0: 8352145325252165435 -> Earthling/portraits/Captain Zelnick\n\
   1: 1532564672346590234 -> Earthling/spaceships/Cruiser\n\
   2: 8465236728346532649 -> Earthling/spaceships/Dominator\n\
   3: 1532564672346590234 -> Earthling/spaceships/Point defense Laser system\n\
\n\
   4: 2841213793444383464 -> Spathi/characters/captain/Fwiffo\n\
   5: 4012756480145431273 -> Spathi/characters/captain/Fwiffo-on-the-moon\n\
   6: 4368570346902094536 -> Ur-Quan/kohr-Ah/spaceships/Marauder/hull\n\
   7: 8334658173689122135 -> Ur-Quan/kohr-Ah/spaceships/ring-of-flames\n\
\n\
   8: 8765325424368900113 -> Ur-Quan/kohr-Ah/spaceships/spinning disk\n\
   9: 3576898544356890986 -> Ur-Quan/Kzer-za/spaceships/Dreadnought/hull\n\
  10: 4376423847623874680 -> Vux/spaceships/admiral Zex/menagarie-transport-ship\n\
  11: 7498273948792334521 -> Vux/spaceships/Intruder\n\
\n\
  12: 7234982374982126710 -> Earthling/Quorum/Slave Shielded\n\
  13: 9223372036854775807 -> Vux/spaceships/mega-watt Laser Cannon\n\
  14: 2384789236478123123 -> Zoq Fot Pik/Sports/Frungy!\n\
  15:      0 -> \n\
-----------------------\n", sz.Text());
	sz.Kill();
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

	TestNamedIndexesAdd();
	TestNamedIndexesRemove();
	TestNamedIndexesCacheEviction();
	TestNamedIndexesLoad();
	TestNamedIndexesOptimise();

	cFileUtil.RemoveDir("NamedIndexes");

	TestStatistics();
}

