#include "ArrayTemplateTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestArrayTemplateItem::Init(int i)
{
	this->i2 = 2;
	this->i1 = i;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* CTestArrayTemplateItem::GetName(void)
{
	return "CTestArrayTemplateItem";
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestOverridenArrayTemplateItem::Init(int i)
{
	this->i2 = 33;
	this->i1 = i;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* CTestOverridenArrayTemplateItem::GetName(void)
{
	return "CTestOverridenArrayTemplateItem";
}

