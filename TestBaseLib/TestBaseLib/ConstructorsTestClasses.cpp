#include "ConstructorsTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CConstructorTestSuper1::Method1(void)
{
	return 1;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* CConstructorTestSuper2::GetName(void)
{
	return "CConstructorTestSuper2";
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CConstructorTestSuper2::GetSize(void)
{
	return sizeof(CConstructorTestSuper2);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CConstructorTestSuper2::Method2(void)
{
	return 2;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* CConstructorTestClass::GetName(void)
{
	return "CConstructorTestClass";
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CConstructorTestClass::GetSize(void)
{
	return sizeof(CConstructorTestClass);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CConstructorTestClass::Method1(void)
{
	return 3;
}
