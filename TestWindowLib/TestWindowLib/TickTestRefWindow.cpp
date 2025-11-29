#include "StandardLib/ClassDefines.h"
#include "SupportLib/ColourARGB32.h"
#include "WindowLib/Window.h"
#include "TickTestRefWindow.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTickTestRefWindow::Init(SDataTestRefWindow* pcData)
{
    PreInit();

    CWindowTick::Init();
    mpcData = pcData;
    mpcData->iX = 0;

    PostInit();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTickTestRefWindow::Tick(Ptr<CWindow> pWindow, int64 iUpdateTimeInMillieconds, int64 iTotalTimeInMillieconds)
{
    pWindow->Paint();

    mpcData->iX++;
    if (mpcData->iX == 11)
    {
        pWindow->Stop();
    }
}

