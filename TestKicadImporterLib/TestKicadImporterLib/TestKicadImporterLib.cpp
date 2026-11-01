#include "BaseLib/LeakDetector.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalMemory.h"
#include "TestLib/Assert.h"


void TestKicadSchemParser(void);
void TestKicadSchemImporter(void);
void TestKicadSchemFile(void);
void TestKicadSchemNetlist(void);
void TestKicadSchemLogicim(void);


int __cdecl main(void)
{
	int iResult;

	BreakOnAllocation(0);
	InitTotalStatistics();

	TypesInit();
	TypeConverterInit();
	MemoryInit();

	TestKicadSchemParser();
	TestKicadSchemImporter();
	TestKicadSchemFile();
	TestKicadSchemNetlist();
	TestKicadSchemLogicim();

	MemoryKill();
	TypeConverterKill();
	TypesKill();

	iResult = TestTotalStatistics();
	LeakDetection();
	return iResult;
}

