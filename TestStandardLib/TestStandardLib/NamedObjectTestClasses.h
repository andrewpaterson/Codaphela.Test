#ifndef __NAMED_OBJECT_TEST_CLASSES_H__
#define __NAMED_OBJECT_TEST_CLASSES_H__
#include "StandardLib/NamedObject.h"
#include "StandardLib/Pointer.h"


class CTestNamedObject : public CNamedObject
{
BASE_FUNCTIONS(CTestNamedObject);
public:
	CPointer<CTestNamedObject>		mpNamedTest1;
	CPointer<CTestNamedObject>		mpNamedTest2;
	int								miNum;

	void Init(int iNum);
	void KillData(void);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


#endif // __NAMED_OBJECT_TEST_CLASSES_H__

