#ifndef __EMBEDDED_OBJECT_TEST_CLASSES_H__
#define __EMBEDDED_OBJECT_TEST_CLASSES_H__
#include "StandardLib/Object.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Array.h"
#include "StandardLib/ObjectSerialiser.h"
#include "StandardLib/ObjectDeserialiser.h"


class CEmbeddedTest : public CObject
{
BASE_FUNCTIONS(CEmbeddedTest);
public:
	int		miAmANumber;
	float	mfSoAmI;
	Ptr<>	mpTest;

	void				Class(void);
	Ptr<CEmbeddedTest>	Init(void);
	void				KillData(void);

	BOOL				Save(CObjectSerialiser* pcFile);
	BOOL				Load(CObjectDeserialiser* pcFile);
};


class CEmbeddedContainer : public CObject
{
BASE_FUNCTIONS(CEmbeddedContainer);
public:
	char				msz[4];
	CEmbeddedTest		mcOne;
	int					mi;
	CEmbeddedTest		mcTwo;
	float				mf;
	Ptr<>				mpTest;

	void	Class(void);
	Ptr<CEmbeddedContainer> Init(void);
	void	KillData(void);

	BOOL	Save(CObjectSerialiser* pcFile);
	BOOL	Load(CObjectDeserialiser* pcFile);
};


class CEmbeddedComplex : public CObject
{
BASE_FUNCTIONS(CEmbeddedComplex);
public:
	CEmbeddedTest		mcSimple;
	int					mai[2];
	CArray<>			ma;
	CEmbeddedContainer	mcContainer;
	Ptr<>				mpTest;

	void	Class(void);
	Ptr<CEmbeddedComplex> Init(void);
	void	KillData(void);

	BOOL	Save(CObjectSerialiser* pcFile);
	BOOL	Load(CObjectDeserialiser* pcFile);
};


#endif // __EMBEDDED_OBJECT_TEST_CLASSES_H__

