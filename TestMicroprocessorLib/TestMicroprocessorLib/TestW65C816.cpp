#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/LogToMemory.h"
#include "MicroprocessorLib/W65C816.h"
#include "MicroprocessorLib/InstructionFactory.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816OnlyInitAndKill(void)
{
	CW65C816	cW65C816;

	CInstructionFactory::GetInstance()->Init();
	cW65C816.Init();
	cW65C816.Kill();
	CInstructionFactory::GetInstance()->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816(void)
{
	TypeConverterInit();
	NumberInit();
	BeginTests();

	DataIOInit();
	

	TestW65C816OnlyInitAndKill();

	DataIOKill();

	TestStatistics();
	NumberKill();
	TypeConverterKill();
}

