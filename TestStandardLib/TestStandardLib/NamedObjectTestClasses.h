#ifndef __NAMED_OBJECT_TEST_CLASSES_H__
#define __NAMED_OBJECT_TEST_CLASSES_H__
#include "StandardLib/Object.h"
#include "StandardLib/Pointer.h"


class CTestNamedObject : public CObject
{
CONSTRUCTABLE(CTestNamedObject);
DESTRUCTABLE(CTestNamedObject);
public:
	Ptr<CTestNamedObject>	mpNamedTest1;
	Ptr<CTestNamedObject>	mpNamedTest2;
	int						miNum;

	Ptr<CTestNamedObject> Init(int iNum);
	void Class(void);
	void Free(void);

	bool Save(CObjectWriter* pcFile) override;
	bool Load(CObjectReader* pcFile) override;
};


class CTestNamedObjectSmall : public CObject
{
CONSTRUCTABLE(CTestNamedObjectSmall);
DESTRUCTABLE(CTestNamedObjectSmall);
public:
	char	mac[4];

	Ptr<CTestNamedObjectSmall> Init(char* sz);
	Ptr<CTestNamedObjectSmall> Init(const char* sz);
	void Class(void);
	void Free(void);

	bool Save(CObjectWriter* pcFile) override;
	bool Load(CObjectReader* pcFile) override;
};


class CTestNamedObjectWithEmbedded : public CObject
{
CONSTRUCTABLE(CTestNamedObjectWithEmbedded);
DESTRUCTABLE(CTestNamedObjectWithEmbedded);
public:
	CTestNamedObject				mNamedTest1;
	CTestNamedObject				mNamedTest2;
	CPointer						mpObject;
	Ptr<CTestNamedObjectSmall>		mpSmall;
	int								miX;
	int								miY;
	void*							mpvUnmanaged;
	int								miUnmagedSize;

	Ptr<CTestNamedObjectWithEmbedded> Init(int iX, int iY, int iName1, int iName2, CPointer pObject, Ptr<CTestNamedObjectSmall> pSmall);
	void Class(void);
	void Free(void);

	bool Save(CObjectWriter* pcFile) override;
	bool Load(CObjectReader* pcFile) override;
};


#endif // __NAMED_OBJECT_TEST_CLASSES_H__

