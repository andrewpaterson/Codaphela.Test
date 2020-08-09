#ifndef __OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__
#define __OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__
#include "StandardLib/Object.h"
#include "StandardLib/NamedObject.h"
#include "StandardLib/ArrayObject.h"
#include "StandardLib/String.h"


class CTestWithArray : public CNamedObject
{
CONSTRUCTABLE(CTestWithArray);
public:
	Ptr<CArrayObject>	mcArray;

	CChars		mszString;
	int			mx;

	Ptr<CTestWithArray>	Init(char* szString, int x);
	void				Class(void);
	void				KillData(void);

	void				Add(CPointer& pcObject);

	BOOL				Save(CObjectSerialiser* pcFile);
	BOOL				Load(CObjectDeserialiser* pcFile);
};


class CTestInteger : public CObject
{
CONSTRUCTABLE(CTestInteger);
public:
	int mx;
	int my; 
	int mz;

	Ptr<CTestInteger>	Init(int x, int y, int z);
	void				Class(void);
	void				KillData(void);

	BOOL				Save(CObjectSerialiser* pcFile);
	BOOL				Load(CObjectDeserialiser* pcFile);
};


class CTestNamedString : public CNamedObject
{
CONSTRUCTABLE(CTestNamedString);
public:
	Ptr<CString>			mszString;
	Ptr<CTestNamedString>	mpAnother;
	CChars					mszEmbedded;

	Ptr<CTestNamedString>	Init(void);
	Ptr<CTestNamedString>	Init(Ptr<CString> szString, Ptr<CTestNamedString> pAnother, char* szEmbedded);
	void					Class(void);
	void					KillData(void);

	BOOL					Save(CObjectSerialiser* pcFile);
	BOOL					Load(CObjectDeserialiser* pcFile);
};


class CTestDoubleNamedString : public CNamedObject
{
CONSTRUCTABLE(CTestDoubleNamedString);
public:
	Ptr<CString>			mszString;
	Ptr<CTestNamedString>	mpSplit2;
	Ptr<CTestNamedString>	mpSplit1;

	Ptr<CTestDoubleNamedString>	Init(void);
	Ptr<CTestDoubleNamedString>	Init(Ptr<CString> szString, Ptr<CTestNamedString> pSplit2, Ptr<CTestNamedString> pSplit1);
	void						Class(void);
	void						KillData(void);

	BOOL						Save(CObjectSerialiser* pcFile);
	BOOL						Load(CObjectDeserialiser* pcFile);
};


#endif // __OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__

