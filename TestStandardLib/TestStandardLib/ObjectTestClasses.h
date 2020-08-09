#ifndef __OBJECT_TEST_CLASSES_H__
#define __OBJECT_TEST_CLASSES_H__
#include "StandardLib/Object.h"
#include "StandardLib/NamedObject.h"
#include "StandardLib/Pointer.h"


struct STestObjectKilledNotifier
{
	BOOL bKilled;
};


class CTestObject : public CObject
{
CONSTRUCTABLE(CTestObject);
public:
	CPointer					mpObject;
	Ptr<CTestObject>			mpTest;
	STestObjectKilledNotifier*	mpsKilledNotifier;

	Ptr<CTestObject>	Init(void);
	Ptr<CTestObject>	Init(STestObjectKilledNotifier* psKilledNotifier);
	Ptr<CTestObject>	Init(CPointer pObject, Ptr<CTestObject> pTest);
	void				Class(void);
	void				KillData(void);

	BOOL				Save(CObjectSerialiser* pcFile);
	BOOL				Load(CObjectDeserialiser* pcFile);
};


class CTestTriPointerObject : public CObject
{
CONSTRUCTABLE(CTestTriPointerObject);
public:
	CPointer					mpObject1;
	CPointer					mpObject2;
	CPointer					mpObject3;
	STestObjectKilledNotifier*	mpsKilledNotifier;

	Ptr<CTestTriPointerObject>	Init(void);
	Ptr<CTestTriPointerObject>	Init(STestObjectKilledNotifier* psKilledNotifier);
	void						Class(void);
	void						KillData(void);

	BOOL						Save(CObjectSerialiser* pcFile);
	BOOL						Load(CObjectDeserialiser* pcFile);
};


class CTestSaveableObject1 : public CNamedObject
{
CONSTRUCTABLE(CTestSaveableObject1);
public:
	CPointer	mpObject;
	int			miInt;
	CChars		mszString;
	BOOL		mbSaved;

	Ptr<CTestSaveableObject1>	Init(void);
	void						Class(void);
	void						KillData(void);

	BOOL						Save(CObjectSerialiser* pcFile);
	BOOL						Load(CObjectDeserialiser* pcFile);
};


class CTestSaveableObject2 : public CNamedObject
{
CONSTRUCTABLE(CTestSaveableObject2);
public:
	CChars						msz;
	Ptr<CTestSaveableObject1>	mp1;
	CPointer					mp2;
	BOOL						mbSaved;

	Ptr<CTestSaveableObject2>	Init(char* psz);
	void						Class(void);
	void						KillData(void);

	BOOL						Save(CObjectSerialiser* pcFile);
	BOOL						Load(CObjectDeserialiser* pcFile);
};


#endif // __OBJECT_TEST_CLASSES_H__

