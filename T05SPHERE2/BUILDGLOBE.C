#include "globe.h"

BuildGlobe( HDC hDC, INT w, INT h )
{
  SelectObject(hDC, GetStockObject(NULL_PEN));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(0, 0, 0));
  Ellipse(hDC, w / 2 - 50, h / 2 - 50, w / 2 + 50, h / 2 + 50);  
}