#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/LogToMemory.h"
#include "MicroprocessorLib/W65C816.h"
#include "MicroprocessorLib/InstructionFactory.h"
#include "MicroprocessorLib/MetaW65C816.h"
#include "TestLib/Assert.h"
#include "TestW65C816Context.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816AddADCImmediateFullLog(void)
{
	CMetaW65C816			cMPU;
	size					uiInstructions;
	CTestW65C816Context		cTestContext;

	CInstructionFactory::GetInstance()->Init();

	cTestContext.Init(0x10000, 0xea);
	cTestContext.SetPrint(true, true, true, true, true, true, true, true, true, true, false, false, false, false);

	cTestContext.SetMemory(0xfffc, 0x00);
	cTestContext.SetMemory(0xfffd, 0x02);
	cTestContext.SetMemory(0x0200, LDA_Immediate);
	cTestContext.SetMemory(0x0201, 0x01);
	cTestContext.SetMemory(0x0202, ADC_Immediate);
	cTestContext.SetMemory(0x0203, 0x02);
	cTestContext.SetMemory(0x0204, STP_Implied);

	cMPU.Init(TestW65C81ContextTickHigh, TestW65C81ContextTickLow, &cTestContext);

	uiInstructions = cTestContext.Run(&cMPU);

	cMPU.Kill();

	AssertSize(3, uiInstructions);

	AssertString("RES: (1)  IO              A.0000  X.0000  Y.0000  PC.00:0000  S.01ff\n"\
				 "RES: (2)  IO              A.0000  X.0000  Y.0000  PC.00:0000  S.01ff\n"\
				 "RES: (3)  IO              A.0000  X.0000  Y.0000  PC.00:0000  S.01ff\n"\
				 "RES: (4)  IO              A.0000  X.0000  Y.0000  PC.00:0000  S.01fe\n"\
				 "RES: (5)  IO              A.0000  X.0000  Y.0000  PC.00:0000  S.01fd\n"\
				 "RES: (6)  Read(AAL)       A.0000  X.0000  Y.0000  PC.00:0000  S.01fc\n"\
				 "RES: (7)  Read(AAH)       A.0000  X.0000  Y.0000  PC.00:0000  S.01fc\n"\
				 "OPC: (1)  Read(Opcode)    A.0000  X.0000  Y.0000  PC.00:0200  S.01fc\n"\
				 "LDA: (2)  Read(DL)        A.0000  X.0000  Y.0000  PC.00:0201  S.01fc\n"\
				 "OPC: (1)  Read(Opcode)    A.0001  X.0000  Y.0000  PC.00:0202  S.01fc\n"\
				 "ADC: (2)  Read(DL)        A.0001  X.0000  Y.0000  PC.00:0203  S.01fc\n"\
				 "OPC: (1)  Read(Opcode)    A.0003  X.0000  Y.0000  PC.00:0204  S.01fc\n"\
				 "STP: (2)  IO              A.0003  X.0000  Y.0000  PC.00:0205  S.01fc\n"\
				 "STP: (3)  IO              A.0003  X.0000  Y.0000  PC.00:0205  S.01fc\n" , cTestContext.SequenceText());

	cTestContext.Kill();

	CInstructionFactory::GetInstance()->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816AddADCImmediateSimpleLog(void)
{
	CMetaW65C816			cMPU;
	size					uiInstructions;
	CTestW65C816Context		cTestContext;

	CInstructionFactory::GetInstance()->Init();

	cTestContext.Init(0x10000, 0xea);
	cTestContext.SetPrint(true, true, true, false, false, true, true, true, true, false, false, false, false, true);

	cTestContext.SetMemory(0xfffc, 0x00);
	cTestContext.SetMemory(0xfffd, 0x02);
	cTestContext.SetMemory(0x0200, LDA_Immediate);
	cTestContext.SetMemory(0x0201, 0x01);
	cTestContext.SetMemory(0x0202, ADC_Immediate);
	cTestContext.SetMemory(0x0203, 0x05);
	cTestContext.SetMemory(0x0204, STP_Implied);

	cMPU.Init(TestW65C81ContextTickHigh, TestW65C81ContextTickLow, &cTestContext);

	uiInstructions = cTestContext.Run(&cMPU);

	cMPU.Kill();

	AssertSize(3, uiInstructions);

	AssertString("RES: A.0000  X.0000  Y.0000  PC.00:0200\n"\
				 "LDA: A.0001  X.0000  Y.0000  PC.00:0202\n"\
				 "ADC: A.0006  X.0000  Y.0000  PC.00:0204\n"\
				 "STP: A.0006  X.0000  Y.0000  PC.00:0205\n" , cTestContext.SequenceText());

	cTestContext.Kill();

	CInstructionFactory::GetInstance()->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816Add(void)
{
	TypeConverterInit();
	NumberInit();
	BeginTests();

	DataIOInit();

	TestW65C816AddADCImmediateFullLog();
	TestW65C816AddADCImmediateSimpleLog();

	DataIOKill();

	TestStatistics();
	NumberKill();
	TypeConverterKill();
}

