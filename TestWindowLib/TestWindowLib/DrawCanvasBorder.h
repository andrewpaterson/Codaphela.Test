#ifndef __DRAW_CANVAS_BORDER_H__
#define __DRAW_CANVAS_BORDER_H__
#include "SupportLib/ColourARGB32.h"
#include "WindowLib/CanvasDraw.h"
#include "DataTestRefWindow.h"


class CDrawCanvasBorder: public CCanvasDraw
{
CONSTRUCTABLE(CDrawCanvasBorder);
DESTRUCTABLE(CDrawCanvasBorder);
protected:
	ARGB32	msColour;

public:
	void	Init(ARGB32 sColour);
	bool	Draw(Ptr<CCanvas> pCanvas) override;
};


#endif // __DRAW_CANVAS_BORDER_H__

