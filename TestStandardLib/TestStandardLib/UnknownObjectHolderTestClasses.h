#include "ObjectTestClasses.h"
#include "StandardLib/Unknown.h"


class CUnknownObjectHolder : public CUnknown
{
public:
	CTestObject* mpcTestObject;

	void	Init(void);
	void	Kill(void);
};

