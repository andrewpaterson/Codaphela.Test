#ifndef __OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__
#define __OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__
#include "StandardLib/Object.h"

#include "StandardLib/ArrayObject.h"
#include "StandardLib/String.h"


class CTestWithArray : public CObject
{
CONSTRUCTABLE(CTestWithArray);
DESTRUCTABLE(CTestWithArray);
public:
	Ptr<CArrayObject>	mcArray;

	CChars				mszString;
	int					mx;

public:
	void	Init(const char* szString, int x);
	void	Class(void);
	void	Free(void);

	void	Add(CPointer& pcObject);

	bool	Save(CObjectWriter* pcFile) override;
	bool	Load(CObjectReader* pcFile) override;
};


class CTestInteger : public CObject
{
CONSTRUCTABLE(CTestInteger);
DESTRUCTABLE(CTestInteger);
public:
	int mx;
	int my; 
	int mz;

	void	Init(int x, int y, int z);
	void	Class(void);
	void	Free(void);

	bool	Save(CObjectWriter* pcFile) override;
	bool	Load(CObjectReader* pcFile) override;
};


class CTestNamedString : public CObject
{
CONSTRUCTABLE(CTestNamedString);
DESTRUCTABLE(CTestNamedString);
public:
	Ptr<CString>			mszString;
	Ptr<CTestNamedString>	mpAnother;
	CChars					mszEmbedded;

	void	Init(void);
	void	Init(Ptr<CString> szString, Ptr<CTestNamedString> pAnother, const char* szEmbedded);
	void	Class(void);
	void	Free(void);

	void	Set(Ptr<CString> szString, Ptr<CTestNamedString> pAnother, const char* szEmbedded);

	bool	Save(CObjectWriter* pcFile) override;
	bool	Load(CObjectReader* pcFile) override;
};


class CTestDoubleNamedString : public CObject
{
CONSTRUCTABLE(CTestDoubleNamedString);
DESTRUCTABLE(CTestDoubleNamedString);
public:
	Ptr<CString>			mszString;
	Ptr<CTestNamedString>	mpSplit2;
	Ptr<CTestNamedString>	mpSplit1;

	void	Init(void);
	void	Init(Ptr<CString> szString, Ptr<CTestNamedString> pSplit2, Ptr<CTestNamedString> pSplit1);
	void	Class(void);
	void	Free(void);
};


#endif // !__OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__

