#ifndef __REFERENCE_TEST_WINDOW_H__
#define __REFERENCE_TEST_WINDOW_H__
#include "WindowLib/Window.h"


class CReferenceTestWindow : public CWindow
{
    CONSTRUCTABLE(CReferenceTestWindow)
protected:
    int64	miTime;
    int32	miX;

public:
    void	Init(char* szWindowTitle, CNativeWindowFactory* pcWindowFactory);
    void	Kill(void);

    void	Tick(int64 iUpdateTimeInMillieconds, int64 iTotalTimeInMillieconds);
    void	CanvasChanged(CCanvas* pcNewCanvas);
};


#endif // __REFERENCE_TEST_WINDOW_H__

