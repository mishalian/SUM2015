/*T02CLOCK.C
 *MC11
 *02.06.2015
 *Create clock animation.
 */

#pragma warning(disable: 4244)

#include <math.h>
#include <string.h>
#include <time.h>

#include <windows.h>

#define SQR(X) (X) * (X)
#define PI 3.14159265358979323846

#define WND_CLASS_NAME "My window class"


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
      "Time",                      /* ��������� ���� */
      WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,          /* ����� ���� - ���� ������ ���� */
      960 - 450, 540 - 450, /* ������� ���� (x, y) - �� ��������� */
      900, 900, /* ������� ���� (w, h) - �� ��������� */
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

VOID DrawHand( HDC hDC, INT X1, INT Y1, INT Len, INT w, DOUBLE Angle )
{
  DOUBLE si = sin(Angle), co = cos(Angle);
  INT i;
  POINT pnts[] = 
  {
    {0, -w}, {-w, 0}, {0, Len}, {w, 0}
  }, pntdraw[sizeof pnts / sizeof pnts[0]];

  for (i = 0; i < sizeof pnts / sizeof pnts[0]; i++)
  {
    pntdraw[i].x = X1 + pnts[i].x * co - pnts[i].y * si;
    pntdraw[i].y = Y1 + pnts[i].x * si + pnts[i].y * co;
  }
  Polygon(hDC, pntdraw, 4);
} /* End of 'DrawArrow' function */


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
  HDC hDC;
  CREATESTRUCT *cs; 
  POINT pt;
  SYSTEMTIME st;
  CHAR Buf[100];
  HFONT hFnt;
  HPEN hPen;
  DOUBLE Angle;
  static BITMAP bm;
  static HBITMAP hBm, hBmLogo;
  static HDC hMemDC, hMemDCLogo;
  static INT w, h;


  switch (Msg)
  {
  case WM_CREATE:
    cs = (CREATESTRUCT *)lParam;
    SetTimer(hWnd, 111, 50, NULL);

    hDC = GetDC(hWnd);
    hBmLogo = LoadImage(NULL, "clock.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hBmLogo, sizeof(bm), &bm);

    /* ������� �������� � ������ */
    hMemDC = CreateCompatibleDC(hDC);
    hMemDCLogo = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);

    SelectObject(hMemDCLogo, hBmLogo);
    return 0;

  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);

    /* ������� �������� �������� � ���� */
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
    SetDCBrushColor(hMemDC, RGB(0, 0, 0));
    Rectangle(hMemDC, 0, 0, w + 1, h + 1);

    SelectObject(hMemDC, hBm);
    BitBlt(hMemDC, w / 2 - 300, h / 2 - 300, 600, 600,
      hMemDCLogo, 0, 0, SRCCOPY);

    /* Draw picture */
    hFnt = CreateFont(100, 0, 0, 0, FW_BOLD, FALSE, FALSE,
      FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
      CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
      VARIABLE_PITCH | FF_ROMAN, "");
    hFnt = SelectObject(hMemDC, hFnt);
    GetLocalTime(&st);
    SetTextColor(hMemDC, RGB(0, 200, 200));
    SetBkColor(hMemDC, RGB(0, 0, 0));  
    SetBkMode(hMemDC, TRANSPARENT);
    TextOut(hMemDC, w / 2 - 165, h / 2 - 400, Buf,
      sprintf(Buf, "%02d:%02d:%02d",
        st.wHour, st.wMinute, st.wSecond));
    TextOut(hMemDC, w / 2 - 200, h / 2 + 300, Buf,
      sprintf(Buf, "%02d.%02d.%d",
        st.wDay, st.wMonth, st.wYear));

    DeleteObject(hFnt);

 //   Angle = st.wSecond / 30.0 * PI + PI / 2;

    hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
    SelectObject(hMemDC, hPen);

/*    pt.x = cos(Angle) * 250;
    pt.y = sin(Angle) * 250;
    MoveToEx(hMemDC, w / 2, h / 2, NULL);
    LineTo(hMemDC, w / 2 - pt.x, h / 2 - pt.y);  */

    SetDCBrushColor(hMemDC, RGB(0, 200, 200)); 
    DrawHand(hMemDC, w / 2, h / 2, 150, 10, (int)(st.wHour) % 12 * PI / 180 + 0.25);
    DrawHand(hMemDC, w / 2, h / 2, 200, 10, st.wMinute * 6 * PI / 180 + PI);
    
    SetDCBrushColor(hMemDC, RGB(0, 0, 0));
    DrawHand(hMemDC, w / 2, h / 2, 250, 10, st.wSecond * 6 * PI / 180 + PI);

    DeleteObject(hPen);   
  
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;

  case WM_CLOSE:
    break;

  case WM_ERASEBKGND:
    BitBlt((HDC)wParam, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    return 0;


  case WM_DESTROY:
    DeleteDC(hMemDC);
    DeleteObject(hBm);
    DeleteDC(hMemDCLogo);
    DeleteObject(hBmLogo);
    KillTimer(hWnd, 111);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' function */

