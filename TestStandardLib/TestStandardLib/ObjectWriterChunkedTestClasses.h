#ifndef __OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__
#define __OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__
#include "StandardLib/Object.h"
#include "StandardLib/Array.h"


class CTestWithArray : public CObject
{
BASE_FUNCTIONS(CTestWithArray);
protected:
	CPointer<CArray>	mcArray;

public:
	CChars				mszString;
	int					mx;

	void Init(char* szString, int x);
	void Kill(void);

	void Add(CPointerObject pcObject);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


class CTestInteger : public CObject
{
BASE_FUNCTIONS(CTestWithArray);
public:
	int mx;
	int my; 
	int mz;

	void Init(int x, int y, int z);
	void Kill(void);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


#endif // __OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__
