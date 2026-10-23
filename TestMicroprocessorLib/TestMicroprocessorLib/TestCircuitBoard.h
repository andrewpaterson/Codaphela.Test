#ifndef __TEST_CIRCUIT_BOARD_H__
#define __TEST_CIRCUIT_BOARD_H__
#include "BaseLib/ConstructorCall.h"
#include "BaseLib/PointerFunctions.h"
#include "BaseLib/Logger.h"
#include "MicroprocessorLib/LongTime.h"
#include "MicroprocessorLib/Units.h"
#include "MicroprocessorLib/Voltage.h"
#include "MicroprocessorLib/CircuitSimulation.h"
#include "MicroprocessorLib/PowerSource.h"
#include "MicroprocessorLib/PowerInPort.h"
#include "MicroprocessorLib/FamilyVoltageConfigurationStore.h"
#include "MicroprocessorLib/AndGate.h"
#include "MicroprocessorLib/OrGate.h"
#include "MicroprocessorLib/XorGate.h"
#include "MicroprocessorLib/Buffer.h"
#include "MicroprocessorLib/Constant.h"
#include "MicroprocessorLib/Probe.h"
#include "MicroprocessorLib/ClockOscillator.h"
#include "MicroprocessorLib/DTypeFlipFlop.h"
#include "MicroprocessorLib/Counter.h"


enum EGate
{
	G_And,
	G_Nand,
	G_Or,
	G_Nor,
	G_Xor,
	G_Xnor,
};


//////////////////////////////////////////////////////////////////////////
//
// A circuit simulation powered at 3.3V with LVC parts from Logicim's
// propagation times, and helpers to wire it.
//
//////////////////////////////////////////////////////////////////////////
class CTestBoard
{
public:
	CCircuitSimulation					mcSimulation;
	CFamilyVoltageConfigurationStore	mcStore;
	CVoltageConfigurationSource*		mpcFamily;
	CSubcircuitSimulation*				mpcTop;
	CTimeline*							mpcTimeline;
	CTrace*								mpcVCC;
	CTrace*								mpcGND;

	void Init(void)
	{
		CPowerSource*	pcPower;

		CEvent::ResetNextID();
		CTrace::ResetNextID();
		mcStore.Init();
		mcStore.Load("Input/PropagationTimes.csv");
		mpcFamily = mcStore.Get("LVC");

		mcSimulation.Init("Board");
		mpcTop = mcSimulation.GetSubcircuitTopSimulation();
		mpcTimeline = mcSimulation.GetTimeline();
		mpcVCC = NewTrace();
		mpcGND = NewTrace();
		pcPower = NewMalloc<CPowerSource>();
		pcPower->Init(mpcTop, "VCC", 3.3f);
		pcPower->GetPowerOutPort()->Connect(mpcVCC);
		pcPower = NewMalloc<CPowerSource>();
		pcPower->Init(mpcTop, "GND", 0.0f);
		pcPower->GetPowerOutPort()->Connect(mpcGND);
	}

	void Kill(void)
	{
		mcSimulation.Kill();
		mcStore.Kill();
	}

	CTrace* NewTrace(void)
	{
		return mcSimulation.GetCircuit()->AddTrace();
	}

	void Power(CIntegratedCircuit* pcIntegratedCircuit)
	{
		pcIntegratedCircuit->GetPins()->GetVoltageCommon()->Connect(mpcVCC);
		pcIntegratedCircuit->GetPins()->GetVoltageGround()->Connect(mpcGND);
	}

	//A constant on a new trace, driven when the simulation starts.
	CConstant* Input(const char* szName, int64 iValue, size uiBits, CTrace** apcTraces)
	{
		CConstantPins*	pcPins;
		CConstant*		pcConstant;
		size			i;

		pcPins = NewMalloc<CConstantPins>();
		pcPins->Init(mpcFamily, uiBits);
		pcConstant = NewMalloc<CConstant>();
		pcConstant->Init(mpcTop, szName, pcPins, iValue);
		Power(pcConstant);
		for (i = 0; i < uiBits; i++)
		{
			apcTraces[i] = NewTrace();
			pcPins->GetOutput(i)->Connect(apcTraces[i]);
		}
		return pcConstant;
	}

	CTrace* Input(const char* szName, bool bValue)
	{
		CTrace*	pcTrace;

		Input(szName, bValue ? 1 : 0, 1, &pcTrace);
		return pcTrace;
	}

	//A gate whose inputs are connected to the traces, with its output on a new trace.
	CTrace* Gate(EGate eGate, CTrace* pcA, CTrace* pcB, CTrace* pcC = NULL)
	{
		CIntegratedCircuit*	pcGate;
		CArrayLogicPortPtr*	papcInputs;
		CLogicPort*			pcOutput;
		CTrace*				apcInputs[3];
		size				uiInputs;
		size				i;
		CTrace*				pcOut;

		apcInputs[0] = pcA;
		apcInputs[1] = pcB;
		apcInputs[2] = pcC;
		uiInputs = (pcC == NULL) ? 2 : 3;

		if ((eGate == G_And) || (eGate == G_Nand))
		{
			CAndGatePins*	pcPins = NewMalloc<CAndGatePins>();
			CAndGate*		pcAnd = (eGate == G_And) ? NewMalloc<CAndGate>() : NewMalloc<CNandGate>();

			pcPins->Init(uiInputs, mpcFamily);
			pcAnd->Init(mpcTop, "", pcPins);
			pcGate = pcAnd;
			papcInputs = pcPins->GetInputs();
			pcOutput = pcPins->GetOutput();
		}
		else if ((eGate == G_Or) || (eGate == G_Nor))
		{
			COrGatePins*	pcPins = NewMalloc<COrGatePins>();
			COrGate*		pcOr = (eGate == G_Or) ? NewMalloc<COrGate>() : NewMalloc<CNorGate>();

			pcPins->Init(uiInputs, mpcFamily);
			pcOr->Init(mpcTop, "", pcPins);
			pcGate = pcOr;
			papcInputs = pcPins->GetInputs();
			pcOutput = pcPins->GetOutput();
		}
		else
		{
			CXorGatePins*	pcPins = NewMalloc<CXorGatePins>();
			CXorGate*		pcXor = (eGate == G_Xor) ? NewMalloc<CXorGate>() : NewMalloc<CXnorGate>();

			pcPins->Init(uiInputs, mpcFamily);
			pcXor->Init(mpcTop, "", pcPins);
			pcGate = pcXor;
			papcInputs = pcPins->GetInputs();
			pcOutput = pcPins->GetOutput();
		}

		Power(pcGate);
		for (i = 0; i < uiInputs; i++)
		{
			papcInputs->GetPtr(i)->Connect(apcInputs[i]);
		}
		pcOut = NewTrace();
		pcOutput->Connect(pcOut);
		return pcOut;
	}

	//A gate whose output drives an existing trace, for feedback.
	void GateTo(EGate eGate, CTrace* pcA, CTrace* pcB, CTrace* pcOut)
	{
		CTrace*		pcNew;
		CPort*		pcOutput;

		pcNew = Gate(eGate, pcA, pcB);
		pcOutput = pcNew->GetConnectedPort(0);
		pcOutput->Disconnect(mpcTimeline);
		pcOutput->Connect(pcOut);
	}

	CTrace* Buffer(CTrace* pcIn, bool bInvert)
	{
		CBufferPins*	pcPins;
		CBuffer*		pcBuffer;
		CTrace*			pcOut;

		pcPins = NewMalloc<CBufferPins>();
		pcPins->Init(1, mpcFamily);
		pcBuffer = bInvert ? NewMalloc<CInverter>() : NewMalloc<CBuffer>();
		pcBuffer->Init(mpcTop, "", pcPins);
		Power(pcBuffer);
		pcPins->GetInput(0)->Connect(pcIn);
		pcOut = NewTrace();
		pcPins->GetOutput(0)->Connect(pcOut);
		return pcOut;
	}

	CTrace* Not(CTrace* pcIn)
	{
		return Buffer(pcIn, true);
	}

	CProbe* Probe(CTrace** apcTraces, size uiBits)
	{
		CProbePins*	pcPins;
		CProbe*		pcProbe;
		size		i;

		pcPins = NewMalloc<CProbePins>();
		pcPins->Init(mpcFamily, uiBits);
		pcProbe = NewMalloc<CProbe>();
		pcProbe->Init(mpcTop, "", pcPins);
		Power(pcProbe);
		for (i = 0; i < uiBits; i++)
		{
			pcPins->GetInput(i)->Connect(apcTraces[i]);
		}
		return pcProbe;
	}

	CProbe* Probe(CTrace* pcTrace)
	{
		return Probe(&pcTrace, 1);
	}

	void Start(void)
	{
		mcSimulation.SimulationStarted();
	}

	void Run(void)
	{
		mpcTimeline->Run();
	}

	uint64 Read(CProbe* pcProbe)
	{
		return pcProbe->ReadValue(mpcTimeline);
	}

	ETraceValue Value(CTrace* pcTrace)
	{
		return mpcFamily->GetValue(pcTrace->GetVoltage(mpcTimeline->GetTime()), 3.3f);
	}

	void Write(CConstant* pcConstant, bool bValue)
	{
		pcConstant->GetConstantPins()->GetOutput(0)->Write(mpcTimeline, bValue);
	}
};


#endif // __TEST_CIRCUIT_BOARD_H__

