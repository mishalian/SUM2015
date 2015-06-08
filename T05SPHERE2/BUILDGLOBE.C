#include "globe.h"

VOID PutCir(HDC hDC, DBL x, DBL y)
{
	SelectObject(hDC, GetStockObject(NULL_PEN));
	SelectObject(hDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hDC, RGB(0, 0, 0));
	Ellipse(hDC, x - 5, y - 5, x + 5, y + 5);
}

VOID DrawQuad(HDC hDC, VEC P0, VEC P1, VEC P2, VEC P3, INT W, INT H)
{
	POINT pnts[4];

	pnts[0].x = P0.X;
	pnts[0].y = -P0.Y + H;

	pnts[1].x = P1.X;
	pnts[1].y = -P1.Y + H;

	pnts[2].x = P2.X;
	pnts[2].y = -P2.Y + H;

	pnts[3].x = P3.X;
	pnts[3].y = -P3.Y + H;

	if ((pnts[0].x - pnts[1].x) * (pnts[0].y + pnts[1].y) +
		(pnts[1].x - pnts[2].x) * (pnts[1].y + pnts[2].y) +
		(pnts[2].x - pnts[3].x) * (pnts[2].y + pnts[3].y) +
		(pnts[3].x - pnts[0].x) * (pnts[3].y + pnts[0].y) < 0)
		return;

	SelectObject(hDC, GetStockObject(DC_PEN));
	SelectObject(hDC, GetStockObject(NULL_BRUSH));
	Polygon(hDC, pnts, 4);
} /* End of 'DrawQuad' function */


VOID BuildGlobe(HDC hDC, INT w, INT h)
{
	DOUBLE phi, theta;
	INT i, j;

	for (i = 0; i < N; i++)
	{
		theta = 2 * PI * i / N;
		for (j = 0; j < M; j++)
		{
			phi = 2 * PI * j / M;
			Grid[i][j].X = w / 2 + cos(theta) * cos(phi) * R;
			Grid[i][j].Y = h / 2 + sin(phi) * R;
			Grid[i][j].Z = cos(PI / 2 - theta) * R;
		}
	}
}


VOID DrawGlobe(HDC hDC, INT w, INT h)
{
	int i, j;

	BuildGlobe(hDC, w, h);

	for (i = 0; i < N - 1; i++)
		for (j = 0; j < M - 1; j++)
		{
			if (Grid[i][j].Z > 0)
<<<<<<< 7657d15ee41ca1055590354e8fe077ff86efc760
				DrawQuad(hDC, Grid[i][j], Grid[i + 1][j], Grid[i + 1][j + 1], Grid[i][j + 1], w, h);
		}
}
=======
				DrawQuad(hDC, Grid[i][j], Grid[i + 1][j],
                                Grid[i + 1][j + 1], Grid[i][j + 1], w, h);
		}
}
>>>>>>> 977fc549a26382dff558fe32d092344f27deec0b
