#include "BaseLib/ConstructorCall.h"
#include "BaseLib/Logger.h"
#include "BaseLib/PointerFunctions.h"
#include "MicroprocessorLib/LongTime.h"
#include "MicroprocessorLib/Voltage.h"
#include "MicroprocessorLib/Timeline.h"
#include "MicroprocessorLib/Circuit.h"
#include "MicroprocessorLib/PowerInPort.h"
#include "MicroprocessorLib/PowerOutPort.h"
#include "MicroprocessorLib/LogicPort.h"
#include "MicroprocessorLib/LogicPortBus.h"
#include "MicroprocessorLib/PortEvent.h"
#include "MicroprocessorLib/TickEvent.h"
#include "MicroprocessorLib/FixedVoltageConfiguration.h"
#include "MicroprocessorLib/FamilyVoltageConfiguration.h"
#include "MicroprocessorLib/W65C02Pins.h"
#include "MicroprocessorLib/MetaTrace.h"
#include "MicroprocessorLib/MetaBus8.h"
#include "MicroprocessorLib/MetaBus16.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
// A power supply: one power out port.
//
//////////////////////////////////////////////////////////////////////////
class CTestPowerSource : public CPortHolder
{
public:
	CPowerOutPort*	mpcOut;

	void Init(float32 fVoltage)
	{
		CPortHolder::Init();
		mpcOut = NewMalloc<CPowerOutPort>();
		mpcOut->Init("Out", this, fVoltage);
	}

	void TraceConnected(CTimeline* pcTimeline, CPort* pcPort) {}
	char* GetName(void) { return (char*)"Power"; }
	void AppendDescription(CChars* psz) { psz->Append("Power"); }
};


//////////////////////////////////////////////////////////////////////////
//
// An input and an output.
//
//////////////////////////////////////////////////////////////////////////
class CTestBufferPins : public CPins
{
public:
	CLogicPort*		mpcIn;
	CLogicPort*		mpcOut;

	void Init(CVoltageConfigurationSource* pcSource)
	{
		CPins::Init();
		mpcIn = NewMalloc<CLogicPort>();
		mpcIn->Init(PT_Input, this, "In", pcSource);
		mpcOut = NewMalloc<CLogicPort>();
		mpcOut->Init(PT_Output, this, "Out", pcSource);
	}
};


//////////////////////////////////////////////////////////////////////////
//
// Copies its input to its output, and logs "name:value@time;" for each
// input transition.
//
//////////////////////////////////////////////////////////////////////////
class CTestBuffer : public CIntegratedCircuit
{
CONSTRUCTABLE(CTestBuffer);
public:
	CChars*		mpszLog;

	void Init(CCircuit* pcCircuit, const char* szName, CVoltageConfigurationSource* pcSource, CChars* pszLog)
	{
		CTestBufferPins*	pcPins;

		pcPins = NewMalloc<CTestBufferPins>();
		pcPins->Init(pcSource);
		CIntegratedCircuit::Init(pcCircuit, szName, pcPins);
		mpszLog = pszLog;
	}

	CTestBufferPins* GetBufferPins(void) { return (CTestBufferPins*)mpcPins; }
	CState* CreateState(void) { return NewMalloc<CStateless>(); }
	void SimulationStarted(CTimeline* pcTimeline) {}
	const char* GetType(void) { return "Buffer"; }

	void InputTransition(CTimeline* pcTimeline, CLogicPort* pcPort)
	{
		STraceValue	sValue;

		sValue = pcPort->Read(pcTimeline);
		mpszLog->Append(mszName);
		mpszLog->Append(':');
		sValue.Print(mpszLog);
		mpszLog->Append('@');
		mpszLog->Append(pcTimeline->GetTime());
		mpszLog->Append(';');

		if (sValue.IsHigh() || sValue.IsLow())
		{
			GetBufferPins()->mpcOut->Write(pcTimeline, sValue.IsHigh());
		}
	}
};


//////////////////////////////////////////////////////////////////////////
//
// Toggles its output every period, from ticks.
//
//////////////////////////////////////////////////////////////////////////
class CTestClockState : public CState
{
CONSTRUCTABLE(CTestClockState);
public:
	bool	mbHigh;
	size	muiTicks;
};


class CTestClock : public CIntegratedCircuit
{
CONSTRUCTABLE(CTestClock);
public:
	int64	miPeriod;

	void Init(CCircuit* pcCircuit, const char* szName, CVoltageConfigurationSource* pcSource, int64 iPeriod)
	{
		CTestBufferPins*	pcPins;

		pcPins = NewMalloc<CTestBufferPins>();
		pcPins->Init(pcSource);
		CIntegratedCircuit::Init(pcCircuit, szName, pcPins);
		miPeriod = iPeriod;
	}

	CTestClockState* GetClockState(void) { return (CTestClockState*)mpcState; }
	const char* GetType(void) { return "Clock"; }
	void InputTransition(CTimeline* pcTimeline, CLogicPort* pcPort) {}

	CState* CreateState(void)
	{
		CTestClockState*	pcState;

		pcState = NewMalloc<CTestClockState>();
		pcState->mbHigh = false;
		pcState->muiTicks = 0;
		return pcState;
	}

	void SimulationStarted(CTimeline* pcTimeline)
	{
		CTickEvent::Schedule(miPeriod, this, pcTimeline);
	}

	void ExecuteTick(CTimeline* pcTimeline)
	{
		GetClockState()->mbHigh = !GetClockState()->mbHigh;
		GetClockState()->muiTicks++;
		((CTestBufferPins*)mpcPins)->mpcOut->Write(pcTimeline, GetClockState()->mbHigh);
		CTickEvent::Schedule(miPeriod, this, pcTimeline);
	}
};


//////////////////////////////////////////////////////////////////////////
//
// A timeline, a circuit and its 4V supply.
//
//////////////////////////////////////////////////////////////////////////
class CTestLogicCircuit
{
public:
	CTimeline					mcTimeline;
	CCircuit					mcCircuit;
	CTestPowerSource			mcVCCSource;
	CTestPowerSource			mcGNDSource;
	CTrace*						mpcVCC;
	CTrace*						mpcGND;
	CFixedVoltageConfiguration	mcFixed;
	CChars						mszLog;

	void Init(void)
	{
		CEvent::ResetNextID();
		CTrace::ResetNextID();
		mcTimeline.Init();
		mcCircuit.Init(&mcTimeline);
		mpcVCC = mcCircuit.AddTrace();
		mpcGND = mcCircuit.AddTrace();
		mcVCCSource.Init(4.0f);
		mcGNDSource.Init(0.0f);
		mcVCCSource.mpcOut->Connect(mpcVCC);
		mcGNDSource.mpcOut->Connect(mpcGND);

		//Outputs 0V and 4V, inputs low at 1V and high at 3V, 1024 to propagate: holds of 512 and slews of 1024.
		mcFixed.Init(4.0f, 1.0f, 3.0f, 0.0f, 4.0f, 1024, 1024);
		mszLog.Init();
	}

	void Kill(void)
	{
		mcVCCSource.Kill();
		mcGNDSource.Kill();
		mcCircuit.Kill();
		mcTimeline.Kill();
		mcFixed.Kill();
		mszLog.Kill();
	}

	void Power(CIntegratedCircuit* pcIntegratedCircuit)
	{
		pcIntegratedCircuit->GetPins()->GetVoltageCommon()->Connect(mpcVCC);
		pcIntegratedCircuit->GetPins()->GetVoltageGround()->Connect(mpcGND);
	}

	CTestBuffer* AddBuffer(const char* szName, CVoltageConfigurationSource* pcSource)
	{
		CTestBuffer*	pcBuffer;

		pcBuffer = NewMalloc<CTestBuffer>();
		pcBuffer->Init(&mcCircuit, szName, pcSource, &mszLog);
		Power(pcBuffer);
		return pcBuffer;
	}
};


#define AssertLog(e)	AssertString(e, cTest.mszLog.Text()); cTest.mszLog.Clear()


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogicPortTrace(void)
{
	CTestLogicCircuit	cTest;
	CTrace*				pcTrace;
	CTestPowerSource	cHigh;
	CTestPowerSource	cLow;
	CChars				sz;
	SLogConfig			sLogConfig;

	cTest.Init();
	pcTrace = cTest.mcCircuit.AddTrace();
	AssertLong(3, pcTrace->GetID());
	AssertFalse(IsVoltage(pcTrace->GetVoltage(0)));
	AssertFloat(0.0f, pcTrace->GetShortVoltage(0), 3);

	cHigh.Init(4.0f);
	cLow.Init(1.0f);
	AssertTrue(cHigh.mpcOut->Connect(pcTrace));
	AssertFloat(4.0f, pcTrace->GetVoltage(0), 3);
	AssertTrue(cLow.mpcOut->Connect(pcTrace));
	AssertFloat(2.5f, pcTrace->GetVoltage(0), 3);
	AssertFloat(3.0f, pcTrace->GetShortVoltage(0), 3);
	AssertFloat(1.0f, pcTrace->GetMinimumVoltage(0), 3);
	AssertFloat(4.0f, pcTrace->GetMaximumVoltage(0), 3);
	AssertSize(2, pcTrace->NumConnectedPorts());
	AssertLong(3, cHigh.mpcOut->GetTraceID());

	sz.Init();
	pcTrace->AppendVoltage(&sz, 0);
	AssertString("2.5V", sz.Text());
	sz.Clear();
	cHigh.mpcOut->AppendDescription(&sz);
	AssertString("Out (4.0V)", sz.Text());
	sz.Kill();

	sLogConfig = gcLogger.SetSilent();
	AssertFalse(cHigh.mpcOut->Connect(pcTrace));
	gcLogger.SetConfig(&sLogConfig);

	cHigh.mpcOut->Disconnect(&cTest.mcTimeline);
	AssertSize(1, pcTrace->NumConnectedPorts());
	AssertFloat(1.0f, pcTrace->GetVoltage(0), 3);
	AssertLong(0, cHigh.mpcOut->GetTraceID());

	cHigh.Kill();
	cLow.Kill();
	AssertSize(0, pcTrace->NumConnectedPorts());
	cTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A driver's rising edge through a buffer.
//
//////////////////////////////////////////////////////////////////////////
void TestLogicPortSlewAndTransition(void)
{
	CTestLogicCircuit	cTest;
	CTestBuffer*		pcDriver;
	CTestBuffer*		pcBuffer;
	CLogicPort*			pcDriverOut;
	CLogicPort*			pcBufferIn;
	CLogicPort*			pcBufferOut;
	CTrace*				pcA;
	CTrace*				pcB;
	CChars				sz;

	cTest.Init();
	pcDriver = cTest.AddBuffer("D", &cTest.mcFixed);
	pcBuffer = cTest.AddBuffer("U1", &cTest.mcFixed);
	cTest.mcCircuit.SimulationStarted();
	AssertTrue(pcBuffer->IsPowered(0));
	AssertTrue(pcBuffer->IsStateless());

	pcDriverOut = pcDriver->GetBufferPins()->mpcOut;
	pcBufferIn = pcBuffer->GetBufferPins()->mpcIn;
	pcBufferOut = pcBuffer->GetBufferPins()->mpcOut;
	pcA = cTest.mcCircuit.AddTrace();
	pcB = cTest.mcCircuit.AddTrace();
	pcDriverOut->Connect(pcA);
	pcBufferIn->Connect(pcA);
	pcBufferOut->Connect(pcB);

	AssertInt(TV_Undriven, pcBufferIn->ReadValue(0).eValue);

	//Hold 512 then slew 0V to 4V over 1024, crossing 3V at 512 + 768.
	pcDriverOut->Write(&cTest.mcTimeline, true);
	AssertSize(1, pcDriverOut->NumEvents());
	sz.Init();
	pcDriverOut->AppendEvents(&sz);
	AssertString("Events [1]:  Slew: Time [512] ---- -> 4.0V,  ", sz.Text());
	sz.Kill();

	AssertTrue(cTest.mcTimeline.RunToTime(512));
	AssertLong(512, cTest.mcTimeline.GetTime());
	AssertTrue(pcDriverOut->GetOutput()->IsSlew());
	AssertLong(1024, pcDriverOut->GetOutput()->GetSlewTime());
	AssertFloat(0.0f, pcDriverOut->GetOutput()->GetStartVoltage(), 3);
	AssertSize(1, pcDriverOut->NumEvents());  //The drive at the end of the slew.
	AssertSize(1, pcBufferIn->NumEvents());  //The transition.
	AssertLong(1536, pcDriverOut->GetEvent(0)->GetTime());
	AssertLong(1280, pcBufferIn->GetEvent(0)->GetTime());

	AssertFloat(0.0f, pcA->GetVoltage(512), 3);
	AssertFloat(2.0f, pcA->GetVoltage(1024), 3);
	AssertInt(TV_Unsettled, pcBufferIn->ReadValue(1024).eValue);
	AssertFloat(3.0f, pcA->GetVoltage(1280), 3);
	AssertInt(TV_High, pcBufferIn->ReadValue(1280).eValue);
	AssertFloat(4.0f, pcA->GetVoltage(1536), 3);
	AssertFalse(IsVoltage(pcA->GetVoltage(1537)));  //Until the drive executes.

	AssertTrue(cTest.mcTimeline.RunToTime(1280 - 512));
	AssertLog("U1:1@1280;");
	AssertSize(1, pcBufferOut->NumEvents());
	AssertLong(1280 + 512, pcBufferOut->GetEvent(0)->GetTime());

	cTest.mcTimeline.Run();
	AssertLong(1280 + 512 + 1024, cTest.mcTimeline.GetTime());
	AssertTrue(pcDriverOut->GetOutput()->IsDrive());
	AssertFloat(4.0f, pcA->GetVoltage(cTest.mcTimeline.GetTime()), 3);
	AssertFloat(4.0f, pcB->GetVoltage(cTest.mcTimeline.GetTime()), 3);
	AssertInt(TV_High, pcBufferIn->Read(&cTest.mcTimeline).eValue);
	AssertSize(0, pcDriverOut->NumEvents());
	AssertSize(0, pcBufferIn->NumEvents());
	AssertSize(0, pcBufferOut->NumEvents());
	AssertLog("");

	//Falling at 2816: hold 512, slew 4V to 0V, crossing 1V 768 later.
	pcDriverOut->Write(&cTest.mcTimeline, false);
	cTest.mcTimeline.Run();
	AssertLog("U1:0@4096;");
	AssertFloat(0.0f, pcB->GetVoltage(cTest.mcTimeline.GetTime()), 3);

	cTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogicPortImpedance(void)
{
	CTestLogicCircuit	cTest;
	CTestBuffer*		pcDriver;
	CLogicPort*			pcDriverOut;
	CTrace*				pcA;

	cTest.Init();
	pcDriver = cTest.AddBuffer("D", &cTest.mcFixed);
	cTest.mcCircuit.SimulationStarted();
	pcDriverOut = pcDriver->GetBufferPins()->mpcOut;
	pcA = cTest.mcCircuit.AddTrace();
	pcDriverOut->Connect(pcA);

	pcDriverOut->Write(&cTest.mcTimeline, true);
	cTest.mcTimeline.Run();
	AssertFloat(4.0f, pcA->GetVoltage(cTest.mcTimeline.GetTime()), 3);

	//0.01ns later.
	pcDriverOut->WriteImpedance(&cTest.mcTimeline);
	AssertLong(cTest.mcTimeline.GetTime() + 10, pcDriverOut->GetEvent(0)->GetTime());
	cTest.mcTimeline.Run();
	AssertFalse(IsVoltage(pcA->GetVoltage(cTest.mcTimeline.GetTime())));
	AssertInt(TV_Undriven, pcDriverOut->Read(&cTest.mcTimeline).eValue);

	cTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A slew replaces the drive of an earlier slew that hasn't finished.
//
//////////////////////////////////////////////////////////////////////////
void TestLogicPortSlewInterrupted(void)
{
	CTestLogicCircuit	cTest;
	CTestBuffer*		pcDriver;
	CLogicPort*			pcDriverOut;
	CTrace*				pcA;

	cTest.Init();
	pcDriver = cTest.AddBuffer("D", &cTest.mcFixed);
	cTest.mcCircuit.SimulationStarted();
	pcDriverOut = pcDriver->GetBufferPins()->mpcOut;
	pcA = cTest.mcCircuit.AddTrace();
	pcDriverOut->Connect(pcA);

	pcDriverOut->Write(&cTest.mcTimeline, true);
	cTest.mcTimeline.RunToTime(1024);  //Slewing since 512, at 2V.
	AssertFloat(2.0f, pcA->GetVoltage(1024), 3);
	AssertSize(1, pcDriverOut->NumEvents());

	//Falling, so a hold of 512.  The first slew's drive runs first at 1536, so the second slew starts from 4V.
	pcDriverOut->Write(&cTest.mcTimeline, false);
	AssertSize(2, pcDriverOut->NumEvents());
	cTest.mcTimeline.RunToTime(512);
	AssertLong(1536, cTest.mcTimeline.GetTime());
	AssertTrue(pcDriverOut->GetOutput()->IsSlew());
	AssertFloat(4.0f, pcDriverOut->GetOutput()->GetStartVoltage(), 3);
	AssertLong(1024, pcDriverOut->GetOutput()->GetSlewTime());
	AssertSize(1, pcDriverOut->NumEvents());
	AssertLong(2560, pcDriverOut->GetEvent(0)->GetTime());

	cTest.mcTimeline.Run();
	AssertLong(2560, cTest.mcTimeline.GetTime());
	AssertFloat(0.0f, pcA->GetVoltage(2560), 3);

	cTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// With a family's configuration a chip with no power doesn't drive.
//
//////////////////////////////////////////////////////////////////////////
void TestLogicPortNoPower(void)
{
	CTestLogicCircuit			cTest;
	CTestBuffer*				pcDriver;
	CLogicPort*					pcDriverOut;
	CFamilyVoltageConfiguration	cFamily;
	CVoltageConfiguration		cConfiguration;

	cTest.Init();
	cFamily.Init("TEST");
	cConfiguration.Init(4.0f, 1.0f, 3.0f, 0.0f, 4.0f, 1024, 1024);
	cFamily.Add(&cConfiguration, LOGIC_LEVEL_TTL);

	pcDriver = NewMalloc<CTestBuffer>();
	pcDriver->Init(&cTest.mcCircuit, "D", &cFamily, &cTest.mszLog);
	cTest.mcCircuit.SimulationStarted();
	pcDriverOut = pcDriver->GetBufferPins()->mpcOut;
	AssertFalse(pcDriver->IsPowered(0));

	pcDriverOut->Write(&cTest.mcTimeline, true);
	AssertSize(0, pcDriverOut->NumEvents());

	cTest.Power(pcDriver);
	AssertTrue(pcDriver->IsPowered(0));
	pcDriverOut->Write(&cTest.mcTimeline, true);
	AssertSize(1, pcDriverOut->NumEvents());
	AssertLong(512, pcDriverOut->GetEvent(0)->GetTime());

	cTest.Kill();
	cFamily.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A port connected to a trace already high sees a transition at once.
//
//////////////////////////////////////////////////////////////////////////
void TestLogicPortTraceConnected(void)
{
	CTestLogicCircuit	cTest;
	CTestBuffer*		pcBuffer;
	CLogicPort*			pcBufferIn;
	CTestPowerSource	cHigh;
	CTrace*				pcA;

	cTest.Init();
	pcBuffer = cTest.AddBuffer("U1", &cTest.mcFixed);
	cTest.mcCircuit.SimulationStarted();
	pcBufferIn = pcBuffer->GetBufferPins()->mpcIn;

	pcA = cTest.mcCircuit.AddTrace();
	cHigh.Init(4.0f);
	cHigh.mpcOut->Connect(pcA);
	pcBufferIn->Connect(pcA);
	pcBufferIn->TraceConnected(&cTest.mcTimeline);
	AssertSize(1, pcBufferIn->NumEvents());
	AssertLong(1, pcBufferIn->GetEvent(0)->GetTime());

	cTest.mcTimeline.Run();
	AssertLog("U1:1@1;");

	cHigh.Kill();
	cTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Disconnecting a port takes its events off the timeline; killing the
// circuit takes them all off.
//
//////////////////////////////////////////////////////////////////////////
void TestLogicPortDisconnect(void)
{
	CTestLogicCircuit	cTest;
	CTestBuffer*		pcDriver;
	CTestBuffer*		pcBuffer;
	CLogicPort*			pcDriverOut;
	CTrace*				pcA;

	cTest.Init();
	pcDriver = cTest.AddBuffer("D", &cTest.mcFixed);
	pcBuffer = cTest.AddBuffer("U1", &cTest.mcFixed);
	cTest.mcCircuit.SimulationStarted();
	pcDriverOut = pcDriver->GetBufferPins()->mpcOut;
	pcA = cTest.mcCircuit.AddTrace();
	pcDriverOut->Connect(pcA);
	pcBuffer->GetBufferPins()->mpcIn->Connect(pcA);

	pcDriverOut->Write(&cTest.mcTimeline, true);
	AssertSize(1, cTest.mcTimeline.NumSimultaneousEvents());
	pcDriverOut->Disconnect(&cTest.mcTimeline);
	AssertSize(0, cTest.mcTimeline.NumSimultaneousEvents());
	AssertSize(0, pcDriverOut->NumEvents());
	AssertNull(pcDriverOut->GetTrace());
	AssertSize(1, pcA->NumConnectedPorts());

	pcDriverOut->Connect(pcA);
	pcDriverOut->Write(&cTest.mcTimeline, true);
	cTest.mcTimeline.RunToTime(512);
	AssertSize(2, cTest.mcTimeline.NumSimultaneousEvents());  //The drive and the transition.

	cTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogicPortTick(void)
{
	CTestLogicCircuit	cTest;
	CTestClock*			pcClock;
	CTestBuffer*		pcBuffer;
	CTrace*				pcClockTrace;
	CChars				sz;
	SLogConfig			sLogConfig;
	CStateless*			pcState;

	cTest.Init();
	pcClock = NewMalloc<CTestClock>();
	pcClock->Init(&cTest.mcCircuit, "Clock", &cTest.mcFixed, 10000);
	cTest.Power(pcClock);
	pcBuffer = cTest.AddBuffer("U1", &cTest.mcFixed);
	pcClockTrace = cTest.mcCircuit.AddTrace();
	((CTestBufferPins*)pcClock->GetPins())->mpcOut->Connect(pcClockTrace);
	pcBuffer->GetBufferPins()->mpcIn->Connect(pcClockTrace);

	cTest.mcCircuit.SimulationStarted();
	AssertFalse(pcClock->IsStateless());
	AssertSize(1, pcClock->NumEvents());

	cTest.mcTimeline.RunToTime(45000);
	AssertSize(4, pcClock->GetClockState()->muiTicks);
	AssertLog("U1:1@11280;U1:0@21280;U1:1@31280;U1:0@41280;");

	sz.Init();
	pcClock->AppendDescription(&sz);
	AssertString("Clock \"Clock\"", sz.Text());
	sz.Kill();

	pcState = NewMalloc<CStateless>();
	sLogConfig = gcLogger.SetSilent();
	AssertFalse(pcClock->SetState(pcState));
	AssertFalse(pcClock->SetState(NULL));
	gcLogger.SetConfig(&sLogConfig);
	SafeKill(pcState);

	cTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A CW65C02Pins on analog traces: a CLogicPortBus for the address and
// data and logic ports for the signals.
//
//////////////////////////////////////////////////////////////////////////
void TestLogicPortPins(void)
{
	CTestLogicCircuit	cTest;
	CTestBuffer*		apcBits[8];
	CTestBuffer*		pcSignals;
	CLogicPortBus		cData;
	CW65C02Pins			cPins;
	CTrace*				pcTrace;
	size				i;
	CMetaBus16			cMetaAddress;
	CMetaTrace			cMetaPHI2;

	cTest.Init();
	cData.Init();
	for (i = 0; i < 8; i++)
	{
		apcBits[i] = cTest.AddBuffer("", &cTest.mcFixed);
		cData.Add(apcBits[i]->GetBufferPins()->mpcOut);
		pcTrace = cTest.mcCircuit.AddTrace();
		apcBits[i]->GetBufferPins()->mpcOut->Connect(pcTrace);
	}
	pcSignals = cTest.AddBuffer("", &cTest.mcFixed);
	cTest.mcCircuit.SimulationStarted();
	AssertSize(8, cData.GetWidth());
	AssertNull(cData.GetPort(8));

	//Address on an ideal bus, data on analog traces.
	cMetaAddress.Init();
	cMetaPHI2.Init(true);
	cPins.Init(&cMetaAddress, &cData, &cMetaPHI2, pcSignals->GetBufferPins()->mpcIn, pcSignals->GetBufferPins()->mpcOut);

	cPins.WriteAddress(&cTest.mcTimeline, 0x1234);
	AssertInt(0x1234, cMetaAddress.Get());
	AssertInt(0x1234, cPins.ReadAddress(&cTest.mcTimeline));

	cPins.WriteData(&cTest.mcTimeline, 0xA5);
	AssertInt(0, cPins.ReadData(&cTest.mcTimeline));  //Not slewed yet.
	cTest.mcTimeline.Run();
	AssertInt(0xA5, cPins.ReadData(&cTest.mcTimeline));
	AssertInt(TV_High, cPins.ReadPhi2(&cTest.mcTimeline).eValue);
	AssertInt(TV_Undriven, cPins.ReadRES(&cTest.mcTimeline).eValue);
	AssertInt(TV_Undriven, cPins.ReadSOB(&cTest.mcTimeline).eValue);  //Not connected.

	cData.WriteImpedance(&cTest.mcTimeline);
	cTest.mcTimeline.Run();
	AssertInt(0, cPins.ReadData(&cTest.mcTimeline));
	AssertInt(TV_Undriven, apcBits[0]->GetBufferPins()->mpcOut->Read(&cTest.mcTimeline).eValue);

	cPins.Kill();
	cData.Kill();
	cMetaAddress.Kill();
	cMetaPHI2.Kill();
	cTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogicPortIdealSignals(void)
{
	CMetaTrace		cTrace;
	CMetaBus8		cBus;
	CLogicSignal*	pcSignal;
	CLogicBus*		pcBus;

	cTrace.Init();
	cBus.Init();
	pcSignal = &cTrace;
	pcBus = &cBus;

	pcSignal->Write(NULL, true);
	AssertTrue(cTrace.IsHigh());
	AssertInt(TV_High, pcSignal->Read(NULL).eValue);
	pcSignal->WriteImpedance(NULL);
	AssertInt(TV_Undriven, pcSignal->Read(NULL).eValue);

	pcBus->Write(NULL, 0x1FF);
	AssertInt(0xFF, cBus.Get());
	AssertInt(0xFF, pcBus->Read(NULL));
	AssertSize(8, pcBus->GetWidth());

	cTrace.Kill();
	cBus.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogicPort(void)
{
	BeginTests();

	TestLogicPortIdealSignals();
	TestLogicPortTrace();
	TestLogicPortSlewAndTransition();
	TestLogicPortImpedance();
	TestLogicPortSlewInterrupted();
	TestLogicPortNoPower();
	TestLogicPortTraceConnected();
	TestLogicPortDisconnect();
	TestLogicPortTick();
	TestLogicPortPins();

	TestStatistics();
}

