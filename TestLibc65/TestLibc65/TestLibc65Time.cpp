#include "BaseLib/Chars.h"
#include "TestLib/Assert.h"
#include "TestLibc65Context.h"


//The fields of a struct tm in declaration order.
struct STestLibc65Time
{
	int32	iSec;
	int32	iMin;
	int32	iHour;
	int32	iMDay;
	int32	iMon;
	int32	iYear;
	int32	iWDay;
	int32	iYDay;
	int32	iIsDst;
};


//////////////////////////////////////////////////////////////////////////
//
// Days from 1970-01-01 to iYear-iMonth-iDay (iMonth 1 to 12) in the proleptic Gregorian calendar.  Howard
// Hinnant's days_from_civil, so the expected times don't come from the code being tested.
//
//////////////////////////////////////////////////////////////////////////
static int64 TestLibc65DaysFromCivil(int64 iYear, int64 iMonth, int64 iDay)
{
	int64	iEra;
	int64	iYearOfEra;
	int64	iDayOfYear;
	int64	iDayOfEra;

	iYear -= (iMonth <= 2) ? 1 : 0;
	iEra = ((iYear >= 0) ? iYear : iYear - 399) / 400;
	iYearOfEra = iYear - iEra * 400;
	iDayOfYear = (153 * (iMonth + ((iMonth > 2) ? -3 : 9)) + 2) / 5 + iDay - 1;
	iDayOfEra = iYearOfEra * 365 + iYearOfEra / 4 - iYearOfEra / 100 + iDayOfYear;
	return iEra * 146097 + iDayOfEra - 719468;
}


//////////////////////////////////////////////////////////////////////////
//
// The UTC calendar time of iTime seconds since 1970-01-01, as gmtime should give it.
//
//////////////////////////////////////////////////////////////////////////
static void TestLibc65ExpectedTime(STestLibc65Time* psTime, int64 iTime)
{
	int64	iDays;
	int64	iSeconds;
	int64	iDayOfEra;
	int64	iEra;
	int64	iYearOfEra;
	int64	iDayOfYear;
	int64	iMonthIndex;
	int64	iYear;
	int64	iMonth;

	iDays = iTime / 86400;
	iSeconds = iTime % 86400;
	if (iSeconds < 0)
	{
		iSeconds += 86400;
		iDays--;
	}
	psTime->iSec = (int32)(iSeconds % 60);
	psTime->iMin = (int32)((iSeconds / 60) % 60);
	psTime->iHour = (int32)(iSeconds / 3600);
	psTime->iWDay = (int32)(((iDays + 4) % 7 + 7) % 7);

	//Howard Hinnant's civil_from_days.
	iDayOfEra = iDays + 719468;
	iEra = ((iDayOfEra >= 0) ? iDayOfEra : iDayOfEra - 146096) / 146097;
	iDayOfEra -= iEra * 146097;
	iYearOfEra = (iDayOfEra - iDayOfEra / 1460 + iDayOfEra / 36524 - iDayOfEra / 146096) / 365;
	iDayOfYear = iDayOfEra - (365 * iYearOfEra + iYearOfEra / 4 - iYearOfEra / 100);
	iMonthIndex = (5 * iDayOfYear + 2) / 153;
	psTime->iMDay = (int32)(iDayOfYear - (153 * iMonthIndex + 2) / 5 + 1);
	iMonth = (iMonthIndex < 10) ? iMonthIndex + 3 : iMonthIndex - 9;
	iYear = iYearOfEra + iEra * 400 + ((iMonth <= 2) ? 1 : 0);

	psTime->iMon = (int32)(iMonth - 1);
	psTime->iYear = (int32)(iYear - 1900);
	psTime->iYDay = (int32)(iDays - TestLibc65DaysFromCivil(iYear, 1, 1));
	psTime->iIsDst = 0;
}


//////////////////////////////////////////////////////////////////////////
//
// Checks the 9 struct tm fields written from uiIndex.
//
//////////////////////////////////////////////////////////////////////////
static void TestLibc65AssertTime(STestLibc65Time* psExpected, STestLibc65Run* psRun, size uiIndex)
{
	AssertInt(psExpected->iSec, TestLibc65Result(psRun, uiIndex + 0));
	AssertInt(psExpected->iMin, TestLibc65Result(psRun, uiIndex + 1));
	AssertInt(psExpected->iHour, TestLibc65Result(psRun, uiIndex + 2));
	AssertInt(psExpected->iMDay, TestLibc65Result(psRun, uiIndex + 3));
	AssertInt(psExpected->iMon, TestLibc65Result(psRun, uiIndex + 4));
	AssertInt(psExpected->iYear, TestLibc65Result(psRun, uiIndex + 5));
	AssertInt(psExpected->iWDay, TestLibc65Result(psRun, uiIndex + 6));
	AssertInt(psExpected->iYDay, TestLibc65Result(psRun, uiIndex + 7));
	AssertInt(psExpected->iIsDst, TestLibc65Result(psRun, uiIndex + 8));
}


//////////////////////////////////////////////////////////////////////////
//
// gmtime and localtime (UTC on the 65C64) of each time, and mktime back again.
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65TimeGmtime(void)
{
	static const char*	aszUnits[] = { "time.cpp", NULL };
	static const int64	aiTimes[] =
	{
		0,				//1970-01-01, a Thursday
		86399,
		86400,
		-1,				//1969-12-31 23:59:59
		951782400,		//2000-02-29
		951868800,		//2000-03-01
		978307199,		//2000-12-31 23:59:59, day 365 of a leap year
		1700000000,
		2147483647,		//2038-01-19 03:14:07
		-2147483647 - 1,	//1901-12-13 20:45:52
	};
	STestLibc65Run		sRun;
	STestLibc65Time		sExpected;
	CChars				szSource;
	size				uiTimes;
	size				i;

	uiTimes = sizeof(aiTimes) / sizeof(int64);
	szSource.Init("#include <time.h>\nlong gaTimes[] = {");
	for (i = 0; i < uiTimes; i++)
	{
		if (aiTimes[i] == -2147483647 - 1)
		{
			szSource.Append(" -2147483647L - 1,");
		}
		else
		{
			szSource.Append(' ')->Append(aiTimes[i])->Append("L,");
		}
	}
	szSource.Append(" };\n");
	szSource.Append(
		"void Write(int** pp, struct tm* ps)\n"
		"{\n"
		"	int* p = *pp;\n"
		"	*p++ = ps->tm_sec;\n"
		"	*p++ = ps->tm_min;\n"
		"	*p++ = ps->tm_hour;\n"
		"	*p++ = ps->tm_mday;\n"
		"	*p++ = ps->tm_mon;\n"
		"	*p++ = ps->tm_year;\n"
		"	*p++ = ps->tm_wday;\n"
		"	*p++ = ps->tm_yday;\n"
		"	*p++ = ps->tm_isdst;\n"
		"	*pp = p;\n"
		"}\n"
		"int main()\n"
		"{\n"
		"	int* p = (int*)0x100000;\n"
		"	struct tm s;\n");
	szSource.Append("\tfor (int i = 0; i < ")->Append((int)uiTimes)->Append("; i++)\n");
	szSource.Append(
		"	{\n"
		"		s = *gmtime(&gaTimes[i]);\n"
		"		Write(&p, &s);\n"
		"		Write(&p, localtime(&gaTimes[i]));\n"
		"		*p++ = (int)mktime(&s);\n"
		"	}\n"
		"	return 0;\n"
		"}\n");

	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "", szSource.Text()));
	AssertTrue(TestLibc65Run(&sRun, 20000000));

	for (i = 0; i < uiTimes; i++)
	{
		TestLibc65ExpectedTime(&sExpected, aiTimes[i]);
		TestLibc65AssertTime(&sExpected, &sRun, 19 * i);
		TestLibc65AssertTime(&sExpected, &sRun, 19 * i + 9);
		AssertInt((int32)aiTimes[i], TestLibc65Result(&sRun, 19 * i + 18));
	}

	TestLibc65End(&sRun);
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// mktime brings fields outside their ranges into them and sets tm_wday and tm_yday, as the C standard says.
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65TimeMktimeNormalise(void)
{
	static const char*	aszUnits[] = { "time.cpp", NULL };
	STestLibc65Run		sRun;
	STestLibc65Time		sExpected;

	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <time.h>\n"
		"void Write(int** pp, long lTime, struct tm* ps)\n"
		"{\n"
		"	int* p = *pp;\n"
		"	*p++ = (int)lTime;\n"
		"	*p++ = ps->tm_sec;\n"
		"	*p++ = ps->tm_min;\n"
		"	*p++ = ps->tm_hour;\n"
		"	*p++ = ps->tm_mday;\n"
		"	*p++ = ps->tm_mon;\n"
		"	*p++ = ps->tm_year;\n"
		"	*p++ = ps->tm_wday;\n"
		"	*p++ = ps->tm_yday;\n"
		"	*p++ = ps->tm_isdst;\n"
		"	*pp = p;\n"
		"}\n"
		"int main()\n"
		"{\n"
		"	int* p = (int*)0x100000;\n"
		"	struct tm s;\n"
		"	time_t t;\n"
		"	s.tm_year = 99;\n"
		"	s.tm_mon = 12;\n"
		"	s.tm_mday = 0;\n"
		"	s.tm_hour = 25;\n"
		"	s.tm_min = -1;\n"
		"	s.tm_sec = 60;\n"
		"	s.tm_wday = 3;\n"
		"	s.tm_yday = 77;\n"
		"	s.tm_isdst = 0;\n"
		"	Write(&p, mktime(&s), &s);\n"
		"	s.tm_year = 100;\n"
		"	s.tm_mon = -1;\n"
		"	s.tm_mday = 1;\n"
		"	s.tm_hour = 0;\n"
		"	s.tm_min = 0;\n"
		"	s.tm_sec = 0;\n"
		"	Write(&p, mktime(&s), &s);\n"
		"	t = 5;\n"
		"	*p++ = (int)time(NULL);\n"
		"	*p++ = (int)time(&t);\n"
		"	*p++ = (int)t;\n"
		"	*p++ = (int)clock();\n"
		"	return 0;\n"
		"}\n"));
	AssertTrue(TestLibc65Run(&sRun, 20000000));

	//1999-12-00 25:-1:60 is 2000-01-01 01:00:00, a Saturday.
	AssertInt(946688400, TestLibc65Result(&sRun, 0));
	TestLibc65ExpectedTime(&sExpected, 946688400);
	TestLibc65AssertTime(&sExpected, &sRun, 1);

	//Month -1 of 2000 is 1999-12.
	AssertInt(944006400, TestLibc65Result(&sRun, 10));
	TestLibc65ExpectedTime(&sExpected, 944006400);
	TestLibc65AssertTime(&sExpected, &sRun, 11);

	//There is no clock: the time is 0 and processor time is unavailable.
	AssertInt(0, TestLibc65Result(&sRun, 20));
	AssertInt(0, TestLibc65Result(&sRun, 21));
	AssertInt(0, TestLibc65Result(&sRun, 22));
	AssertInt(-1, TestLibc65Result(&sRun, 23));

	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65Time(void)
{
	BeginTests();

	TestLibc65TimeGmtime();
	TestLibc65TimeMktimeNormalise();

	TestStatistics();
}

