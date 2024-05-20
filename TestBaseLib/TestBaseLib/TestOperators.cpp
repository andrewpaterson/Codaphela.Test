#include "stdio.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/Define.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/Operators.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestOperatorAdd(void)
{
	OperatorsInit();

	int	ix, iy, iz;
	uint64_t ullix, ulliy, ulliz;
	char cx, cy, cz;

	ix = 3;
	iy = 4;
	gcOperators.mcAdd.Do(PT_int32, &iz, PT_int32, &ix, PT_int32, &iy);
	AssertInt(7, iz);

	ullix = 0x00ffffffffffffffLL;
	ulliy = 0x7fedcba987654321LL;
	gcOperators.mcAdd.Do(PT_int64, &ulliz, PT_int64, &ullix, PT_int64, &ulliy);
	AssertLong(0x80edcba987654320LL, ulliz);

	cx = 31;
	cy = 76;
	gcOperators.mcAdd.Do(PT_char8, &cz, PT_char8, &cx, PT_char8, &cy);
	AssertChar(0x6b, cz);

	gcOperators.mcAdd.Do(PT_char8, &cz, PT_int64, &ullix, PT_int64, &ulliy);
	AssertChar(0x20, cz);

	gcOperators.mcAdd.Do(PT_int32, &iz, PT_int64, &ullix, PT_char8, &cy);
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
	TypeConverterInit();

	TestOperatorAdd();

	TypeConverterKill();
	TestStatistics();
}

