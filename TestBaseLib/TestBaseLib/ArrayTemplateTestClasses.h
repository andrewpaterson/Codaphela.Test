#ifndef __ARRAY_TEMPLATE_TEST_CLASSES__
#define __ARRAY_TEMPLATE_TEST_CLASSES__
#include "BaseLib/ArrayTemplate.h"


struct STestArrayTemplateItem
{
	int	i1;
	int	i2;
};


typedef CArrayTemplate<STestArrayTemplateItem> CTestArray;


class CTestArrayTemplateItem : public STestArrayTemplateItem
{
public:
	virtual void Init(int i);
};


class CTestOverridenArrayTemplateItem : public CTestArrayTemplateItem
{
public:
	virtual void Init(int i);
};


typedef CArrayTemplate<CTestOverridenArrayTemplateItem> CTestOverriddenArray;


#endif // __ARRAY_TEMPLATE_TEST_CLASSES__


