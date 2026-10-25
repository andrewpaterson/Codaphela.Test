#include "BaseLib/StringHelper.h"
#include "BaseLib/LogToMemory.h"
#include "BaseLib/Chars.h"
#include "KicadImporterLib/KicadSchemFile.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool IsKicadSchemPointConnected(CKicadSchemFile* pcFile, SKicadSchemPoint* psPoint, CKicadSchemSymbol* pcPinSymbol, CKicadSchemLibPin* pcPinLibPin)
{
	size					i;
	size					j;
	size					k;
	CKicadSchemSymbol*		pcSymbol;
	CKicadSchemLibSymbol*	pcLibSymbol;
	CKicadSchemLibPin*		pcPin;
	CKicadSchemSheet*		pcSheet;
	SKicadSchemPoint		sPosition;

	for (i = 0; i < pcFile->NumWires(); i++)
	{
		if (pcFile->GetWire(i)->Contains(psPoint))
		{
			return true;
		}
	}
	for (i = 0; i < pcFile->NumLabels(); i++)
	{
		if (pcFile->GetLabel(i)->GetPosition()->Equals(psPoint))
		{
			return true;
		}
	}
	for (i = 0; i < pcFile->NumNoConnects(); i++)
	{
		if (pcFile->GetNoConnect(i)->GetPosition()->Equals(psPoint))
		{
			return true;
		}
	}
	for (i = 0; i < pcFile->NumJunctions(); i++)
	{
		if (pcFile->GetJunction(i)->GetPosition()->Equals(psPoint))
		{
			return true;
		}
	}
	for (i = 0; i < pcFile->NumSheets(); i++)
	{
		pcSheet = pcFile->GetSheet(i);
		for (j = 0; j < pcSheet->NumPins(); j++)
		{
			if (pcSheet->GetPin(j)->GetPosition()->Equals(psPoint))
			{
				return true;
			}
		}
	}

	//Pins placed directly on each other.
	for (i = 0; i < pcFile->NumSymbols(); i++)
	{
		pcSymbol = pcFile->GetSymbol(i);
		pcLibSymbol = pcFile->GetLibSymbol(pcSymbol);
		for (k = 0; k < pcLibSymbol->NumPins(); k++)
		{
			pcPin = pcLibSymbol->GetPin(k);
			if (((pcSymbol == pcPinSymbol) && (pcPin == pcPinLibPin)) || !pcPin->IsOn(pcSymbol->GetUnit(), pcSymbol->GetBodyStyle()))
			{
				continue;
			}

			pcFile->GetPinPosition(&sPosition, pcSymbol, pcPin);
			if (sPosition.Equals(psPoint))
			{
				return true;
			}
		}
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertKicadSchemPinsConnected(CKicadSchemFile* pcFile)
{
	size					i;
	size					k;
	CKicadSchemSymbol*		pcSymbol;
	CKicadSchemLibSymbol*	pcLibSymbol;
	CKicadSchemLibPin*		pcPin;
	SKicadSchemPoint		sPosition;
	CChars					szUnconnected;
	size					uiNumPins;

	//Every visible pin of a placed unit must touch something: in these schematics nothing is left floating.  This checks
	//the pin positions, and so the rotation and mirroring, against where KiCad itself drew the wires.  Hidden power pins
	//connect by name instead.
	szUnconnected.Init();
	uiNumPins = 0;
	for (i = 0; i < pcFile->NumSymbols(); i++)
	{
		pcSymbol = pcFile->GetSymbol(i);
		pcLibSymbol = pcFile->GetLibSymbol(pcSymbol);
		AssertNotNull(pcLibSymbol);

		for (k = 0; k < pcLibSymbol->NumPins(); k++)
		{
			pcPin = pcLibSymbol->GetPin(k);
			if (pcPin->IsHidden() || !pcPin->IsOn(pcSymbol->GetUnit(), pcSymbol->GetBodyStyle()))
			{
				continue;
			}

			uiNumPins++;
			AssertTrue(pcFile->GetPinPosition(&sPosition, pcSymbol, pcPin));
			if (!IsKicadSchemPointConnected(pcFile, &sPosition, pcSymbol, pcPin))
			{
				szUnconnected.Append(pcSymbol->GetReference());
				szUnconnected.Append('.');
				szUnconnected.Append(pcPin->GetNumber());
				szUnconnected.Append(' ');
			}
		}
	}

	AssertTrue(uiNumPins > 0);
	AssertString("", szUnconnected.Text());
	szUnconnected.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertKicadSchemFileCounts(CKicadSchemFile* pcFile, size uiLibSymbols, size uiSymbols, size uiWires, size uiJunctions, size uiNoConnects, size uiBusEntries, size uiLabels, size uiSheets)
{
	AssertSize(uiLibSymbols, pcFile->NumLibSymbols());
	AssertSize(uiSymbols, pcFile->NumSymbols());
	AssertSize(uiWires, pcFile->NumWires());
	AssertSize(uiJunctions, pcFile->NumJunctions());
	AssertSize(uiNoConnects, pcFile->NumNoConnects());
	AssertSize(uiBusEntries, pcFile->NumBusEntries());
	AssertSize(uiLabels, pcFile->NumLabels());
	AssertSize(uiSheets, pcFile->NumSheets());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
size CountKicadSchemLabels(CKicadSchemFile* pcFile, EKicadSchemLabelType eType)
{
	size	i;
	size	uiCount;

	uiCount = 0;
	for (i = 0; i < pcFile->NumLabels(); i++)
	{
		if (pcFile->GetLabel(i)->GetType() == eType)
		{
			uiCount++;
		}
	}
	return uiCount;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
size CountKicadSchemBuses(CKicadSchemFile* pcFile)
{
	size	i;
	size	uiCount;

	uiCount = 0;
	for (i = 0; i < pcFile->NumWires(); i++)
	{
		if (pcFile->GetWire(i)->IsBus())
		{
			uiCount++;
		}
	}
	return uiCount;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemFileClockOscillator(void)
{
	CKicadSchemFile		cFile;
	CKicadSchemSymbol*	pcSymbol;
	size				i;

	cFile.Init();
	AssertTrue(cFile.Load("Input" _FS_ "Clock Oscillator.kicad_sch"));
	AssertString("Clock Oscillator.kicad_sch", cFile.GetFileName());
	AssertInt(20250114, cFile.GetVersion());
	AssertString("eeschema", cFile.GetGenerator());
	AssertString("9.0", cFile.GetGeneratorVersion());

	//Nothing but pins, labels and no-connects: every connection is a label placed on a pin.
	AssertKicadSchemFileCounts(&cFile, 3, 4, 0, 0, 3, 0, 9, 0);
	AssertSize(9, CountKicadSchemLabels(&cFile, KSLT_Local));

	for (i = 0; i < cFile.NumSymbols(); i++)
	{
		pcSymbol = cFile.GetSymbol(i);
		AssertNotNull(cFile.GetLibSymbol(pcSymbol));
		AssertNotNull(pcSymbol->GetReference());

		//The board is used by more than one project.
		AssertTrue(pcSymbol->NumInstances() >= 1);
	}
	AssertKicadSchemPinsConnected(&cFile);

	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemFileHierarchy(void)
{
	CKicadSchemFile		cFile;
	CKicadSchemFile		cSubFile;
	CKicadSchemSheet*	pcSheet;
	CKicadSchemLabel*	pcLabel;
	CChars				szPath;
	size				i;
	size				j;
	bool				bFound;

	cFile.Init();
	AssertTrue(cFile.Load("Input" _FS_ "LCD Dual 7 Segment Tester.kicad_sch"));
	AssertKicadSchemFileCounts(&cFile, 9, 12, 60, 18, 1, 0, 45, 1);
	AssertSize(37, CountKicadSchemLabels(&cFile, KSLT_Local));
	AssertSize(8, CountKicadSchemLabels(&cFile, KSLT_Global));
	AssertKicadSchemPinsConnected(&cFile);

	pcSheet = cFile.GetSheet(0);
	AssertString("LED Display.kicad_sch", pcSheet->GetSheetFile());
	AssertSize(12, pcSheet->NumPins());

	//Every sheet pin has a hierarchical label of the same name in the sheet's file.
	szPath.Init("Input" _FS_);
	szPath.Append(pcSheet->GetSheetFile());
	cSubFile.Init();
	AssertTrue(cSubFile.Load(szPath.Text()));
	szPath.Kill();

	AssertKicadSchemFileCounts(&cSubFile, 4, 10, 12, 0, 8, 0, 98, 0);
	AssertSize(12, CountKicadSchemLabels(&cSubFile, KSLT_Hierarchical));
	AssertKicadSchemPinsConnected(&cSubFile);

	for (i = 0; i < pcSheet->NumPins(); i++)
	{
		bFound = false;
		for (j = 0; j < cSubFile.NumLabels(); j++)
		{
			pcLabel = cSubFile.GetLabel(j);
			if ((pcLabel->GetType() == KSLT_Hierarchical) && (StringCompare(pcLabel->GetText(), pcSheet->GetPin(i)->GetName()) == 0))
			{
				AssertInt(pcSheet->GetPin(i)->GetShape(), pcLabel->GetShape());
				bFound = true;
			}
		}
		AssertTrue(bFound);
	}

	cSubFile.Kill();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemFileBuses(void)
{
	CKicadSchemFile	cFile;

	cFile.Init();
	AssertTrue(cFile.Load("Input" _FS_ "Clock Hold V1 to V2.kicad_sch"));
	AssertKicadSchemFileCounts(&cFile, 3, 3, 55, 3, 9, 4, 62, 0);
	AssertSize(5, CountKicadSchemBuses(&cFile));
	AssertSize(26, CountKicadSchemLabels(&cFile, KSLT_Global));
	AssertKicadSchemPinsConnected(&cFile);
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemFileKicad6(void)
{
	CKicadSchemFile		cFile;
	CKicadSchemSymbol*	pcSymbol;
	size				i;

	cFile.Init();
	AssertTrue(cFile.Load("Input" _FS_ "LSF0204.kicad_sch"));
	AssertInt(20211123, cFile.GetVersion());
	AssertString("eeschema", cFile.GetGenerator());
	AssertKicadSchemFileCounts(&cFile, 3, 12, 49, 17, 2, 0, 11, 0);
	AssertSize(8, CountKicadSchemLabels(&cFile, KSLT_Hierarchical));

	//The references come from the root (symbol_instances).
	for (i = 0; i < cFile.NumSymbols(); i++)
	{
		pcSymbol = cFile.GetSymbol(i);
		AssertSize(1, pcSymbol->NumInstances());
	}
	AssertKicadSchemPinsConnected(&cFile);
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemFileKicad10(void)
{
	CKicadSchemFile	cFile;

	cFile.Init();
	AssertTrue(cFile.Load("Input" _FS_ "Power and Reset.kicad_sch"));
	AssertInt(20260306, cFile.GetVersion());
	AssertString("10.0", cFile.GetGeneratorVersion());
	AssertString("Power and Reset", cFile.GetTitle());
	AssertKicadSchemFileCounts(&cFile, 14, 25, 50, 14, 27, 0, 40, 0);
	AssertKicadSchemPinsConnected(&cFile);
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemFileMissing(void)
{
	CKicadSchemFile	cFile;
	CLogToMemory	cMemoryLog;
	char			szLogText[400];
	bool			bResult;

	cMemoryLog.Start(true);
	cFile.Init();
	bResult = cFile.Load("Input" _FS_ "Missing.kicad_sch");
	cFile.Kill();
	cMemoryLog.Stop(szLogText, 400);

	AssertFalse(bResult);
	AssertTrue(strstr(szLogText, "Could not read KiCad schematic file") != NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemFile(void)
{
	BeginTests();

	TestKicadSchemFileClockOscillator();
	TestKicadSchemFileHierarchy();
	TestKicadSchemFileBuses();
	TestKicadSchemFileKicad6();
	TestKicadSchemFileKicad10();
	TestKicadSchemFileMissing();

	TestStatistics();
}

