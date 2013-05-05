#include "BaseLib/FastFunctions.h"
#include "BaseLib/Define.h"
#include "TestLib/Assert.h"
#include "stdio.h"
#include "CoreLib/Operators.h"
#include "CoreLib/TypeConverter.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestOperatorAdd(void)
{
	OperatorsInit();

	int	ix, iy, iz;
	unsigned long long int ullix, ulliy, ulliz;
	char cx, cy, cz;

	ix = 3;
	iy = 4;
	gcOperators.mcAdd.Do(PT_int, &iz, PT_int, &ix, PT_int, &iy);
	AssertInt(7, iz);

	ullix = 0x00ffffffffffffffLL;
	ulliy = 0x7fedcba987654321LL;
	gcOperators.mcAdd.Do(PT_long, &ulliz, PT_long, &ullix, PT_long, &ulliy);
	AssertLongLongInt(0x80edcba987654320LL, ulliz);

	cx = 31;
	cy = 76;
	gcOperators.mcAdd.Do(PT_char, &cz, PT_char, &cx, PT_char, &cy);
	AssertChar(0x6b, cz);

	gcOperators.mcAdd.Do(PT_char, &cz, PT_long, &ullix, PT_long, &ulliy);
	AssertChar(0x20, cz);

	gcOperators.mcAdd.Do(PT_int, &iz, PT_long, &ullix, PT_char, &cy);
	AssertInt(0x4b, iz);

	OperatorsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestOperators(void)
{
	BeginTests();
	FastFunctionsInit();    
	TypeConverterInit();

	TestOperatorAdd();

	TypeConverterKill();
	FastFunctionsKill();    
	TestStatistics();
}

