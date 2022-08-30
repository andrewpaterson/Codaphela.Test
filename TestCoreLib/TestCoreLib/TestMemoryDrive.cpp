#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/MemoryDrive.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryDrive(void)
{
	TypeConverterInit();
	BeginTests();
	
	CMemoryDrive	cDrive;

	char	szExpected[512];
	char	szActual[512];
	int		i;
	for (i = 0; i < 511; i++)
	{
		szExpected[i] = i % 26 + 'a';
	}
	szExpected[i] = '\0';

	cDrive.Init(DRIVE_SECTOR_SIZE * 16);
	AssertTrue(cDrive.CFileDrive::Write(1, szExpected));

	AssertTrue(cDrive.CFileDrive::Read(0, szActual));
	AssertString("", szActual)

	AssertTrue(cDrive.CFileDrive::Read(1, szActual));
	AssertString(szExpected, szActual)

	cDrive.Kill();

	TestStatistics();
	TypeConverterKill();
}

