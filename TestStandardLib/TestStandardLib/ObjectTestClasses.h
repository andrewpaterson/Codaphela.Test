#ifndef __OBJECT_TEST_CLASSES_H__
#define __OBJECT_TEST_CLASSES_H__
#include "StandardLib/Object.h"
#include "StandardLib/NamedObject.h"
#include "StandardLib/Pointer.h"


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


#endif // __OBJECT_TEST_CLASSES_H__

