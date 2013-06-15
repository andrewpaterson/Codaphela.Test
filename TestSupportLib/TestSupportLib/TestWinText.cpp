#include "stdafx.h"
#include "StandardLib/Objects.h"
#include "SupportLib/WinText.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageCopier.h"
#include "TestLib/Assert.h"
#include "TestWinText.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestWinText(void)
{
	BeginTests();

	ObjectsInit();

	CWinText			cWinText;
	SWinFontInstance*	psWinFont;
	CFont*				pcFont;
	CGlyph*				pcCel;
	CImage				cDestImage;

	cWinText.Init(NULL);
	psWinFont = cWinText.Create("Fixedsys", 0, 0, FW_DONTCARE);
	pcFont = cWinText.GenerateFont(psWinFont, "Fixedsys");

	WriteImage(pcFont->GetImage(), "Output/Fixedsys.bmp");
	AssertFile("Input/Fixedsys.bmp", "Output/Fixedsys.bmp");

	pcCel = pcFont->GetGlyph('H');
	pcCel->GetSubImage()->SetAlignment(SUB_IMAGE_ALIGNMENT_LEFT|SUB_IMAGE_ALIGNMENT_TOP);
	cDestImage.Init(pcCel->GetFullWidth(), pcCel->GetFullHeight(), pcCel->GetSourceImage());
	cDestImage.Clear();
	CImageCopier::Copy(pcCel->GetCel(), &cDestImage, 0, 0);
	WriteImage(&cDestImage, "Output/TheLetterH.png");
	cDestImage.Kill();
	AssertFile("Input/TheLetterH.png", "Output/TheLetterH.png");

	pcFont->Kill();
	cWinText.Kill();

	ObjectsKill();

	TestStatistics();
}

