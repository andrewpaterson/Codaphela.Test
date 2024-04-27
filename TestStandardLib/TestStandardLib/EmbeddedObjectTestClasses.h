#ifndef __EMBEDDED_OBJECT_TEST_CLASSES_H__
#define __EMBEDDED_OBJECT_TEST_CLASSES_H__
#include "StandardLib/Object.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Array.h"
#include "StandardLib/ObjectWriter.h"
#include "StandardLib/ObjectReader.h"


class CEmbeddedTest : public CObject
{
CONSTRUCTABLE(CEmbeddedTest);
DESTRUCTABLE(CEmbeddedTest);
public:
	int		miAmANumber;
	float	mfSoAmI;
	Ptr<>	mpTest;

	void				Class(void);
	Ptr<CEmbeddedTest>	Init(void);
	void				Free(void);

	bool				Save(CObjectWriter* pcFile) override;
	bool				Load(CObjectReader* pcFile) override;
};


class CEmbeddedContainer : public CObject
{
CONSTRUCTABLE(CEmbeddedContainer);
DESTRUCTABLE(CEmbeddedContainer);
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

	bool						Save(CObjectWriter* pcFile) override;
	bool						Load(CObjectReader* pcFile) override;
};


class CEmbeddedComplex : public CObject
{
CONSTRUCTABLE(CEmbeddedComplex);
DESTRUCTABLE(CEmbeddedComplex);
public:
	CEmbeddedTest		mcSimple;
	int					mai[2];
	CArray<>			ma;
	CEmbeddedContainer	mcContainer;
	Ptr<>				mpTest;

	void	Class(void);
	Ptr<CEmbeddedComplex> Init(void);
	void	Free(void);

	void	Add(Ptr<> pObject);

	bool	Save(CObjectWriter* pcFile) override;
	bool	Load(CObjectReader* pcFile) override;
};


#endif // __EMBEDDED_OBJECT_TEST_CLASSES_H__

