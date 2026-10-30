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

	gulliTestSoftFloatRandom = 0x9E3779B97F4A7C15ULL + eKind;
	uiSpecials = sizeof(gauiTestSoftFloatSpecials) / sizeof(uint32);
	psCases->uiCount = 0;
	if ((eKind == TSFK_DoubleDoubleToDouble) || (eKind == TSFK_DoubleDoubleToInt))
	{
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
	else if ((eKind == TSFK_DoubleToDouble) || (eKind == TSFK_DoubleToInt) || (eKind == TSFK_DoubleToLongLong))
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
	return (eKind == TSFK_LongLongToFloat) || (eKind == TSFK_DoubleToFloat) || (eKind >= TSFK_DoubleDoubleToDouble && eKind <= TSFK_DoubleToLongLong) || (eKind == TSFK_LongLongToDouble);
}


//////////////////////////////////////////////////////////////////////////
//
// Whether the result is 8 bytes.
//
//////////////////////////////////////////////////////////////////////////
static bool TestSoftFloatWideResult(ETestSoftFloatKind eKind)
{
	return (eKind == TSFK_FloatToLongLong) || (eKind == TSFK_DoubleDoubleToDouble) || (eKind == TSFK_DoubleToDouble) || (eKind == TSFK_DoubleToLongLong) || (eKind == TSFK_IntToDouble) || (eKind == TSFK_LongLongToDouble);
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
	STestSoftFloatCases*	psCases;
	STestLibc65Run			sRun;
	CChars					szSource;
	size					i;
	uint64					ulliArgument;
	uint64					ulliExpected;
	uint64					ulliResult;
	uint32					uiSecond;

	psCases = (STestSoftFloatCases*)malloc(sizeof(STestSoftFloatCases));
	TestSoftFloatMakeCases(psCases, eKind, uiRandom);
	TestSoftFloatProgram(&szSource, szName, eKind, psCases->uiCount);
	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "", szSource.Text()));
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
		AssertTrue(TestLibc65Run(&sRun, 400 * psCases->uiCount + 1000));
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
void TestLibc65SoftFloat(void)
{
	BeginTests();

	TestLibc65SoftFloatArithmetic();
	TestLibc65SoftFloatConversions();
	TestLibc65SoftFloatDouble();
	TestLibc65SoftFloatOperators();

	TestStatistics();
}

