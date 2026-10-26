#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Image.h"
#include "SupportLib/GeometryMap.h"
#include "SupportLib/SpriteMap.h"
#include "SupportLib/PNGWriter.h"
#include "TestLib/Assert.h"
#include "TestLib/AssertFile.h"
#include "TestLogicimRender.h"


//////////////////////////////////////////////////////////////////////////
//
// Needs the objects initialised.
//
//////////////////////////////////////////////////////////////////////////
bool RenderCircuitPNG(CCircuitView* pcCircuit, CCircuitColours* pcColours, int32 iWidth, int32 iHeight, float64 fZoom, CViewPath* pcViewPath, CCircuitSimulation* pcSimulation, bool bGrid, const char* szOutput, CCircuitFonts* pcFonts)
{
	Ptr<CImage>			pImage;
	Ptr<CGeometryMap>	pMap;
	Ptr<CSpriteMap>		pSprites;
	CCircuitViewport	cViewport;
	CCircuitPainter		cPainter;
	bool				bResult;

	pImage = OMalloc<CImage>(iWidth, iHeight, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
	pMap = OMalloc<CGeometryMap>();
	pSprites = OMalloc<CSpriteMap>();

	cViewport.Init(iWidth, iHeight);
	cViewport.SetZoom(fZoom);
	cPainter.InitImage(pImage, &cViewport, &pMap, &pSprites, pcColours, pcFonts, pcViewPath, pcSimulation);
	if (bGrid)
	{
		PaintCircuitGrid(&cPainter);
	}
	pcCircuit->Paint(&cPainter);

	bResult = cPainter.BlitImage();
	bResult &= SavePNG(pImage, (char*)szOutput);

	cPainter.Kill();
	cViewport.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Writes Output/szName.png and compares it with Input/szName.png.  The
// output is removed when it matches.
//
//////////////////////////////////////////////////////////////////////////
void AssertRenderedCircuit(CCircuitView* pcCircuit, CCircuitColours* pcColours, int32 iWidth, int32 iHeight, float64 fZoom, CViewPath* pcViewPath, CCircuitSimulation* pcSimulation, bool bGrid, const char* szName, CCircuitFonts* pcFonts)
{
	CFileUtil	cFileUtil;
	CChars		szOutput;
	CChars		szInput;
	bool		bMatched;

	cFileUtil.MakeDir("Output");
	szOutput.Init("Output" _FS_);
	szOutput.Append(szName);
	szOutput.Append(".png");
	szInput.Init("Input" _FS_);
	szInput.Append(szName);
	szInput.Append(".png");

	AssertTrue(RenderCircuitPNG(pcCircuit, pcColours, iWidth, iHeight, fZoom, pcViewPath, pcSimulation, bGrid, szOutput.Text(), pcFonts));
	bMatched = PrivateAssertFile(szInput.Text(), szOutput.Text(), NULL, __LINE__, __FILE__);
	Validate(bMatched);
	if (bMatched)
	{
		//A different image is kept to look at.
		cFileUtil.Delete(szOutput.Text());
		cFileUtil.RemoveDir("Output");
	}

	szInput.Kill();
	szOutput.Kill();
}

