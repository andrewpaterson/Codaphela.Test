#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/LogToMemory.h"
#include "CoreLib/CodabaseFactory.h"
#include "CoreLib/SequenceFactory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/String.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStringAddConstructors(void)
{
	gcObjects.AddConstructor<CRoot>();
	gcObjects.AddConstructor<CSetObject>();
	gcObjects.AddConstructor<CString>();
	gcObjects.AddConstructor<CTestEmbeddedStrings>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStringDirty(void)
{
	Ptr<CString>	pString1;
	OIndex			oi1;
	CCodabase*		pcDatabase;
	CSequence*		pcSequence;
	CFileUtil		cFileUtil;
	Ptr<CRoot>		pRoot;
	char			szDirectory[] = "Output" _FS_ "String" _FS_ "Database1";

	cFileUtil.RemoveDir(szDirectory);
	MemoryInit();


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestStringAddConstructors();

	pRoot = ORoot();
	pString1 = OMalloc<CString>("Hello");
	oi1 = pString1->GetIndex();
	AssertTrue(pString1.IsDirty());

	pRoot->Add(pString1);
	pString1->Flush();
	AssertFalse(pString1.IsDirty());

	pString1->AppendBool(TRUE);
	AssertTrue(pString1.IsDirty());
	AssertString("HelloTrue", pString1->Text());

	ObjectsFlush();
	AssertFalse(pString1.IsDirty());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();
	AssertNull(&pString1);


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestStringAddConstructors();

	pString1 = gcObjects.Get(oi1);
	pString1->AppendHexHiLo(szDirectory, 7);
	AssertTrue(pString1.IsDirty());
	AssertString("HelloTrue5C74757074754F", pString1->Text());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();


	MemoryKill();
	cFileUtil.RemoveDir(szDirectory);
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStringEmbedded(void)
{
	Ptr<CString>				pString1;
	Ptr<CString>				pString2;
	Ptr<CString>				pString3;
	Ptr<CTestEmbeddedStrings>	pContainer;
	OIndex						oi;
	CCodabase*					pcDatabase;
	CSequence*					pcSequence;
	CFileUtil					cFileUtil;
	Ptr<CRoot>					pRoot;
	char						szDirectory[] = "Output" _FS_ "String" _FS_ "Database2";

	cFileUtil.RemoveDir(szDirectory);
	MemoryInit();


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestStringAddConstructors();

	pRoot = ORoot();
	pContainer = OMalloc<CTestEmbeddedStrings>();
	oi = pContainer->GetIndex();
	AssertTrue(pContainer.IsDirty());

	pRoot->Add(pContainer);
	ObjectsFlush();
	AssertFalse(pString1.IsDirty());

	pContainer->mString1.Set("This is first");
	pContainer->mString2.Set("Burke is great");
	pContainer->mString3.Set("Wooglers");

	ObjectsFlush();  //Close calls Flush.  Why must flush be called here?
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();
	AssertNull(&pString1);


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestStringAddConstructors();

	ORoot()->TouchAll();
	pContainer = gcObjects.Get(oi);
	pString1 = &pContainer->mString1;
	pString2 = &pContainer->mString2;
	pString3 = &pContainer->mString3;
	AssertInt(2, pString1.GetDistToRoot());
	AssertInt(2, pString2.GetDistToRoot());
	AssertInt(2, pString3.GetDistToRoot());
	AssertInt(2, pContainer.GetDistToRoot());

	AssertString("This is first", pString1->Text());
	AssertString("Burke is great", pString2->Text());
	AssertString("Wooglers", pString3->Text());

	pString1->RemoveEnd(7);
	AssertTrue(pString1.IsDirty());
	AssertTrue(pContainer.IsDirty());
	AssertString("This is", pString1->Text());

	ObjectsFlush();  //Close calls Flush.  Why must flush be called here?
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestStringAddConstructors();

	pContainer = gcObjects.Get(oi);
	ORoot()->TouchAll();
	pString1 = &pContainer->mString1;
	pString2 = &pContainer->mString2;
	pString3 = &pContainer->mString3;
	AssertInt(2, pString1.GetDistToRoot());
	AssertInt(2, pString2.GetDistToRoot());
	AssertInt(2, pString3.GetDistToRoot());
	AssertInt(2, pContainer.GetDistToRoot());

	AssertString("This is", pString1->Text());
	AssertString("Burke is great", pString2->Text());
	AssertString("Wooglers", pString3->Text());

	pString1->RemoveEnd(7);
	AssertString("This is", pString1->Text());
	AssertTrue(pString1.IsDirty());
	AssertTrue(pContainer.IsDirty());

	pString2->Insert(9, "the ");
	AssertTrue(pString2.IsDirty());
	pString2->Append("est");
	AssertString("Burke is the greatest", pString2->Text());

	pString3->Set("Boogaloo");
	AssertTrue(pString3.IsDirty());
	AssertString("Boogaloo", pString3->Text());

	ObjectsFlush();  //Close calls Flush.  Why must flush be called here?
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();
	AssertNull(&pString1);
	AssertNull(&pString2);
	AssertNull(&pString3);


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestStringAddConstructors();

	pContainer = gcObjects.Get(oi);
	pString1 = &pContainer->mString1;
	pString2 = &pContainer->mString2;
	pString3 = &pContainer->mString3;
	ORoot()->TouchAll();
	AssertInt(2, pString1.GetDistToRoot());
	AssertInt(2, pString2.GetDistToRoot());
	AssertInt(2, pString3.GetDistToRoot());
	AssertInt(2, pContainer.GetDistToRoot());

	AssertString("This is", pString1->Text());
	AssertString("Burke is the greatest", pString2->Text());
	AssertString("Boogaloo", pString3->Text());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();


	MemoryKill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestString(void)
{
	BeginTests();

	TestStringDirty();
	TestStringEmbedded();

	TestStatistics();
}

