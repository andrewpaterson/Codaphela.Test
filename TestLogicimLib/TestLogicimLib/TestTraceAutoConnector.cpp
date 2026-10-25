#include <math.h>
#include "BaseLib/ConstructorCall.h"
#include "BaseLib/ArrayInt.h"
#include "BaseLib/LogToMemory.h"
#include "LogicimLib/BufferView.h"
#include "LogicimLib/CircuitView.h"
#include "LogicimLib/TraceAutoConnector.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CBufferView* AddAutoConnectBuffer(CCircuitView* pcCircuit, int32 x, int32 y, int iCount)
{
	CBufferView*	pcBuffer;

	pcBuffer = NewMalloc<CBufferView>();
	pcBuffer->Init(x, y, ROT_East, "", "LVC", false, iCount, 1);
	pcCircuit->Add(pcBuffer);
	return pcBuffer;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int FindAutoConnectRoot(CArrayInt* paiParents, int i)
{
	while (paiParents->GetValue(i) != i)
	{
		i = paiParents->GetValue(i);
	}
	return i;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void JoinAutoConnectRoots(CArrayInt* paiParents, int i, int j)
{
	i = FindAutoConnectRoot(paiParents, i);
	j = FindAutoConnectRoot(paiParents, j);
	if (i != j)
	{
		paiParents->SetValue(j, i);
	}
}


//////////////////////////////////////////////////////////////////////////
//
// The group each port is in, joined as Logicim's wiring joins them
// (CCircuitWiring::JoinLevel): wires that touch, ports on wires and ports
// at the same place.  Ports are numbered after the wires.
//
//////////////////////////////////////////////////////////////////////////
void GetAutoConnectGroups(CCircuitView* pcCircuit, CArrayPortViewPtr* papcPorts, CArrayInt* paiParents)
{
	size	i;
	size	j;
	size	uiTraces;

	papcPorts->Init();
	pcCircuit->CollectPortViews(papcPorts);
	uiTraces = pcCircuit->NumTraces();
	paiParents->Init();
	for (i = 0; i < uiTraces + papcPorts->NumElements(); i++)
	{
		paiParents->Add((int)i);
	}
	for (i = 0; i < uiTraces; i++)
	{
		for (j = i + 1; j < uiTraces; j++)
		{
			if (pcCircuit->GetTrace(i)->Touches(pcCircuit->GetTrace(j)))
			{
				JoinAutoConnectRoots(paiParents, (int)i, (int)j);
			}
		}
	}
	for (i = 0; i < papcPorts->NumElements(); i++)
	{
		for (j = 0; j < uiTraces; j++)
		{
			if (pcCircuit->GetTrace(j)->Contains(papcPorts->GetPtr(i)->GetGridPosition()))
			{
				JoinAutoConnectRoots(paiParents, (int)(uiTraces + i), (int)j);
			}
		}
		for (j = i + 1; j < papcPorts->NumElements(); j++)
		{
			if (papcPorts->GetPtr(i)->GetGridPosition() == papcPorts->GetPtr(j)->GetGridPosition())
			{
				JoinAutoConnectRoots(paiParents, (int)(uiTraces + i), (int)(uiTraces + j));
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int GetAutoConnectGroup(CCircuitView* pcCircuit, CArrayPortViewPtr* papcPorts, CArrayInt* paiParents, CPortView* pcPort)
{
	return FindAutoConnectRoot(paiParents, (int)(pcCircuit->NumTraces() + papcPorts->Find(pcPort)));
}


//////////////////////////////////////////////////////////////////////////
//
// Whether the two ports are joined by the circuit's wires.
//
//////////////////////////////////////////////////////////////////////////
bool AreAutoConnected(CCircuitView* pcCircuit, CPortView* pcPort1, CPortView* pcPort2)
{
	CArrayPortViewPtr	apcPorts;
	CArrayInt			aiParents;
	bool				bResult;

	GetAutoConnectGroups(pcCircuit, &apcPorts, &aiParents);
	bResult = GetAutoConnectGroup(pcCircuit, &apcPorts, &aiParents, pcPort1) == GetAutoConnectGroup(pcCircuit, &apcPorts, &aiParents, pcPort2);
	aiParents.Kill();
	apcPorts.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// How many ports the port's group has.
//
//////////////////////////////////////////////////////////////////////////
size NumAutoConnectedPorts(CCircuitView* pcCircuit, CPortView* pcPort)
{
	CArrayPortViewPtr	apcPorts;
	CArrayInt			aiParents;
	int					iGroup;
	size				i;
	size				uiPorts;

	GetAutoConnectGroups(pcCircuit, &apcPorts, &aiParents);
	iGroup = GetAutoConnectGroup(pcCircuit, &apcPorts, &aiParents, pcPort);
	uiPorts = 0;
	for (i = 0; i < apcPorts.NumElements(); i++)
	{
		if (FindAutoConnectRoot(&aiParents, (int)(pcCircuit->NumTraces() + i)) == iGroup)
		{
			uiPorts++;
		}
	}
	aiParents.Kill();
	apcPorts.Kill();
	return uiPorts;
}


//////////////////////////////////////////////////////////////////////////
//
// Whether any wire goes into the component's box (its ports' ends aside).
//
//////////////////////////////////////////////////////////////////////////
bool IsAutoConnectThroughBox(CCircuitView* pcCircuit, CComponentView* pcComponent)
{
	SFloat64Vec2	sMinimum;
	SFloat64Vec2	sMaximum;
	size			i;
	CTraceView*		pcTrace;
	SInt32Vec2		sStart;
	SInt32Vec2		sEnd;
	SInt32Vec2		sPoint;
	int32			iSteps;
	int32			j;

	pcComponent->GetBoundingBox(&sMinimum, &sMaximum);
	for (i = 0; i < pcCircuit->NumTraces(); i++)
	{
		pcTrace = pcCircuit->GetTrace(i);
		sStart = pcTrace->GetStart();
		sEnd = pcTrace->GetEnd();
		iSteps = abs(sEnd.x - sStart.x) + abs(sEnd.y - sStart.y);
		for (j = 0; j <= iSteps; j++)
		{
			sPoint.x = sStart.x + ((sEnd.x > sStart.x) ? j : ((sEnd.x < sStart.x) ? -j : 0));
			sPoint.y = sStart.y + ((sEnd.y > sStart.y) ? j : ((sEnd.y < sStart.y) ? -j : 0));
			if ((sPoint.x >= ceil(sMinimum.x)) && (sPoint.x <= floor(sMaximum.x)) && (sPoint.y >= ceil(sMinimum.y)) && (sPoint.y <= floor(sMaximum.y)))
			{
				return true;
			}
		}
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////
//
// The x of the first vertical wire, or -1000.
//
//////////////////////////////////////////////////////////////////////////
int32 GetAutoConnectVerticalX(CCircuitView* pcCircuit, size uiFirst)
{
	size			i;
	CTraceView*		pcTrace;

	for (i = uiFirst; i < pcCircuit->NumTraces(); i++)
	{
		pcTrace = pcCircuit->GetTrace(i);
		if ((pcTrace->GetStart().x == pcTrace->GetEnd().x) && (pcTrace->GetStart().y != pcTrace->GetEnd().y))
		{
			return pcTrace->GetStart().x;
		}
	}
	return -1000;
}


//////////////////////////////////////////////////////////////////////////
//
// An output to an input below and to the right turns down where its hint
// says: halfway, then a quarter of the way, across the gap between the
// buffers' boxes.
//
//////////////////////////////////////////////////////////////////////////
void TestTraceAutoConnectorBend(void)
{
	CCircuitView			cCircuit;
	CTraceAutoConnector		cConnector;
	CBufferView*			pcFrom;
	CBufferView*			pcTo;
	SFloat64Vec2			sFromMinimum;
	SFloat64Vec2			sFromMaximum;
	SFloat64Vec2			sToMinimum;
	SFloat64Vec2			sToMaximum;
	size					uiNet;

	cCircuit.Init();
	pcFrom = AddAutoConnectBuffer(&cCircuit, 0, 0, 1);
	pcTo = AddAutoConnectBuffer(&cCircuit, 20, 8, 1);
	pcFrom->GetBoundingBox(&sFromMinimum, &sFromMaximum);
	pcTo->GetBoundingBox(&sToMinimum, &sToMaximum);

	cConnector.Init(&cCircuit);
	uiNet = cConnector.AddNet();
	AssertTrue(cConnector.AddConnection(uiNet, pcFrom->GetPortView((size)1), pcTo->GetPortView((size)0), 0.5));
	AssertTrue(cConnector.Connect());
	cConnector.Kill();
	AssertTrue(AreAutoConnected(&cCircuit, pcFrom->GetPortView((size)1), pcTo->GetPortView((size)0)));
	AssertSize(3, cCircuit.NumTraces());
	AssertInt((int32)floor(sFromMaximum.x + 0.5 * (sToMinimum.x - sFromMaximum.x) + 0.5), GetAutoConnectVerticalX(&cCircuit, 0));

	cCircuit.KillTraces();
	AssertSize(0, cCircuit.NumTraces());
	cConnector.Init(&cCircuit);
	uiNet = cConnector.AddNet();
	AssertTrue(cConnector.AddConnection(uiNet, pcFrom->GetPortView((size)1), pcTo->GetPortView((size)0), 0.25));
	AssertTrue(cConnector.Connect());
	cConnector.Kill();
	AssertTrue(AreAutoConnected(&cCircuit, pcFrom->GetPortView((size)1), pcTo->GetPortView((size)0)));
	AssertInt((int32)floor(sFromMaximum.x + 0.25 * (sToMinimum.x - sFromMaximum.x) + 0.5), GetAutoConnectVerticalX(&cCircuit, 0));

	cCircuit.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A buffer in the way of the hinted route is gone round.
//
//////////////////////////////////////////////////////////////////////////
void TestTraceAutoConnectorObstacle(void)
{
	CCircuitView			cCircuit;
	CTraceAutoConnector		cConnector;
	CBufferView*			pcFrom;
	CBufferView*			pcTo;
	CBufferView*			pcInTheWay;
	size					uiNet;

	cCircuit.Init();
	pcFrom = AddAutoConnectBuffer(&cCircuit, 0, 0, 1);
	pcTo = AddAutoConnectBuffer(&cCircuit, 20, 0, 1);
	pcInTheWay = AddAutoConnectBuffer(&cCircuit, 10, 0, 3);

	cConnector.Init(&cCircuit);
	uiNet = cConnector.AddNet();
	AssertTrue(cConnector.AddConnection(uiNet, pcFrom->GetPortView((size)1), pcTo->GetPortView((size)0), 0.5));
	AssertTrue(cConnector.Connect());
	AssertSize(0, cConnector.NumUnconnected());
	cConnector.Kill();

	AssertTrue(AreAutoConnected(&cCircuit, pcFrom->GetPortView((size)1), pcTo->GetPortView((size)0)));
	AssertFalse(IsAutoConnectThroughBox(&cCircuit, pcInTheWay));
	AssertSize(2, NumAutoConnectedPorts(&cCircuit, pcTo->GetPortView((size)0)));

	cCircuit.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Two nets that have to cross stay apart.
//
//////////////////////////////////////////////////////////////////////////
void TestTraceAutoConnectorCrossing(void)
{
	CCircuitView			cCircuit;
	CTraceAutoConnector		cConnector;
	CBufferView*			pcTop;
	CBufferView*			pcBottom;
	CBufferView*			pcTopTo;
	CBufferView*			pcBottomTo;
	size					uiNet1;
	size					uiNet2;

	cCircuit.Init();
	pcTop = AddAutoConnectBuffer(&cCircuit, 0, 0, 1);
	pcBottom = AddAutoConnectBuffer(&cCircuit, 0, 10, 1);
	pcTopTo = AddAutoConnectBuffer(&cCircuit, 20, 10, 1);
	pcBottomTo = AddAutoConnectBuffer(&cCircuit, 20, 0, 1);

	cConnector.Init(&cCircuit);
	uiNet1 = cConnector.AddNet();
	uiNet2 = cConnector.AddNet();
	AssertTrue(cConnector.AddConnection(uiNet1, pcTop->GetPortView((size)1), pcTopTo->GetPortView((size)0), 0.5));
	AssertTrue(cConnector.AddConnection(uiNet2, pcBottom->GetPortView((size)1), pcBottomTo->GetPortView((size)0), 0.5));
	AssertTrue(cConnector.Connect());
	cConnector.Kill();

	AssertTrue(AreAutoConnected(&cCircuit, pcTop->GetPortView((size)1), pcTopTo->GetPortView((size)0)));
	AssertTrue(AreAutoConnected(&cCircuit, pcBottom->GetPortView((size)1), pcBottomTo->GetPortView((size)0)));
	AssertFalse(AreAutoConnected(&cCircuit, pcTop->GetPortView((size)1), pcBottom->GetPortView((size)1)));
	AssertSize(2, NumAutoConnectedPorts(&cCircuit, pcTop->GetPortView((size)1)));
	AssertSize(2, NumAutoConnectedPorts(&cCircuit, pcBottom->GetPortView((size)1)));

	cCircuit.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Four outputs to four inputs down and to the right as a run: each its own
// net, each turning down at its own x.
//
//////////////////////////////////////////////////////////////////////////
void TestTraceAutoConnectorRun(void)
{
	CCircuitView			cCircuit;
	CTraceAutoConnector		cConnector;
	CBufferView*			pcFrom;
	CBufferView*			pcTo;
	size					auiNets[4];
	size					uiRun;
	size					i;
	size					j;
	CArrayInt				aiBends;
	CTraceView*				pcTrace;

	cCircuit.Init();
	pcFrom = AddAutoConnectBuffer(&cCircuit, 0, 0, 4);
	pcTo = AddAutoConnectBuffer(&cCircuit, 24, 14, 4);

	cConnector.Init(&cCircuit);
	uiRun = cConnector.AddRun();
	for (i = 0; i < 4; i++)
	{
		auiNets[i] = cConnector.AddNet();
		AssertTrue(cConnector.AddConnection(auiNets[i], pcFrom->GetPortView(4 + i), pcTo->GetPortView(i), 0.5, (int)uiRun));
	}
	AssertTrue(cConnector.Connect());
	cConnector.Kill();

	for (i = 0; i < 4; i++)
	{
		AssertTrue(AreAutoConnected(&cCircuit, pcFrom->GetPortView(4 + i), pcTo->GetPortView(i)));
		AssertSize(2, NumAutoConnectedPorts(&cCircuit, pcTo->GetPortView(i)));
	}

	aiBends.Init();
	for (i = 0; i < cCircuit.NumTraces(); i++)
	{
		pcTrace = cCircuit.GetTrace(i);
		if ((pcTrace->GetStart().x == pcTrace->GetEnd().x) && (pcTrace->GetStart().y != pcTrace->GetEnd().y))
		{
			for (j = 0; j < aiBends.NumElements(); j++)
			{
				AssertFalse(aiBends.GetValue(j) == pcTrace->GetStart().x);
			}
			aiBends.Add(pcTrace->GetStart().x);
		}
	}
	AssertSize(4, aiBends.NumElements());
	AssertSize(12, cCircuit.NumTraces());
	aiBends.Kill();

	cCircuit.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// One output to three inputs: each input joins the wires already routed.
//
//////////////////////////////////////////////////////////////////////////
void TestTraceAutoConnectorFanOut(void)
{
	CCircuitView			cCircuit;
	CTraceAutoConnector		cConnector;
	CBufferView*			pcFrom;
	CBufferView*			apcTo[3];
	size					uiNet;
	size					i;

	cCircuit.Init();
	pcFrom = AddAutoConnectBuffer(&cCircuit, 0, 6, 1);
	apcTo[0] = AddAutoConnectBuffer(&cCircuit, 20, 0, 1);
	apcTo[1] = AddAutoConnectBuffer(&cCircuit, 20, 6, 1);
	apcTo[2] = AddAutoConnectBuffer(&cCircuit, 20, 12, 1);

	cConnector.Init(&cCircuit);
	uiNet = cConnector.AddNet();
	for (i = 0; i < 3; i++)
	{
		AssertTrue(cConnector.AddConnection(uiNet, apcTo[i]->GetPortView((size)0), pcFrom->GetPortView((size)1), 0.5));
	}
	AssertTrue(cConnector.Connect());
	cConnector.Kill();

	AssertSize(4, NumAutoConnectedPorts(&cCircuit, pcFrom->GetPortView((size)1)));

	cCircuit.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A wire already in the circuit that isn't on a net being connected is
// kept clear of; one on a port of the net is joined.
//
//////////////////////////////////////////////////////////////////////////
void TestTraceAutoConnectorExisting(void)
{
	CCircuitView			cCircuit;
	CTraceAutoConnector		cConnector;
	CBufferView*			pcFrom;
	CBufferView*			pcTo;
	CBufferView*			pcOther;
	CTraceView*				pcForeign;
	SInt32Vec2				sOutput;
	size					uiNet;

	cCircuit.Init();
	pcFrom = AddAutoConnectBuffer(&cCircuit, 0, 0, 1);
	pcTo = AddAutoConnectBuffer(&cCircuit, 20, 0, 1);
	pcOther = AddAutoConnectBuffer(&cCircuit, 0, 10, 1);

	//A foreign wire across the way, and a stub on the from port.
	pcForeign = cCircuit.AddTrace(10, -6, 10, 6);
	sOutput = pcFrom->GetPortView((size)1)->GetGridPosition();
	cCircuit.AddTrace(sOutput.x, sOutput.y, sOutput.x + 2, sOutput.y);

	cConnector.Init(&cCircuit);
	uiNet = cConnector.AddNet();
	AssertTrue(cConnector.AddConnection(uiNet, pcTo->GetPortView((size)0), pcFrom->GetPortView((size)1), TRACE_AUTO_CONNECT_NO_BEND));
	AssertTrue(cConnector.AddConnection(uiNet, pcOther->GetPortView((size)1), pcTo->GetPortView((size)0), TRACE_AUTO_CONNECT_NO_BEND));
	AssertTrue(cConnector.Connect());
	cConnector.Kill();

	AssertTrue(AreAutoConnected(&cCircuit, pcFrom->GetPortView((size)1), pcTo->GetPortView((size)0)));
	AssertTrue(AreAutoConnected(&cCircuit, pcOther->GetPortView((size)1), pcTo->GetPortView((size)0)));
	AssertSize(3, NumAutoConnectedPorts(&cCircuit, pcTo->GetPortView((size)0)));
	AssertTrue(cCircuit.GetTrace(0) == pcForeign);

	cCircuit.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A port can't be on two nets.
//
//////////////////////////////////////////////////////////////////////////
void TestTraceAutoConnectorErrors(void)
{
	CCircuitView			cCircuit;
	CTraceAutoConnector		cConnector;
	CBufferView*			pcFrom;
	CBufferView*			pcTo;
	size					uiNet1;
	size					uiNet2;
	CLogToMemory			cMemoryLog;
	char					szLogText[1024];
	bool					bOtherNet;
	bool					bNoNet;

	cCircuit.Init();
	pcFrom = AddAutoConnectBuffer(&cCircuit, 0, 0, 1);
	pcTo = AddAutoConnectBuffer(&cCircuit, 20, 0, 1);

	cConnector.Init(&cCircuit);
	uiNet1 = cConnector.AddNet();
	uiNet2 = cConnector.AddNet();
	AssertTrue(cConnector.AddConnection(uiNet1, pcFrom->GetPortView((size)1), pcTo->GetPortView((size)0), 0.5));
	cMemoryLog.Start(true);
	bOtherNet = cConnector.AddConnection(uiNet2, pcFrom->GetPortView((size)1), pcTo->GetPortView((size)0), 0.5);
	bNoNet = cConnector.AddConnection(7, pcFrom->GetPortView((size)1), pcTo->GetPortView((size)0), 0.5);
	cMemoryLog.Stop(szLogText, 1024);
	AssertFalse(bOtherNet);
	AssertFalse(bNoNet);
	AssertTrue(strstr(szLogText, "is already on another net.") != NULL);
	AssertTrue(strstr(szLogText, "There is no net [7].") != NULL);
	AssertSize(1, cConnector.NumConnections());
	cConnector.Kill();

	cCircuit.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTraceAutoConnector(void)
{
	BeginTests();

	TestTraceAutoConnectorBend();
	TestTraceAutoConnectorObstacle();
	TestTraceAutoConnectorCrossing();
	TestTraceAutoConnectorRun();
	TestTraceAutoConnectorFanOut();
	TestTraceAutoConnectorExisting();
	TestTraceAutoConnectorErrors();

	TestStatistics();
}

