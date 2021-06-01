#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "StandardLib/Object.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Array.h"
#include "StandardLib/Integer.h"
#include "StandardLib/Float.h"
#include "StandardLib/ObjectSerialiser.h"
#include "StandardLib/ObjectDeserialiser.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ChunkFileObjectWriter.h"
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


class CTestClass : public CObject
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
	AssertInt(168, pcField->GetOffset());
	pcPointerField = (CPointerField*)pcField;

	pcField = pcTestClassClass->GetField("mpTest");
	AssertTrue(pcField->IsPointer());
	AssertInt(176, pcField->GetOffset());

	pcField = pcTestClassClass->GetField("mInt");
	AssertTrue(pcField->IsPrimitive());
	AssertString("mInt", pcField->GetName());
	AssertInt(184, pcField->GetOffset());

	pcField = pcTestClassClass->GetField("miUnmanagedInt");
	AssertTrue(pcField->IsUnmanaged());
	AssertFalse(pcField->IsArray());
	AssertString("miUnmanagedInt", pcField->GetName());
	AssertInt(192, pcField->GetOffset());

	pcField = pcTestClassClass->GetField("mTiny");
	AssertTrue(pcField->IsEmbeddedObject());
	AssertString("mTiny", pcField->GetName());
	AssertInt(200, pcField->GetOffset());

	pcField = pcTestClassClass->GetField("mDouble");
	AssertTrue(pcField->IsPrimitive());
	AssertInt(376, pcField->GetOffset());

	pcField = pcTestClassClass->GetField("mauiData");
	AssertTrue(pcField->IsUnmanaged());
	AssertInt(392, pcField->GetOffset());

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
	CClasses*					pcClasses;
	CObjectSingleSerialiser		cSerialiser;
	CChunkFileObjectWriter		cWriter;
	CFileUtil					cFileUtil;
	char						szDirectory[] = "Output" _FS_ "Class" _FS_;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	DataIOInit();
	ObjectsInit();

	pcClasses = gcObjects.GetClasses();

	pTestClass = gcObjects.Malloc<CTestClass>();
	pTestClass->Init();

	cWriter.Init(szDirectory, "", "TestClass");
	cSerialiser.Init(&cWriter);
	cSerialiser.Write(&pTestClass);
	cSerialiser.Kill();
	cWriter.Kill();

	ObjectsKill();
	DataIOKill();

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClass(void)
{
	BeginTests();
	MemoryInit();
	TypesInit();

	TestClassDefinition();
	TestClassSave();

	TypesKill();
	MemoryKill();
	TestStatistics();
}

