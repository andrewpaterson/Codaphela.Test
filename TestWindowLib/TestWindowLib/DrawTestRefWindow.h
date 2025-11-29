#ifndef __DRAW_TEST_REF_WINDOW_H__
#define __DRAW_TEST_REF_WINDOW_H__
#include "WindowLib/CanvasDraw.h"
#include "DataTestRefWindow.h"


class CDrawTestRefWindow : public CCanvasDraw
{
CONSTRUCTABLE(CDrawTestRefWindow);
DESTRUCTABLE(CDrawTestRefWindow);
protected:
	SDataTestRefWindow* mpcData;

public:
	void	Init(SDataTestRefWindow* pcData);
	bool	Draw(Ptr<CCanvas> pCanvas) override;
};


#endif // __DRAW_TEST_REF_WINDOW_H__


