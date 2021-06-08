#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/LogToMemory.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/GlobalDataTypesIO.h"
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
	TypesInit();
	DataIOInit();


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestStringAddConstructors();

	pRoot = ORoot();
	pString1 = OString("Hello");
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

	pString1 = gcObjects.Get(oi1);
	pString1->AppendHexHiLo(szDirectory, 7);
	AssertTrue(pString1.IsDirty());
	AssertString("HelloTrue5C74757074754F", pString1->Text());

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	DataIOKill();
	TypesKill();
	MemoryKill();
	cFileUtil.RemoveDir(szDirectory);
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStringEmbeddedDirty(void)
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
	TypesInit();
	DataIOInit();


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

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();
	AssertNull(&pString1);


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

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

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

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

	ObjectsFlush();
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

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();


	DataIOKill();
	TypesKill();
	MemoryKill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStringAlteration(void)
{
	Ptr<CString>	pString1;
	Ptr<CString>	pString2;
	Ptr<CString>	pDest;
	Ptr<CString>	pYes;
	Ptr<CString>	pNo;
	Ptr<CRoot>		pRoot;

	MemoryInit();
	TypesInit();
	DataIOInit();
	ObjectsInit();

	pString1 = OString("Hello");
	pString2 = OString("World!");
	pDest = OString();
	pYes = OString("Yes");
	pNo = OString("No");

	pDest->Set(pString1)->Append(' ')->AppendSubString(pString2, 5);
	AssertString(pDest->Text(), "Hello World");

	pDest->Clear()->AppendBool(TRUE)->Append(pString1, 3)->AppendBool(FALSE, pYes, pNo);
	AssertString(pDest->Text(), "TrueHelNo");

	pDest->Clear()->AppendFlag(0x03, 0x02, pString1);
	pDest->AppendFlag(0x03, 0x01, pString2, TRUE);
	AssertString("Hello, World!", pDest->Text());

	pDest->Set("Left:")->LeftAlign(pString1, ' ', 20)->Append(":Right");
	AssertString("Left:Hello               :Right", pDest->Text());

	pDest->Set("Left:")->RightAlign(pString2, ' ', 20)->Append(":Right");
	AssertString("Left:              World!:Right", pDest->Text());

	pDest->Set(pNo)->Insert(1, pYes);
	AssertString("NYeso", pDest->Text());

	pString1->Set("Banana");
	pString2->Set("omo");

	pString1->Replace(OString("a"), pString2);
	AssertString("Bomonomonomo", pString1->Text());

	pString1->Overwrite(6, pYes);
	AssertString("BomonoYesomo", pString1->Text());

	ObjectsKill();
	DataIOKill();
	TypesKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStringTests(void)
{
	Ptr<CString>	pString1;
	Ptr<CString>	pDest;
	Ptr<CString>	pYes;
	Ptr<CString>	pNo;
	Ptr<CRoot>		pRoot;

	MemoryInit();
	TypesInit();
	DataIOInit();
	ObjectsInit();

	pDest = OString();
	pYes = OString("Yes");
	pNo = OString("No");

	pDest->Set("Yes");
	AssertTrue(pYes->Equals(pYes));
	AssertTrue(pDest->Equals(pYes));
	AssertFalse(pDest->Equals(pNo));

	pDest->Set("yeS");
	AssertTrue(pYes->EqualsIgnoreCase(pYes));
	AssertTrue(pDest->EqualsIgnoreCase(pYes));
	AssertFalse(pDest->EqualsIgnoreCase(pNo));

	pString1 = OString("Banana in Pajama");

	AssertTrue(pString1->Contains(OString("nana")));
	AssertTrue(pString1->ContainsIgnoreCase(OString("NANa")));
	AssertFalse(pString1->Contains(OString("Panama")));
	AssertFalse(pString1->ContainsIgnoreCase(OString("Panama")));

	AssertTrue(pString1->EndsWith(OString("Pajama")));
	AssertTrue(pString1->EndsWithIgnoreCase(OString("paJAma")));
	AssertFalse(pString1->EndsWith(OString("Pajam")));
	AssertFalse(pString1->EndsWithIgnoreCase(OString("paJAm")));

	AssertTrue(pString1->StartsWith(OString("Banana")));
	AssertTrue(pString1->StartsWithIgnoreCase(OString("baNaNa")));
	AssertFalse(pString1->StartsWith(OString("anana")));
	AssertFalse(pString1->StartsWithIgnoreCase(OString("AnAnA")));

	AssertTrue(pString1->SubStringEquals(1, OString("anana")));
	AssertTrue(pString1->SubStringEqualsIgnoreCase(1, OString("ANANA")));
	AssertFalse(pString1->SubStringEquals(2, OString("anana")));
	AssertFalse(pString1->SubStringEqualsIgnoreCase(2, OString("ANANA")));

	pString1->Append(" in Manila");

	AssertInt(7, pString1->Find("in"));
	AssertInt(7, pString1->Find(7, "in"));
	AssertInt(17, pString1->Find(8, "in"));
	AssertInt(-1, pString1->Find("Nope"));

	AssertInt(17, pString1->FindFromEnd("in"));
	AssertInt(17, pString1->FindFromEnd(17, "in"));
	AssertInt(7, pString1->FindFromEnd(16, "in"));
	AssertInt(-1, pString1->FindFromEnd("Nope"));

	ObjectsKill();
	DataIOKill();
	TypesKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStringSplit(void)
{
	Ptr<CString>			pString;
	Ptr<CArray<CString>>	paDest;

	MemoryInit();
	TypesInit();
	DataIOInit();
	ObjectsInit();

	pString = OString("And,the,Aardvark,walked,over,the,Hill,and,far,Away");
	AssertLongLongInt(1LL, gcObjects.NumMemoryIndexes());

	paDest = pString->Split(',');
	AssertInt(10, paDest->Length());
	AssertLongLongInt(12LL, gcObjects.NumMemoryIndexes());

	AssertString("And", paDest->Get(0)->Text());
	AssertString("the", paDest->Get(1)->Text());
	AssertString("Aardvark", paDest->Get(2)->Text());
	AssertString("walked", paDest->Get(3)->Text());
	AssertString("over", paDest->Get(4)->Text());
	AssertString("the", paDest->Get(5)->Text());
	AssertString("Hill", paDest->Get(6)->Text());
	AssertString("and", paDest->Get(7)->Text());
	AssertString("far", paDest->Get(8)->Text());
	AssertString("Away", paDest->Get(9)->Text());

	pString = NULL;
	AssertLongLongInt(11LL, gcObjects.NumMemoryIndexes());
	paDest->Clear();
	AssertLongLongInt(1LL, gcObjects.NumMemoryIndexes());
	paDest = NULL;
	AssertLongLongInt(0LL, gcObjects.NumMemoryIndexes());

	pString = OString("And,the,Aardvark,walked,over,the,Hill,and,far,Away");
	AssertLongLongInt(1LL, gcObjects.NumMemoryIndexes());

	paDest = pString->Split(',');
	AssertInt(10, paDest->Length());
	AssertLongLongInt(12LL, gcObjects.NumMemoryIndexes());

	paDest = NULL;
	AssertLongLongInt(1LL, gcObjects.NumMemoryIndexes());

	ObjectsKill();
	DataIOKill();
	TypesKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestString(void)
{
	BeginTests();

	TestStringDirty();
	TestStringEmbeddedDirty();
	TestStringAlteration();
	TestStringTests();
	TestStringSplit();

	TestStatistics();
}

