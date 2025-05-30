#include "SupportLib/Image.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/LogToMemory.h"
#include "GerberLib/GerberParser.h"
#include "GerberLib/GerberCommands.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCommandEndOfFile(void)
{
	CChars					szGerberFile;
	CGerberParser			cParser;
	CGerberCommands			cCommands;
	TRISTATE				tResult;
	size					uiNumCommands;
	CGerberCommand*			pcCommand;

	szGerberFile.Init("M02*\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(1, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsEndOfFile());

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCommandComment(void)
{
	CChars					szGerberFile;
	CGerberParser			cParser;
	CGerberCommands			cCommands;
	TRISTATE				tResult;
	size					uiNumCommands;
	CGerberCommand*			pcCommand;
	CGerberCommandComment*	pcComment;

	szGerberFile.Init(
		"G04 Ucamco ex. 1: Twon\n"
		"square boxes *\n"
		"G04 Ucamco ex. 2: Shapes*\n"
		"M02*\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(3, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsComment());
	AssertTrue(pcCommand->IsType(GC_G04));

	pcComment = (CGerberCommandComment*)pcCommand;
	AssertString("Ucamco ex. 1: Twon\nsquare boxes ", pcComment->Text());

	pcCommand = cCommands.GetCommand(1);
	AssertTrue(pcCommand->IsComment());

	pcComment = (CGerberCommandComment*)pcCommand;
	AssertString("Ucamco ex. 2: Shapes", pcComment->Text());

	pcCommand = cCommands.GetCommand(2);
	AssertTrue(pcCommand->IsEndOfFile());

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCommandFormatSpecifier(void)
{
	CChars							szGerberFile;
	CGerberParser					cParser;
	CGerberCommands					cCommands;
	TRISTATE						tResult;
	size							uiNumCommands;
	CGerberCommand*					pcCommand;
	CGerberCommandFormatSpecifier*	pcFormatSpecifier;
	uint16							ui;

	szGerberFile.Init(
		"%FSLAX26Y35*%\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(1, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsFormatSpecifier());
	AssertTrue(pcCommand->IsType(GC_FS));

	pcFormatSpecifier = (CGerberCommandFormatSpecifier*)pcCommand;

	ui = pcFormatSpecifier->GetXWholeNumbers();
	AssertShort((uint16)2, ui);

	ui = pcFormatSpecifier->GetXDecimals();
	AssertShort((uint16)5, ui);

	ui = pcFormatSpecifier->GetYWholeNumbers();
	AssertShort((uint16)3, ui);

	ui = pcFormatSpecifier->GetYDecimals();
	AssertShort((uint16)5, ui);

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCommandMeasurementMode(void)
{
	CChars							szGerberFile;
	CGerberParser					cParser;
	CGerberCommands					cCommands;
	TRISTATE						tResult;
	size							uiNumCommands;
	CGerberCommand*					pcCommand;
	CGerberCommandMeasurementMode*	pcMeasurementMode;
	CLogToMemory					cMemoryLog;
	char							szLogText[200];
	char*							szSyntaxError;

	szGerberFile.Init("%MOMM*%");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(1, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsMeasurementMode());
	AssertTrue(pcCommand->IsType(GC_MO));

	pcMeasurementMode = (CGerberCommandMeasurementMode*)pcCommand;

	AssertTrue(pcMeasurementMode->IsMillimeters());
	AssertFalse(pcMeasurementMode->IsInches());

	cCommands.Kill();


	szGerberFile.Init("%MOIN*%");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(1, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsMeasurementMode());

	pcMeasurementMode = (CGerberCommandMeasurementMode*)pcCommand;

	AssertTrue(pcMeasurementMode->IsInches());
	AssertFalse(pcMeasurementMode->IsMillimeters());

	cCommands.Kill();


	cMemoryLog.Start(true);
	szGerberFile.Init("%MOPT*%");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTrierror(tResult);
	
	cMemoryLog.Stop(szLogText, 200);
	szSyntaxError = strstr(szLogText, "Syntax Error");
	AssertString(
"Syntax Error, could not parse Command:\n"
"%MOPT*\n"
"   ^\n", szSyntaxError);

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCommandPlotMode(void)
{
	CChars							szGerberFile;
	CGerberParser					cParser;
	CGerberCommands					cCommands;
	TRISTATE						tResult;
	size							uiNumCommands;
	CGerberCommand*					pcCommand;
	CGerberCommandPlotMode*			pcPlotMode;

	szGerberFile.Init("G01*G02*G03*");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(3, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsPlotMode());
	AssertTrue(pcCommand->IsType(GC_G01));
	pcPlotMode = (CGerberCommandPlotMode*)pcCommand;
	AssertTrue(pcPlotMode->IsLinear());
	AssertFalse(pcPlotMode->IsCircular());

	pcCommand = cCommands.GetCommand(1);
	AssertTrue(pcCommand->IsPlotMode());
	AssertTrue(pcCommand->IsType(GC_G02));
	pcPlotMode = (CGerberCommandPlotMode*)pcCommand;
	AssertTrue(pcPlotMode->IsCircular());
	AssertFalse(pcPlotMode->IsLinear());
	AssertTrue(pcPlotMode->IsClockwise());
	AssertFalse(pcPlotMode->IsAnticlockwise());

	pcCommand = cCommands.GetCommand(2);
	AssertTrue(pcCommand->IsPlotMode());
	AssertTrue(pcCommand->IsType(GC_G03));
	pcPlotMode = (CGerberCommandPlotMode*)pcCommand;
	AssertTrue(pcPlotMode->IsCircular());
	AssertFalse(pcPlotMode->IsLinear());
	AssertFalse(pcPlotMode->IsClockwise());
	AssertTrue(pcPlotMode->IsAnticlockwise());

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCommandLoadPolarity(void)
{
	CChars							szGerberFile;
	CGerberParser					cParser;
	CGerberCommands					cCommands;
	TRISTATE						tResult;
	size							uiNumCommands;
	CGerberCommand*					pcCommand;
	CGerberCommandLoadPolarity*		pcPolarity;

	szGerberFile.Init(
		"%LPC*%\n"
		"%LPD*%\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(2, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsLoadPolarity());
	AssertTrue(pcCommand->IsType(GC_LP));
	pcPolarity = (CGerberCommandLoadPolarity*)pcCommand;
	AssertTrue(pcPolarity->IsClear());
	AssertFalse(pcPolarity->IsDark());

	pcCommand = cCommands.GetCommand(1);
	AssertTrue(pcCommand->IsLoadPolarity());
	pcPolarity = (CGerberCommandLoadPolarity*)pcCommand;
	AssertTrue(pcPolarity->IsDark());
	AssertFalse(pcPolarity->IsClear());

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCommandLoadMirroring(void)
{
	CChars							szGerberFile;
	CGerberParser					cParser;
	CGerberCommands					cCommands;
	TRISTATE						tResult;
	size							uiNumCommands;
	CGerberCommand*					pcCommand;
	CGerberCommandLoadMirroring*	pcMirroring;

	szGerberFile.Init(
		"%LMN*%\n"
		"%LMX*%\n"
		"%LMY*%\n"
		"%LMXY*%\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(4, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsLoadMirroring());
	AssertTrue(pcCommand->IsType(GC_LM));
	pcMirroring = (CGerberCommandLoadMirroring*)pcCommand;
	AssertTrue(pcMirroring->IsNone());

	pcCommand = cCommands.GetCommand(1);
	AssertTrue(pcCommand->IsLoadMirroring());
	pcMirroring = (CGerberCommandLoadMirroring*)pcCommand;
	AssertTrue(pcMirroring->IsX());

	pcCommand = cCommands.GetCommand(2);
	AssertTrue(pcCommand->IsLoadMirroring());
	pcMirroring = (CGerberCommandLoadMirroring*)pcCommand;
	AssertTrue(pcMirroring->IsY());

	pcCommand = cCommands.GetCommand(3);
	AssertTrue(pcCommand->IsLoadMirroring());
	pcMirroring = (CGerberCommandLoadMirroring*)pcCommand;
	AssertTrue(pcMirroring->IsXY());

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCommandLoadRotation(void)
{
	CChars							szGerberFile;
	CGerberParser					cParser;
	CGerberCommands					cCommands;
	TRISTATE						tResult;
	size							uiNumCommands;
	CGerberCommand*					pcCommand;
	CGerberCommandLoadRotation*		pcRotation;

	szGerberFile.Init(
		"%LR90*%\n"
		"%LR0.008192*%\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(2, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsLoadRotation());
	AssertTrue(pcCommand->IsType(GC_LR));
	pcRotation = (CGerberCommandLoadRotation*)pcCommand;
	AssertNumber("90", pcRotation->GetRotation());

	pcCommand = cCommands.GetCommand(1);
	AssertTrue(pcCommand->IsLoadRotation());
	pcRotation = (CGerberCommandLoadRotation*)pcCommand;
	AssertNumber("0.008192", pcRotation->GetRotation());

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCommandLoadScaling(void)
{
	CChars							szGerberFile;
	CGerberParser					cParser;
	CGerberCommands					cCommands;
	TRISTATE						tResult;
	size							uiNumCommands;
	CGerberCommand*					pcCommand;
	CGerberCommandLoadScaling*		pcScaling;

	szGerberFile.Init(
		"%LS90*%\n"
		"%LS0.008192*%\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(2, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsLoadScaling());
	AssertTrue(pcCommand->IsType(GC_LS));
	pcScaling = (CGerberCommandLoadScaling*)pcCommand;
	AssertNumber("90", pcScaling->GetScaling());

	pcCommand = cCommands.GetCommand(1);
	AssertTrue(pcCommand->IsLoadScaling());
	pcScaling = (CGerberCommandLoadScaling*)pcCommand;
	AssertNumber("0.008192", pcScaling->GetScaling());

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCommandFileAttribute(void)
{
	CChars							szGerberFile;
	CGerberParser					cParser;
	CGerberCommands					cCommands;
	TRISTATE						tResult;
	size							uiNumCommands;
	CGerberCommand*					pcCommand;
	CGerberCommandFileAttribute*	pcAttribute;
	char*							szAttribute;
	char*							szValue;
	size							uiNumValues;

	szGerberFile.Init(
		"%TF.CreationDate,2016-04-25T00:00;00+01:00*%\n"
		"%TF.FileFunction,Soldermask,Top*%\n"
		"%TF.FileFunction,Copper,L1,Top*%");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(3, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsFileAttribute());
	AssertTrue(pcCommand->IsType(GC_TF));
	pcAttribute = (CGerberCommandFileAttribute*)pcCommand;

	szAttribute = pcAttribute->NameText();
	AssertString(".CreationDate", szAttribute);
	uiNumValues = pcAttribute->NumValues();
	AssertSize(1, uiNumValues);
	szValue = pcAttribute->ValueText(0);
	AssertString("2016-04-25T00:00;00+01:00", szValue);

	pcCommand = cCommands.GetCommand(1);
	AssertTrue(pcCommand->IsFileAttribute());
	pcAttribute = (CGerberCommandFileAttribute*)pcCommand;

	szAttribute = pcAttribute->NameText();
	AssertString(".FileFunction", szAttribute);
	uiNumValues = pcAttribute->NumValues();
	AssertSize(2, uiNumValues);
	szValue = pcAttribute->ValueText(0);
	AssertString("Soldermask", szValue);
	szValue = pcAttribute->ValueText(1);
	AssertString("Top", szValue);

	pcCommand = cCommands.GetCommand(2);
	AssertTrue(pcCommand->IsFileAttribute());
	pcAttribute = (CGerberCommandFileAttribute*)pcCommand;

	szAttribute = pcAttribute->NameText();
	AssertString(".FileFunction", szAttribute);
	uiNumValues = pcAttribute->NumValues();
	AssertSize(3, uiNumValues);
	szValue = pcAttribute->ValueText(0);
	AssertString("Copper", szValue);
	szValue = pcAttribute->ValueText(1);
	AssertString("L1", szValue);
	szValue = pcAttribute->ValueText(2);
	AssertString("Top", szValue);

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCommandApertureAttribute(void)
{
	CChars								szGerberFile;
	CGerberParser						cParser;
	CGerberCommands						cCommands;
	TRISTATE							tResult;
	size								uiNumCommands;
	CGerberCommand*						pcCommand;
	CGerberCommandApertureAttribute*	pcAttribute;
	char*								szAttribute;
	char*								szValue;
	size								uiNumValues;

	szGerberFile.Init("%TA.AperFunction,Conductor*%");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(1, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsApertureAttribute());
	AssertTrue(pcCommand->IsType(GC_TA));
	pcAttribute = (CGerberCommandApertureAttribute*)pcCommand;

	szAttribute = pcAttribute->NameText();
	AssertString(".AperFunction", szAttribute);
	uiNumValues = pcAttribute->NumValues();
	AssertSize(1, uiNumValues);
	szValue = pcAttribute->ValueText(0);
	AssertString("Conductor", szValue);

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCommandObjectAttribute(void)
{
	CChars								szGerberFile;
	CGerberParser						cParser;
	CGerberCommands						cCommands;
	TRISTATE							tResult;
	size								uiNumCommands;
	CGerberCommand*						pcCommand;
	CGerberCommandObjectAttribute*		pcAttribute;
	char*								szAttribute;
	char*								szValue;
	size								uiNumValues;

	szGerberFile.Init("%TO.C,R6*%");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(1, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsObjectAttribute());
	AssertTrue(pcCommand->IsType(GC_TO));
	pcAttribute = (CGerberCommandObjectAttribute*)pcCommand;

	szAttribute = pcAttribute->NameText();
	AssertString(".C", szAttribute);
	uiNumValues = pcAttribute->NumValues();
	AssertSize(1, uiNumValues);
	szValue = pcAttribute->ValueText(0);
	AssertString("R6", szValue);

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCommandDeleteAttribute(void)
{
	CChars								szGerberFile;
	CGerberParser						cParser;
	CGerberCommands						cCommands;
	TRISTATE							tResult;
	size								uiNumCommands;
	CGerberCommand*						pcCommand;
	CGerberCommandObjectAttribute*		pcAttribute;
	char*								szAttribute;
	char*								szValue;
	size								uiNumValues;

	szGerberFile.Init("%TO.C,R6*%");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(1, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsObjectAttribute());
	AssertTrue(pcCommand->IsType(GC_TO));
	pcAttribute = (CGerberCommandObjectAttribute*)pcCommand;

	szAttribute = pcAttribute->NameText();
	AssertString(".C", szAttribute);
	uiNumValues = pcAttribute->NumValues();
	AssertSize(1, uiNumValues);
	szValue = pcAttribute->ValueText(0);
	AssertString("R6", szValue);

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCircleMacro(void)
{
	CChars							szGerberFile;
	CGerberParser					cParser;
	CGerberCommands					cCommands;
	TRISTATE						tResult;
	size							uiNumCommands;
	CGerberCommand*					pcCommand;
	CGerberCommandApertureMacro*	pcApetureMacro;
	size							uiNumPrimitives;
	CGerberApertureMacro*			pcPrimitive;
	CGerberApertureMacroCircle*		pcCircle;
	CNumber*						pcNumber;

	szGerberFile.Init(
		"%AMCircle*\n"
		"1,1,1.5,4.36,2,90.8234795*%\n"
		"M02*\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(2, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsApertureMacro());

	pcApetureMacro = (CGerberCommandApertureMacro*)pcCommand;
	uiNumPrimitives = pcApetureMacro->NumPrimitives();
	AssertInt(1, uiNumPrimitives);

	pcPrimitive = pcApetureMacro->GetPrimitive(0);
	AssertTrue(pcPrimitive->IsCircle());

	pcCircle = (CGerberApertureMacroCircle*)pcPrimitive;
	pcNumber = pcCircle->GetCenterX()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(4.36f, pcNumber->FloatValue(), 2);

	pcNumber = pcCircle->GetCenterY()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(2.0f, pcNumber->FloatValue(), 2);

	pcNumber = pcCircle->GetDiameter()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(1.5f, pcNumber->FloatValue(), 2);

	pcNumber = pcCircle->GetRotation()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(90.82348f, pcNumber->FloatValue(), 5);

	pcNumber = pcCircle->GetExposure()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(1.f, pcNumber->FloatValue(), 5);

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserVectorLineMacro(void)
{
	CChars								szGerberFile;
	CGerberParser						cParser;
	CGerberCommands						cCommands;
	TRISTATE							tResult;
	size								uiNumCommands;
	CGerberCommand*						pcCommand;
	CGerberCommandApertureMacro*		pcApetureMacro;
	size								uiNumPrimitives;
	CGerberApertureMacro*				pcPrimitive;
	CGerberApertureMacroVectorLine*		pcLine;
	Float64								pcValue;

	szGerberFile.Init(
		"%AMLine*\n"
		"20, 0, 2.3, 3, 4, 5, 6, 0*%\n"
		"M02*\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(2, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsApertureMacro());

	pcApetureMacro = (CGerberCommandApertureMacro*)pcCommand;
	uiNumPrimitives = pcApetureMacro->NumPrimitives();
	AssertInt(1, uiNumPrimitives);

	pcPrimitive = pcApetureMacro->GetPrimitive(0);
	AssertTrue(pcPrimitive->IsVectorLine());
	pcLine = (CGerberApertureMacroVectorLine*)pcPrimitive;

	pcValue = pcLine->GetExposure()->DoubleValue();
	AssertDouble(0.0, pcValue, 2);

	pcValue = pcLine->GetWidth()->DoubleValue();
	AssertDouble(2.3, pcValue, 2);

	pcValue = pcLine->GetStartX()->DoubleValue();
	AssertDouble(3.0, pcValue, 2);

	pcValue = pcLine->GetStartY()->DoubleValue();
	AssertDouble(4.0, pcValue, 2);

	pcValue = pcLine->GetEndX()->DoubleValue();
	AssertDouble(5.0, pcValue, 2);

	pcValue = pcLine->GetEndY()->DoubleValue();
	AssertDouble(6.0, pcValue, 2);

	pcValue = pcLine->GetRotation()->DoubleValue();
	AssertDouble(0.0, pcValue, 2);

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCenterLineMacro(void)
{
	CChars								szGerberFile;
	CGerberParser						cParser;
	CGerberCommands						cCommands;
	TRISTATE							tResult;
	size								uiNumCommands;
	CGerberCommand*						pcCommand;
	CGerberCommandApertureMacro*		pcApetureMacro;
	size								uiNumPrimitives;
	CGerberApertureMacro*				pcPrimitive;
	CGerberApertureMacroCenterLine*		pcLine;
	Float64								pcValue;

	szGerberFile.Init(
		"%AMLine*\n"
		"21, 1, 2.3, 3.5, 3, 4, 87*%\n"
		"M02*\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(2, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsApertureMacro());
	AssertTrue(pcCommand->IsType(GC_AM));

	pcApetureMacro = (CGerberCommandApertureMacro*)pcCommand;
	uiNumPrimitives = pcApetureMacro->NumPrimitives();
	AssertInt(1, uiNumPrimitives);

	pcPrimitive = pcApetureMacro->GetPrimitive(0);
	AssertTrue(pcPrimitive->IsCenterLine());
	pcLine = (CGerberApertureMacroCenterLine*)pcPrimitive;

	pcValue = pcLine->GetExposure()->DoubleValue();
	AssertDouble(1.0, pcValue, 2);

	pcValue = pcLine->GetWidth()->DoubleValue();
	AssertDouble(2.3, pcValue, 2);

	pcValue = pcLine->GetHeight()->DoubleValue();
	AssertDouble(3.5, pcValue, 2);

	pcValue = pcLine->GetCenterX()->DoubleValue();
	AssertDouble(3.0, pcValue, 2);

	pcValue = pcLine->GetCenterY()->DoubleValue();
	AssertDouble(4.0, pcValue, 2);

	pcValue = pcLine->GetRotation()->DoubleValue();
	AssertDouble(87.0, pcValue, 2);

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserOutlineMacro(void)
{
	CChars								szGerberFile;
	CGerberParser						cParser;
	CGerberCommands						cCommands;
	TRISTATE							tResult;
	size								uiNumCommands;
	CGerberCommand*						pcCommand;
	CGerberCommandApertureMacro*		pcApetureMacro;
	size								uiNumPrimitives;
	CGerberApertureMacro*				pcPrimitive;
	CGerberApertureMacroOutline*		pcShape;
	Float64								pcValue;
	size								uiNumPositions;
	CGerberExpressionPosition*			pcPosition;

	szGerberFile.Init(
		"%AMLine*\n"
		"4, 1, 7, 0,1, 2,3, 4,5, 6,7, 8,9, 10,11, 12,13, 45.235456*%\n"
		"M02*\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(2, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsApertureMacro());

	pcApetureMacro = (CGerberCommandApertureMacro*)pcCommand;
	uiNumPrimitives = pcApetureMacro->NumPrimitives();
	AssertInt(1, uiNumPrimitives);

	pcPrimitive = pcApetureMacro->GetPrimitive(0);
	AssertTrue(pcPrimitive->IsOutline());
	pcShape = (CGerberApertureMacroOutline*)pcPrimitive;

	pcValue = pcShape->GetExposure()->DoubleValue();
	AssertDouble(1.0, pcValue, 2);

	uiNumPositions = pcShape->NumPositions();
	AssertSize(7, uiNumPositions);

	pcPosition = pcShape->GetPosition(0);
	pcValue = pcPosition->GetX()->DoubleValue();
	AssertDouble(0.0, pcValue, 2);
	pcValue = pcPosition->GetY()->DoubleValue();
	AssertDouble(1.0, pcValue, 2);

	pcPosition = pcShape->GetPosition(1);
	pcValue = pcPosition->GetX()->DoubleValue();
	AssertDouble(2.0, pcValue, 2);
	pcValue = pcPosition->GetY()->DoubleValue();
	AssertDouble(3.0, pcValue, 2);

	pcPosition = pcShape->GetPosition(2);
	pcValue = pcPosition->GetX()->DoubleValue();
	AssertDouble(4.0, pcValue, 2);
	pcValue = pcPosition->GetY()->DoubleValue();
	AssertDouble(5.0, pcValue, 2);

	pcPosition = pcShape->GetPosition(3);
	pcValue = pcPosition->GetX()->DoubleValue();
	AssertDouble(6.0, pcValue, 2);
	pcValue = pcPosition->GetY()->DoubleValue();
	AssertDouble(7.0, pcValue, 2);

	pcPosition = pcShape->GetPosition(4);
	pcValue = pcPosition->GetX()->DoubleValue();
	AssertDouble(8.0, pcValue, 2);
	pcValue = pcPosition->GetY()->DoubleValue();
	AssertDouble(9.0, pcValue, 2);

	pcPosition = pcShape->GetPosition(5);
	pcValue = pcPosition->GetX()->DoubleValue();
	AssertDouble(10.0, pcValue, 2);
	pcValue = pcPosition->GetY()->DoubleValue();
	AssertDouble(11.0, pcValue, 2);

	pcPosition = pcShape->GetPosition(6);
	pcValue = pcPosition->GetX()->DoubleValue();
	AssertDouble(12.0, pcValue, 2);
	pcValue = pcPosition->GetY()->DoubleValue();
	AssertDouble(13.0, pcValue, 2);

	pcValue = pcShape->GetRotation()->DoubleValue();
	AssertDouble(45.235456, pcValue, 6);

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserCommentMacro(void)
{
	CChars								szGerberFile;
	CGerberParser						cParser;
	CGerberCommands						cCommands;
	TRISTATE							tResult;
	size								uiNumCommands;
	CGerberCommand*						pcCommand;
	CGerberCommandApertureMacro*		pcApetureMacro;
	size								uiNumPrimitives;
	CGerberApertureMacro*				pcPrimitive;
	CGerberApertureMacroComment*		pcComment;

	szGerberFile.Init(
		"%AMComment*\n"
		"0 Rectangle with rounded corners, with rotation*\n"
		"0 The origin of the aperture is its center*\n"
		"0 $1 X-size*\n"
		"0 $2 Y-size*\n"
		"0 $3 Rounding radius*\n"
		"0 $4 Rotation angle, in degrees counterclockwise*%\n"
		"M02*\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(2, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsApertureMacro());

	pcApetureMacro = (CGerberCommandApertureMacro*)pcCommand;
	uiNumPrimitives = pcApetureMacro->NumPrimitives();
	AssertInt(6, uiNumPrimitives);

	pcPrimitive = pcApetureMacro->GetPrimitive(0);
	AssertTrue(pcPrimitive->IsComment());
	pcComment = (CGerberApertureMacroComment*)pcPrimitive;
	AssertString("Rectangle with rounded corners, with rotation", pcComment->Text());

	pcPrimitive = pcApetureMacro->GetPrimitive(1);
	AssertTrue(pcPrimitive->IsComment());
	pcComment = (CGerberApertureMacroComment*)pcPrimitive;
	AssertString("The origin of the aperture is its center", pcComment->Text());

	pcPrimitive = pcApetureMacro->GetPrimitive(2);
	AssertTrue(pcPrimitive->IsComment());
	pcComment = (CGerberApertureMacroComment*)pcPrimitive;
	AssertString("$1 X-size", pcComment->Text());

	pcPrimitive = pcApetureMacro->GetPrimitive(3);
	AssertTrue(pcPrimitive->IsComment());
	pcComment = (CGerberApertureMacroComment*)pcPrimitive;
	AssertString("$2 Y-size", pcComment->Text());

	pcPrimitive = pcApetureMacro->GetPrimitive(4);
	AssertTrue(pcPrimitive->IsComment());
	pcComment = (CGerberApertureMacroComment*)pcPrimitive;
	AssertString("$3 Rounding radius", pcComment->Text());

	pcPrimitive = pcApetureMacro->GetPrimitive(5);
	AssertTrue(pcPrimitive->IsComment());
	pcComment = (CGerberApertureMacroComment*)pcPrimitive;
	AssertString("$4 Rotation angle, in degrees counterclockwise", pcComment->Text());

	pcCommand = cCommands.GetCommand(1);
	AssertTrue(pcCommand->IsEndOfFile());

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserPolygonMacro(void)
{
	CChars							szGerberFile;
	CGerberParser					cParser;
	CGerberCommands					cCommands;
	TRISTATE						tResult;
	size							uiNumCommands;
	CGerberCommand*					pcCommand;
	CGerberCommandApertureMacro*	pcApetureMacro;
	size							uiNumPrimitives;
	CGerberApertureMacro*			pcPrimitive;
	CGerberApertureMacroPolygon*	pcPolygon;
	CNumber*						pcNumber;

	szGerberFile.Init(
		"%AM Polygon*\n"
		"5,1,8,0,0,7,0*%\n"
		"M02*\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(2, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsApertureMacro());

	pcApetureMacro = (CGerberCommandApertureMacro*)pcCommand;
	uiNumPrimitives = pcApetureMacro->NumPrimitives();
	AssertInt(1, uiNumPrimitives);

	pcPrimitive = pcApetureMacro->GetPrimitive(0);
	AssertTrue(pcPrimitive->IsPolygon());

	pcPolygon = (CGerberApertureMacroPolygon*)pcPrimitive;
	pcNumber = pcPolygon->GetCenterX()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(0.f, pcNumber->FloatValue(), 2);

	pcNumber = pcPolygon->GetCenterY()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(0.f, pcNumber->FloatValue(), 2);

	pcNumber = pcPolygon->GetDiameter()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(7.f, pcNumber->FloatValue(), 2);

	pcNumber = pcPolygon->GetNumberOfVertices()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertInt(8, pcNumber->IntValue());

	pcNumber = pcPolygon->GetRotation()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(0.f, pcNumber->FloatValue(), 5);

	pcNumber = pcPolygon->GetExposure()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(1.f, pcNumber->FloatValue(), 5);

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserThermalMacro(void)
{
	CChars							szGerberFile;
	CGerberParser					cParser;
	CGerberCommands					cCommands;
	TRISTATE						tResult;
	size							uiNumCommands;
	CGerberCommand*					pcCommand;
	CGerberCommandApertureMacro*	pcApetureMacro;
	size							uiNumPrimitives;
	CGerberApertureMacro*			pcPrimitive;
	CGerberApertureMacroThermal*	pcThermal;
	CNumber*						pcNumber;

	szGerberFile.Init(
		"%AM Thermal*\n"
		"7,1,2,0.95,0.75,0.175,3.0*%\n"
		"M02*\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	cParser.Kill();

	AssertTritrue(tResult);
	uiNumCommands = cCommands.NumCommands();
	AssertInt(2, uiNumCommands);

	pcCommand = cCommands.GetCommand(0);
	AssertTrue(pcCommand->IsApertureMacro());

	pcApetureMacro = (CGerberCommandApertureMacro*)pcCommand;
	uiNumPrimitives = pcApetureMacro->NumPrimitives();
	AssertInt(1, uiNumPrimitives);

	pcPrimitive = pcApetureMacro->GetPrimitive(0);
	AssertTrue(pcPrimitive->IsThermal());

	pcThermal = (CGerberApertureMacroThermal*)pcPrimitive;
	pcNumber = pcThermal->GetCenterX()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(1.f, pcNumber->FloatValue(), 2);

	pcNumber = pcThermal->GetCenterY()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(2.f, pcNumber->FloatValue(), 2);

	pcNumber = pcThermal->GetInnerDiameter()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(0.75f, pcNumber->FloatValue(), 2);

	pcNumber = pcThermal->GetOuterDiameter()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(0.95f, pcNumber->FloatValue(), 2);

	pcNumber = pcThermal->GetRotation()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(3.f, pcNumber->FloatValue(), 5);

	pcNumber = pcThermal->GetGapThickness()->GetConstNumber();
	AssertNotNull(pcNumber);
	AssertFloat(0.175f, pcNumber->FloatValue(), 5);

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserExample1(void)
{
	CChars				szGerberFile;
	CGerberParser		cParser;
	CGerberCommands		cCommands;

	szGerberFile.Init(
		"%FSLAX26Y26*%\n"
		"%MOMM*%\n"
		"%ADD100C,1.5*%\n"
		"D100*\n"
		"X0Y0D03*\n"
		"M02*\n");
	
	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	cParser.Parse();
	cParser.Kill();

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserPartialKiCadReal(void)
{
	CChars				szGerberFile;
	CGerberParser		cParser;
	CGerberCommands		cCommands;
	TRISTATE			tResult;

	szGerberFile.Init(
		"G04 Gerber Test File*\n"
		"%TF.GenerationSoftware,KiCad,Pcbnew,8.0.7*%\n"
		"%TF.CreationDate,2025-02-09T12:46:03+02:00*%\n"
		"%TF.ProjectId,EPM570 Programmer,45504d35-3730-4205-9072-6f6772616d6d,V0*%\n"
		"%TF.SameCoordinates,Original*%\n"
		"%TF.FileFunction,Copper,L1,Top*%\n"
		"%TF.FilePolarity,Positive*%\n"
		"%FSLAX46Y46*%\n"
		"G04 Gerber Fmt 4.6, Leading zero omitted, Abs format (unit mm)*\n"
		"G04 Created by KiCad (PCBNEW 8.0.7) date 2025-02-09 12:46:03*\n"
		"%MOMM*%\n"
		"%LPD*%\n"
		"G01*\n"
		"G04 APERTURE LIST*\n"
		"G04 Aperture macros list*\n"
		"%AMRoundRect*\n"
		"0 Rectangle with rounded corners*\n"
		"0 $1 Rounding radius*\n"
		"0 $2 $3 $4 $5 $6 $7 $8 $9 X,Y pos of 4 corners*\n"
		"0 Add a 4 corners polygon primitive as box body*\n"
		"4,1,4,$2,$3,$4,$5,$6,$7,$8,$9,$2,$3,0*\n"
		"0 Add four circle primitives for the rounded corners*\n"
		"1,1,$1+$1,$2,$3*\n"
		"1,1,$1+$1,$4,$5*\n"
		"1,1,$1+$1,$6,$7*\n"
		"1,1,$1+$1,$8,$9*\n"
		"0 Add four rect primitives between the rounded corners*\n"
		"20,1,$1+$1,$2,$3,$4,$5,0*\n"
		"20,1,$1+$1,$4,$5,$6,$7,0*\n"
		"20,1,$1+$1,$6,$7,$8,$9,0*\n"
		"20,1,$1+$1,$8,$9,$2,$3,0*%\n"
		"G04 Aperture macros list end*\n"
		"%TA.AperFunction,EtchedComponent*%\n"
		"%ADD10C,0.000000*%\n"
		"%TD*%\n"
		"%TA.AperFunction,SMDPad,CuDef*%\n"
		"%ADD11R,1.150000X0.600000*%\n"
		"%TD*%\n"
		"%TA.AperFunction,SMDPad,CuDef*%\n"
		"%ADD12RoundRect,0.250000X-0.475000X0.250000X-0.475000X-0.250000X0.475000X-0.250000X0.475000X0.250000X0*%\n"
		"%TD*%\n"
		"M02*\n");

	cCommands.Init();
	cParser.Init(szGerberFile.Text(), szGerberFile.Length(), "none.txt", &cCommands);
	tResult = cParser.Parse();
	AssertTritrue(tResult);

	cParser.Kill();

	cCommands.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParser(void)
{
	TypeConverterInit();
	NumberInit();
	BeginTests();

	DataIOInit();
	ObjectsInit();
	
	TestGerberParserCommandEndOfFile();			//M02
	TestGerberParserCommandComment();			//G04
	TestGerberParserCommandFormatSpecifier();	//FS
	TestGerberParserCommandMeasurementMode();	//MO
	TestGerberParserCommandPlotMode();			//G01, G02, G03
	TestGerberParserCommandLoadPolarity();		//LP
	TestGerberParserCommandLoadMirroring();		//LM
	TestGerberParserCommandLoadRotation();		//LR
	TestGerberParserCommandLoadScaling();		//LS
	TestGerberParserCommandFileAttribute();		//TF
	TestGerberParserCommandApertureAttribute(); //TA
	TestGerberParserCommandObjectAttribute();	//TO
	TestGerberParserCommandDeleteAttribute();	//TD
	TestGerberParserCircleMacro();
	TestGerberParserVectorLineMacro();
	TestGerberParserCenterLineMacro();
	TestGerberParserOutlineMacro();
	TestGerberParserCommentMacro();
	TestGerberParserPolygonMacro();
	TestGerberParserThermalMacro();
	TestGerberParserExample1();
	//TestGerberParserPartialKiCadReal();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
	NumberKill();
	TypeConverterKill();
}

