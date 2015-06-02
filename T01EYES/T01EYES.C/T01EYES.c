/* T01FWIN.C
 * ������ �������� ������ ��������� ��� WinAPI.
 * �������� � ��������� ����������� ����.
 */

#include <windows.h>
#include <math.h>

/* ��� ������ ���� */
#define WND_CLASS_NAME "My window class"
#define SQR(X) ((X) * (X))

/* ������ ������ */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam );

VOID PutCir( HDC hDC, int x, int y )
{
  SelectObject (hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(0, 0, 0));
  Ellipse(hDC, x - 10, y - 10, x + 10, y + 10 );
}


VOID DrawEye( HDC hDC, int px, int py, int w, int h, int ex )
{
  int dx, dy, Dx, Dy;

  dx = px - ex;
  dy = h / 2 - py;
  
  if (sqrt(SQR(dx) + SQR(dy)) <= 500)
  {
    Dx = dx / 13;
    Dy = dy / 13;
    PutCir(hDC, ex + Dx, h / 2 - Dy);
  }
}



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
  /* HINSTANCE hIns = LoadLibrary("shell32"); */

  /* ����������� ������ ���� */
  wc.style = CS_VREDRAW | CS_HREDRAW; /* ����� ����: ��������� ��������������
                                       * ��� ��������� ������������� ���
                                       * ��������������� ��������
                                       * ��� ����� CS_DBLCLKS ��� ����������
                                       * ��������� �������� ������� */
  wc.cbClsExtra = 0; /* �������������� ���������� ���� ��� ������ */
  wc.cbWndExtra = 0; /* �������������� ���������� ���� ��� ���� */
  wc.hbrBackground = CreateSolidBrush(RGB(0, 255, 0));
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
      "Title",                      /* ��������� ���� */
      WS_OVERLAPPEDWINDOW,          /* ����� ���� - ���� ������ ���� */
      CW_USEDEFAULT, CW_USEDEFAULT, /* ������� ���� (x, y) - �� ��������� */
      CW_USEDEFAULT, CW_USEDEFAULT, /* ������� ���� (w, h) - �� ��������� */
      NULL,                         /* ���������� ������������� ���� */
      NULL,                         /* ���������� ������������ ���� */
      hInstance,                    /* ���������� ���������� */
      NULL);                        /* ��������� �� �������������� ��������� */

  ShowWindow(hWnd, ShowCmd);
  UpdateWindow(hWnd);

  /* ������ ����� ��������� ���� */
  while (GetMessage(&msg, NULL, 0, 0))
    /* �������� ��������� � ������� ���� */
    DispatchMessage(&msg);

  return 30;
} /* End of 'WinMain' function */

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
  INT px, py, lx, rx;
  POINT pt;
  static INT w, h;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 111, 50, NULL);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    return 0;

  case WM_TIMER:
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    px = pt.x;
    py = pt.y;   

    hDC = GetDC(hWnd);
    /*SelectObject (hDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hDC, RGB(0, 255, 0));
    Rectangle(hDC, 0, 0, w, h); */

    lx = w / 2 - 100;
    rx = w / 2 + 100;

    SetDCBrushColor(hDC, RGB(255, 255, 255));
    Ellipse(hDC, lx - 50, h / 2 + 50, lx + 50, h / 2 - 50);
    Ellipse(hDC, rx - 50, h / 2 + 50, rx + 50, h / 2 - 50);

   /* SetDCBrushColor(hDC, RGB(255, 0, 0));
    Ellipse(hDC, px - 5, py + 5, px + 5, py - 5);*/

    DrawEye(hDC, px, py, w, h, lx);
    DrawEye(hDC, px, py, w, h, rx);    

    ReleaseDC(hWnd, hDC);
    return 0;

  case WM_DESTROY:
    KillTimer(hWnd, 111);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' function */



/* END OF 'T01FWIN.C' FILE */
