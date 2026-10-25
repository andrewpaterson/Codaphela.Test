//Random cases for the memory and string functions, run the same way on the 65C64 (with Libc65's string.asm and
//string.cpp) or the W65C816 (string.cpp) and natively (with the host's C library, the reference).  Each case writes
//int32_ts to piResults: pointers returned as offsets from their buffer (-1 for NULL), lengths, the signs of
//comparisons and a hash of the memory written.  The two runs must give the same values.  pucA and pucB are buffers
//of STRING_CASES_BUFFER bytes.  The random numbers and the hash are 32 bits whatever the size of an int.
#include <string.h>
#include <stdint.h>


#define STRING_CASES_BUFFER		640
#define STRING_CASES_COUNT		60


uint32_t	guiStringCasesSeed;


uint32_t StringCasesRandom(uint32_t uiLimit)
{
	guiStringCasesSeed = guiStringCasesSeed * 1103515245u + 12345u;
	return (guiStringCasesSeed >> 8) % uiLimit;
}


//Any byte, or a small alphabet (so searches and comparisons find things).
void StringCasesFill(unsigned char* puc, int iBytes, int iAlphabet)
{
	int	i;

	for (i = 0; i < iBytes; i++)
	{
		puc[i] = (unsigned char)((iAlphabet == 0) ? StringCasesRandom(256) : ('a' + StringCasesRandom(iAlphabet)));
	}
}


//A string of iLength characters that are not zero (some at $80 and above) and its zero.
void StringCasesString(unsigned char* puc, int iLength, int iAlphabet)
{
	int	i;

	for (i = 0; i < iLength; i++)
	{
		puc[i] = (unsigned char)((iAlphabet == 0) ? (1 + StringCasesRandom(255)) : ('a' + StringCasesRandom(iAlphabet)));
	}
	puc[iLength] = 0;
}


int32_t StringCasesHash(unsigned char* puc, int iBytes)
{
	uint32_t	uiHash;
	int			i;

	uiHash = 0;
	for (i = 0; i < iBytes; i++)
	{
		uiHash = uiHash * 31 + puc[i];
	}
	return (int32_t)uiHash;
}


int StringCasesSign(int i)
{
	return (i > 0) - (i < 0);
}


int StringCasesOffset(void* pv, unsigned char* pucBase)
{
	return pv ? (int)((unsigned char*)pv - pucBase) : -1;
}


int RunStringCases(int32_t* piResults, unsigned char* pucA, unsigned char* pucB)
{
	int				iCount;
	int				i;
	int				iLength;
	int				iOther;
	int				iFrom;
	int				iTo;
	int				iValue;

	guiStringCasesSeed = 1234;
	iCount = 0;
	for (i = 0; i < STRING_CASES_COUNT; i++)
	{
		//memcpy between buffers at any alignment, of up to 300 bytes.
		StringCasesFill(pucA, STRING_CASES_BUFFER, 0);
		StringCasesFill(pucB, STRING_CASES_BUFFER, 0);
		iLength = (int)StringCasesRandom((i < 20) ? 20 : 300);
		iFrom = (int)StringCasesRandom(16);
		iTo = (int)StringCasesRandom(16);
		piResults[iCount++] = StringCasesOffset(memcpy(pucB + iTo, pucA + iFrom, iLength), pucB);
		piResults[iCount++] = StringCasesHash(pucB, STRING_CASES_BUFFER);

		//memmove in one buffer, overlapping either way.
		iFrom = (int)StringCasesRandom(40);
		iTo = (int)StringCasesRandom(40);
		piResults[iCount++] = StringCasesOffset(memmove(pucA + iTo, pucA + iFrom, iLength), pucA);
		piResults[iCount++] = StringCasesHash(pucA, STRING_CASES_BUFFER);

		//memset with any int (only its low byte is used).
		iValue = (int)StringCasesRandom(1000) - 500;
		piResults[iCount++] = StringCasesOffset(memset(pucB + iTo, iValue, iLength), pucB);
		piResults[iCount++] = StringCasesHash(pucB, STRING_CASES_BUFFER);

		//memcmp of equal memory, or with one byte different (above or below).
		StringCasesFill(pucA, STRING_CASES_BUFFER, 0);
		memcpy(pucB + iTo, pucA + iFrom, iLength + 1);
		if ((iLength > 0) && (StringCasesRandom(3) != 0))
		{
			//Two statements: the order the two sides of = are worked out in differs between compilers.
			iValue = (int)StringCasesRandom(iLength);
			pucB[iTo + iValue] = (unsigned char)StringCasesRandom(256);
		}
		piResults[iCount++] = StringCasesSign(memcmp(pucA + iFrom, pucB + iTo, iLength));
		piResults[iCount++] = StringCasesSign(memcmp(pucB + iTo, pucA + iFrom, iLength));

		//memchr in a small alphabet, for a character that is there or not.
		StringCasesFill(pucA, STRING_CASES_BUFFER, 12);
		iValue = 'a' + (int)StringCasesRandom(14);
		piResults[iCount++] = StringCasesOffset(memchr(pucA + iFrom, iValue, iLength), pucA);

		//strlen, strchr and strrchr (also for the zero), and strstr.
		StringCasesString(pucA + iFrom, iLength, (i & 1) ? 0 : 10);
		piResults[iCount++] = (int)strlen((char*)pucA + iFrom);
		iValue = (StringCasesRandom(8) == 0) ? 0 : ('a' + (int)StringCasesRandom(12));
		piResults[iCount++] = StringCasesOffset(strchr((char*)pucA + iFrom, iValue), pucA);
		piResults[iCount++] = StringCasesOffset(strrchr((char*)pucA + iFrom, iValue), pucA);
		iOther = (int)StringCasesRandom(5);
		if ((iLength > iOther) && (StringCasesRandom(2) == 0))
		{
			//A needle that is in the haystack.
			iValue = (int)StringCasesRandom(iLength - iOther);
			memcpy(pucB, pucA + iFrom + iValue, iOther);
			pucB[iOther] = 0;
		}
		else
		{
			StringCasesString(pucB, iOther, 3);
		}
		piResults[iCount++] = StringCasesOffset(strstr((char*)pucA + iFrom, (char*)pucB), pucA);

		//strcmp and strncmp of strings that share a prefix.
		StringCasesString(pucA + iFrom, iLength, (i & 1) ? 0 : 3);
		iOther = (int)StringCasesRandom(iLength + 3);
		memcpy(pucB + iTo, pucA + iFrom, (iOther < iLength) ? iOther : iLength);
		if (iOther <= iLength)
		{
			StringCasesString(pucB + iTo + iOther, (int)StringCasesRandom(4), (i & 1) ? 0 : 3);
		}
		else
		{
			pucB[iTo + iLength] = 0;
		}
		piResults[iCount++] = StringCasesSign(strcmp((char*)pucA + iFrom, (char*)pucB + iTo));
		piResults[iCount++] = StringCasesSign(strcmp((char*)pucB + iTo, (char*)pucA + iFrom));
		iValue = (int)StringCasesRandom(iLength + 4);
		piResults[iCount++] = StringCasesSign(strncmp((char*)pucA + iFrom, (char*)pucB + iTo, iValue));
		piResults[iCount++] = StringCasesSign(strncmp((char*)pucB + iTo, (char*)pucA + iFrom, iValue));

		//strcpy, strcat, strncpy and strncat into a buffer of known bytes.
		StringCasesFill(pucB, STRING_CASES_BUFFER, 0);
		iOther = (int)StringCasesRandom(100);
		StringCasesString(pucA, iOther, 0);
		StringCasesString(pucA + 200, iLength, 0);
		piResults[iCount++] = StringCasesOffset(strcpy((char*)pucB + iTo, (char*)pucA), pucB);
		piResults[iCount++] = StringCasesOffset(strcat((char*)pucB + iTo, (char*)pucA + 200), pucB);
		piResults[iCount++] = StringCasesHash(pucB, STRING_CASES_BUFFER);
		iValue = (int)StringCasesRandom(iLength + 10);
		piResults[iCount++] = StringCasesOffset(strncpy((char*)pucB + iFrom, (char*)pucA + 200, iValue), pucB);
		piResults[iCount++] = StringCasesHash(pucB, STRING_CASES_BUFFER);
		pucB[iFrom + iValue] = 0;
		piResults[iCount++] = StringCasesOffset(strncat((char*)pucB + iFrom, (char*)pucA, (int)StringCasesRandom(iOther + 5)), pucB);
		piResults[iCount++] = StringCasesHash(pucB, STRING_CASES_BUFFER);
	}
	return iCount;
}

