#include "SupportLib/Image.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/NaiveFile.h"
#include "GerberLib/GerberParser.h"
#include "GerberLib/GerberCommands.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGerberParserBasic(void)
{
	CChars				szGerberFile;
	CGerberParser		cParser;
	CGerberCommands		cCommands;

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
	cParser.Parse();
	cParser.Kill();

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
void TestGerberParser(void)
{
	TypeConverterInit();
	NumberInit();
	BeginTests();

	DataIOInit();
	ObjectsInit();
	
	//TestGerberParserBasic();
	TestGerberParserCircleMacro();
	TestGerberParserVectorLineMacro();
	TestGerberParserCenterLineMacro();
	//TestGerberParserExample1();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
	NumberKill();
	TypeConverterKill();
}

