#include "BaseLib/Chars.h"
#include "StandardLib/ClassDefines.h"
#include "SupportLib/ColourARGB32.h"
#include "ReferenceTestWindow.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CReferenceTestWindow::Init(char* szWindowTitle, CNativeWindowFactory* pcWindowFactory)
{
    CWindow::Init(szWindowTitle, pcWindowFactory);
    miTime = 0;
    miX = 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CReferenceTestWindow::Free(void)
{
    CWindow::Free();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CReferenceTestWindow::Class(void)
{
    CWindow::Class();

    U_Int64(miTime);
    U_Int32(miX);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool CReferenceTestWindow::Save(CObjectWriter* pcFile)
{
    return false;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool CReferenceTestWindow::Load(CObjectReader* pcFile)
{
    return false;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CReferenceTestWindow::Tick(int64 iUpdateTimeInMillieconds, int64 iTotalTimeInMillieconds)
{
    CRectangle      cRect;
    ARGB32          sGrey;
    ARGB32          sGreen;
    ARGB32          sBlue;

    if (mpCanvas->IsValid())
    {
        cRect.miLeft = 0;
        cRect.miRight = mpCanvas->GetWidth();
        cRect.miTop = 0;
        cRect.miBottom = mpCanvas->GetHeight();

        sGrey = Set32BitColour((uint8)64, 64, 64);
        mpCanvas->DrawBox(&cRect, true, sGrey);

        sGreen = Set32BitColour((uint8)192, 255, 180);
        sBlue = Set32BitColour((uint8)60, 80, 255);
        for (int x = 0; x < 96; x += 4)
        {
            for (int y = 5; y < 64; y += 4)
            {
                if ((x == 0) || (y == 5))
                {
                    mpCanvas->DrawPixel(x + miX, y, sGreen);
                }
                else
                {
                    mpCanvas->DrawPixel(x + miX, y, sBlue);
                }
            }
        }
        miX++;
    }

    Paint();

    if (miX == 10)
    {
        mpcNativeWindow->Stop();
    }
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CReferenceTestWindow::CanvasChanged(Ptr<CCanvas> pcNewCanvas)
{
}

