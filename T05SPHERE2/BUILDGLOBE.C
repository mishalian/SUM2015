#include "globe.h"

PutCir( HDC hDC, INT x, INT y )
{
  SelectObject(hDC, GetStockObject(NULL_PEN));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(0, 0, 0));
  Ellipse(hDC, x - 5, y - 5, x + 5, y + 5);  
}

BuildGlobe( HDC hDC, INT w, INT h )
{
  MPT pt;
  DOUBLE phi, theta;

  PutCir(hDC, pt.x, pt.y);  
}