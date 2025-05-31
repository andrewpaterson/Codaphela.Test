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
	size					i;
	bool					bRunning;
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

	for (i = 0;; i++)
	{
		bRunning = cMPU.TickInstruction();
		if (!bRunning)
		{
			break;
		}
	}

	cMPU.Kill();

	AssertSize(3, i);

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
	size					i;
	bool					bRunning;
	CTestW65C816Context		cTestContext;

	CInstructionFactory::GetInstance()->Init();

	cTestContext.Init(0x10000, 0xea);
	cTestContext.SetPrint(true, false, true, false, false, true, true, true, true, false, false, false, false, true);

	cTestContext.SetMemory(0xfffc, 0x00);
	cTestContext.SetMemory(0xfffd, 0x02);
	cTestContext.SetMemory(0x0200, INC_Absolute);
	cTestContext.SetMemory(0x0201, 0x04);
	cTestContext.SetMemory(0x0202, 0x02);
	cTestContext.SetMemory(0x0203, LDA_Immediate);
	cTestContext.SetMemory(0x0204, 0x01);
	cTestContext.SetMemory(0x0205, ADC_Immediate);
	cTestContext.SetMemory(0x0206, 0x02);
	cTestContext.SetMemory(0x0207, STP_Implied);

	cMPU.Init(TestW65C81ContextTickHigh, TestW65C81ContextTickLow, &cTestContext);

	for (i = 0;; i++)
	{
		bRunning = cMPU.TickInstruction();
		if (!bRunning)
		{
			break;
		}
	}

	cMPU.Kill();

	AssertSize(3, i);

	AssertString("LDA: A.0001  X.0000  Y.0000  PC.00:0202\n"\
				 "ADC: A.0003  X.0000  Y.0000  PC.00:0204\n" , cTestContext.SequenceText());

	cTestContext.GetSequence()->Dump();


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

	//TestW65C816AddADCImmediateFullLog();
	TestW65C816AddADCImmediateSimpleLog();

	DataIOKill();

	TestStatistics();
	NumberKill();
	TypeConverterKill();
}

