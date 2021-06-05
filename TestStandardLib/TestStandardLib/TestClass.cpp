#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "StandardLib/Object.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Array.h"
#include "StandardLib/Integer.h"
#include "StandardLib/Float.h"
#include "StandardLib/ObjectSerialiser.h"
#include "StandardLib/ExternalObjectDeserialiser.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ChunkFileObjectWriter.h"
#include "StandardLib/ObjectReaderChunkFileDisk.h"
#include "TestLib/Assert.h"


class CTinyTestClass : public CObject
{
CONSTRUCTABLE(CTinyTestClass);
public:
	Int8						mc;

	Ptr<CTinyTestClass> Init(void)
	{
		PreInit();
		mc = 127;
		PostInit();
		return this;
	}

	void Class(void)
	{
		CObject::Class();
		Primitive(&mc, "mc");
	}

	void Free(void)
	{
	}
};


class CTestClass : public CNamedObject
{
CONSTRUCTABLE(CTestClass);
public:
	CPointer					mpObject;
	Ptr<CTestClass>				mpTest;
	Int32						mInt;
	int							miUnmanagedInt;
	CTinyTestClass				mTiny;
	Float64						mDouble;
	unsigned char				mauiData[12];

	Ptr<CTestClass> Init(void)
	{
		PreInit();
		mTiny.Init();
		mInt = 0;
		miUnmanagedInt = 0;
		mDouble = 0;
		memset(mauiData, 0, 12);
		PostInit();
		return this;
	}

	void Class(void)
	{
		CObject::Class();
		Pointer(mpObject.This(), "mpObject");
		Pointer(mpTest.This(), "mpTest");
		UnmanagedInt(&miUnmanagedInt, "miUnmanagedInt");
		Primitive(&mInt, "mInt");
		Embedded(&mTiny, "mTiny");
		Primitive(&mDouble, "mDouble");
		UnmanagedData(mauiData, 12, "mauiData");
	}

	void Free(void)
	{
	}
};



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClassAddConstructors(void)
{
	gcObjects.AddConstructor<CArrayObject>();
	gcObjects.AddConstructor<CSetObject>();
	gcObjects.AddConstructor<CRoot>();
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
	AssertInt(400, pcField->GetOffset());

	pcField = pcTestClassClass->GetField("mauiData");
	AssertTrue(pcField->IsUnmanaged());
	AssertInt(416, pcField->GetOffset());

	ObjectsKill();
	DataIOKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClassOnStackWrapped(void)
{
	CTestClass			cTestClass;
	CTestClass			cTestClass2;
	CClass*				pcTestClassClass;
	CClass*				pcTinyTestClassClass;
	CClasses*			pcClasses;
	CClass*				pcTemp;
	EPrimitiveType		eType;
	CField*				pcField;
	CPointerField*		pcPointerField;
	CPointer*			pcPointer;
	CTestClass*			pcTestClass;

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

	cTestClass2.Init();
	cTestClass2.mDouble = 45648739045.0;
	cTestClass.mpObject = &cTestClass2;

	pcPointer = pcPointerField->GetPointer(&cTestClass);
	pcTestClass = (CTestClass*)pcPointer->BaseObject();
	AssertDouble(45648739045.0, pcTestClass->mDouble, 0);

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

	TestClassOnStackWrapped();

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
	CNamedObject*		pcNamedObject;
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
void TestClassSave(void)
{
	Ptr<CTestClass>				pTestClass;
	CObjectSingleSerialiser		cSerialiser;
	CChunkFileObjectWriter		cWriter;
	CFileUtil					cFileUtil;
	BOOL						bResult;
	char						szDirectory[] = "Output" _FS_ "TestClass";
	char						szData[] = "0123456789A";
	CExternalObjectDeserialiser	cGraphDeserialiser;
	CDependentReadObjects		cDependentReadObjects;
	CObjectReaderChunkFileDisk 	cReader;
	OIndex						oi;

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

	cDependentReadObjects.Init();
	cReader.Init(szDirectory, "File");
	cGraphDeserialiser.Init(&cReader, FALSE, &gcObjects, &cDependentReadObjects, gcObjects.GetMemory());
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
	TestClassSave();
	TestClassHeapObjectEmbeddedPointers();

	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

