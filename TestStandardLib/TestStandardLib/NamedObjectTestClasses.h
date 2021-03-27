#ifndef __NAMED_OBJECT_TEST_CLASSES_H__
#define __NAMED_OBJECT_TEST_CLASSES_H__
#include "StandardLib/NamedObject.h"
#include "StandardLib/Pointer.h"


class CTestNamedObject : public CNamedObject
{
CONSTRUCTABLE(CTestNamedObject);
public:
	Ptr<CTestNamedObject>	mpNamedTest1;
	Ptr<CTestNamedObject>	mpNamedTest2;
	int						miNum;

	Ptr<CTestNamedObject> Init(int iNum);
	void Class(void);
	void Free(void);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


class CTestNamedObjectSmall : public CNamedObject
{
CONSTRUCTABLE(CTestNamedObjectSmall);
public:
	char	mac[4];

	Ptr<CTestNamedObjectSmall> Init(char* sz);
	void Class(void);
	void Free(void);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


#endif // __NAMED_OBJECT_TEST_CLASSES_H__

