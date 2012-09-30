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
BASE_FUNCTIONS(CTestObject);
public:
	CPointerObject				mpObject;
	CPointer<CTestObject>		mpTest;
	STestObjectKilledNotifier*	mpsKilledNotifier;

	void Init(STestObjectKilledNotifier* psKilledNotifier);
	void KillData(void);
	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


class CTestSaveableObject1 : public CNamedObject
{
BASE_FUNCTIONS(CTestSaveableObject1);
public:
	CPointerObject		mpObject;
	int					miInt;
	CChars				mszString;
	BOOL				mbSaved;

	void Init(void);
	void KillData(void);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


class CTestSaveableObject2 : public CNamedObject
{
BASE_FUNCTIONS(CTestSaveableObject2);
public:
	CChars							msz;
	CPointer<CTestSaveableObject1>	mp1;
	CPointerObject					mp2;
	BOOL							mbSaved;

	void Init(char* psz);
	void KillData(void);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


#endif // __OBJECT_TEST_CLASSES_H__

