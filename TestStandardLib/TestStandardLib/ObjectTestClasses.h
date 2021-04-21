#ifndef __OBJECT_TEST_CLASSES_H__
#define __OBJECT_TEST_CLASSES_H__
#include "StandardLib/Object.h"
#include "StandardLib/NamedObject.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Integer.h"
#include "StandardLib/Float.h"
#include "StandardLib/Character.h"
#include "StandardLib/String.h"


struct STestObjectFreedNotifier
{
	BOOL bFreed;
};


class CTestObject : public CObject
{
CONSTRUCTABLE(CTestObject);
public:
	CPointer					mpObject;
	Ptr<CTestObject>			mpTest;
	int							mi;
	STestObjectFreedNotifier*	mpsFreedNotifier;

	void	Init(void);
	void	Init(STestObjectFreedNotifier* psKilledNotifier);
	void	Init(CPointer pObject, Ptr<CTestObject> pTest);
	void	Class(void);
	void	Free(void);

	BOOL	Save(CObjectSerialiser* pcFile);
	BOOL	Load(CObjectDeserialiser* pcFile);

	void	SomeMethod(void);
};


class CTestTriPointerObject : public CObject
{
CONSTRUCTABLE(CTestTriPointerObject);
public:
	CPointer					mpObject1;
	CPointer					mpObject2;
	CPointer					mpObject3;
	STestObjectFreedNotifier*	mpsFreedNotifier;

	void	Init(void);
	void	Init(STestObjectFreedNotifier* psKilledNotifier);
	void	Class(void);
	void	Free(void);

	BOOL	Save(CObjectSerialiser* pcFile);
	BOOL	Load(CObjectDeserialiser* pcFile);
};


class CTestSaveableObject1 : public CNamedObject
{
CONSTRUCTABLE(CTestSaveableObject1);
public:
	CPointer	mpObject;
	int			miInt;
	CChars		mszString;
	BOOL		mbSaved;

	void		Init(void);
	void		Class(void);
	void		Free(void);

	BOOL		Save(CObjectSerialiser* pcFile);
	BOOL		Load(CObjectDeserialiser* pcFile);
};


class CTestSaveableObject2 : public CNamedObject
{
CONSTRUCTABLE(CTestSaveableObject2);
public:
	CChars						msz;
	Ptr<CTestSaveableObject1>	mp1;
	CPointer					mp2;
	BOOL						mbSaved;

	void	Init(const char* psz);
	void	Class(void);
	void	Free(void);

	BOOL	Save(CObjectSerialiser* pcFile);
	BOOL	Load(CObjectDeserialiser* pcFile);
};



class CTestObjectWithFields : public CObject
{
CONSTRUCTABLE(CTestObjectWithFields);
public:
	CPointer			mpObject;
	Ptr<CTestObject>	mpTest;

	Int8				mi8;
	UInt8				mui8;
	Int32				mi32;
	UInt32				mui32;
	Int16				mi16;
	UInt16				mui16;
	Char8				mc8;
	Char16				mc16;
	Float32				mf32;
	Float64				mf64;
	Int64				mi64;
	UInt64				mui64;
	Bool				mb;

	char*				mpsz;

	void	Init(void);
	void	Init(CPointer pObject, Ptr<CTestObject> pTest);
	void	Class(void);
	void	Free(void);

	BOOL	Save(CObjectSerialiser* pcFile);
	BOOL	Load(CObjectDeserialiser* pcFile);

	void	Update(int8 i8);
	void	Update(char* sz);
}; 


class CTestEmbeddedObjectWithFields : public CObject
{
CONSTRUCTABLE(CTestEmbeddedObjectWithFields);
public:
	Bool						mbX;
	CPointer					mpObjectA;
	CTestObjectWithFields		mcEmbedded1;
	CPointer					mpObjectB;
	CTestObjectWithFields		mcEmbedded2;
	CPointer					mpObjectC;
	Bool						mbY;


	void	Init(void);
	void	Class(void);
	void	Free(void);

	BOOL	Save(CObjectSerialiser* pcFile);
	BOOL	Load(CObjectDeserialiser* pcFile);
};


class CTestEmbeddedStrings : public CObject
{
CONSTRUCTABLE(CTestEmbeddedStrings);
public:
	CString		mString1;
	CString		mString2;
	CString		mString3;

	void	Init(void);
	void	Class(void);
	void	Free(void);

	BOOL	Save(CObjectSerialiser* pcFile);
	BOOL	Load(CObjectDeserialiser* pcFile);

};


#endif // __OBJECT_TEST_CLASSES_H__

