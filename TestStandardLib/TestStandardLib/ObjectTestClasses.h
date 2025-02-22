#ifndef __OBJECT_TEST_CLASSES_H__
#define __OBJECT_TEST_CLASSES_H__
#include "StandardLib/Object.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Integer.h"
#include "StandardLib/Float.h"
#include "StandardLib/Character.h"
#include "StandardLib/String.h"


struct STestObjectFreedNotifier
{
	bool bFreed;
};


class CTestObject : public CObject
{
CONSTRUCTABLE(CTestObject);
DESTRUCTABLE(CTestObject);
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

	bool	Save(CObjectWriter* pcFile) override;
	bool	Load(CObjectReader* pcFile) override;

	void	SomeMethod(void);
};


class CTestTriPointerObject : public CObject
{
CONSTRUCTABLE(CTestTriPointerObject);
DESTRUCTABLE(CTestTriPointerObject);
public:
	CPointer					mpObject1;
	CPointer					mpObject2;
	CPointer					mpObject3;
	STestObjectFreedNotifier*	mpsFreedNotifier;

	void	Init(void);
	void	Init(STestObjectFreedNotifier* psKilledNotifier);
	void	Class(void);
	void	Free(void);
};


class CTestSaveableObject1 : public CObject
{
CONSTRUCTABLE(CTestSaveableObject1);
DESTRUCTABLE(CTestSaveableObject1);
public:
	CPointer	mpObject;
	int32		miInt;
	CChars		mszString;
	bool		mbSaved;

	void		Init(void);
	void		Class(void);
	void		Free(void);

	bool		Save(CObjectWriter* pcFile) override;
	bool		Load(CObjectReader* pcFile) override;
};


class CTestSaveableObject2 : public CObject
{
CONSTRUCTABLE(CTestSaveableObject2);
DESTRUCTABLE(CTestSaveableObject2);
public:
	CChars						msz;
	Ptr<CTestSaveableObject1>	mp1;
	CPointer					mp2;
	bool						mbSaved;

	void	Init(const char* psz);
	void	Class(void);
	void	Free(void);

	bool	Save(CObjectWriter* pcFile) override;
	bool	Load(CObjectReader* pcFile) override;
};



class CTestObjectWithFields : public CObject
{
CONSTRUCTABLE(CTestObjectWithFields);
DESTRUCTABLE(CTestObjectWithFields);
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

	void	Update(int8 i8);
	void	Update(char* sz);
}; 


class CTestEmbeddedObjectWithFields : public CObject
{
CONSTRUCTABLE(CTestEmbeddedObjectWithFields);
DESTRUCTABLE(CTestEmbeddedObjectWithFields);
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
};


class CTestEmbeddedStrings : public CObject
{
CONSTRUCTABLE(CTestEmbeddedStrings);
DESTRUCTABLE(CTestEmbeddedStrings);
public:
	CString		mString1;
	CString		mString2;
	CString		mString3;

	void	Init(void);
	void	Class(void);
	void	Free(void);
};


#endif // __OBJECT_TEST_CLASSES_H__

