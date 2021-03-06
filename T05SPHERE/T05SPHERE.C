/*T05SPHERE
 *MC6 spr11
 *05.06.2015
 *Build a sphere in a three-dimentional space.
 */

/*T02CLOCK.C
 *MC11
 *02.06.2015
 *Create clock animation.
 */

#pragma warning(disable: 4244)

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <windows.h>

#define PI 3.14159265358979323846

#define WND_CLASS_NAME "My window class"
#define N 10
#define M 10

typedef struct
{
  DOUBLE X, Y, Z;
} VEC;

VEC Dot[M][N];

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam ); /* ������� ���������. */

/* ������� ������� ���������.
 *   - ���������� ���������� ����������:
 *       HINSTANCE hInstance;
 *   - ���������� ����������� ���������� ����������
 *     (�� ������������ � ������ ���� NULL):
 *       HINSTANCE hPrevInstance;
 *   - ��������� ������:
 *       CHAR *CmdLine;
 * ������������ ��������:
 *   (INT) ��� �������� � ������������ �������.
 *   0 - ��� ������.
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_VREDRAW | CS_HREDRAW; /* ����� ���� */
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
  wc.hCursor = LoadCursor(NULL, IDC_HAND); /* �������� ������� (����������) */
  wc.hIcon = LoadIcon(NULL, IDI_ASTERISK); /* �������� ����������� (���������) */
  wc.hInstance = hInstance; /* ���������� ����������, ��������������� ����� */
  wc.lpszMenuName = NULL; /* ��� ������� ���� */
  wc.lpfnWndProc = MyWindowFunc; /* ��������� �� ������� ��������� */
  wc.lpszClassName = WND_CLASS_NAME;


  /* ����������� ������ � ������� */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }

    /* �������� ���� */
  hWnd =
    CreateWindow(WND_CLASS_NAME,    /* ��� ������ ���� */
      "3D Sphere",                      /* ��������� ���� */
      WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,          /* ����� ���� - ���� ������ ���� */
      960 - 500, 540 - 500, /* ������� ���� (x, y) - �� ��������� */
      1000, 1000, /* ������� ���� (w, h) - �� ��������� */
      NULL,                         /* ���������� ������������� ���� */
      NULL,                         /* ���������� ������������ ���� */
      hInstance,                    /* ���������� ���������� */
      NULL);                        /* ��������� �� �������������� ��������� */

  ShowWindow(hWnd, ShowCmd);
  UpdateWindow(hWnd);

    /* ������ ����� ��������� ���� */
  while (GetMessage(&msg, NULL, 0, 0))
  {
    /* ��������� ��������� �� ���������� */
    TranslateMessage(&msg);
    /* �������� ��������� � ������� ���� */
    DispatchMessage(&msg);
  }
  return msg.wParam;
}


VEC RotateX( VEC P, DOUBLE AngleDegree )
{
  DOUBLE a = AngleDegree * PI / 180, si = sin(a), co = cos(a);
  VEC r;

  r.X = P.X;
  r.Y = P.Y * co - P.Z * si;
  r.Z = P.Y * si + P.Z * co;
  return r;
} /* End of 'RotateX' function */

VEC VecCrossVec( VEC A, VEC B )
{
  VEC r;

  r.X = A.Y * B.Z - A.Z * B.Y;
  r.Y = A.Z * B.X - A.X * B.Z;
  r.Z = A.X * B.Y - A.Y * B.X;
  return r;
} /* End of 'VecCrossVec' function */

/* ������� ��������� �������� */
VEC VecSubVec( VEC A, VEC B )
{
  VEC r;

  r.X = A.X - B.X;
  r.Y = A.Y - B.Y;
  r.Z = A.Z - B.Z;
  return r;
} /* End of 'VecSubVec' function */

/* ��������� ���������������� */
VOID DrawQuad( HDC hDC, VEC P0, VEC P1, VEC P2, VEC P3, INT W, INT H )
{
  VEC Norm = VecCrossVec(VecSubVec(P3, P0), VecSubVec(P1, P0));
  POINT pnts[4];

  /* back-face culling */
  if (Norm.Z < 0)
    return;

  pnts[0].x = P0.X + W / 2;
  pnts[0].y = -P0.Y + H / 2;

  pnts[1].x = P1.X + W / 2;
  pnts[1].y = -P1.Y + H / 2;

  pnts[2].x = P2.X + W / 2;
  pnts[2].y = -P2.Y + H / 2;

  pnts[3].x = P3.X + W / 2;
  pnts[3].y = -P3.Y + H / 2;

  Polygon(hDC, pnts, 4);
} /* End of 'DrawQuad' function */

VOID DrawGlobe(HDC hDC, INT w, INT h)
{
  DOUBLE phi, theta, R = 200/*, t = clock() / (DOUBLE)CLOCK_PER_SEC*/;
  INT i, j, x, y, z;

  SelectObject(hDC, GetStockObject(NULL_PEN));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(0, 0, 0));
  x = w / 2;
  y = h / 2;
  Ellipse(hDC, x - 2, y - 2, x + 2, y + 2);

  /*for (i = 0; i < N; i++)
  {
    phi = i / (N - 1) * 2 * PI;
    x = R * sin(phi) + w / 2;   
    y = h / 2;

    SelectObject(hDC, GetStockObject(NULL_PEN));
    SelectObject(hDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hDC, RGB(0, 0, 0));
    Ellipse(hDC, x - 2, y - 2, x + 2, y + 2);
  } */
}




/* ������� ��������� ��������� ����.
 * ���������:
 *   - ���������� ����:
 *       HWND hWnd;
 *   - ����� ��������� (��. WM_***):
 *       UINT Msg;
 *   - �������� ��������� ('word parameter'):
 *       WPARAM wParam;
 *   - �������� ��������� ('long parameter'):
 *       LPARAM lParam;
 * ������������ ��������:
 *   (LRESULT) - � ����������� �� ���������.
 */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  CREATESTRUCT *cs; 
  POINT pt;
  SYSTEMTIME st;
  HPEN hPen;
  DOUBLE Angle;
  static HDC hDC, hMemDC;
  static HBITMAP hBm;
  static INT w, h, R;


  switch (Msg)
  {
  case WM_CREATE:
    cs = (CREATESTRUCT *)lParam;
    SetTimer(hWnd, 111, 50, NULL);

    hDC = GetDC(hWnd);
        /* ������� �������� � ������ */
    hMemDC = CreateCompatibleDC(hDC);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);

    return 0;

  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);

    if (hBm != NULL)
      DeleteObject(hBm);

    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);

    SelectObject(hMemDC, hBm);

    SendMessage(hWnd, WM_TIMER, 111, 0);
    return 0;

  case WM_TIMER:
    /* Clear Background */
    SelectObject(hMemDC, GetStockObject(NULL_PEN));
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hMemDC, RGB(255, 255, 150));
    Rectangle(hMemDC, 0, 0, w + 1, h + 1);
    

    GetLocalTime(&st);

/*    SelectObject(hMemDC, GetStockObject(NULL_PEN));
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hMemDC, RGB(0, 0, 0));*/
    DrawGlobe(hDC, w, h);
    SelectObject(hMemDC, hBm);

    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
  
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;

  case WM_CLOSE:
    break;

  case WM_ERASEBKGND:
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    return 0;

  case WM_DESTROY:
    DeleteDC(hMemDC);
    KillTimer(hWnd, 111);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' function */

