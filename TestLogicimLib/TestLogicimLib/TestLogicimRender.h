#ifndef __TEST_LOGICIM_RENDER_H__
#define __TEST_LOGICIM_RENDER_H__
#include "LogicimLib/CircuitView.h"


//Draws the circuit on its background (and grid) into an RGB image and saves it as szOutput (a PNG).
bool RenderCircuitPNG(CCircuitView* pcCircuit, CCircuitColours* pcColours, int32 iWidth, int32 iHeight, float64 fZoom, int64 iTime, bool bGrid, const char* szOutput);
void AssertRenderedCircuit(CCircuitView* pcCircuit, CCircuitColours* pcColours, int32 iWidth, int32 iHeight, float64 fZoom, int64 iTime, bool bGrid, const char* szName);


#endif // __TEST_LOGICIM_RENDER_H__
