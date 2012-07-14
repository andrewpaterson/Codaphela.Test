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
	CNamedIndexes			cNamedIndexes;
	CDurableFileController	cController;
	CFileUtil				cFileUtil;
	BOOL					bResult;

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

	cController.End();
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

	BeginTests();

	cFileUtil.RemoveDir("NamedIndexes");

	//TestAdd();
	//TestRemove();
	TestCacheEviction();

	cFileUtil.RemoveDir("NamedIndexes");

	TestStatistics();
}

