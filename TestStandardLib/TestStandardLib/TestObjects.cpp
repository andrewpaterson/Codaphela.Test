#include "BaseLib/GlobalMemory.h"
#include "CoreLib/Codabase.h"
#include "CoreLib/CodabaseFactory.h"
#include "CoreLib/ValueIndexedDataConfig.h"
#include "CoreLib/ValueNamedIndexesConfig.h"
#include "CoreLib/NamedIndexedHeader.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"
#include "ObjectWriterChunkedTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CTestDoubleNamedString> SetupObjectsForDehollowfication(void)
{
	Ptr<CTestNamedString>			cNS1;
	Ptr<CTestNamedString>			cNS2;
	Ptr<CTestNamedString>			cNS3;
	Ptr<CTestNamedString>			cDiamond;
	Ptr<CTestDoubleNamedString>		pDouble;
	Ptr<CRoot>						pRoot;
	Ptr<CString>					cS1;
	Ptr<CString>					cS2;

	pRoot = ORoot();

	cDiamond = ONMalloc(CTestNamedString, "Diamond")->Init();

	cS1 = OMalloc(CString)->Init("CS1");
	cNS1 = ONMalloc(CTestNamedString, "NS1")->Init(cS1, cDiamond, "NS1");

	cNS2 = ONMalloc(CTestNamedString, "NS2")->Init(ONull, cDiamond, "NS2");

	cNS3 = ONMalloc(CTestNamedString, "NS3")->Init(ONull, cNS1, "NS3");

	cS2 = OMalloc(CString)->Init("CS2");
	cDiamond->Init(cS2, ONull, "Diamond");

	pDouble = ONMalloc(CTestDoubleNamedString, "Double")->Init(ONull, cNS2, cNS3);

	pRoot->Add(pDouble);
	return pDouble;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void SetupObjectsConstructors(void)
{
	gcObjects.AddConstructor<CTestWithArray>();
	gcObjects.AddConstructor<CTestInteger>();
	gcObjects.AddConstructor<CTestNamedString>();
	gcObjects.AddConstructor<CTestDoubleNamedString>();
	gcObjects.AddConstructor<CString>();
	gcObjects.AddConstructor<CArrayObject>();
	gcObjects.AddConstructor<CSetObject>();
	gcObjects.AddConstructor<CRoot>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsInMemoryIteration()
{
	SIndexesIterator	sIter;
	OIndex				oi;

	ObjectsInit();
	SetupObjectsForDehollowfication();

	oi = gcObjects.StartMemoryIteration(&sIter);
	AssertLongLongInt(1LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(2LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(3LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(4LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(5LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(6LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(7LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(8LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(9LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(INVALID_O_INDEX, oi);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsObjectSave(void)
{
	Ptr<CTestDoubleNamedString>			pDouble;
	BOOL								bResult;
	CFileUtil							cFileUtil;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CDurableFileController				cDurableController;
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	char								szDirectory[] = "Output" _FS_ "ObjectSave";
	CCodabase*							pcDatabase;
	int									iSerialisedSize;

	cDurableController.Init(szDirectory);
	cFileUtil.RemoveDir(szDirectory);
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);

	pDouble = SetupObjectsForDehollowfication();

	AssertLongLongInt(0, pcDatabase->NumIndices());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	AssertTrue(pDouble.IsDirty());
	Pass();
	
	bResult = gcObjects.Save(pDouble.BaseObject());
	AssertTrue(bResult);
	AssertTrue(pDouble.IsDirty());  //This object is *still* dirty after save.  Almost no objects will answer true to IsDirty.

	AssertLongLongInt(1, pcDatabase->NumIndices());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	iSerialisedSize = pDouble->SerialisedSize();
	AssertInt(106, pDouble->SerialisedSize());
	AssertLongLongInt(1, pcDatabase->NumDataCached(NamedIndexedHeaderSize(pDouble->GetName(), iSerialisedSize)));
	AssertLongLongInt(1, pcDatabase->NumDataCached());
	Pass();

	bResult = gcObjects.Save(pDouble.BaseObject());
	AssertTrue(bResult);
	AssertLongLongInt(1, pcDatabase->NumIndices());
	iSerialisedSize = pDouble->SerialisedSize();
	AssertInt(106, iSerialisedSize);
	AssertLongLongInt(1, pcDatabase->NumDataCached(NamedIndexedHeaderSize(pDouble->GetName(), iSerialisedSize)));
	AssertLongLongInt(1, pcDatabase->NumDataCached());
	
	pDouble->mszString = OMalloc(CString);
	pDouble->mszString->Init("A String");

	bResult = gcObjects.Save(pDouble.BaseObject());
	AssertTrue(bResult);
	AssertLongLongInt(1, pcDatabase->NumIndices());
	iSerialisedSize = pDouble->SerialisedSize();
	AssertInt(118, iSerialisedSize);
	AssertLongLongInt(1, pcDatabase->NumDataCached(NamedIndexedHeaderSize(pDouble->GetName(), iSerialisedSize)));
	AssertLongLongInt(1, pcDatabase->NumDataCached());

	pDouble->mszString = OMalloc(CString);
	pDouble->mszString->Init("Different Object");

	iSerialisedSize = pDouble->SerialisedSize();
	AssertInt(118, iSerialisedSize);
	bResult = gcObjects.Save(pDouble.BaseObject());
	AssertTrue(bResult);
	AssertLongLongInt(1, pcDatabase->NumIndices());
	iSerialisedSize = pDouble->SerialisedSize();
	AssertInt(118, iSerialisedSize);
	AssertLongLongInt(1, pcDatabase->NumDataCached(NamedIndexedHeaderSize(pDouble->GetName(), iSerialisedSize)));
	AssertLongLongInt(1, pcDatabase->NumDataCached());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsFlushNoClear(void)
{
	CFileUtil	cFileUtil;
	BOOL		bResult;
	CCodabase*	pcDatabase;
	char		szDirectory[] = "Output" _FS_ "Flush1";

	cFileUtil.RemoveDir(szDirectory);
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);

	SetupObjectsForDehollowfication();

	AssertLongLongInt(0, pcDatabase->NumIndices());
	AssertLongLongInt(0, pcDatabase->NumNames());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	
	bResult = gcObjects.Flush(FALSE, FALSE);
	AssertTrue(bResult);

	AssertLongLongInt(9, pcDatabase->NumIndices());
	AssertLongLongInt(6, pcDatabase->NumNames());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();

	CArrayChars	aszFileNames;
	int				i;
	CChars*			psz;
	CChars			szOutput;
	CChars			szFileName;
	CChars			szCurrent;
	CChars			szInputDirectory;

	szInputDirectory.Init("Input" _FS_ "Dehollowfication");

	aszFileNames.Init();
	cFileUtil.FindAllFiles(szInputDirectory.Text(), &aszFileNames, TRUE, FALSE);

	AssertTrue(aszFileNames.NumElements() > 0);
	for (i = 0; i < aszFileNames.NumElements(); i++)
	{
		psz = aszFileNames.Get(i);

		szCurrent.Init();
		cFileUtil.CurrentDirectory(&szCurrent);

		szFileName.Init(psz->Text());
		szFileName.RemoveFromStart(szCurrent.Length() + 1);
		szFileName.RemoveFromStart(szInputDirectory.Length() + 1);
		szOutput.Init(szCurrent);
		cFileUtil.AppendToPath(&szOutput, szDirectory);
		cFileUtil.AppendToPath(&szOutput, szFileName.Text());

		AssertFile(psz->Text(), szOutput.Text());

		szOutput.Kill();
		szFileName.Kill();
		szCurrent.Kill();
	}

	szInputDirectory.Kill();
	aszFileNames.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsFlushDurable(void)
{
	BOOL								bResult;
	CFileUtil							cFileUtil;
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	char								szDirectory[] = "Output" _FS_ "Flush2";
	CCodabase*							pcDatabase;

	cFileUtil.RemoveDir(szDirectory);
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);
	SetupObjectsForDehollowfication();

	AssertLongLongInt(0, pcDatabase->NumIndices());
	AssertLongLongInt(0, pcDatabase->NumNames());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());

	bResult = gcObjects.Flush(FALSE, FALSE);
	AssertTrue(bResult);

	AssertLongLongInt(9, pcDatabase->NumIndices());
	AssertLongLongInt(6, pcDatabase->NumNames());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();


	AssertFile("Input" _FS_ "Dehollowfication" _FS_ "48_0.DAT",     "Output" _FS_ "Flush2" _FS_ "48_0.DAT");
	AssertFile("Input" _FS_ "Dehollowfication" _FS_ "56_0.DAT",     "Output" _FS_ "Flush2" _FS_ "56_0.DAT");
	AssertFile("Input" _FS_ "Dehollowfication" _FS_ "68_0.DAT",     "Output" _FS_ "Flush2" _FS_ "68_0.DAT");
	AssertFile("Input" _FS_ "Dehollowfication" _FS_ "89_0.DAT",     "Output" _FS_ "Flush2" _FS_ "89_0.DAT");
	AssertFile("Input" _FS_ "Dehollowfication" _FS_ "93_0.DAT",     "Output" _FS_ "Flush2" _FS_ "93_0.DAT");
	AssertFile("Input" _FS_ "Dehollowfication" _FS_ "101_0.DAT",    "Output" _FS_ "Flush2" _FS_ "101_0.DAT");
	AssertFile("Input" _FS_ "Dehollowfication" _FS_ "102_0.DAT",    "Output" _FS_ "Flush2" _FS_ "102_0.DAT");
	AssertFile("Input" _FS_ "Dehollowfication" _FS_ "Files.DAT",    "Output" _FS_ "Flush2" _FS_ "Files.DAT");
	AssertFile("Input" _FS_ "Dehollowfication" _FS_ "Indicies.DAT", "Output" _FS_ "Flush2" _FS_ "Indicies.DAT");
	AssertFile("Input" _FS_ "Dehollowfication" _FS_ "32_0.NAM",     "Output" _FS_ "Flush2" _FS_ "32_0.NAM");
	AssertFile("Input" _FS_ "Dehollowfication" _FS_ "Files.NAM",    "Output" _FS_ "Flush2" _FS_ "Files.NAM");

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsEvict(void)
{
	CFileUtil	cFileUtil;
	BOOL		bResult;
	CCodabase*	pcDatabase;
	char		szDirectory[] = "Output" _FS_ "Eviction";

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);
	SetupObjectsForDehollowfication();

	AssertLongLongInt(0, pcDatabase->NumIndices());
	AssertLongLongInt(0, pcDatabase->NumIndicesCached());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());

	bResult = gcObjects.Flush(FALSE, FALSE);
	AssertTrue(bResult);

	AssertLongLongInt(9, pcDatabase->NumIndices());
	AssertLongLongInt(9, pcDatabase->NumIndicesCached());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);
	SetupObjectsForDehollowfication();

	//This flush's clear cache does not work.
	bResult = gcObjects.Flush(FALSE, TRUE);
	AssertTrue(bResult);

	//AssertLongLongInt(0, pcDatabase->NumIndicesCached());
	AssertLongLongInt(9, pcDatabase->NumIndices());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();


	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);
	SetupObjectsForDehollowfication();

	bResult = gcObjects.Flush(TRUE, FALSE);
	AssertTrue(bResult);

	AssertLongLongInt(9, pcDatabase->NumIndices());
	AssertLongLongInt(9, pcDatabase->NumIndicesCached());
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(0, gcObjects.NumMemoryNames());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();


	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);
	SetupObjectsForDehollowfication();

	//This flush's clear cache does not work.
	bResult = gcObjects.Flush(TRUE, TRUE);
	AssertTrue(bResult);

	//AssertLongLongInt(0, pcDatabase->NumIndicesCached());
	AssertLongLongInt(9, pcDatabase->NumIndices());
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(0, gcObjects.NumMemoryNames());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsObjectKillInGraph(void)
{
	Ptr<CTestNamedString>	cNS1;
	Ptr<CTestNamedString>	cNS2;
	Ptr<CRoot>				pRoot;
	Ptr<CString>			cS1;
	Ptr<CString>			cS2;
	CTestNamedString*		pcNS2;
	CString*				pcS2;

	ObjectsInit();

	pRoot = ORoot();

	cS1 = OMalloc(CString);
	cS1->Init("CS1");
	cNS1 = ONMalloc(CTestNamedString, "NS1")->Init(cS1, ONull, "NS1");

	cS2 = OMalloc(CString)->Init("CS2");
	cNS2 = ONMalloc(CTestNamedString, "NS2")->Init(cS2, cNS1, "NS2");

	pRoot->Add(cNS2);
	
	AssertPointer(cNS2->mpAnother.Object(), cNS1.Object());
	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());
	pcNS2 = &cNS2;
	cNS2 = NULL;
	pRoot = NULL;
	cS1 = NULL;
	pcS2 = &cS2;
	cS2 = NULL;
	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());

	cNS1->Kill();

	AssertNull(pcNS2->mpAnother.Object());
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());
	AssertPointer(pcNS2->mszString.Object(), pcS2);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsArrayKillInGraph(void)
{
	Ptr<CTestNamedString>	cNS1;
	Ptr<CArrayObject>		cA1;
	Ptr<CArrayObject>		cA2;
	Ptr<CRoot>				pRoot;
	Ptr<CString>			cS1;

	ObjectsInit();

	pRoot = ORoot();

	cS1 = OMalloc(CString)->Init("CS1");
	cNS1 = ONMalloc(CTestNamedString, "NS1")->Init(cS1, ONull, "NS1");

	cA1 = OMalloc(CArrayObject)->Init();
	cA2 = OMalloc(CArrayObject)->Init();

	cA1->Add(cNS1);
	cA2->Add(cNS1);

	pRoot->Add(cA1);
	pRoot->Add(cA2);

	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());

	cNS1 = NULL;
	pRoot = NULL;
	cS1 = NULL;

	cA1->Kill();
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());

	cA2->Kill();
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsObjectKillInArrayInGraph(void)
{
	Ptr<CTestNamedString>	cNS1;
	Ptr<CArrayObject>		cA1;
	Ptr<CArrayObject>		cA2;
	Ptr<CRoot>				pRoot;
	Ptr<CString>			cS1;

	ObjectsInit();

	pRoot = ORoot();

	cS1 = OMalloc(CString)->Init("CS1");
	cNS1 = ONMalloc(CTestNamedString, "NS1")->Init(cS1, ONull, "NS1");

	cA1 = OMalloc(CArrayObject)->Init();
	cA2 = OMalloc(CArrayObject)->Init();

	cA1->Add(cNS1);
	cA2->Add(cNS1);

	pRoot->Add(cA1);
	pRoot->Add(cA2);

	AssertInt(1, cA1->NumPointerTos());
	AssertInt(1, cA2->NumPointerTos());
	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());
	pRoot = NULL;
	cS1 = NULL;
	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());

	cNS1->Kill();
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());

	AssertInt(0, cA1->NumPointerTos());
	AssertInt(0, cA2->NumPointerTos());


	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectDehollowfication(void)
{
	CFileUtil						cFileUtil;
	CPointer						pPointer;
	CTestDoubleNamedString*			pcInternal;
	Ptr<CTestDoubleNamedString>		pDouble;
	Ptr<CTestNamedString>			pSingle;
	int								iClassSize;
	OIndex							oiOld;
	OIndex							oiNew;
	CCodabase*						pcDatabase;
	char							szDirectory[] = "Output" _FS_ "Dehollowfication";

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);
	SetupObjectsForDehollowfication();
	gcObjects.Flush(TRUE, TRUE);
	AssertLongLongInt(9, pcDatabase->NumIndices());
	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();

	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);
	SetupObjectsConstructors();
	AssertLongLongInt(9, pcDatabase->NumIndices());

	AssertTrue(gcObjects.Contains("Double"));

	pPointer = gcObjects.Get("Double");
	AssertNotNull(pPointer.Object());
	AssertString("CTestDoubleNamedString", pPointer.ClassName());

	pcInternal = (CTestDoubleNamedString*)pPointer.Object();
	AssertTrue(pcInternal->mpSplit1.IsNotNull());
	AssertTrue(pcInternal->mpSplit1.IsHollow());
	AssertTrue(pcInternal->mpSplit2.IsNotNull());
	AssertTrue(pcInternal->mpSplit2.IsHollow());

	pDouble = pPointer;

	oiOld = pDouble->mpSplit1.GetIndex();
	AssertTrue(pcInternal->mpSplit1.IsHollow());  //Making sure we haven't de-hollowed the object by calling GetIndex.

	//Problem - An oi of 1 is briefly assigned to the de-hollowed object and then it is reassigned back to its original value.
	iClassSize = pDouble->mpSplit1->ClassSize();  //The method call - ClassSize() - is irrelevant as long as the -> operator on mpSplit1 is invoked.
	AssertTrue(pcInternal->mpSplit1.IsNotNull());
	AssertFalse(pcInternal->mpSplit1.IsHollow());
	AssertInt(sizeof(CTestNamedString), iClassSize);
	AssertString("CTestNamedString", pcInternal->mpSplit1.ClassName());
	oiNew = pDouble->mpSplit1.GetIndex();
	AssertLongLongInt(oiOld, oiNew);

	pSingle = pDouble->mpSplit2;
	AssertTrue(pcInternal->mpSplit2.IsNotNull());
	AssertTrue(pcInternal->mpSplit2.IsHollow());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsFlushClearGetByOid(void)
{
	CFileUtil						cFileUtil;
	CPointer						pObject;
	Ptr<CTestDoubleNamedString>		pDouble;
	Ptr<CRoot>						pRoot;
	CCodabase*						pcDatabase;
	char							szDirectory[] = "Output" _FS_ "Dehollowfication";

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);
	SetupObjectsConstructors();
	
	pRoot = ORoot();
	pDouble = ONMalloc(CTestDoubleNamedString, "Double")->Init();
	pRoot->Add(pDouble);
	AssertLongLongInt(0, pcDatabase->NumIndices());
	pObject = gcObjects.Get(3);
	AssertNotNull(pObject.Object());
	AssertString("CTestDoubleNamedString", pObject.ClassName());

	gcObjects.Flush(TRUE, TRUE);
	AssertLongLongInt(3, pcDatabase->NumIndices());

	pObject = gcObjects.Get(3);
	AssertNotNull(pObject.Object());
	AssertString("CTestDoubleNamedString", pObject.ClassName());
	
	pRoot = ORoot();
	AssertString("CRoot", pRoot.ClassName());

	pObject = gcObjects.Get("Double");
	AssertNotNull(pObject.Object());
	AssertString("CTestDoubleNamedString", pObject.ClassName());
	AssertString("CRoot", pRoot.ClassName());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsFlushClearGetByName(void)
{
	CFileUtil						cFileUtil;
	CPointer						pObject;
	Ptr<CTestDoubleNamedString>		pDouble;
	Ptr<CRoot>						pRoot;
	CCodabase*						pcDatabase;
	char							szDirectory[] = "Output" _FS_ "Dehollowfication";

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);
	SetupObjectsConstructors();

	pRoot = ORoot();
	pDouble = ONMalloc(CTestDoubleNamedString, "Double")->Init();
	pRoot->Add(pDouble);
	AssertLongLongInt(0, pcDatabase->NumIndices());
	AssertLongLongInt(0, pcDatabase->NumNames());
	pObject = gcObjects.Get(3);
	AssertNotNull(pObject.Object());
	AssertString("CTestDoubleNamedString", pObject.ClassName());

	gcObjects.Flush(TRUE, TRUE);
	AssertLongLongInt(3, pcDatabase->NumIndices());
	AssertLongLongInt(2, pcDatabase->NumNames());

	pObject = gcObjects.Get("Double");
	AssertNotNull(pObject.Object());
	AssertString("CTestDoubleNamedString", pObject.ClassName());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsFlushRemovesStackPointers(void)
{
	CFileUtil						cFileUtil;
	Ptr<CTestDoubleNamedString>		pDouble;
	Ptr<CRoot>						pRoot;
	CCodabase*						pcDatabase;
	char							szDirectory[] = "Output" _FS_ "ClearPointers";

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);


	SetupObjectsConstructors();

	pRoot = ORoot();

	gcObjects.Flush(TRUE, TRUE);
	AssertLongLongInt(2, pcDatabase->NumIndices());

	AssertNull(&pRoot);

	pDouble = ONMalloc(CTestDoubleNamedString, "Double")->Init();
	AssertString("CTestDoubleNamedString", pDouble.ClassName());

	pRoot = ORoot();
	AssertString("CRoot", pRoot.ClassName());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjects(void)
{
	BeginTests();
	MemoryInit();

	TestObjectsObjectKillInGraph();
	TestObjectsArrayKillInGraph();
	TestObjectsObjectKillInArrayInGraph();
	TestObjectsInMemoryIteration();
	TestObjectsObjectSave();
	TestObjectsFlushRemovesStackPointers();
	TestObjectsFlushNoClear();
	TestObjectsFlushClearGetByOid();
	TestObjectsFlushClearGetByName();
	TestObjectsFlushDurable();
	TestObjectsEvict();
	TestObjectDehollowfication();

	MemoryKill();
	TestStatistics();
}

