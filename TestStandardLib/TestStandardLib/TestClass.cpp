#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "StandardLib/ExternalObjectDeserialiser.h"
#include "StandardLib/ExternalObjectSerialiser.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ChunkFileObjectWriter.h"
#include "StandardLib/ChunkFileSystemObjectReader.h"
#include "TestLib/Assert.h"
#include "TestClass.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClassAddConstructors(void)
{
	gcObjects.AddConstructor<CTestClass>();
	gcObjects.AddConstructor<CTinyTestClass>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClassDefinition(void)
{
	Ptr<CTestClass>		pTestClass;
	CClass*				pcTestClassClass;
	CClass*				pcTinyTestClassClass;
	CClasses*			pcClasses;
	CClass*				pcTemp;
	CField*				pcField;
	CPointerField*		pcPointerField;
	EPrimitiveType		eType;

	DataIOInit();
	ObjectsInit();

	pcClasses = gcObjects.GetClasses();

	pTestClass = gcObjects.Malloc<CTestClass>();
	pTestClass->Init();

	pcTestClassClass = pTestClass->GetClass();
	AssertNotNull(pcTestClassClass);
	AssertString("CTestClass", pcTestClassClass->GetName());
	AssertTrue(pcTestClassClass->GetType() > CLASS_TYPES);
	AssertTrue(pcTestClassClass->IsComplete());
	eType = pcTestClassClass->GetType();

	pcTemp = pcClasses->Get(eType);
	AssertPointer(pcTestClassClass, pcTemp);
	pcTemp = pcClasses->Get("CTestClass");
	AssertPointer(pcTestClassClass, pcTemp);

	pcTinyTestClassClass = pTestClass->mTiny.GetClass();
	AssertNotNull(pcTinyTestClassClass);
	AssertString("CTinyTestClass", pcTinyTestClassClass->GetName());
	AssertInt(eType + 1, pcTinyTestClassClass->GetType());
	AssertTrue(pcTinyTestClassClass->IsComplete());

	pcTemp = pcClasses->Get(eType + 1);
	AssertPointer(pcTinyTestClassClass, pcTemp);
	pcTemp = pcClasses->Get("CTinyTestClass");
	AssertPointer(pcTinyTestClassClass, pcTemp);

	pcField = pcTestClassClass->GetField("mpObject");
	AssertTrue(pcField->IsPointer());
	AssertString("mpObject", pcField->GetName());
	AssertInt(192, pcField->GetOffset());
	pcPointerField = (CPointerField*)pcField;

	pcField = pcTestClassClass->GetField("mpTest");
	AssertTrue(pcField->IsPointer());
	AssertInt(200, pcField->GetOffset());

	pcField = pcTestClassClass->GetField("mInt");
	AssertTrue(pcField->IsPrimitive());
	AssertString("mInt", pcField->GetName());
	AssertInt(208, pcField->GetOffset());

	pcField = pcTestClassClass->GetField("miUnmanagedInt");
	AssertTrue(pcField->IsUnmanaged());
	AssertFalse(pcField->IsArray());
	AssertString("miUnmanagedInt", pcField->GetName());
	AssertInt(216, pcField->GetOffset());

	pcField = pcTestClassClass->GetField("mTiny");
	AssertTrue(pcField->IsEmbeddedObject());
	AssertString("mTiny", pcField->GetName());
	AssertInt(224, pcField->GetOffset());

	pcField = pcTestClassClass->GetField("mDouble");
	AssertTrue(pcField->IsPrimitive());
	AssertInt(424, pcField->GetOffset());

	pcField = pcTestClassClass->GetField("mauiData");
	AssertTrue(pcField->IsUnmanaged());
	AssertInt(440, pcField->GetOffset());

	ObjectsKill();
	DataIOKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClassOnStackOutOfFrame(void)
{
	CTestClass			cTestClass;
	CClass*				pcTestClassClass;
	CClass*				pcTinyTestClassClass;
	CClasses*			pcClasses;
	CClass*				pcTemp;
	EPrimitiveType		eType;
	CField*				pcField;
	CPointerField*		pcPointerField;
	CPointer*			pcPointer;
	CTestClass*			pcTestClass;
	Ptr<CTestClass>		pTestClass3;

	pcClasses = gcObjects.GetClasses();

	cTestClass.Init();
	pcTestClassClass = cTestClass.GetClass();
	AssertNotNull(pcTestClassClass);
	AssertString("CTestClass", pcTestClassClass->GetName());
	AssertTrue(pcTestClassClass->GetType() > CLASS_TYPES);
	AssertTrue(pcTestClassClass->IsComplete());
	eType = pcTestClassClass->GetType();

	pcTemp = pcClasses->Get(eType);
	AssertPointer(pcTestClassClass, pcTemp);
	pcTemp = pcClasses->Get("CTestClass");
	AssertPointer(pcTestClassClass, pcTemp);

	pcTinyTestClassClass = cTestClass.mTiny.GetClass();
	AssertNotNull(pcTinyTestClassClass);
	AssertString("CTinyTestClass", pcTinyTestClassClass->GetName());
	AssertInt(eType + 1, pcTinyTestClassClass->GetType());
	AssertTrue(pcTinyTestClassClass->IsComplete());

	pcField = pcTestClassClass->GetField("mpObject");
	AssertTrue(pcField->IsPointer());
	AssertString("mpObject", pcField->GetName());
	AssertInt(192, pcField->GetOffset());
	pcPointerField = (CPointerField*)pcField;


	pTestClass3 = OMalloc<CTestClass>();
	cTestClass.mpObject = pTestClass3;
	pTestClass3->mDouble = 45648739045.0;

	pcPointer = pcPointerField->GetPointer(&cTestClass);
	pcTestClass = (CTestClass*)pcPointer->BaseObject();
	AssertDouble(45648739045.0, pcTestClass->mDouble, 0);

	pTestClass3->Kill();

	Pass();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClassOnStack(void)
{
	DataIOInit();
	ObjectsInit();

	TestClassOnStackOutOfFrame();

	ObjectsKill();
	DataIOKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClassName(void)
{
	Ptr<CTestClass>		pTestClass1;
	CTestClass*			pcTestClass;
	CObject*			pcNamedObject;
	CObject*			pcObject;
	CBaseObject*		pcBaseObject;
	CEmbeddedObject*	pcEmbeddedObject;
	CUnknown*			pcUnknown;
	CConstructable*		pcConstructable;

	DataIOInit();
	ObjectsInit();

	pTestClass1 = gcObjects.Malloc<CTestClass>();
	pTestClass1->Init();

	pcTestClass = &pTestClass1;
	AssertString("CTestClass", pcTestClass->ClassName());

	pcNamedObject = &pTestClass1;
	AssertString("CTestClass", pcNamedObject->ClassName());

	pcObject = &pTestClass1;
	AssertString("CTestClass", pcObject->ClassName());

	pcBaseObject = &pTestClass1;
	AssertString("CTestClass", pcBaseObject->ClassName());

	pcEmbeddedObject = &pTestClass1;
	AssertString("CTestClass", pcEmbeddedObject->ClassName());

	pcUnknown = &pTestClass1;
	AssertString("CTestClass", pcUnknown->ClassName());

	pcConstructable = &pTestClass1;
	AssertString("CTestClass", pcConstructable->ClassName());

	ObjectsKill();
	DataIOKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClassSerialisation(void)
{
	Ptr<CTestClass>					pTestClass;
	CExternalObjectSerialiser		cSerialiser;
	CChunkFileObjectWriter			cWriter;
	CFileUtil						cFileUtil;
	BOOL							bResult;
	char							szDirectory[] = "Output" _FS_ "TestClass";
	char							szData[] = "0123456789A";
	CExternalObjectDeserialiser		cGraphDeserialiser;
	CChunkFileSystemObjectReader 		cReader;
	OIndex							oi;

	DataIOInit();
	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	ObjectsInit();
	TestClassAddConstructors();

	pTestClass = gcObjects.Malloc<CTestClass>("Burke");
	pTestClass->Init();
	oi = pTestClass->GetIndex();
	pTestClass->mpObject = NULL;;
	pTestClass->mpTest = NULL;
	memcpy(pTestClass->mauiData, szData, 12);
	pTestClass->mDouble = 7980345645697084.0;
	pTestClass->mInt = 45978634;
	pTestClass->miUnmanagedInt = 907843256;
	pTestClass->mTiny.mc = 'c';

	cWriter.Init(szDirectory, "", "File");
	cSerialiser.Init(&cWriter);
	bResult = cSerialiser.Write(&pTestClass);
	cSerialiser.Kill();
	cWriter.Kill();

	ObjectsKill();
	AssertNull(&pTestClass);
	ObjectsInit();

	cReader.Init(szDirectory, "File");
	cGraphDeserialiser.Init(&cReader, FALSE, &gcObjects, gcObjects.GetMemory());
	pTestClass = cGraphDeserialiser.Read("Burke");
	AssertNotNull(&pTestClass);

	AssertMemory(szData, pTestClass->mauiData, 12);
	AssertInt(45978634, pTestClass->mInt);
	AssertDouble(7980345645697084.0, pTestClass->mDouble, 0);
	AssertInt(907843256, pTestClass->miUnmanagedInt);
	AssertChar('c', pTestClass->mTiny.mc);
	AssertLongLongInt(oi, pTestClass->GetIndex());

	pTestClass = NULL;

	ObjectsKill();

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	DataIOKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClassHeapObjectEmbeddedPointers(void)
{
	Ptr<CTestClass>		pTestClass1;
	Ptr<CTestClass>		pTestClass2;

	DataIOInit();
	ObjectsInit();

	pTestClass1 = gcObjects.Malloc<CTestClass>();
	AssertTrue(pTestClass1->IsAllocatedInObjects());
	AssertTrue(pTestClass1->mpObject.IsEmbeddingAllocatedInObjects());
	AssertTrue(pTestClass1->mTiny.IsEmbedded());
	pTestClass1->Init();

	pTestClass2 = gcObjects.Malloc<CTestClass>();
	AssertTrue(pTestClass2->IsAllocatedInObjects());
	AssertTrue(pTestClass2->mpObject.IsEmbeddingAllocatedInObjects());
	AssertTrue(pTestClass2->mTiny.IsEmbedded());
	pTestClass2->Init();

	pTestClass1 = NULL;
	pTestClass2 = NULL;

	ObjectsKill();
	DataIOKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClass(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();
	TypesInit();

	TestClassDefinition();
	TestClassOnStack();
	TestClassName();
	TestClassSerialisation();
	TestClassHeapObjectEmbeddedPointers();

	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

