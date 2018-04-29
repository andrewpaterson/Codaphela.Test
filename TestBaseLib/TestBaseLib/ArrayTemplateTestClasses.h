#ifndef __ARRAY_TEMPLATE_TEST_CLASSES__
#define __ARRAY_TEMPLATE_TEST_CLASSES__


struct STestArrayTemplateItem
{
	int	i1;
	int	i2;
};


class CTestArrayTemplateItem : public STestArrayTemplateItem
{
public:
	virtual void	Init(int i);
	virtual char*	GetName(void);
};


class CTestOverridenArrayTemplateItem : public CTestArrayTemplateItem
{
public:
	void	Init(int i);
	char*	GetName(void);
};


#endif // __ARRAY_TEMPLATE_TEST_CLASSES__


