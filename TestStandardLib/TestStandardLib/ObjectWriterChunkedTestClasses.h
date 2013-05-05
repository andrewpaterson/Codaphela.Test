#ifndef __OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__
#define __OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__
#include "StandardLib/Object.h"
#include "StandardLib/NamedObject.h"
#include "StandardLib/Array.h"
#include "StandardLib/String.h"


class CTestWithArray : public CNamedObject
{
BASE_FUNCTIONS(CTestWithArray);
public:
	CPointer<CArray>	mcArray;

	CChars				mszString;
	int					mx;

	void Init(char* szString, int x);
	void KillData(void);

	void Add(CPointerObject pcObject);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


class CTestInteger : public CObject
{
BASE_FUNCTIONS(CTestInteger);
public:
	int mx;
	int my; 
	int mz;

	void Init(int x, int y, int z);
	void KillData(void);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


class CTestNamedString : public CNamedObject
{
BASE_FUNCTIONS(CTestNamedString);
public:
	CPointer<CString>			mszString;
	CPointer<CTestNamedString>	mpAnother;
	CChars						mszEmbedded;

	void Init(CPointer<CString> szString, CPointer<CTestNamedString> pAnother, char* szEmbedded);
	void KillData(void);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


class CTestDoubleNamedString : public CNamedObject
{
BASE_FUNCTIONS(CTestDoubleNamedString);
public:
	CPointer<CString>			mszString;
	CPointer<CTestNamedString>	mpSplit2;
	CPointer<CTestNamedString>	mpSplit1;

	void Init(void);
	void Init(CPointer<CString> szString, CPointer<CTestNamedString> pSplit2, CPointer<CTestNamedString> pSplit1);
	void KillData(void);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


#endif // __OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__

