#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/ArrayVoidPtr.h"
#include "StandardLib/Unknowns.h"
#include "StandardLib/MapUnknownUnknown.h"
#include "TestLib/Assert.h"
#include "UnknownTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapUnknownUnknownAdd(void)
{
	MemoryInit();
	UnknownsInit();

	CMapUnknownUnknown		cMap;
	CTestNamedUnknown*		pcKey1;
	CTestUnknownJobbie*		pcValue1;
	CTestNamedUnknown*		pcKey2;
	CTestUnknownJobbie*		pcValue2;

	gcUnknowns.AddConstructor<CTestUnknown>();
	gcUnknowns.AddConstructor<CTestNamedUnknown>();
	gcUnknowns.AddConstructor<CTestUnknownJobbie>();
	gcUnknowns.AddConstructor<CTestIterableUnknown>();
	AssertInt(0, gcUnknowns.NumElements());

	cMap.Init();

	pcKey1 = gcUnknowns.Add<CTestNamedUnknown>();
	pcValue1 = gcUnknowns.Add<CTestUnknownJobbie>();
	pcKey2 = gcUnknowns.Add<CTestNamedUnknown>();
	pcValue2 = gcUnknowns.Add<CTestUnknownJobbie>();
	pcKey1->Init("Hello");
	pcValue1->Init(4, "Snurk");
	pcKey2->Init("World");
	pcValue2->Init(67, "krust");
	AssertSize(0, cMap.NumElements());

	cMap.Put(pcKey1, pcValue1);
	AssertSize(1, cMap.NumElements());

	cMap.Put(pcKey2, pcValue2);
	AssertSize(2, cMap.NumElements());

	cMap.Kill();

	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapUnknownUnknownIterate(void)
{
	MemoryInit();
	UnknownsInit();

	CMapUnknownUnknown		cMap;
	CTestNamedUnknown*		pcKeyA;
	CTestNamedUnknown*		pcKeyB;
	CTestNamedUnknown*		pcKeyC;
	CTestNamedUnknown*		pcKey1;
	CTestUnknownJobbie*		pcValue1;
	CTestNamedUnknown*		pcKey2;
	CTestUnknownJobbie*		pcValue2;
	CTestNamedUnknown*		pcKey3;
	CTestUnknownJobbie*		pcValue3;
	SMapIterator			sIter;
	CUnknown*				pcKey;
	CUnknown*				pcValue;
	bool					bExists;
	CArrayVoidPtr			cArrayPtr;

	gcUnknowns.AddConstructor<CTestUnknown>();
	gcUnknowns.AddConstructor<CTestNamedUnknown>();
	gcUnknowns.AddConstructor<CTestUnknownJobbie>();
	gcUnknowns.AddConstructor<CTestIterableUnknown>();
	AssertInt(0, gcUnknowns.NumElements());

	cMap.Init();

	pcKey1 = NULL;
	pcKey2 = NULL;
	pcKey3 = NULL;

	pcKeyA = gcUnknowns.Add<CTestNamedUnknown>();
	pcKeyB = gcUnknowns.Add<CTestNamedUnknown>();
	pcKeyC = gcUnknowns.Add<CTestNamedUnknown>();

	cArrayPtr.Init();
	cArrayPtr.Add(pcKeyA);
	cArrayPtr.Add(pcKeyB);
	cArrayPtr.Add(pcKeyC);
	cArrayPtr.TimSort();
	pcKey1 = (CTestNamedUnknown*)cArrayPtr.GetPtr(0);
	pcKey2 = (CTestNamedUnknown*)cArrayPtr.GetPtr(1);
	pcKey3 = (CTestNamedUnknown*)cArrayPtr.GetPtr(2);
	cArrayPtr.Kill();

	pcKeyA = NULL;
	pcKeyB = NULL;
	pcKeyC = NULL;

	pcValue1 = gcUnknowns.Add<CTestUnknownJobbie>();
	pcValue2 = gcUnknowns.Add<CTestUnknownJobbie>();
	pcValue3 = gcUnknowns.Add<CTestUnknownJobbie>();
	pcKey1->Init("Hello");
	pcValue1->Init(4, "Snurk");
	pcKey2->Init("World");
	pcValue2->Init(67, "krust");
	pcKey3->Init("Aardvark");
	pcValue3->Init(67, "Berry");
	AssertSize(0, cMap.NumElements());

	cMap.Put(pcKey1, pcValue1);
	cMap.Put(pcKey2, pcValue2);
	cMap.Put(pcKey3, pcValue3);
	AssertSize(3, cMap.NumElements());

	bExists = cMap.StartIteration(&sIter, &pcKey, &pcValue);
	AssertTrue(bExists);
	AssertPointer(pcKey1, pcKey);
	AssertPointer(pcValue1, pcValue);
	bExists = cMap.Iterate(&sIter, &pcKey, &pcValue);
	AssertTrue(bExists);
	AssertPointer(pcKey2, pcKey);
	AssertPointer(pcValue2, pcValue);
	bExists = cMap.Iterate(&sIter, &pcKey, &pcValue);
	AssertTrue(bExists);
	AssertPointer(pcKey3, pcKey);
	AssertPointer(pcValue3, pcValue);
	bExists = cMap.Iterate(&sIter, &pcKey, &pcValue);
	AssertFalse(bExists);
	AssertSize(3, cMap.GetHoldingSize());
	AssertSize(0, cMap.GetSortedSize());

	cMap.Pack();
	AssertSize(3, cMap.NumElements());
	AssertSize(3, cMap.GetSortedSize());
	AssertSize(0, cMap.GetHoldingSize());

	bExists = cMap.StartIteration(&sIter, &pcKey, &pcValue);
	AssertTrue(bExists);
	AssertPointer(pcKey1, pcKey);
	AssertPointer(pcValue1, pcValue);
	bExists = cMap.Iterate(&sIter, &pcKey, &pcValue);
	AssertTrue(bExists);
	AssertPointer(pcKey2, pcKey);
	AssertPointer(pcValue2, pcValue);
	bExists = cMap.Iterate(&sIter, &pcKey, &pcValue);
	AssertTrue(bExists);
	AssertPointer(pcKey3, pcKey);
	AssertPointer(pcValue3, pcValue);
	bExists = cMap.Iterate(&sIter, &pcKey, &pcValue);
	AssertFalse(bExists);

	cMap.Kill();

	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapUnknownUnknownSave(void)
{
	MemoryInit();
	UnknownsInit();

	CMapUnknownUnknown		cMap;
	CTestNamedUnknown*		pcKey1;
	CTestUnknownJobbie*		pcValue1;
	CTestNamedUnknown*		pcKey2;
	CTestUnknownJobbie*		pcValue2;
	CFileUtil				cFileUtil;

	gcUnknowns.AddConstructor<CTestUnknown>();
	gcUnknowns.AddConstructor<CTestNamedUnknown>();
	gcUnknowns.AddConstructor<CTestUnknownJobbie>();
	gcUnknowns.AddConstructor<CTestIterableUnknown>();
	AssertInt(0, gcUnknowns.NumElements());

	cFileUtil.RemoveDir("Output" _FS_ "MapUnknownUnknown");
	cFileUtil.MakeDir("Output" _FS_ "MapUnknownUnknown");

	cMap.Init();

	pcKey1 = gcUnknowns.Add<CTestNamedUnknown>();
	pcValue1 = gcUnknowns.Add<CTestUnknownJobbie>();
	pcKey2 = gcUnknowns.Add<CTestNamedUnknown>();
	pcValue2 = gcUnknowns.Add<CTestUnknownJobbie>();
	AssertSize(0, cMap.NumElements());

	cMap.Put(pcKey1, pcValue2);
	AssertSize(1, cMap.NumElements());

	cMap.Put(pcKey2, pcValue2);
	AssertSize(2, cMap.NumElements());

	cMap.Kill();

	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//                                                                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void TestMapUnknownUnknown(void)
{
	BeginTests();

	TestMapUnknownUnknownAdd();
	TestMapUnknownUnknownIterate();

	TestStatistics();
}

