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

	cTestContext.SetOpcd(0x0200, CLC_Implied);
	cTestContext.SetOpcd(XCE_Implied);
	cTestContext.SetOpcd(REP_Immediate);
	cTestContext.SetByte(0x30);
	cTestContext.SetOpcd(LDA_Immediate);
	cTestContext.SetByte(0xef);
	cTestContext.SetByte(0xcd);
	cTestContext.SetOpcd(STA_Absolute);
	cTestContext.SetByte(0x00);
	cTestContext.SetByte(0x01);
	cTestContext.SetOpcd(STP_Implied);

	cMPU.Init(TestW65C81ContextTickHigh, TestW65C81ContextTickLow, &cTestContext);

	uiInstructions = cTestContext.Run(&cMPU);

	cMPU.Kill();

	AssertLong(6, uiInstructions);
	AssertShortHex((uint16)0xcdef, cTestContext.GetShort(0x0100));

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
		"OPC: (1)  Read(Opcode)    A.cdef  X.0000  Y.0000  PC.00:0207  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STA: (2)  Read(AAL)       A.cdef  X.0000  Y.0000  PC.00:0208  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STA: (3)  Read(AAH)       A.cdef  X.0000  Y.0000  PC.00:0209  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STA: (4)  Write(DL)       A.cdef  X.0000  Y.0000  PC.00:020a  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STA: (5)  Write(DH)       A.cdef  X.0000  Y.0000  PC.00:020a  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"OPC: (1)  Read(Opcode)    A.cdef  X.0000  Y.0000  PC.00:020a  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STP: (2)  IO              A.cdef  X.0000  Y.0000  PC.00:020b  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STP: (3)  IO              A.cdef  X.0000  Y.0000  PC.00:020b  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n", cTestContext.SequenceText());

	cTestContext.Kill();

	CInstructionFactory::GetInstance()->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816LoadLDAAbsolute(void)
{
	CMetaW65C816			cMPU;
	uint64					uiInstructions;
	CTestW65C816Context		cTestContext;

	CInstructionFactory::GetInstance()->Init();

	cTestContext.Init(0x10000, 0xea, 0x0200);
	cTestContext.SetPrint(false, false, true, true, true, true, true, true, true, true, false, false, true, false);

	cTestContext.SetShort(0x3003, 0xcdef);

	cTestContext.SetOpcd(0x0200, CLC_Implied);
	cTestContext.SetOpcd(XCE_Implied);
	cTestContext.SetOpcd(REP_Immediate);
	cTestContext.SetByte(0x30);
	cTestContext.SetOpcd(LDA_Absolute);
	cTestContext.SetByte(0x03);
	cTestContext.SetByte(0x30);
	cTestContext.SetOpcd(STA_Absolute);
	cTestContext.SetByte(0x00);
	cTestContext.SetByte(0x01);
	cTestContext.SetOpcd(STP_Implied);

	cMPU.Init(TestW65C81ContextTickHigh, TestW65C81ContextTickLow, &cTestContext);

	uiInstructions = cTestContext.Run(&cMPU);

	cMPU.Kill();

	AssertLong(6, uiInstructions);
	AssertShortHex((uint16)0xcdef, cTestContext.GetShort(0x0100));

	cTestContext.StripToInstruction("LDA");
	AssertString(""\
		"OPC: (1)  Read(Opcode)    A.0000  X.0000  Y.0000  PC.00:0204  S.01fc    P(Z0 N0 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"LDA: (2)  Read(AAL)       A.0000  X.0000  Y.0000  PC.00:0205  S.01fc    P(Z0 N0 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"LDA: (3)  Read(AAH)       A.0000  X.0000  Y.0000  PC.00:0206  S.01fc    P(Z0 N0 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"LDA: (4)  Read(DL)        A.0000  X.0000  Y.0000  PC.00:0207  S.01fc    P(Z0 N0 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"LDA: (5)  Read(DH)        A.0000  X.0000  Y.0000  PC.00:0207  S.01fc    P(Z0 N0 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"OPC: (1)  Read(Opcode)    A.cdef  X.0000  Y.0000  PC.00:0207  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STA: (2)  Read(AAL)       A.cdef  X.0000  Y.0000  PC.00:0208  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STA: (3)  Read(AAH)       A.cdef  X.0000  Y.0000  PC.00:0209  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STA: (4)  Write(DL)       A.cdef  X.0000  Y.0000  PC.00:020a  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"STA: (5)  Write(DH)       A.cdef  X.0000  Y.0000  PC.00:020a  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n"\
		"OPC: (1)  Read(Opcode)    A.cdef  X.0000  Y.0000  PC.00:020a  S.01fc    P(Z0 N1 D0 I1 M16 X16 C1 E0 V0 ..)\n", cTestContext.SequenceText());

	cTestContext.Kill();

	CInstructionFactory::GetInstance()->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816LoadLDAStackRelative(void)
{
	CMetaW65C816			cMPU;
	uint64					uiInstructions;
	CTestW65C816Context		cTestContext;

	CInstructionFactory::GetInstance()->Init();

	cTestContext.Init(0x10000, 0xea, 0x0200);
	cTestContext.SetPrint(false, false, true, true, true, true, true, true, true, true, false, false, false, false);

	cTestContext.SetOpcd(0x0200, CLC_Implied);
	cTestContext.SetOpcd(XCE_Implied);
	cTestContext.SetOpcd(REP_Immediate);
	cTestContext.SetByte(0x30);
	cTestContext.SetOpcd(LDA_Immediate);
	cTestContext.SetShort(0x1ff);
	cTestContext.SetOpcd(TCS_Implied);
	cTestContext.SetOpcd(LDX_Immediate);
	cTestContext.SetShort(0xcdef);
	cTestContext.SetOpcd(PHX_StackImplied);
	cTestContext.SetOpcd(LDX_Immediate);
	cTestContext.SetShort(0x6789);
	cTestContext.SetOpcd(PHX_StackImplied);
	cTestContext.SetOpcd(LDA_StackRelative);
	cTestContext.SetByte(3);
	cTestContext.SetOpcd(STA_Absolute);
	cTestContext.SetShort(0x0100);
	cTestContext.SetOpcd(STP_Implied);

	cMPU.Init(TestW65C81ContextTickHigh, TestW65C81ContextTickLow, &cTestContext);

	uiInstructions = cTestContext.Run(&cMPU);

	cMPU.Kill();

	AssertLong(12, uiInstructions);
	AssertShortHex((uint16)0xcdef, cTestContext.GetShort(0x0100));

	cTestContext.StripToInstruction("LDA");
	AssertString(""\
		"OPC: (1)  Read(Opcode)    A.0000  X.0000  Y.0000  PC.00:0204  S.01fc\n"\
		"LDA: (2)  Read(DL)        A.0000  X.0000  Y.0000  PC.00:0205  S.01fc\n"\
		"LDA: (3)  Read(DH)        A.0000  X.0000  Y.0000  PC.00:0206  S.01fc\n"\
		"OPC: (1)  Read(Opcode)    A.01ff  X.0000  Y.0000  PC.00:0207  S.01fc\n"\
		"TCS: (2)  IO              A.01ff  X.0000  Y.0000  PC.00:0208  S.01fc\n"\
		"OPC: (1)  Read(Opcode)    A.01ff  X.0000  Y.0000  PC.00:0208  S.01ff\n"\
		"LDX: (2)  Read(DL)        A.01ff  X.0000  Y.0000  PC.00:0209  S.01ff\n"\
		"LDX: (3)  Read(DH)        A.01ff  X.0000  Y.0000  PC.00:020a  S.01ff\n"\
		"OPC: (1)  Read(Opcode)    A.01ff  X.cdef  Y.0000  PC.00:020b  S.01ff\n"\
		"PHX: (2)  IO              A.01ff  X.cdef  Y.0000  PC.00:020c  S.01ff\n"\
		"PHX: (3)  Write(DH)       A.01ff  X.cdef  Y.0000  PC.00:020c  S.01ff\n"\
		"PHX: (4)  Write(DL)       A.01ff  X.cdef  Y.0000  PC.00:020c  S.01fe\n"\
		"OPC: (1)  Read(Opcode)    A.01ff  X.cdef  Y.0000  PC.00:020c  S.01fd\n"\
		"LDX: (2)  Read(DL)        A.01ff  X.cdef  Y.0000  PC.00:020d  S.01fd\n"\
		"LDX: (3)  Read(DH)        A.01ff  X.cdef  Y.0000  PC.00:020e  S.01fd\n"\
		"OPC: (1)  Read(Opcode)    A.01ff  X.6789  Y.0000  PC.00:020f  S.01fd\n"\
		"PHX: (2)  IO              A.01ff  X.6789  Y.0000  PC.00:0210  S.01fd\n"\
		"PHX: (3)  Write(DH)       A.01ff  X.6789  Y.0000  PC.00:0210  S.01fd\n"\
		"PHX: (4)  Write(DL)       A.01ff  X.6789  Y.0000  PC.00:0210  S.01fc\n"\
		"OPC: (1)  Read(Opcode)    A.01ff  X.6789  Y.0000  PC.00:0210  S.01fb\n"\
		"LDA: (2)  Read(D0)        A.01ff  X.6789  Y.0000  PC.00:0211  S.01fb\n"\
		"LDA: (3)  IO              A.01ff  X.6789  Y.0000  PC.00:0212  S.01fb\n"\
		"LDA: (4)  Read(DL)        A.01ff  X.6789  Y.0000  PC.00:0212  S.01fb\n"\
		"LDA: (5)  Read(DH)        A.01ff  X.6789  Y.0000  PC.00:0212  S.01fb\n"\
		"OPC: (1)  Read(Opcode)    A.cdef  X.6789  Y.0000  PC.00:0212  S.01fb\n"\
		"STA: (2)  Read(AAL)       A.cdef  X.6789  Y.0000  PC.00:0213  S.01fb\n"\
		"STA: (3)  Read(AAH)       A.cdef  X.6789  Y.0000  PC.00:0214  S.01fb\n"\
		"STA: (4)  Write(DL)       A.cdef  X.6789  Y.0000  PC.00:0215  S.01fb\n"\
		"STA: (5)  Write(DH)       A.cdef  X.6789  Y.0000  PC.00:0215  S.01fb\n"\
		"OPC: (1)  Read(Opcode)    A.cdef  X.6789  Y.0000  PC.00:0215  S.01fb\n", cTestContext.SequenceText());

	cTestContext.Kill();

	CInstructionFactory::GetInstance()->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816LoadLDAStackRelativeIndirectIndexedWithY(void)
{
	CMetaW65C816			cMPU;
	uint64					uiInstructions;
	CTestW65C816Context		cTestContext;

	CInstructionFactory::GetInstance()->Init();

	cTestContext.Init(0x10000, 0xea, 0x0200);
	cTestContext.SetPrint(false, false, true, true, true, true, true, true, true, true, false, false, false, false);

	cTestContext.SetShort(0x3003, 0xcdef);

	cTestContext.SetOpcd(0x0200, CLC_Implied);
	cTestContext.SetOpcd(XCE_Implied);
	cTestContext.SetOpcd(REP_Immediate);
	cTestContext.SetByte(0x30);
	cTestContext.SetOpcd(LDA_Immediate);
	cTestContext.SetShort(0x1ff);
	cTestContext.SetOpcd(TCS_Implied);
	cTestContext.SetOpcd(LDX_Immediate);
	cTestContext.SetShort(0x3001);
	cTestContext.SetOpcd(PHX_StackImplied);
	cTestContext.SetOpcd(LDX_Immediate);
	cTestContext.SetShort(0x6789);
	cTestContext.SetOpcd(PHX_StackImplied);
	cTestContext.SetOpcd(LDY_Immediate);
	cTestContext.SetShort(2);
	cTestContext.SetOpcd(LDA_StackRelativeIndirectIndexedWithY);
	cTestContext.SetByte(3);
	cTestContext.SetOpcd(STA_Absolute);
	cTestContext.SetShort(0x0100);
	cTestContext.SetOpcd(STP_Implied);

	cMPU.Init(TestW65C81ContextTickHigh, TestW65C81ContextTickLow, &cTestContext);

	uiInstructions = cTestContext.Run(&cMPU);

	cMPU.Kill();

	AssertLong(13, uiInstructions);
	AssertShortHex((uint16)0xcdef, cTestContext.GetShort(0x0100));

	cTestContext.StripToInstruction("LDA");
	AssertString(""\
		"OPC: (1)  Read(Opcode)    A.0000  X.0000  Y.0000  PC.00:0204  S.01fc\n"\
		"LDA: (2)  Read(DL)        A.0000  X.0000  Y.0000  PC.00:0205  S.01fc\n"\
		"LDA: (3)  Read(DH)        A.0000  X.0000  Y.0000  PC.00:0206  S.01fc\n"\
		"OPC: (1)  Read(Opcode)    A.01ff  X.0000  Y.0000  PC.00:0207  S.01fc\n"\
		"TCS: (2)  IO              A.01ff  X.0000  Y.0000  PC.00:0208  S.01fc\n"\
		"OPC: (1)  Read(Opcode)    A.01ff  X.0000  Y.0000  PC.00:0208  S.01ff\n"\
		"LDX: (2)  Read(DL)        A.01ff  X.0000  Y.0000  PC.00:0209  S.01ff\n"\
		"LDX: (3)  Read(DH)        A.01ff  X.0000  Y.0000  PC.00:020a  S.01ff\n"\
		"OPC: (1)  Read(Opcode)    A.01ff  X.3001  Y.0000  PC.00:020b  S.01ff\n"\
		"PHX: (2)  IO              A.01ff  X.3001  Y.0000  PC.00:020c  S.01ff\n"\
		"PHX: (3)  Write(DH)       A.01ff  X.3001  Y.0000  PC.00:020c  S.01ff\n"\
		"PHX: (4)  Write(DL)       A.01ff  X.3001  Y.0000  PC.00:020c  S.01fe\n"\
		"OPC: (1)  Read(Opcode)    A.01ff  X.3001  Y.0000  PC.00:020c  S.01fd\n"\
		"LDX: (2)  Read(DL)        A.01ff  X.3001  Y.0000  PC.00:020d  S.01fd\n"\
		"LDX: (3)  Read(DH)        A.01ff  X.3001  Y.0000  PC.00:020e  S.01fd\n"\
		"OPC: (1)  Read(Opcode)    A.01ff  X.6789  Y.0000  PC.00:020f  S.01fd\n"\
		"PHX: (2)  IO              A.01ff  X.6789  Y.0000  PC.00:0210  S.01fd\n"\
		"PHX: (3)  Write(DH)       A.01ff  X.6789  Y.0000  PC.00:0210  S.01fd\n"\
		"PHX: (4)  Write(DL)       A.01ff  X.6789  Y.0000  PC.00:0210  S.01fc\n"\
		"OPC: (1)  Read(Opcode)    A.01ff  X.6789  Y.0000  PC.00:0210  S.01fb\n"\
		"LDY: (2)  Read(DL)        A.01ff  X.6789  Y.0000  PC.00:0211  S.01fb\n"\
		"LDY: (3)  Read(DH)        A.01ff  X.6789  Y.0000  PC.00:0212  S.01fb\n"\
		"OPC: (1)  Read(Opcode)    A.01ff  X.6789  Y.0002  PC.00:0213  S.01fb\n"\
		"LDA: (2)  Read(D0)        A.01ff  X.6789  Y.0002  PC.00:0214  S.01fb\n"\
		"LDA: (3)  IO              A.01ff  X.6789  Y.0002  PC.00:0215  S.01fb\n"\
		"LDA: (4)  Read(AAL)       A.01ff  X.6789  Y.0002  PC.00:0215  S.01fb\n"\
		"LDA: (5)  Read(AAH)       A.01ff  X.6789  Y.0002  PC.00:0215  S.01fb\n"\
		"LDA: (6)  IO              A.01ff  X.6789  Y.0002  PC.00:0215  S.01fb\n"\
		"LDA: (7)  Read(DL)        A.01ff  X.6789  Y.0002  PC.00:0215  S.01fb\n"\
		"LDA: (8)  Read(DH)        A.01ff  X.6789  Y.0002  PC.00:0215  S.01fb\n"\
		"OPC: (1)  Read(Opcode)    A.cdef  X.6789  Y.0002  PC.00:0215  S.01fb\n"\
		"STA: (2)  Read(AAL)       A.cdef  X.6789  Y.0002  PC.00:0216  S.01fb\n"\
		"STA: (3)  Read(AAH)       A.cdef  X.6789  Y.0002  PC.00:0217  S.01fb\n"\
		"STA: (4)  Write(DL)       A.cdef  X.6789  Y.0002  PC.00:0218  S.01fb\n"\
		"STA: (5)  Write(DH)       A.cdef  X.6789  Y.0002  PC.00:0218  S.01fb\n"\
		"OPC: (1)  Read(Opcode)    A.cdef  X.6789  Y.0002  PC.00:0218  S.01fb\n", cTestContext.SequenceText());

	cTestContext.Kill();

	CInstructionFactory::GetInstance()->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816LoadLDADirectPageIndexedIndirectWithX(void)
{
	CMetaW65C816			cMPU;
	uint64					uiInstructions;
	CTestW65C816Context		cTestContext;

	CInstructionFactory::GetInstance()->Init();

	cTestContext.Init(0x10000, 0xea, 0x0200);
	cTestContext.SetPrint(false, false, true, true, true, true, true, true, true, true, true, true, false, false);

	cTestContext.SetShort(0x0007, 0x3003);
	cTestContext.SetShort(0x3003, 0xcdef);

	cTestContext.SetOpcd(0x0200, CLC_Implied);
	cTestContext.SetOpcd(XCE_Implied);
	cTestContext.SetOpcd(REP_Immediate);
	cTestContext.SetByte(0x30);
	cTestContext.SetOpcd(LDX_Immediate);
	cTestContext.SetShort(4);
	cTestContext.SetOpcd(LDA_DirectPageIndexedIndirectWithX);
	cTestContext.SetByte(3);
	cTestContext.SetOpcd(STA_Absolute);
	cTestContext.SetShort(0x0100);
	cTestContext.SetOpcd(STP_Implied);

	cMPU.Init(TestW65C81ContextTickHigh, TestW65C81ContextTickLow, &cTestContext);

	uiInstructions = cTestContext.Run(&cMPU);

	cMPU.Kill();

	AssertLong(7, uiInstructions);
	AssertShortHex((uint16)0xcdef, cTestContext.GetShort(0x0100));

	cTestContext.StripToInstruction("LDA");
	AssertString(""\
		"OPC: (1)  Read(Opcode)    A.0000  X.0004  Y.0000  PC.00:0207  S.01fc  DP.0000  DB.00\n"\
		"LDA: (2)  Read(D0)        A.0000  X.0004  Y.0000  PC.00:0208  S.01fc  DP.0000  DB.00\n"\
		"LDA: (3)  IO              A.0000  X.0004  Y.0000  PC.00:0209  S.01fc  DP.0000  DB.00\n"\
		"LDA: (4)  IO              A.0000  X.0004  Y.0000  PC.00:0209  S.01fc  DP.0000  DB.00\n"\
		"LDA: (5)  Read(AAL)       A.0000  X.0004  Y.0000  PC.00:0209  S.01fc  DP.0000  DB.00\n"\
		"LDA: (6)  Read(AAH)       A.0000  X.0004  Y.0000  PC.00:0209  S.01fc  DP.0000  DB.00\n"\
		"LDA: (7)  Read(DL)        A.0000  X.0004  Y.0000  PC.00:0209  S.01fc  DP.0000  DB.00\n"\
		"LDA: (8)  Read(DH)        A.0000  X.0004  Y.0000  PC.00:0209  S.01fc  DP.0000  DB.00\n"\
		"OPC: (1)  Read(Opcode)    A.cdef  X.0004  Y.0000  PC.00:0209  S.01fc  DP.0000  DB.00\n"\
		"STA: (2)  Read(AAL)       A.cdef  X.0004  Y.0000  PC.00:020a  S.01fc  DP.0000  DB.00\n"\
		"STA: (3)  Read(AAH)       A.cdef  X.0004  Y.0000  PC.00:020b  S.01fc  DP.0000  DB.00\n"\
		"STA: (4)  Write(DL)       A.cdef  X.0004  Y.0000  PC.00:020c  S.01fc  DP.0000  DB.00\n"\
		"STA: (5)  Write(DH)       A.cdef  X.0004  Y.0000  PC.00:020c  S.01fc  DP.0000  DB.00\n"\
		"OPC: (1)  Read(Opcode)    A.cdef  X.0004  Y.0000  PC.00:020c  S.01fc  DP.0000  DB.00\n", cTestContext.SequenceText());

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
	TestW65C816LoadLDAAbsolute();
	TestW65C816LoadLDAStackRelative();
	TestW65C816LoadLDAStackRelativeIndirectIndexedWithY();
	TestW65C816LoadLDADirectPageIndexedIndirectWithX();

	DataIOKill();

	TestStatistics();
	NumberKill();
	TypeConverterKill();
}

