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
		"%TD*%\n");

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
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestGerberParserBasic();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

