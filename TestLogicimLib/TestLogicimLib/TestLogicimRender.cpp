#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Image.h"
#include "SupportLib/GeometryMap.h"
#include "SupportLib/PNGWriter.h"
#include "TestLib/Assert.h"
#include "TestLib/AssertFile.h"
#include "TestLogicimRender.h"


//////////////////////////////////////////////////////////////////////////
//
// Needs the objects initialised.
//
//////////////////////////////////////////////////////////////////////////
bool RenderCircuitPNG(CCircuitView* pcCircuit, CCircuitColours* pcColours, int32 iWidth, int32 iHeight, float64 fZoom, int64 iTime, bool bGrid, const char* szOutput)
{
	Ptr<CImage>			pImage;
	Ptr<CGeometryMap>	pMap;
	CCircuitViewport	cViewport;
	CCircuitPainter		cPainter;
	CInt32Rect			cRect;
	bool				bResult;

	pImage = OMalloc<CImage>(iWidth, iHeight, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
	pMap = OMalloc<CGeometryMap>();
	pMap->SetViewport(pImage);

	cViewport.Init(iWidth, iHeight);
	cViewport.SetZoom(fZoom);
	cPainter.Init(&cViewport, &pMap, pcColours, iTime);

	pMap->AddRectangle(0, 0, iWidth, iHeight, pcColours->msBackground);
	if (bGrid)
	{
		PaintCircuitGrid(&cPainter);
	}
	pcCircuit->Paint(&cPainter);

	cRect.Init(0, 0, iWidth, iHeight);
	bResult = pMap->Blit(&cRect, false);
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
void AssertRenderedCircuit(CCircuitView* pcCircuit, CCircuitColours* pcColours, int32 iWidth, int32 iHeight, float64 fZoom, int64 iTime, bool bGrid, const char* szName)
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

	AssertTrue(RenderCircuitPNG(pcCircuit, pcColours, iWidth, iHeight, fZoom, iTime, bGrid, szOutput.Text()));
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

