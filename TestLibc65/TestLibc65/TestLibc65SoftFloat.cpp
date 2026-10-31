#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "BaseLib/Chars.h"
#include "TestLib/Assert.h"
#include "TestLibc65Context.h"


//Libc65/softfloat.cpp compiled natively (TestLibc65SoftFloatReference.cpp).
extern "C"
{
uint32_t	SoftFloatAdd(uint32_t uiA, uint32_t uiB);
uint32_t	SoftFloatSubtract(uint32_t uiA, uint32_t uiB);
uint32_t	SoftFloatMultiply(uint32_t uiA, uint32_t uiB);
uint32_t	SoftFloatDivide(uint32_t uiA, uint32_t uiB);
int			SoftFloatCompare(uint32_t uiA, uint32_t uiB);
uint32_t	SoftFloatFromInt(int32_t i);
uint32_t	SoftFloatFromUnsigned(uint32_t ui);
uint32_t	SoftFloatFromLongLong(int64_t lli);
uint32_t	SoftFloatFromUnsignedLongLong(uint64_t ulli);
int32_t		SoftFloatToInt(uint32_t ui);
uint32_t	SoftFloatToUnsigned(uint32_t ui);
int64_t		SoftFloatToLongLong(uint32_t ui);
uint64_t	SoftFloatToUnsignedLongLong(uint32_t ui);
uint64_t	SoftFloatToDouble(uint32_t ui);
uint32_t	SoftFloatSqrt(uint32_t ui);
uint32_t	SoftDoubleToFloat(uint64_t ulli);
uint64_t	SoftDoubleAdd(uint64_t ulliA, uint64_t ulliB);
uint64_t	SoftDoubleSubtract(uint64_t ulliA, uint64_t ulliB);
uint64_t	SoftDoubleMultiply(uint64_t ulliA, uint64_t ulliB);
uint64_t	SoftDoubleDivide(uint64_t ulliA, uint64_t ulliB);
int			SoftDoubleCompare(uint64_t ulliA, uint64_t ulliB);
uint64_t	SoftDoubleFromInt(int32_t i);
uint64_t	SoftDoubleFromUnsigned(uint32_t ui);
uint64_t	SoftDoubleFromLongLong(int64_t lli);
uint64_t	SoftDoubleFromUnsignedLongLong(uint64_t ulli);
int32_t		SoftDoubleToInt(uint64_t ulli);
uint32_t	SoftDoubleToUnsigned(uint64_t ulli);
int64_t		SoftDoubleToLongLong(uint64_t ulli);
uint64_t	SoftDoubleToUnsignedLongLong(uint64_t ulli);
uint64_t	SoftDoubleSqrt(uint64_t ulli);
}


//Where the test program reads its arguments (8 bytes each, a double's second argument from
//TEST_SOFT_FLOAT_SECONDS) and writes its results (8 bytes each).
#define TEST_SOFT_FLOAT_ARGUMENTS	0x110000
#define TEST_SOFT_FLOAT_SECONDS		0x138000
#define TEST_SOFT_FLOAT_RESULTS		0x160000
#define TEST_SOFT_FLOAT_MAX_CASES	0x5000


enum ETestSoftFloatKind
{
	TSFK_FloatFloatToFloat,
	TSFK_FloatFloatToInt,
	TSFK_FloatToFloat,
	TSFK_FloatToInt,
	TSFK_FloatToLongLong,
	TSFK_IntToFloat,
	TSFK_LongLongToFloat,
	TSFK_DoubleToFloat,
	TSFK_DoubleDoubleToDouble,
	TSFK_DoubleDoubleToInt,
	TSFK_DoubleToDouble,
	TSFK_DoubleToInt,
	TSFK_DoubleToLongLong,
	TSFK_IntToDouble,
	TSFK_LongLongToDouble,
	TSFK_DoubleIntToDouble,		//ldexp
	TSFK_DoubleToDoubleInt,		//frexp: the int written through its pointer to the second argument's place
	TSFK_DoubleToDoubleDouble,	//modf: the double likewise
};


struct STestSoftFloatCases
{
	uint64	auiFirst[TEST_SOFT_FLOAT_MAX_CASES];
	uint64	auiSecond[TEST_SOFT_FLOAT_MAX_CASES];
	size	uiCount;
};


//Floats where the special cases are: zeros, infinities, NaNs (quiet and signalling), subnormals, the normal
//limits and values around the integer limits.
static const uint32	gauiTestSoftFloatSpecials[] =
{
	0x00000000, 0x80000000, 0x7F800000, 0xFF800000, 0x7FC00000, 0xFFC00000, 0x7F800001, 0xFFBFFFFF, 0x7FA12345,
	0x00000001, 0x80000001, 0x007FFFFF, 0x807FFFFF, 0x00400000, 0x00800000, 0x80800000, 0x7F7FFFFF, 0xFF7FFFFF,
	0x3F800000, 0xBF800000, 0x3F7FFFFF, 0x3FFFFFFF, 0x40000000, 0x3F000000, 0x4B000000, 0x4AFFFFFF, 0x4EFFFFFF,
	0x4F000000, 0xCF000000, 0xCF000001, 0x4F800000, 0x5F000000, 0xDF000000, 0x5F800000, 0x1F800000, 0x20000000,
};


//Doubles where the special cases are, as for floats.
static const uint64	gaulliTestSoftDoubleSpecials[] =
{
	0x0000000000000000ULL, 0x8000000000000000ULL, 0x7FF0000000000000ULL, 0xFFF0000000000000ULL, 0x7FF8000000000000ULL,
	0xFFF8000000000000ULL, 0x7FF0000000000001ULL, 0xFFF7FFFFFFFFFFFFULL, 0x7FF4123456789ABCULL, 0x0000000000000001ULL,
	0x8000000000000001ULL, 0x000FFFFFFFFFFFFFULL, 0x800FFFFFFFFFFFFFULL, 0x0008000000000000ULL, 0x0010000000000000ULL,
	0x8010000000000000ULL, 0x7FEFFFFFFFFFFFFFULL, 0xFFEFFFFFFFFFFFFFULL, 0x3FF0000000000000ULL, 0xBFF0000000000000ULL,
	0x3FEFFFFFFFFFFFFFULL, 0x3FFFFFFFFFFFFFFFULL, 0x4000000000000000ULL, 0x3FE0000000000000ULL, 0x4330000000000000ULL,
	0x432FFFFFFFFFFFFFULL, 0x41DFFFFFFFC00000ULL, 0x41E0000000000000ULL, 0xC1E0000000000000ULL, 0xC1E0000000200000ULL,
	0x41F0000000000000ULL, 0x43E0000000000000ULL, 0xC3E0000000000000ULL, 0x43F0000000000000ULL, 0x1FF0000000000000ULL,
	0x2000000000000000ULL,
};


static uint64	gulliTestSoftFloatRandom;


//////////////////////////////////////////////////////////////////////////
//
// xorshift64, so the cases are the same on every run.
//
//////////////////////////////////////////////////////////////////////////
static uint64 TestSoftFloatRandom(void)
{
	gulliTestSoftFloatRandom ^= gulliTestSoftFloatRandom << 13;
	gulliTestSoftFloatRandom ^= gulliTestSoftFloatRandom >> 7;
	gulliTestSoftFloatRandom ^= gulliTestSoftFloatRandom << 17;
	return gulliTestSoftFloatRandom;
}


//////////////////////////////////////////////////////////////////////////
//
// A float that is often near uiNear (the same or a close exponent, or nearly equal), at the edges of the
// exponents (overflow and underflow), subnormal, special, or has few fraction bits (exact results and ties).
//
//////////////////////////////////////////////////////////////////////////
static uint32 TestSoftFloatRandomFloat(uint32 uiNear)
{
	uint64	ulli;
	uint32	uiSign;
	uint32	uiFraction;
	int		iExponent;

	ulli = TestSoftFloatRandom();
	uiSign = (uint32)(ulli >> 63) << 31;
	uiFraction = (uint32)(ulli >> 8) & 0x7FFFFF;
	switch ((ulli >> 32) % 12)
	{
	case 0:
	case 1:
		return (uint32)ulli;
	case 2:
		return gauiTestSoftFloatSpecials[(ulli >> 40) % (sizeof(gauiTestSoftFloatSpecials) / sizeof(uint32))];
	case 3:
		return uiSign | (uiFraction >> ((ulli >> 40) % 24));
	case 4:
		return uiSign | ((uint32)((ulli >> 40) % 40) << 23) | uiFraction;
	case 5:
		return uiSign | ((254 - (uint32)((ulli >> 40) % 40)) << 23) | uiFraction;
	case 6:
	case 7:
		iExponent = (int)((uiNear >> 23) & 255) + (int)((ulli >> 40) % 61) - 30;
		iExponent = (iExponent < 0) ? 0 : ((iExponent > 254) ? 254 : iExponent);
		return uiSign | ((uint32)iExponent << 23) | uiFraction;
	case 8:
		return (uiNear ^ uiSign) + (uint32)((int)((ulli >> 40) % 9) - 4);
	case 9:
		return uiSign | ((100 + (uint32)((ulli >> 40) % 56)) << 23) | (uiFraction & (0x7FFFFF << ((ulli >> 48) % 24)));
	default:
		return uiSign | ((64 + (uint32)((ulli >> 40) % 128)) << 23) | uiFraction;
	}
}


//////////////////////////////////////////////////////////////////////////
//
// An integer of a random length, a power of two and its neighbours, negative, or 25 bits shifted up (ties).
//
//////////////////////////////////////////////////////////////////////////
static uint64 TestSoftFloatRandomInteger(int iBits)
{
	uint64	ulliChoice;
	uint64	ulli;

	ulliChoice = TestSoftFloatRandom();
	ulli = TestSoftFloatRandom();
	switch (ulliChoice % 6)
	{
	case 0:
		break;
	case 1:
		ulli = ((uint64)1 << ((ulliChoice >> 8) % iBits)) + (uint64)((int)((ulliChoice >> 16) % 7) - 3);
		break;
	case 2:
		ulli = 0 - (ulli & (((uint64)1 << ((ulliChoice >> 8) % iBits)) - 1));
		break;
	case 3:
		ulli = ((ulli & 0x3FFFFFF) | 0x2000000) << ((ulliChoice >> 8) % (iBits - 25));
		break;
	default:
		ulli >>= (ulliChoice >> 8) % iBits;
		break;
	}
	if (iBits == 32)
	{
		ulli &= 0xFFFFFFFF;
	}
	return ulli;
}


//////////////////////////////////////////////////////////////////////////
//
// A double around the float range: any bits, a float's value, near the float limits, or halfway between
// two floats.
//
//////////////////////////////////////////////////////////////////////////
static uint64 TestSoftFloatRandomDouble(void)
{
	uint64	ulli;

	ulli = TestSoftFloatRandom();
	switch ((ulli >> 60) % 6)
	{
	case 0:
		return TestSoftFloatRandom();
	case 1:
		return SoftFloatToDouble(TestSoftFloatRandomFloat(0));
	case 2:
		return (TestSoftFloatRandom() & 0x800FFFFFFFFFFFFFULL) | ((uint64)(1023 - 126 - (ulli % 40)) << 52);
	case 3:
		//Up to two exponents past the largest float's, half with the float fraction all 1s so rounding carries into the exponent (to infinity from the largest).
		return (TestSoftFloatRandom() & 0x800FFFFFFFFFFFFFULL) | ((uint64)(1023 + 129 - (ulli % 8)) << 52) | (((ulli >> 8) & 1) ? 0x000FFFFFE0000000ULL : 0);
	case 4:
		return (SoftFloatToDouble(TestSoftFloatRandomFloat(0)) | ((uint64)1 << 28)) ^ (ulli & 1);
	default:
		return (TestSoftFloatRandom() & 0x800FFFFFFFFFFFFFULL) | ((uint64)(1023 - 60 + (ulli % 120)) << 52);
	}
}


//////////////////////////////////////////////////////////////////////////
//
// A double that is often near ulliNear, at the edges of the exponents, subnormal, special, or
// has few fraction bits, as TestSoftFloatRandomFloat.
//
//////////////////////////////////////////////////////////////////////////
static uint64 TestSoftFloatRandomDoubleNear(uint64 ulliNear)
{
	uint64	ulli;
	uint64	ulliSign;
	uint64	ulliFraction;
	int		iExponent;

	ulli = TestSoftFloatRandom();
	ulliSign = TestSoftFloatRandom() & 0x8000000000000000ULL;
	ulliFraction = TestSoftFloatRandom() & 0xFFFFFFFFFFFFFULL;
	switch (ulli % 12)
	{
	case 0:
	case 1:
		return TestSoftFloatRandom();
	case 2:
		return gaulliTestSoftDoubleSpecials[(ulli >> 8) % (sizeof(gaulliTestSoftDoubleSpecials) / sizeof(uint64))];
	case 3:
		return ulliSign | (ulliFraction >> ((ulli >> 8) % 53));
	case 4:
		return ulliSign | (((ulli >> 8) % 60) << 52) | ulliFraction;
	case 5:
		return ulliSign | ((2046 - (ulli >> 8) % 60) << 52) | ulliFraction;
	case 6:
	case 7:
		iExponent = (int)((ulliNear >> 52) & 2047) + (int)((ulli >> 8) % 121) - 60;
		iExponent = (iExponent < 0) ? 0 : ((iExponent > 2046) ? 2046 : iExponent);
		return ulliSign | ((uint64)iExponent << 52) | ulliFraction;
	case 8:
		return (ulliNear ^ ulliSign) + (uint64)((int)((ulli >> 8) % 9) - 4);
	case 9:
		return ulliSign | ((900 + (ulli >> 8) % 200) << 52) | (ulliFraction & (0xFFFFFFFFFFFFFULL << ((ulli >> 20) % 53)));
	default:
		return ulliSign | ((512 + (ulli >> 8) % 1024) << 52) | ulliFraction;
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Double pairs whose products the W65C816's truncated multiply (softfloat816.asm,
// MultiplyRows7Truncated) would round wrongly without its fall back: a carry from the products
// left out reaches the round bit.  Random cases almost never find one.
//
//////////////////////////////////////////////////////////////////////////
static const uint64 gaulliTestSoftDoublePairs[][2] =
{
	{0x44A00FBFFFCCDBEBULL, 0x42654A93FFFFFFFFULL},
	{0x3841BF257FFFD2E1ULL, 0x3CD43F85FC2FFFFFULL},
	{0x3D038BFFFFA6B8ACULL, 0x42EA3DBCC5FFFFFFULL},
	{0x3E833FFFF3C0762CULL, 0x3843817FFFFFFFFFULL},
	{0x43ABF374397FFFD6ULL, 0x411CAAF1FFFFFFFFULL},
	{0x3DCE50AA547FFFFEULL, 0x3DBC406AC303FFFFULL},
	{0x4414CDF2CA40FFFFULL, 0x3DB3318FFFFFFFFFULL},
	{0x385257FFFE69BC6CULL, 0x43E782D827FFFFFFULL},
	{0x4351376FFFFFF952ULL, 0x3B23880CE23FFFFFULL},
	{0x3ABFB040AFFFFC56ULL, 0x3C6F55C7FFFFFFFFULL},
	{0x42079599805FFFF2ULL, 0x43FF7544FFFFFFFFULL},
	{0x3D4568DFFFF59221ULL, 0x4017CEDFFFFFFFFFULL},
	{0x3AB4458FFFFE35CBULL, 0x40FBF4FFFFFFFFFFULL},
	{0x3A4A4C066530FFFFULL, 0x40FBCCB9CB9FFFFFULL},
	{0x38C544BFFFE7EDFEULL, 0x3E08D54C6763FFFFULL},
	{0x3AB1D1FFFF2D5C3FULL, 0x3981AFEDFFFFFFFFULL},
};


//////////////////////////////////////////////////////////////////////////
//
// Every pair of special floats (or every special float) and then uiRandom random cases.
//
//////////////////////////////////////////////////////////////////////////
static void TestSoftFloatMakeCases(STestSoftFloatCases* psCases, ETestSoftFloatKind eKind, size uiRandom)
{
	size	uiSpecials;
	size	i;
	size	j;
	uint64	ulliFirst;
	uint64	ulliSecond;
	uint64	ulli;

	gulliTestSoftFloatRandom = 0x9E3779B97F4A7C15ULL + eKind;
	uiSpecials = sizeof(gauiTestSoftFloatSpecials) / sizeof(uint32);
	psCases->uiCount = 0;
	if ((eKind == TSFK_DoubleDoubleToDouble) || (eKind == TSFK_DoubleDoubleToInt))
	{
		for (i = 0; i < sizeof(gaulliTestSoftDoublePairs) / sizeof(gaulliTestSoftDoublePairs[0]); i++)
		{
			psCases->auiFirst[psCases->uiCount] = gaulliTestSoftDoublePairs[i][0];
			psCases->auiSecond[psCases->uiCount] = gaulliTestSoftDoublePairs[i][1];
			psCases->uiCount++;
		}
		uiSpecials = sizeof(gaulliTestSoftDoubleSpecials) / sizeof(uint64);
		for (i = 0; i < uiSpecials; i++)
		{
			for (j = 0; j < uiSpecials; j++)
			{
				psCases->auiFirst[psCases->uiCount] = gaulliTestSoftDoubleSpecials[i];
				psCases->auiSecond[psCases->uiCount] = gaulliTestSoftDoubleSpecials[j];
				psCases->uiCount++;
			}
		}
	}
	else if ((eKind == TSFK_DoubleToDouble) || (eKind == TSFK_DoubleToInt) || (eKind == TSFK_DoubleToLongLong) || (eKind >= TSFK_DoubleIntToDouble))
	{
		uiSpecials = sizeof(gaulliTestSoftDoubleSpecials) / sizeof(uint64);
		for (i = 0; i < uiSpecials; i++)
		{
			psCases->auiFirst[psCases->uiCount] = gaulliTestSoftDoubleSpecials[i];
			psCases->auiSecond[psCases->uiCount] = 0;
			psCases->uiCount++;
		}
	}
	else if ((eKind == TSFK_FloatFloatToFloat) || (eKind == TSFK_FloatFloatToInt))
	{
		for (i = 0; i < uiSpecials; i++)
		{
			for (j = 0; j < uiSpecials; j++)
			{
				psCases->auiFirst[psCases->uiCount] = gauiTestSoftFloatSpecials[i];
				psCases->auiSecond[psCases->uiCount] = gauiTestSoftFloatSpecials[j];
				psCases->uiCount++;
			}
		}
	}
	else if ((eKind == TSFK_FloatToFloat) || (eKind == TSFK_FloatToInt) || (eKind == TSFK_FloatToLongLong))
	{
		for (i = 0; i < uiSpecials; i++)
		{
			psCases->auiFirst[psCases->uiCount] = gauiTestSoftFloatSpecials[i];
			psCases->auiSecond[psCases->uiCount] = 0;
			psCases->uiCount++;
		}
	}

	for (i = 0; i < uiRandom; i++)
	{
		switch (eKind)
		{
		case TSFK_DoubleIntToDouble:
			//Mostly the normal range's steps, some far past it and the extremes of an int.
			ulliFirst = TestSoftFloatRandomDoubleNear(TestSoftFloatRandom());
			ulli = TestSoftFloatRandom();
			switch (ulli % 4)
			{
			case 0:		ulliSecond = (uint64)(int64)((int)((ulli >> 8) % 121) - 60);		break;
			case 1:		ulliSecond = (uint64)(int64)((int)((ulli >> 8) % 2201) - 1100);	break;
			case 2:		ulliSecond = (uint64)(int64)((int)((ulli >> 8) % 4401) - 2200);	break;
			default:	ulliSecond = (uint64)(int64)(((ulli >> 8) & 1) ? 32767 : -32768);	break;
			}
			break;
		case TSFK_DoubleToDoubleInt:
		case TSFK_DoubleToDoubleDouble:
			ulliFirst = TestSoftFloatRandomDoubleNear(TestSoftFloatRandom());
			ulliSecond = 0;
			break;
		case TSFK_DoubleDoubleToDouble:
		case TSFK_DoubleDoubleToInt:
		case TSFK_DoubleToDouble:
		case TSFK_DoubleToInt:
		case TSFK_DoubleToLongLong:
			ulliFirst = TestSoftFloatRandomDoubleNear(TestSoftFloatRandom());
			ulliSecond = TestSoftFloatRandomDoubleNear(ulliFirst);
			break;
		case TSFK_IntToDouble:
		case TSFK_IntToFloat:
			ulliFirst = TestSoftFloatRandomInteger(32);
			ulliSecond = 0;
			break;
		case TSFK_LongLongToDouble:
		case TSFK_LongLongToFloat:
			ulliFirst = TestSoftFloatRandomInteger(64);
			ulliSecond = 0;
			break;
		case TSFK_DoubleToFloat:
			ulliFirst = TestSoftFloatRandomDouble();
			ulliSecond = 0;
			break;
		default:
			ulliFirst = TestSoftFloatRandomFloat((uint32)TestSoftFloatRandom());
			ulliSecond = TestSoftFloatRandomFloat((uint32)ulliFirst);
			break;
		}
		psCases->auiFirst[psCases->uiCount] = ulliFirst;
		psCases->auiSecond[psCases->uiCount] = ulliSecond;
		psCases->uiCount++;
	}
}


//////////////////////////////////////////////////////////////////////////
//
// math.cpp's functions that Libc65/softfloat816.asm has on the W65C816, as math.cpp has them, with
// the native soft float for their arithmetic (so the results are the 65C64's and must be the
// W65C816's, bit for bit).  frexp's and modf's second results go to gulliTestMathSecond.
//
//////////////////////////////////////////////////////////////////////////
static uint64	gulliTestMathSecond;
#define TEST_MATH_SIGN	0x8000000000000000ULL
#define TEST_MATH_ONE	0x3FF0000000000000ULL


static int TestMathExponent(uint64 ulli)
{
	return (int)((ulli >> 52) & 0x7FF) - 1023;
}


static int TestMathTopExponent(uint64 ulli)
{
	int		iExponent;

	iExponent = TestMathExponent(ulli);
	if (iExponent == -1023)
	{
		ulli &= 0x000FFFFFFFFFFFFFULL;
		iExponent = -1022;
		while (!(ulli & 0x0010000000000000ULL))
		{
			ulli <<= 1;
			iExponent--;
		}
	}
	return iExponent;
}


static bool TestMathIsNaNOrInfinity(uint64 ulli)
{
	return ((ulli >> 52) & 0x7FF) == 0x7FF;
}


static uint64 TestMathTrunc(uint64 ulli)
{
	int		iExponent;

	iExponent = TestMathExponent(ulli);
	if (iExponent >= 52)
	{
		return ulli;
	}
	if (iExponent < 0)
	{
		return ulli & TEST_MATH_SIGN;
	}
	return ulli & ~(0x000FFFFFFFFFFFFFULL >> iExponent);
}


static uint64 TestMathFloor(uint64 ulli)
{
	uint64	ulliTruncated;

	ulliTruncated = TestMathTrunc(ulli);
	return (SoftDoubleCompare(ulliTruncated, ulli) == 1) ? SoftDoubleSubtract(ulliTruncated, TEST_MATH_ONE) : ulliTruncated;
}


static uint64 TestMathCeil(uint64 ulli)
{
	uint64	ulliTruncated;

	ulliTruncated = TestMathTrunc(ulli);
	return (SoftDoubleCompare(ulliTruncated, ulli) == -1) ? SoftDoubleAdd(ulliTruncated, TEST_MATH_ONE) : ulliTruncated;
}


static uint64 TestMathRound(uint64 ulli)
{
	uint64	ulliTruncated;
	int		iCompare;

	ulliTruncated = TestMathTrunc(ulli);
	iCompare = SoftDoubleCompare(SoftDoubleSubtract(ulli, ulliTruncated) & ~TEST_MATH_SIGN, 0x3FE0000000000000ULL);
	if ((iCompare == 0) || (iCompare == 1))
	{
		return (SoftDoubleCompare(ulli, 0) == 1) ? SoftDoubleAdd(ulliTruncated, TEST_MATH_ONE) : SoftDoubleSubtract(ulliTruncated, TEST_MATH_ONE);
	}
	return ulliTruncated;
}


static uint64 TestMathLdexp(uint64 ulli, int iExponent)
{
	while (iExponent > 1023)
	{
		ulli = SoftDoubleMultiply(ulli, 0x7FE0000000000000ULL);
		iExponent -= 1023;
	}
	while (iExponent < -1022)
	{
		ulli = SoftDoubleMultiply(ulli, 0x0010000000000000ULL);
		iExponent += 1022;
	}
	return SoftDoubleMultiply(ulli, (uint64)(iExponent + 1023) << 52);
}


static uint64 TestMathFrexp(uint64 ulli, int* piExponent)
{
	int		iAdjust;

	*piExponent = 0;
	if ((SoftDoubleCompare(ulli, 0) == 0) || TestMathIsNaNOrInfinity(ulli))
	{
		return ulli;
	}
	iAdjust = 0;
	if (TestMathExponent(ulli) == -1023)
	{
		ulli = SoftDoubleMultiply(ulli, 0x4350000000000000ULL);
		iAdjust = -54;
	}
	*piExponent = TestMathExponent(ulli) + 1 + iAdjust;
	return (ulli & 0x800FFFFFFFFFFFFFULL) | 0x3FE0000000000000ULL;
}


static uint64 TestMathModf(uint64 ulli, uint64* pulliInteger)
{
	uint64	ulliFraction;

	*pulliInteger = TestMathTrunc(ulli);
	if (TestMathIsNaNOrInfinity(ulli) && (SoftDoubleCompare(ulli, ulli) == 0))
	{
		return ulli & TEST_MATH_SIGN;
	}
	ulliFraction = SoftDoubleSubtract(ulli, *pulliInteger);
	if (SoftDoubleCompare(ulliFraction, 0) == 0)
	{
		return ulli & TEST_MATH_SIGN;
	}
	return ulliFraction;
}


static uint64 TestMathFmod(uint64 ulliX, uint64 ulliY)
{
	uint64	ulliRemainder;
	uint64	ulliDivisor;
	uint64	ulliPart;
	int		iCompare;

	if ((SoftDoubleCompare(ulliY, 0) == 0) || TestMathIsNaNOrInfinity(ulliX) || (SoftDoubleCompare(ulliY, ulliY) == 2))
	{
		return SoftDoubleDivide(SoftDoubleSubtract(ulliX, ulliX), SoftDoubleAdd(SoftDoubleSubtract(ulliY, ulliY), SoftDoubleMultiply(0, ulliX)));
	}
	ulliRemainder = ulliX & ~TEST_MATH_SIGN;
	ulliDivisor = ulliY & ~TEST_MATH_SIGN;
	if (TestMathIsNaNOrInfinity(ulliY) || (SoftDoubleCompare(ulliRemainder, ulliDivisor) == -1))
	{
		return ulliX;
	}
	for (;;)
	{
		iCompare = SoftDoubleCompare(ulliRemainder, ulliDivisor);
		if ((iCompare != 0) && (iCompare != 1))
		{
			break;
		}
		ulliPart = TestMathLdexp(ulliDivisor, TestMathTopExponent(ulliRemainder) - TestMathTopExponent(ulliDivisor));
		if (SoftDoubleCompare(ulliPart, ulliRemainder) == 1)
		{
			ulliPart = SoftDoubleDivide(ulliPart, 0x4000000000000000ULL);
		}
		ulliRemainder = SoftDoubleSubtract(ulliRemainder, ulliPart);
	}
	return (SoftDoubleCompare(ulliX, 0) == -1) ? (ulliRemainder ^ TEST_MATH_SIGN) : ulliRemainder;
}


//A float function: math.cpp's in double.
static uint32 TestMathFloat(uint64 (*fDouble)(uint64), uint32 ui)
{
	return SoftDoubleToFloat(fDouble(SoftFloatToDouble(ui)));
}


//////////////////////////////////////////////////////////////////////////
//
// The native result of szName on a case.
//
//////////////////////////////////////////////////////////////////////////
static uint64 TestSoftFloatReference(const char* szName, uint64 ulliFirst, uint64 ulliSecond)
{
	uint32	uiFirst;
	uint32	uiSecond;

	uiFirst = (uint32)ulliFirst;
	uiSecond = (uint32)ulliSecond;
	if (strcmp(szName, "SoftFloatAdd") == 0)					return SoftFloatAdd(uiFirst, uiSecond);
	if (strcmp(szName, "SoftFloatSubtract") == 0)				return SoftFloatSubtract(uiFirst, uiSecond);
	if (strcmp(szName, "SoftFloatMultiply") == 0)				return SoftFloatMultiply(uiFirst, uiSecond);
	if (strcmp(szName, "SoftFloatDivide") == 0)					return SoftFloatDivide(uiFirst, uiSecond);
	if (strcmp(szName, "SoftFloatCompare") == 0)				return (uint32)SoftFloatCompare(uiFirst, uiSecond);
	if (strcmp(szName, "SoftFloatSqrt") == 0)					return SoftFloatSqrt(uiFirst);
	if (strcmp(szName, "SoftFloatToInt") == 0)					return (uint32)SoftFloatToInt(uiFirst);
	if (strcmp(szName, "SoftFloatToUnsigned") == 0)				return SoftFloatToUnsigned(uiFirst);
	if (strcmp(szName, "SoftFloatToLongLong") == 0)				return (uint64)SoftFloatToLongLong(uiFirst);
	if (strcmp(szName, "SoftFloatToUnsignedLongLong") == 0)		return SoftFloatToUnsignedLongLong(uiFirst);
	if (strcmp(szName, "SoftFloatToDouble") == 0)				return SoftFloatToDouble(uiFirst);
	if (strcmp(szName, "SoftFloatFromInt") == 0)				return SoftFloatFromInt((int32_t)uiFirst);
	if (strcmp(szName, "SoftFloatFromUnsigned") == 0)			return SoftFloatFromUnsigned(uiFirst);
	if (strcmp(szName, "SoftFloatFromLongLong") == 0)			return SoftFloatFromLongLong((int64_t)ulliFirst);
	if (strcmp(szName, "SoftFloatFromUnsignedLongLong") == 0)	return SoftFloatFromUnsignedLongLong(ulliFirst);
	if (strcmp(szName, "SoftDoubleToFloat") == 0)				return SoftDoubleToFloat(ulliFirst);
	if (strcmp(szName, "SoftDoubleAdd") == 0)					return SoftDoubleAdd(ulliFirst, ulliSecond);
	if (strcmp(szName, "SoftDoubleSubtract") == 0)				return SoftDoubleSubtract(ulliFirst, ulliSecond);
	if (strcmp(szName, "SoftDoubleMultiply") == 0)				return SoftDoubleMultiply(ulliFirst, ulliSecond);
	if (strcmp(szName, "SoftDoubleDivide") == 0)				return SoftDoubleDivide(ulliFirst, ulliSecond);
	if (strcmp(szName, "SoftDoubleCompare") == 0)				return (uint32)SoftDoubleCompare(ulliFirst, ulliSecond);
	if (strcmp(szName, "SoftDoubleSqrt") == 0)					return SoftDoubleSqrt(ulliFirst);
	if (strcmp(szName, "SoftDoubleToInt") == 0)					return (uint32)SoftDoubleToInt(ulliFirst);
	if (strcmp(szName, "SoftDoubleToUnsigned") == 0)			return SoftDoubleToUnsigned(ulliFirst);
	if (strcmp(szName, "SoftDoubleToLongLong") == 0)			return (uint64)SoftDoubleToLongLong(ulliFirst);
	if (strcmp(szName, "SoftDoubleToUnsignedLongLong") == 0)	return SoftDoubleToUnsignedLongLong(ulliFirst);
	if (strcmp(szName, "SoftDoubleFromInt") == 0)				return SoftDoubleFromInt((int32_t)uiFirst);
	if (strcmp(szName, "SoftDoubleFromUnsigned") == 0)			return SoftDoubleFromUnsigned(uiFirst);
	if (strcmp(szName, "SoftDoubleFromLongLong") == 0)			return SoftDoubleFromLongLong((int64_t)ulliFirst);
	if (strcmp(szName, "SoftDoubleFromUnsignedLongLong") == 0)	return SoftDoubleFromUnsignedLongLong(ulliFirst);
	if (strcmp(szName, "fabs") == 0)							return ulliFirst & ~TEST_MATH_SIGN;
	if (strcmp(szName, "fabsf") == 0)							return uiFirst & 0x7FFFFFFF;
	if (strcmp(szName, "sqrt") == 0)							return SoftDoubleSqrt(ulliFirst);
	if (strcmp(szName, "sqrtf") == 0)							return SoftFloatSqrt(uiFirst);
	if (strcmp(szName, "trunc") == 0)							return TestMathTrunc(ulliFirst);
	if (strcmp(szName, "floor") == 0)							return TestMathFloor(ulliFirst);
	if (strcmp(szName, "ceil") == 0)							return TestMathCeil(ulliFirst);
	if (strcmp(szName, "round") == 0)							return TestMathRound(ulliFirst);
	if (strcmp(szName, "truncf") == 0)							return TestMathFloat(TestMathTrunc, uiFirst);
	if (strcmp(szName, "floorf") == 0)							return TestMathFloat(TestMathFloor, uiFirst);
	if (strcmp(szName, "ceilf") == 0)							return TestMathFloat(TestMathCeil, uiFirst);
	if (strcmp(szName, "roundf") == 0)							return TestMathFloat(TestMathRound, uiFirst);
	if (strcmp(szName, "fmod") == 0)							return TestMathFmod(ulliFirst, ulliSecond);
	if (strcmp(szName, "fmodf") == 0)							return SoftDoubleToFloat(TestMathFmod(SoftFloatToDouble(uiFirst), SoftFloatToDouble(uiSecond)));
	if (strcmp(szName, "ldexp") == 0)							return TestMathLdexp(ulliFirst, (int)(int64)ulliSecond);
	if (strcmp(szName, "frexp") == 0)
	{
		int		iExponent;
		uint64	ulliResult;

		ulliResult = TestMathFrexp(ulliFirst, &iExponent);
		gulliTestMathSecond = (uint64)(int64)iExponent;
		return ulliResult;
	}
	if (strcmp(szName, "modf") == 0)							return TestMathModf(ulliFirst, &gulliTestMathSecond);
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//
// The test program: it calls szName (declared as szDeclaration) for each case and writes the results.
//
//////////////////////////////////////////////////////////////////////////
static void TestSoftFloatProgram(CChars* pszSource, const char* szName, ETestSoftFloatKind eKind, size uiCount)
{
	static const char*	aszDeclarations[] =
	{
		"uint32_t NAME(uint32_t uiA, uint32_t uiB);\n",
		"int NAME(uint32_t uiA, uint32_t uiB);\n",
		"uint32_t NAME(uint32_t ui);\n",
		"uint32_t NAME(uint32_t ui);\n",
		"uint64_t NAME(uint32_t ui);\n",
		"uint32_t NAME(uint32_t ui);\n",
		"uint32_t NAME(uint64_t ulli);\n",
		"uint32_t NAME(uint64_t ulli);\n",
		"uint64_t NAME(uint64_t ulliA, uint64_t ulliB);\n",
		"int NAME(uint64_t ulliA, uint64_t ulliB);\n",
		"uint64_t NAME(uint64_t ulli);\n",
		"uint32_t NAME(uint64_t ulli);\n",
		"uint64_t NAME(uint64_t ulli);\n",
		"uint64_t NAME(uint32_t ui);\n",
		"uint64_t NAME(uint64_t ulli);\n",
		"uint64_t NAME(uint64_t ulli, int i);\n",
		"uint64_t NAME(uint64_t ulli, int* pi);\n",
		"uint64_t NAME(uint64_t ulli, uint64_t* pulli);\n",
	};
	static const char*	aszCalls[] =
	{
		"		puiResult[2 * i] = NAME(puiArgument[2 * i], puiArgument[2 * i + 1]);\n",
		"		puiResult[2 * i] = (uint32_t)NAME(puiArgument[2 * i], puiArgument[2 * i + 1]);\n",
		"		puiResult[2 * i] = NAME(puiArgument[2 * i]);\n",
		"		puiResult[2 * i] = NAME(puiArgument[2 * i]);\n",
		"		pulliResult[i] = NAME(puiArgument[2 * i]);\n",
		"		puiResult[2 * i] = NAME(puiArgument[2 * i]);\n",
		"		puiResult[2 * i] = NAME(pulliArgument[i]);\n",
		"		puiResult[2 * i] = NAME(pulliArgument[i]);\n",
		"		pulliResult[i] = NAME(pulliArgument[i], pulliSecond[i]);\n",
		"		puiResult[2 * i] = (uint32_t)NAME(pulliArgument[i], pulliSecond[i]);\n",
		"		pulliResult[i] = NAME(pulliArgument[i]);\n",
		"		puiResult[2 * i] = NAME(pulliArgument[i]);\n",
		"		pulliResult[i] = NAME(pulliArgument[i]);\n",
		"		pulliResult[i] = NAME(puiArgument[2 * i]);\n",
		"		pulliResult[i] = NAME(pulliArgument[i]);\n",
		"		pulliResult[i] = NAME(pulliArgument[i], (int)pulliSecond[i]);\n",
		"		pulliResult[i] = NAME(pulliArgument[i], (int*)&pulliSecond[i]);\n",
		"		pulliResult[i] = NAME(pulliArgument[i], &pulliSecond[i]);\n",
	};

	pszSource->Init();
	pszSource->Append("#include <stdint.h>\n");
	pszSource->Append("extern \"C\" ");
	pszSource->Append(aszDeclarations[eKind]);
	pszSource->Append("int main(void)\n");
	pszSource->Append("{\n");
	pszSource->Append("	uint32_t*	puiArgument = (uint32_t*)")->Append(TEST_SOFT_FLOAT_ARGUMENTS)->Append(";\n");
	pszSource->Append("	uint64_t*	pulliArgument = (uint64_t*)")->Append(TEST_SOFT_FLOAT_ARGUMENTS)->Append(";\n");
	pszSource->Append("	uint64_t*	pulliSecond = (uint64_t*)")->Append(TEST_SOFT_FLOAT_SECONDS)->Append(";\n");
	pszSource->Append("	uint32_t*	puiResult = (uint32_t*)")->Append(TEST_SOFT_FLOAT_RESULTS)->Append(";\n");
	pszSource->Append("	uint64_t*	pulliResult = (uint64_t*)")->Append(TEST_SOFT_FLOAT_RESULTS)->Append(";\n");
	pszSource->Append("	for (int i = 0; i < ")->Append((int)uiCount)->Append("; i++)\n");
	pszSource->Append("	{\n");
	pszSource->Append(aszCalls[eKind]);
	pszSource->Append("	}\n");
	pszSource->Append("	return 0;\n");
	pszSource->Append("}\n");
	pszSource->Replace("NAME", szName);
}


//////////////////////////////////////////////////////////////////////////
//
// Whether the first argument is 8 bytes (a long long or a double).
//
//////////////////////////////////////////////////////////////////////////
static bool TestSoftFloatWideArgument(ETestSoftFloatKind eKind)
{
	return (eKind == TSFK_LongLongToFloat) || (eKind == TSFK_DoubleToFloat) || (eKind >= TSFK_DoubleDoubleToDouble && eKind <= TSFK_DoubleToLongLong) || (eKind >= TSFK_LongLongToDouble);
}


//////////////////////////////////////////////////////////////////////////
//
// Whether the result is 8 bytes.
//
//////////////////////////////////////////////////////////////////////////
static bool TestSoftFloatWideResult(ETestSoftFloatKind eKind)
{
	return (eKind == TSFK_FloatToLongLong) || (eKind == TSFK_DoubleDoubleToDouble) || (eKind == TSFK_DoubleToDouble) || (eKind == TSFK_DoubleToLongLong) || (eKind == TSFK_IntToDouble) || (eKind >= TSFK_LongLongToDouble);
}


//////////////////////////////////////////////////////////////////////////
//
// Runs szName from Libc65/softfloat.asm on the 65C64 (softfloat.cpp on the W65C816) for the special cases and uiRandom random ones and checks
// every result is the same, bit for bit, as softfloat.cpp's natively.
//
//////////////////////////////////////////////////////////////////////////
static void TestSoftFloatFunction(const char* szName, ETestSoftFloatKind eKind, size uiRandom)
{
	static const char*		aszUnits[] = { "softfloat.asm", "softfloat.cpp", NULL };
	static const char*		aszMathUnits[] = { "softfloat.asm", "softfloat.cpp", "math.cpp", NULL };
	STestSoftFloatCases*	psCases;
	STestLibc65Run			sRun;
	CChars					szSource;
	size					i;
	uint64					ulliArgument;
	uint64					ulliExpected;
	uint64					ulliResult;
	uint32					uiSecond;

	//For tuning: TEST_SOFT_FLOAT_ONLY=name runs only that function.
	if (getenv("TEST_SOFT_FLOAT_ONLY") && (strcmp(getenv("TEST_SOFT_FLOAT_ONLY"), szName) != 0))
	{
		return;
	}
	psCases = (STestSoftFloatCases*)malloc(sizeof(STestSoftFloatCases));
	TestSoftFloatMakeCases(psCases, eKind, uiRandom);
	TestSoftFloatProgram(&szSource, szName, eKind, psCases->uiCount);
	AssertTrue(TestLibc65Begin(&sRun, (strncmp(szName, "Soft", 4) == 0) ? aszUnits : aszMathUnits, "", szSource.Text()));
	szSource.Kill();
	if (sRun.pcMemory)
	{
		for (i = 0; i < psCases->uiCount; i++)
		{
			ulliArgument = psCases->auiFirst[i];
			uiSecond = (uint32)psCases->auiSecond[i];
			if (TestSoftFloatWideArgument(eKind))
			{
				memcpy(sRun.pcMemory->Byte(TEST_SOFT_FLOAT_ARGUMENTS + 8 * (uint32)i), &ulliArgument, 8);
				memcpy(sRun.pcMemory->Byte(TEST_SOFT_FLOAT_SECONDS + 8 * (uint32)i), &psCases->auiSecond[i], 8);
			}
			else
			{
				sRun.pcMemory->SetLong(TEST_SOFT_FLOAT_ARGUMENTS + 8 * (uint32)i, (uint32)ulliArgument);
				sRun.pcMemory->SetLong(TEST_SOFT_FLOAT_ARGUMENTS + 8 * (uint32)i + 4, uiSecond);
			}
		}
		//math.cpp's fmod (C++ on the 65C64) takes a step of soft float calls per bit of x's exponent over y's.
		AssertTrue(TestLibc65Run(&sRun, ((strncmp(szName, "fmod", 4) == 0) ? 400000 : ((strncmp(szName, "Soft", 4) == 0) ? 400 : 4000)) * psCases->uiCount + 1000));
		if (getenv("TEST_SOFT_FLOAT_CYCLES"))
		{
			//The program's cycles (the loop round each call included) over its calls, for tuning.
			printf("CYCLES %s %llu\n", szName, (unsigned long long)(((geTestLibc65Target == CPPT_W65C816) ? sRun.cMPU816.NumCycles() : sRun.cMPU.NumCycles()) / psCases->uiCount));
		}
		for (i = 0; i < psCases->uiCount; i++)
		{
			ulliExpected = TestSoftFloatReference(szName, psCases->auiFirst[i], psCases->auiSecond[i]);
			ulliResult = sRun.pcMemory->GetQuad(TEST_SOFT_FLOAT_RESULTS + 8 * (uint32)i);
			if (!TestSoftFloatWideResult(eKind))
			{
				ulliResult &= 0xFFFFFFFF;
				ulliExpected &= 0xFFFFFFFF;
			}
			AssertLongLongIntHex(ulliExpected, ulliResult);
			if (eKind == TSFK_DoubleToDoubleDouble)
			{
				AssertLongLongIntHex(gulliTestMathSecond, sRun.pcMemory->GetQuad(TEST_SOFT_FLOAT_SECONDS + 8 * (uint32)i));
			}
			else if (eKind == TSFK_DoubleToDoubleInt)
			{
				//An int is 16 bits on the W65C816, 32 on the 65C64; the rest of the place stays 0.
				AssertLongLongIntHex(gulliTestMathSecond & ((geTestLibc65Target == CPPT_W65C816) ? 0xFFFFULL : 0xFFFFFFFFULL), sRun.pcMemory->GetQuad(TEST_SOFT_FLOAT_SECONDS + 8 * (uint32)i));
			}
		}
	}
	TestLibc65End(&sRun);
	free(psCases);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65SoftFloatArithmetic(void)
{
	TestSoftFloatFunction("SoftFloatAdd", TSFK_FloatFloatToFloat, 3000);
	TestSoftFloatFunction("SoftFloatSubtract", TSFK_FloatFloatToFloat, 3000);
	TestSoftFloatFunction("SoftFloatMultiply", TSFK_FloatFloatToFloat, 3000);
	TestSoftFloatFunction("SoftFloatDivide", TSFK_FloatFloatToFloat, 3000);
	TestSoftFloatFunction("SoftFloatCompare", TSFK_FloatFloatToInt, 3000);
	TestSoftFloatFunction("SoftFloatSqrt", TSFK_FloatToFloat, 3000);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65SoftFloatConversions(void)
{
	TestSoftFloatFunction("SoftFloatToInt", TSFK_FloatToInt, 3000);
	TestSoftFloatFunction("SoftFloatToUnsigned", TSFK_FloatToInt, 3000);
	TestSoftFloatFunction("SoftFloatToLongLong", TSFK_FloatToLongLong, 3000);
	TestSoftFloatFunction("SoftFloatToUnsignedLongLong", TSFK_FloatToLongLong, 3000);
	TestSoftFloatFunction("SoftFloatToDouble", TSFK_FloatToLongLong, 3000);
	TestSoftFloatFunction("SoftFloatFromInt", TSFK_IntToFloat, 3000);
	TestSoftFloatFunction("SoftFloatFromUnsigned", TSFK_IntToFloat, 3000);
	TestSoftFloatFunction("SoftFloatFromLongLong", TSFK_LongLongToFloat, 3000);
	TestSoftFloatFunction("SoftFloatFromUnsignedLongLong", TSFK_LongLongToFloat, 3000);
	TestSoftFloatFunction("SoftDoubleToFloat", TSFK_DoubleToFloat, 3000);
}


//////////////////////////////////////////////////////////////////////////
//
// The float operators in C++, which the generator calls softfloat.asm for.
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65SoftFloatDouble(void)
{
	TestSoftFloatFunction("SoftDoubleAdd", TSFK_DoubleDoubleToDouble, 3000);
	TestSoftFloatFunction("SoftDoubleSubtract", TSFK_DoubleDoubleToDouble, 3000);
	TestSoftFloatFunction("SoftDoubleMultiply", TSFK_DoubleDoubleToDouble, 3000);
	TestSoftFloatFunction("SoftDoubleDivide", TSFK_DoubleDoubleToDouble, 3000);
	TestSoftFloatFunction("SoftDoubleCompare", TSFK_DoubleDoubleToInt, 3000);
	TestSoftFloatFunction("SoftDoubleSqrt", TSFK_DoubleToDouble, 3000);
	TestSoftFloatFunction("SoftDoubleToInt", TSFK_DoubleToInt, 3000);
	TestSoftFloatFunction("SoftDoubleToUnsigned", TSFK_DoubleToInt, 3000);
	TestSoftFloatFunction("SoftDoubleToLongLong", TSFK_DoubleToLongLong, 3000);
	TestSoftFloatFunction("SoftDoubleToUnsignedLongLong", TSFK_DoubleToLongLong, 3000);
	TestSoftFloatFunction("SoftDoubleFromInt", TSFK_IntToDouble, 3000);
	TestSoftFloatFunction("SoftDoubleFromUnsigned", TSFK_IntToDouble, 3000);
	TestSoftFloatFunction("SoftDoubleFromLongLong", TSFK_LongLongToDouble, 3000);
	TestSoftFloatFunction("SoftDoubleFromUnsignedLongLong", TSFK_LongLongToDouble, 3000);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65SoftFloatOperators(void)
{
	static const char*	aszUnits[] = { "softfloat.asm", "softfloat.cpp", NULL };
	STestLibc65Run		sRun;

	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"long*	gp = (long*)0x100000;\n"
		"float	gfThree = 3.0f;\n"
		"float	gfFour = 4.0f;\n"
		"float	gfNegative = -7.9f;\n"
		"float	gfLarge = 4000000000.0f;\n"
		"long	glOdd = 16777217;\n"
		"float	gfTenth = 0.1f;\n"
		"double	gdHuge = 1e40;\n"
		"float Hypotenuse(float a, float b)\n"
		"{\n"
		"	float	x;\n"
		"	x = a * a + b * b;\n"
		"	return x / 5.0f;\n"
		"}\n"
		"int main(void)\n"
		"{\n"
		"	float	f;\n"
		"	double	d;\n"
		"	f = Hypotenuse(gfThree, gfFour);\n"
		"	*gp++ = (int)f;\n"
		"	*gp++ = f == 5.0f;\n"
		"	*gp++ = f < 5.5f;\n"
		"	*gp++ = (long)(1.0f / gfThree * 3000000.0f);\n"
		"	*gp++ = (int)gfNegative;\n"
		"	*gp++ = (long)(unsigned long)gfLarge;\n"
		"	f = glOdd;\n"
		"	*gp++ = (long)f;\n"
		"	d = gfTenth;\n"
		"	*gp++ = (long)(d * 1e9);\n"
		"	f = (float)gdHuge;\n"
		"	*gp++ = f > 3.4e38f;\n"
		"	*gp++ = (f - f) == (f - f);\n"
		"	return 0;\n"
		"}\n"));
	AssertTrue(TestLibc65Run(&sRun, 100000));
	AssertInt(5, TestLibc65Result(&sRun, 0));
	AssertInt(1, TestLibc65Result(&sRun, 1));
	AssertInt(1, TestLibc65Result(&sRun, 2));
	AssertInt(1000000, TestLibc65Result(&sRun, 3));
	AssertInt(-7, TestLibc65Result(&sRun, 4));
	AssertInt((int32)4000000000u, TestLibc65Result(&sRun, 5));
	AssertInt(16777216, TestLibc65Result(&sRun, 6));
	AssertInt(100000001, TestLibc65Result(&sRun, 7));
	AssertInt(1, TestLibc65Result(&sRun, 8));
	AssertInt(0, TestLibc65Result(&sRun, 9));
	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
// math.cpp's functions that only take bits apart (softfloat816.asm's on the W65C816).
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65SoftFloatMath(void)
{
	TestSoftFloatFunction("fabs", TSFK_DoubleToDouble, 1000);
	TestSoftFloatFunction("fabsf", TSFK_FloatToFloat, 1000);
	TestSoftFloatFunction("sqrt", TSFK_DoubleToDouble, 1000);
	TestSoftFloatFunction("sqrtf", TSFK_FloatToFloat, 1000);
	TestSoftFloatFunction("trunc", TSFK_DoubleToDouble, 3000);
	TestSoftFloatFunction("floor", TSFK_DoubleToDouble, 3000);
	TestSoftFloatFunction("ceil", TSFK_DoubleToDouble, 3000);
	TestSoftFloatFunction("round", TSFK_DoubleToDouble, 3000);
	TestSoftFloatFunction("truncf", TSFK_FloatToFloat, 3000);
	TestSoftFloatFunction("floorf", TSFK_FloatToFloat, 3000);
	TestSoftFloatFunction("ceilf", TSFK_FloatToFloat, 3000);
	TestSoftFloatFunction("roundf", TSFK_FloatToFloat, 3000);
	TestSoftFloatFunction("ldexp", TSFK_DoubleIntToDouble, 3000);
	TestSoftFloatFunction("frexp", TSFK_DoubleToDoubleInt, 3000);
	TestSoftFloatFunction("modf", TSFK_DoubleToDoubleDouble, 3000);
	TestSoftFloatFunction("fmod", TSFK_DoubleDoubleToDouble, 1000);
	TestSoftFloatFunction("fmodf", TSFK_FloatFloatToFloat, 1000);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65SoftFloat(void)
{
	BeginTests();

	TestLibc65SoftFloatArithmetic();
	TestLibc65SoftFloatConversions();
	TestLibc65SoftFloatDouble();
	TestLibc65SoftFloatOperators();
	TestLibc65SoftFloatMath();

	TestStatistics();
}

