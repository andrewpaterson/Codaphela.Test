#ifndef __EMBEDDED_OBJECT_TEST_CLASSES_H__
#define __EMBEDDED_OBJECT_TEST_CLASSES_H__
#include "StandardLib/Object.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Array.h"
#include "StandardLib/ObjectSerialiser.h"
#include "StandardLib/ObjectDeserialiser.h"


class CEmbeddedTest : public CObject
{
CONSTRUCTABLE(CEmbeddedTest);
public:
	int		miAmANumber;
	float	mfSoAmI;
	Ptr<>	mpTest;

	void				Class(void);
	Ptr<CEmbeddedTest>	Init(void);
	void				Free(void);

	BOOL				Save(CObjectSerialiser* pcFile);
	BOOL				Load(CObjectDeserialiser* pcFile);
};


class CEmbeddedContainer : public CObject
{
CONSTRUCTABLE(CEmbeddedContainer);
public:
	char				msz[4];
	CEmbeddedTest		mcOne;
	int					mi;
	CEmbeddedTest		mcTwo;
	float				mf;
	Ptr<>				mpTest;

	void						Class(void);
	Ptr<CEmbeddedContainer>		Init(void);
	void						Free(void);

	BOOL						Save(CObjectSerialiser* pcFile);
	BOOL						Load(CObjectDeserialiser* pcFile);
};


class CEmbeddedComplex : public CObject
{
CONSTRUCTABLE(CEmbeddedComplex);
public:
	CEmbeddedTest		mcSimple;
	int					mai[2];
	CArray<>			ma;
	CEmbeddedContainer	mcContainer;
	Ptr<>				mpTest;

	void	Class(void);
	Ptr<CEmbeddedComplex> Init(void);
	void	Free(void);

	BOOL	Save(CObjectSerialiser* pcFile);
	BOOL	Load(CObjectDeserialiser* pcFile);
};


#endif // __EMBEDDED_OBJECT_TEST_CLASSES_H__

