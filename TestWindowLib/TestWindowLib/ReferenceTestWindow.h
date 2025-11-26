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
    void	Class(void);
    void 	Free(void);

    bool	Save(CObjectWriter* pcFile) override;
    bool	Load(CObjectReader* pcFile) override;

    void	Tick(int64 iUpdateTimeInMillieconds, int64 iTotalTimeInMillieconds);
    void	CanvasChanged(Ptr<CCanvas> pcNewCanvas);
};


#endif // __REFERENCE_TEST_WINDOW_H__

