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
void TestW65C816LoadLDAImmediate(void)
{
	CMetaW65C816			cMPU;
	uint64					uiInstructions;
	CTestW65C816Context		cTestContext;

	CInstructionFactory::GetInstance()->Init();

	cTestContext.Init(0x10000, 0xea, 0x0200);
	cTestContext.SetPrint(true, true, true, true, true, true, true, true, true, true, false, false, true, false);
	//cTestContext.mbDebugSpew = true;

	cTestContext.SetOpcd(0x0200, CLC_Implied);
	cTestContext.SetOpcd(XCE_Implied);
	cTestContext.SetOpcd(REP_Immediate);
	cTestContext.SetByte(0x30);
	cTestContext.SetOpcd(LDA_Immediate);
	cTestContext.SetByte(0xcd);
	cTestContext.SetByte(0xef);
	cTestContext.SetOpcd(STA_Absolute);
	cTestContext.SetByte(0x00);
	cTestContext.SetByte(0x01);
	cTestContext.SetOpcd(STP_Implied);

	cMPU.Init(TestW65C81ContextTickHigh, TestW65C81ContextTickLow, &cTestContext);

	uiInstructions = cTestContext.Run(&cMPU);

	cMPU.Kill();

	AssertLong(6, uiInstructions);

	AssertString(""\
		"RES: (1)  IO              A.0000  X.0000  Y.0000  PC.00:0000  S.01ff    P(Z0 N0 D0 I0 M.8 X.8 C0 E1 V0 B0)\n"\
		"RES: (2)  IO              A.0000  X.0000  Y.0000  PC.00:0000  S.01ff    P(Z0 N0 D0 I0 M.8 X.8 C0 E1 V0 B0)\n"\
		"RES: (3)  IO              A.0000  X.0000  Y.0000  PC.00:0000  S.01ff    P(Z0 N0 D0 I0 M.8 X.8 C0 E1 V0 B0)\n"\
		"RES: (4)  IO              A.0000  X.0000  Y.0000  PC.00:0000  S.01fe    P(Z0 N0 D0 I0 M.8 X.8 C0 E1 V0 B0)\n"\
		"RES: (5)  IO              A.0000  X.0000  Y.0000  PC.00:0000  S.01fd    P(Z0 N0 D0 I0 M.8 X.8 C0 E1 V0 B0)\n"\
		"RES: (6)  Read(AAL)       A.0000  X.0000  Y.0000  PC.00:0000  S.01fc    P(Z0 N0 D0 I1 M.8 X.8 C0 E1 V0 B0)\n"\
		"RES: (7)  Read(AAH)       A.0000  X.0000  Y.0000  PC.00:0000  S.01fc    P(Z0 N0 D0 I1 M.8 X.8 C0 E1 V0 B0)\n"\
		"OPC: (1)  Read(Opcode)    A.0000  X.0000  Y.0000  PC.00:0200  S.01fc    P(Z0 N0 D0 I1 M.8 X.8 C0 E1 V0 B0)\n"\
		"CLC: (2)  IO              A.0000  X.0000  Y.0000  PC.00:0201  S.01fc    P(Z0 N0 D0 I1 M.8 X.8 C0 E1 V0 B0)\n"\
		"OPC: (1)  Read(Opcode)    A.0000  X.0000  Y.0000  PC.00:0201  S.01fc    P(Z0 N0 D0 I1 M.8 X.8 C0 E1 V0 B0)\n"\
		"XCE: (2)  IO              A.0000  X.0000  Y.0000  PC.00:0202  S.01fc    P(Z0 N0 D0 I1 M.8 X.8 C0 E1 V0 B0)\n"\
		"OPC: (1)  Read(Opcode)    A.0000  X.0000  Y.0000  PC.00:0202  S.01fc    P(Z0 N0 D0 I1 M.8 X.8 C1 E0 V0 ..)\n"\
		"REP: (2)  Read(DL)        A.0000  X.0000  Y.0000  PC.00:0203  S.01fc    P(Z0 N0 D0 I1 M.8 X.8 C1 E0 V0 ..)\n"\
		"REP: (3)  Read(DH)        A.0000  X.0000  Y.0000  PC.00:0204  S.01fc    P(Z0 N0 D0 I1 M.8 X.8 C1 E0 V0 ..)\n"\
		"OPC: (1)  Read(Opcode)    A.0000  X.0000  Y.0000  PC.00:0204  S.01fc    P(Z0 N0 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"LDA: (2)  Read(DL)        A.0000  X.0000  Y.0000  PC.00:0205  S.01fc    P(Z0 N0 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"LDA: (3)  Read(DH)        A.0000  X.0000  Y.0000  PC.00:0206  S.01fc    P(Z0 N0 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"OPC: (1)  Read(Opcode)    A.efcd  X.0000  Y.0000  PC.00:0207  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STA: (2)  Read(AAL)       A.efcd  X.0000  Y.0000  PC.00:0208  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STA: (3)  Read(AAH)       A.efcd  X.0000  Y.0000  PC.00:0209  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STA: (4)  Write(DL)       A.efcd  X.0000  Y.0000  PC.00:020a  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STA: (5)  Write(DH)       A.efcd  X.0000  Y.0000  PC.00:020a  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"OPC: (1)  Read(Opcode)    A.efcd  X.0000  Y.0000  PC.00:020a  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STP: (2)  IO              A.efcd  X.0000  Y.0000  PC.00:020b  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STP: (3)  IO              A.efcd  X.0000  Y.0000  PC.00:020b  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n", cTestContext.SequenceText());

	cTestContext.Kill();

	CInstructionFactory::GetInstance()->Kill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816Load(void)
{
	TypeConverterInit();
	NumberInit();
	BeginTests();

	DataIOInit();

	TestW65C816LoadLDAImmediate();

	DataIOKill();

	TestStatistics();
	NumberKill();
	TypeConverterKill();
}

