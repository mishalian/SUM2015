#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <windows.h>

#pragma warning(disable: 4244)

#define PI 3.14159265358979323846
#define R 200
#define DBL double
#define M 30
#define N 30

typedef struct
{
	DBL X;
	DBL Y;
	DBL Z;
}VEC;

static VEC Grid[N][M];

VOID BuildGlobe(HDC hDC, INT w, INT h);
<<<<<<< 7657d15ee41ca1055590354e8fe077ff86efc760
VOID DrawGlobe(HDC hDC, INT w, INT h);
=======
VOID DrawGlobe(HDC hDC, INT w, INT h);
>>>>>>> 977fc549a26382dff558fe32d092344f27deec0b
