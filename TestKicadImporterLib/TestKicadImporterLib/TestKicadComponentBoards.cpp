#include <time.h>
#include <stdio.h>
#include "BaseLib/FileUtil.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/DataMemory.h"
#include "StandardLib/Objects.h"
#include "LogicimLib/CircuitFile.h"
#include "LogicimLib/CircuitFonts.h"
#include "KicadImporterLib/KicadSchemLogicimConverter.h"
#include "TestLib/Assert.h"


//A temporary sweep of the HCP65 component boards: each converted, saved to Output/Boards and reported in
//Output/ComponentBoards.txt.
#define KICAD_COMPONENT_BOARDS	"D:\\Work\\658-Computer\\Kicad\\Computer\\Component Boards"


static const char* gaszKicadComponentBoards[] =
{
	"Added 8bit", "Adder 16bit", "Address Buffer 16bit", "Address Buffer 24bit", "Audio DAC", "Big Board", "Clock Doubler",
	"Clock Hold Select", "Clock Hold Standard", "Clock Transition", "Comparator 10bit", "Comparator 16bit", "Counter 16bit",
	"Counter 16bit with IO", "Counter 24bit", "Counter 24bit with IO", "D Flip Flop 16bit", "D Flip Flop 24bit",
	"Data and Signal Buffer", "Device Buffer", "Device Decode stage A", "Device Decode stage B", "Dual Comparator 8bit",
	"Flags Enable Interrupt", "GPIO 16bit", "GPIO 4bit", "Main Address Buffer", "Main Data Buffer",
	"Memory 32KB with Output", "Register 24bit with IO", "Register 8bit with IO", "Selector 1-of-4 4bit",
	"Selector 1-of-4 4bit with Input", "Selector 12bit", "Selector 18bit", "State Reader 16bit", "State Reader 8bit",
};


void SweepKicadComponentBoards(void)
{
	size						i;
	CKicadSchemFile				cFile;
	CKicadSchemNetlist			cNetlist;
	CCircuitFonts				cFonts;
	CCircuitViews				cCircuits;
	CKicadSchemLogicimConverter	cConverter;
	CChars						szPath;
	CFileUtil					cFileUtil;
	Ptr<CFontFamily>			pFamily;
	FILE*						pFile;
	clock_t						iStart;
	bool						bLoaded;
	bool						bConverted;

	DataIOInit();
	DataMemoryInit();
	cFileUtil.MakeDir("Output");
	cFileUtil.MakeDir("Output" _FS_ "Boards");
	pFile = fopen("Output" _FS_ "ComponentBoards.txt", "w");
	fprintf(pFile, "%-34s %6s %5s %6s %5s %5s %5s %6s %5s %4s %7s\n", "Board", "Loaded", "Gates", "Blocks", "Place", "Power", "Skip", "Conns", "Uncon", "Ovl", "Seconds");
	fflush(pFile);

	for (i = 0; i < sizeof(gaszKicadComponentBoards) / sizeof(const char*); i++)
	{
		ObjectsInit();
		LoadCircuitFonts(&cFonts, "Input" _FS_ "Fonts", CCO_Unknown);
		pFamily = cFonts.GetSansSerif();
		ORoot()->Add(pFamily);
		pFamily = cFonts.GetMonospaced();
		ORoot()->Add(pFamily);

		iStart = clock();
		szPath.Init(KICAD_COMPONENT_BOARDS _FS_);
		szPath.Append(gaszKicadComponentBoards[i]);
		szPath.Append(_FS_);
		szPath.Append(gaszKicadComponentBoards[i]);
		szPath.Append(".kicad_sch");
		cFile.Init();
		bLoaded = cFile.Load(szPath.Text());
		szPath.Kill();
		cNetlist.Init(&cFile);
		bConverted = false;
		cCircuits.Init();
		cConverter.Init(&cFile, &cNetlist, &cCircuits, &cFonts);
		if (bLoaded && cNetlist.Build())
		{
			bConverted = cConverter.Convert(gaszKicadComponentBoards[i]);
			if (bConverted)
			{
				szPath.Init("Output" _FS_ "Boards" _FS_);
				szPath.Append(gaszKicadComponentBoards[i]);
				szPath.Append(".xml");
				SaveCircuitsFile(&cCircuits, cConverter.GetCircuit(), NULL, szPath.Text());
				szPath.Kill();
			}
		}
		fprintf(pFile, "%-34s %6s %5d %6d %5d %5d %5d %6d %5d %4d %7.1f\n", gaszKicadComponentBoards[i], bConverted ? "yes" : (bLoaded ? "conv" : "load"),
			(int)cConverter.NumGates(), (int)cConverter.NumBlocks(), (int)cConverter.NumPlaceholders(), (int)cConverter.NumPowers(), (int)cConverter.NumSkipped(),
			(int)cConverter.NumConnections(), (int)cConverter.NumUnconnected(), (int)cConverter.NumOverlaps(), (float)(clock() - iStart) / CLOCKS_PER_SEC);
		fflush(pFile);

		cConverter.Kill();
		cCircuits.Kill();
		cNetlist.Kill();
		cFile.Kill();
		cFonts.Kill();
		ORoot()->RemoveAll();
		ObjectsFlush();
		ObjectsKill(false);
	}
	fclose(pFile);
	DataMemoryKill();
	DataIOKill();
}

