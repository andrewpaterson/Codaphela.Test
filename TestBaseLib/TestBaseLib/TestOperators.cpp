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
void TestOperatorCompare(void)
{
	OperatorsInit();

	int			ix, iy;
	int64_t		llix;
	char		cx;
	double		dx;
	bool		bx, by;
	bool		bResult;

	ix = 3;
	iy = 4;
	gcOperators.mcEqual.Do(&bResult, PT_int32, &ix, PT_int32, &iy);
	AssertFalse(bResult);
	gcOperators.mcNotEqual.Do(&bResult, PT_int32, &ix, PT_int32, &iy);
	AssertTrue(bResult);
	gcOperators.mcLess.Do(&bResult, PT_int32, &ix, PT_int32, &iy);
	AssertTrue(bResult);
	gcOperators.mcLessOrEqual.Do(&bResult, PT_int32, &ix, PT_int32, &ix);
	AssertTrue(bResult);
	gcOperators.mcGreater.Do(&bResult, PT_int32, &ix, PT_int32, &iy);
	AssertFalse(bResult);
	gcOperators.mcGreaterOrEqual.Do(&bResult, PT_int32, &iy, PT_int32, &ix);
	AssertTrue(bResult);

	llix = 0x7fedcba987654321LL;
	cx = 76;
	gcOperators.mcGreater.Do(&bResult, PT_int64, &llix, PT_char8, &cx);
	AssertTrue(bResult);
	gcOperators.mcLess.Do(&bResult, PT_char8, &cx, PT_int64, &llix);
	AssertTrue(bResult);

	dx = 3.0;
	gcOperators.mcEqual.Do(&bResult, PT_float64, &dx, PT_int32, &ix);
	AssertTrue(bResult);
	gcOperators.mcLessOrEqual.Do(&bResult, PT_int32, &iy, PT_float64, &dx);
	AssertFalse(bResult);

	bx = true;
	by = false;
	gcOperators.mcEqual.Do(&bResult, PT_bool, &bx, PT_bool, &by);
	AssertFalse(bResult);
	gcOperators.mcNotEqual.Do(&bResult, PT_bool, &bx, PT_bool, &by);
	AssertTrue(bResult);

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

	TestOperatorCompare();

	TypeConverterKill();
	TestStatistics();
}

