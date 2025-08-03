#include "BaseLib/Logger.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/Operators.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "InputLib/Input.h"
//#include "WinInputLib/WinInput.h"
#include "TestLib/Assert.h"
#include "Player.h"


struct STestEventValue
{
	char*	szName;
	float	fValue;
};


typedef CArrayTemplate<STestEventValue> CArrayTestEventValue;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertEvents(CInput* pcInput, CProgramDeviceDetail* pcDetail, CPlayer* pcPlayer, char* szExpectedAction, char* szFirstEvent, ...)
{
	va_list						vaMarker;
	char*						pc;
	size						iCount;
	CArrayTestEventValue		cArray;
	size						iLen;
	float						fValue;
	size						i;
	STestEventValue*			pcEvent;

	cArray.Init();
	pcPlayer->GetEvents()->ReInit();

	iCount = 0;
	pc = szFirstEvent;
	va_start(vaMarker, szFirstEvent);
	while (pc != NULL)
	{
		pcEvent =  cArray.Add();

		pcEvent->szName = pc;
		iLen = (int)strlen(pc);
		fValue = (float)atof(&pc[iLen+1]);
		pcEvent->fValue = fValue;

		iCount++;
		pc = va_arg(vaMarker, char*);
	}

	for (i = 0; i < cArray.NumElements()-1; i++)
	{
		pcEvent = cArray.Get(i);
		pcDetail->AddEvent(pcEvent->szName, pcEvent->fValue);
		pcInput->Update();
		AssertInt(0, pcPlayer->GetEvents()->NumElements());
	}

	pcEvent = cArray.Get(i);
	pcDetail->AddEvent(pcEvent->szName, pcEvent->fValue);
	pcInput->Update();
	AssertInt(1, pcPlayer->GetEvents()->NumElements());
	AssertString(szExpectedAction, pcPlayer->GetEvents()->GetText(0));

	cArray.Kill();

	va_end(vaMarker);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CProgramDeviceDetail* AddProgrammaticDevice(CProgramInput*	pcProgram)
{
	CProgramDeviceDetail*	pcDetail;

	pcDetail = pcProgram->AddDetail("Programmatic: Device 1", "Happy Device");
	pcDetail->AddSource("W");
	pcDetail->AddSource("A");
	pcDetail->AddSource("S");
	pcDetail->AddSource("D");
	pcDetail->AddSource("Left Control");
	pcDetail->AddSource("Space");
	pcDetail->AddSource("Cursor Left");
	pcDetail->AddSource("Cursor Right");
	pcDetail->AddSource("Cursor Up");
	pcDetail->AddSource("Cursor Down");
	pcDetail->AddSource("Right Control");
	return pcDetail;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestInputChords(void)
{
	FastFunctionsInit();
	TypesInit();
	TypeConverterInit();
	OperatorsInit();
	MemoryInit();
	DataIOInit();
	UnknownsInit();
	ObjectsInit();

	BeginTests();

	CInput						cInput;
	CPlayer						cPlayer1;
	CPlayer						cPlayer2;
	CProgramDeviceDetail*		pcDetail;
	CInputVirtualDevice*		pcPlayer1;
	bool						bResult;
	CInputDevice*				pcDevice;
	CInputVirtualDevice*		pcPlayer2;
	CInputChord*				pcChord;
	COrderedInputChordCriteria*	pcOrdered;
	CGroupInputChordCriteria*	pcGroup;

	cInput.Init(NULL);
	pcDetail = AddProgrammaticDevice(cInput.GetProgramInput());
	cInput.AddProgramInput();
	
	cPlayer1.Init();
	pcPlayer1 = cInput.GetDevices()->GetFirstVirtualDeviceInCategoryKeyboard(cInput.GetProgramInput()->GetCategoryName(), false);
	pcDevice = pcPlayer1->GetDefaultDevice();

	pcPlayer1 = cInput.GetDevices()->CreateVirtualDevice("Player 1");
	bResult = pcPlayer1->AddSources(pcDevice, "W", "A", "S", "D", "Left Control", NULL);
	AssertBool(true, bResult);

	pcPlayer1->AddOrderedAction(cInput.GetActions()->AddActionWithListener("Player 1 Up", &CPlayerListener::Up, (CPlayerListener*)&cPlayer1), "W", "W", NULL);
	pcPlayer1->AddOrderedAction(cInput.GetActions()->AddActionWithListener("Player 1 Down", &CPlayerListener::Down, (CPlayerListener*)&cPlayer1), "S", "W", "W", "W", NULL);
	pcPlayer1->AddOrderedAction(cInput.GetActions()->AddActionWithListener("Player 1 Left", &CPlayerListener::Left, (CPlayerListener*)&cPlayer1), "A", "D", "A", "A", NULL);
	pcPlayer1->AddOrderedAction(cInput.GetActions()->AddActionWithListener("Player 1 Right", &CPlayerListener::Right, (CPlayerListener*)&cPlayer1), "A", "D", "A", "D", NULL);

	pcPlayer1->Enable();

	pcDetail->AddEvent("W", 1.0f);
	cInput.Update();
	AssertInt(0, cPlayer1.GetEvents()->NumElements());

	pcDetail->AddEvent("W", 0.0f);
	cInput.Update();
	AssertInt(0, cPlayer1.GetEvents()->NumElements());

	pcDetail->AddEvent("W", 1.0f);
	cInput.Update();
	AssertInt(1, cPlayer1.GetEvents()->NumElements());
	AssertString("Player 1 Up: Up", cPlayer1.GetEvents()->GetText(0));
	cPlayer1.GetEvents()->ReInit();

	pcDetail->AddEvent("W", 0.0f);
	cInput.Update();
	AssertInt(0, cPlayer1.GetEvents()->NumElements());

	AssertEvents(&cInput, pcDetail, &cPlayer1, "Player 1 Up: Up",  "W\0 1", "W\0 0", "W\0 1", NULL);
	pcDetail->AddEvent("W", 0.0f);
	cInput.Update();

	AssertEvents(&cInput, pcDetail, &cPlayer1, "Player 1 Down: Down",  "S\0 1", "S\0 0", "W\0 1", "W\0 0", "W\0 1", "W\0 0", "W\0 1", NULL);
	pcDetail->AddEvent("W", 0.0f);
	cInput.Update();

	AssertEvents(&cInput, pcDetail, &cPlayer1, "Player 1 Left: Left",  "A\0 1", "A\0 0", "D\0 1", "D\0 0", "A\0 1", "A\0 0", "A\0 1", NULL);
	pcDetail->AddEvent("A", 0.0f);
	cInput.Update();

	AssertEvents(&cInput, pcDetail, &cPlayer1, "Player 1 Right: Right",  "A\0 1", "A\0 0", "D\0 1", "D\0 0", "A\0 1", "A\0 0", "D\0 1", NULL);
	pcDetail->AddEvent("D", 0.0f);
	cInput.Update();

	AssertEvents(&cInput, pcDetail, &cPlayer1, "Player 1 Up: Up",  "S\0 1", "S\0 0", "A\0 1", "A\0 0", "W\0 1", "W\0 0", "W\0 1", NULL);
	pcDetail->AddEvent("W", 0.0f);
	cInput.Update();

	cPlayer2.Init();
	pcPlayer2 = cInput.GetDevices()->CreateVirtualDevice("Player 2");
	bResult = pcPlayer2->AddSources(pcDevice, "Cursor Up", "Cursor Left", "Cursor Down", "Cursor Right", "Right Control", NULL);
	AssertBool(true, bResult);

	pcChord = pcPlayer2->AddChordAction(cInput.GetActions()->AddActionWithListener("Player 2 Up", &CPlayerListener::Up, (CPlayerListener*)&cPlayer2));
	pcOrdered = pcChord->AsOrdered();
	pcGroup = pcOrdered->AddGroupAction();
	pcGroup->AddActiveAction(pcChord->AddEvaluatorSpecificSource(pcDevice, pcDevice->GetSource("Cursor Left"), ICT_Toggle));
	pcGroup->AddActiveAction(pcChord->AddEvaluatorSpecificSource(pcDevice, pcDevice->GetSource("Cursor Right"), ICT_Toggle));
	pcGroup = pcOrdered->AddGroupAction();
	pcGroup->AddInactiveAction(pcChord->AddEvaluatorSpecificSource(pcDevice, pcDevice->GetSource("Cursor Left"), ICT_Toggle));
	pcGroup->AddInactiveAction(pcChord->AddEvaluatorSpecificSource(pcDevice, pcDevice->GetSource("Cursor Right"), ICT_Toggle));
	pcOrdered->AddActiveAction(pcChord->AddEvaluatorSpecificSource(pcDevice, pcDevice->GetSource("Cursor Up"), ICT_Toggle));
	pcOrdered->AddInactiveAction(pcChord->AddEvaluatorSpecificSource(pcDevice, pcDevice->GetSource("Cursor Up"), ICT_Toggle));
	pcChord->Done();
	pcChord = pcPlayer2->AddChordAction(cInput.GetActions()->AddActionWithListener("Player 2 Down", &CPlayerListener::Down, (CPlayerListener*)&cPlayer2));
	pcOrdered = pcChord->AsOrdered();
	pcGroup = pcOrdered->AddGroupAction();
	pcGroup->AddActiveAction(pcChord->AddEvaluatorSpecificSource(pcDevice, pcDevice->GetSource("Cursor Left"), ICT_Toggle));
	pcGroup->AddActiveAction(pcChord->AddEvaluatorSpecificSource(pcDevice, pcDevice->GetSource("Cursor Right"), ICT_Toggle));
	pcGroup = pcOrdered->AddGroupAction();
	pcGroup->AddInactiveAction(pcChord->AddEvaluatorSpecificSource(pcDevice, pcDevice->GetSource("Cursor Left"), ICT_Toggle));
	pcGroup->AddInactiveAction(pcChord->AddEvaluatorSpecificSource(pcDevice, pcDevice->GetSource("Cursor Right"), ICT_Toggle));
	pcOrdered->AddActiveAction(pcChord->AddEvaluatorSpecificSource(pcDevice, pcDevice->GetSource("Cursor Down"), ICT_Toggle));
	pcOrdered->AddInactiveAction(pcChord->AddEvaluatorSpecificSource(pcDevice, pcDevice->GetSource("Cursor Down"), ICT_Toggle));
	pcChord->Done();
	pcPlayer2->Enable();

	AssertEvents(&cInput, pcDetail, &cPlayer2, "Player 2 Up: Up", "Cursor Left\0 1", "Cursor Right\0 1", "Cursor Left\0 0", "Cursor Right\0 0", "Cursor Up\0 1", "Cursor Up\0 0", NULL);
	AssertEvents(&cInput, pcDetail, &cPlayer2, "Player 2 Up: Up", "Cursor Left\0 1", "Cursor Right\0 1", "Cursor Right\0 0", "Cursor Left\0 0", "Cursor Up\0 1", "Cursor Up\0 0", NULL);
	AssertEvents(&cInput, pcDetail, &cPlayer2, "Player 2 Up: Up", "Cursor Right\0 1", "Cursor Left\0 1", "Cursor Left\0 0", "Cursor Right\0 0", "Cursor Up\0 1", "Cursor Up\0 0", NULL);
	AssertEvents(&cInput, pcDetail, &cPlayer2, "Player 2 Up: Up", "Cursor Right\0 1", "Cursor Left\0 1", "Cursor Right\0 0", "Cursor Left\0 0", "Cursor Up\0 1", "Cursor Up\0 0", NULL);

	AssertEvents(&cInput, pcDetail, &cPlayer2, "Player 2 Down: Down", "Cursor Left\0 1", "Cursor Right\0 1", "Cursor Left\0 0", "Cursor Right\0 0", "Cursor Down\0 1", "Cursor Down\0 0", NULL);
	AssertEvents(&cInput, pcDetail, &cPlayer2, "Player 2 Down: Down", "Cursor Left\0 1", "Cursor Right\0 1", "Cursor Right\0 0", "Cursor Left\0 0", "Cursor Down\0 1", "Cursor Down\0 0", NULL);
	AssertEvents(&cInput, pcDetail, &cPlayer2, "Player 2 Down: Down", "Cursor Right\0 1", "Cursor Left\0 1", "Cursor Left\0 0", "Cursor Right\0 0", "Cursor Down\0 1", "Cursor Down\0 0", NULL);
	AssertEvents(&cInput, pcDetail, &cPlayer2, "Player 2 Down: Down", "Cursor Right\0 1", "Cursor Left\0 1", "Cursor Right\0 0", "Cursor Left\0 0", "Cursor Down\0 1", "Cursor Down\0 0", NULL);

	cPlayer1.GetEvents()->ReInit();
	pcDetail->AddEvent("W", 1.0f);
	cInput.Update();
	AssertInt(0, cPlayer1.GetEvents()->NumElements());

	pcDetail->AddEvent("Cursor Left", 1.0f);
	cInput.Update();
	AssertInt(0, cPlayer1.GetEvents()->NumElements());

	pcDetail->AddEvent("W", 0.0f);
	cInput.Update();
	AssertInt(0, cPlayer1.GetEvents()->NumElements());

	pcDetail->AddEvent("W", 1.0f);
	cInput.Update();
	AssertInt(1, cPlayer1.GetEvents()->NumElements());
	AssertString("Player 1 Up: Up", cPlayer1.GetEvents()->GetText(0));
	cPlayer1.GetEvents()->ReInit();

	cPlayer2.Kill();
	cPlayer1.Kill();
	cInput.Kill();

	TestStatistics();

	ObjectsKill();
	UnknownsKill();
	DataIOKill();
	MemoryKill();
	OperatorsKill();
	TypeConverterKill();
	TypesKill();
	FastFunctionsKill();
}

