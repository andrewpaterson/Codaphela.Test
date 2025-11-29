#include "StandardLib/ClassDefines.h"
#include "SupportLib/ColourARGB32.h"
#include "WindowLib/Canvas.h"
#include "DrawTestRefWindow.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDrawTestRefWindow::Init(SDataTestRefWindow* pcData)
{
    PreInit();
    
    CCanvasDraw::Init();
    mpcData = pcData;

    PostInit();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool CDrawTestRefWindow::Draw(Ptr<CCanvas> pCanvas)
{
    CRectangle      cRect;
    ARGB32          sGrey;
    ARGB32          sGreen;
    ARGB32          sBlue;

    if (pCanvas->IsValid())
    {
        cRect.miLeft = 0;
        cRect.miRight = pCanvas->GetWidth();
        cRect.miTop = 0;
        cRect.miBottom = pCanvas->GetHeight();

        sGrey = Set32BitColour((uint8)64, 64, 64);
        pCanvas->DrawBox(&cRect, true, sGrey);

        sGreen = Set32BitColour((uint8)192, 255, 180);
        sBlue = Set32BitColour((uint8)60, 80, 255);
        for (int x = 0; x < 96; x += 4)
        {
            for (int y = 5; y < 64; y += 4)
            {
                if ((x == 0) || (y == 5))
                {
                    pCanvas->DrawPixel(x + mpcData->iX, y, sGreen);
                }
                else
                {
                    pCanvas->DrawPixel(x + mpcData->iX, y, sBlue);
                }
            }
        }
    }

    return true;
}

