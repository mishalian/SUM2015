#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <windows.h>

#pragma warning(disable: 4244)

#define PI 3.14159265358979323846
#define R 200

typedef struct
{
  INT x;
  INT y;
}MPT;

BuildGlobe( HDC hDC, INT w, INT h );