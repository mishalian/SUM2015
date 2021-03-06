/* FILENAME: ANIM.C
 * PROGRAMMER: MC6
 * PURPOSE: Animation system module.
 * LAST UPDATE: 08.06.2015
 */

#include "anim.h"
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm")

/* ��������� �������� ��� ��������� */
#define MC6_GET_AXIS_VALUE(Axis) \
  (2.0 * (ji.dw ## Axis ## pos - jc.w ## Axis ## min) / (jc.w ## Axis ## max - jc.w ## Axis ## min) - 1.0)

/* ��������� �������� �������� */
mc6ANIM MC6_Anim;
/* ������ ��� ������������� �� ������� */
static INT64
  TimeFreq,  /* ������ ��������� � ������� */
  TimeStart, /* ����� ������ �������� */
  TimeOld,   /* ����� �������� ����� */
  TimePause, /* ����� ������� � ����� */
  TimeFPS;   /* ����� ��� ������ FPS */
static INT
  FrameCounter; /* ������� ������ */

/* ����������� ������� ���������� */
static INT
  MC6_MouseOldX, MC6_MouseOldY;


/* ������� ��������� ����� ��������.
 * ���������:
 *   - ���� �����:
 *       BOOL NewPauseFlag;
 * ������������ ��������: ���.
 */
VOID MC6_AnimSetPause( BOOL NewPauseFlag )
{
  MC6_Anim.IsPause = NewPauseFlag;
} /* End of 'AS3_AnimSetPause' function */


/* ������� ������������� ��������.
 * ���������:
 *   - ���������� ����:
 *       HWND hWnd;
 * ������������ ��������: ���.
 */
VOID MC6_AnimInit( HWND hWnd )
{
  HDC hDC = GetDC(hWnd);
  POINT pt;
  LARGE_INTEGER li;

  memset(&MC6_Anim, 0, sizeof(mc6ANIM));

  QueryPerformanceFrequency(&li);
  TimeFreq = li.QuadPart;
  QueryPerformanceCounter(&li);
  TimeStart = TimeOld = TimeFPS = li.QuadPart;
  MC6_Anim.IsPause = FALSE;
  FrameCounter = 0;

  MC6_Anim.hWnd = hWnd;
  /* �������������� ����� ����� */
  MC6_Anim.hDC = CreateCompatibleDC(hDC);
  MC6_Anim.hBmFrame = CreateCompatibleBitmap(hDC, 30, 30);
  SelectObject(MC6_Anim.hDC, MC6_Anim.hBmFrame);
  MC6_Anim.W = 30;
  MC6_Anim.H = 30;
  MC6_Anim.NumOfUnits = 0;
  ReleaseDC(hWnd, hDC);

  /* ������������� ������� */
  QueryPerformanceFrequency(&li);
  QueryPerformanceCounter(&li);

  /* ������������� ����� */
  GetCursorPos(&pt);
  ScreenToClient(MC6_Anim.hWnd, &pt);
  MC6_MouseOldX = pt.x;
  MC6_MouseOldY = pt.y;
  GetKeyboardState(MC6_Anim.KeysOld);

} /* End of 'MC6_AnimInit' function */

/* ������� ��������������� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID MC6_AnimClose( VOID )
{
  INT i;

  /* ������������ ������ ��-��� �������� �������� */
  for (i = 0; i < MC6_Anim.NumOfUnits; i++)
  {
    MC6_Anim.Units[i]->Close(MC6_Anim.Units[i], &MC6_Anim);
    free(MC6_Anim.Units[i]);
    MC6_Anim.Units[i] = NULL;
  }

  /* ������� ������� GDI */
  DeleteObject(MC6_Anim.hBmFrame);
  DeleteDC(MC6_Anim.hDC);
} /* End of 'MC6_AnimClose' function */

/* ������� ��������� ��������� ������� ������� ������.
 * ���������:
 *   - ����� ������ ������� ������:
 *       INT W, H;
 * ������������ ��������: ���.
 */
VOID MC6_AnimResize( INT W, INT H )
{
  HDC hDC = GetDC(MC6_Anim.hWnd);

  /* ������������� ������ � ������ ����� */
  DeleteObject(MC6_Anim.hBmFrame);
  MC6_Anim.hBmFrame = CreateCompatibleBitmap(hDC, W, H);
  SelectObject(MC6_Anim.hDC, MC6_Anim.hBmFrame);

  /* ���������� ������� */
  MC6_Anim.W = W;
  MC6_Anim.H = H;

  ReleaseDC(MC6_Anim.hWnd, hDC);

  if (W > H)
    MC6_RndWp = (DBL)W / H * 3, MC6_RndHp = 3;
  else
    MC6_RndHp = (DBL)H / W * 3, MC6_RndWp = 3;

    MC6_RndMatrProj = MatrFrustum(-MC6_RndWp / 2, MC6_RndWp / 2, -MC6_RndHp / 2, MC6_RndHp / 2, MC6_RndProjDist, 800);
} /* End of 'MC6_AnimResize' function */

/* ������� ���������� ����� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID MC6_AnimRender( VOID )
{
  INT i;
  POINT pt;
  LARGE_INTEGER li;

  QueryPerformanceCounter(&li);
  MC6_Anim.GlobalTime = (DBL)(li.QuadPart - TimeStart) / TimeFreq;
  MC6_Anim.GlobalDeltaTime = (DBL)(li.QuadPart - TimeOld) / TimeFreq;

  if (!MC6_Anim.IsPause)
    MC6_Anim.DeltaTime = MC6_Anim.GlobalDeltaTime;
  else
  {
    TimePause += li.QuadPart - TimeOld;
    MC6_Anim.DeltaTime = 0;
  }

  MC6_Anim.Time = (DBL)(li.QuadPart - TimePause - TimeStart) / TimeFreq;

    /* ��������� FPS */
  if (li.QuadPart - TimeFPS > TimeFreq)
  {
    static CHAR Buf[100];

    sprintf(Buf, "FPS: %.5f", MC6_Anim.FPS);
    SetWindowText(MC6_Anim.hWnd, Buf);

    MC6_Anim.FPS = FrameCounter / ((DBL)(li.QuadPart - TimeFPS) / TimeFreq);
    TimeFPS = li.QuadPart;
    FrameCounter = 0;
  }

  /* ����� "��������" ����� */
  TimeOld = li.QuadPart;

  FrameCounter++;

  /* ����� �� ��������� ��������� �������� */
  for (i = 0; i < MC6_Anim.NumOfUnits; i++)
    MC6_Anim.Units[i]->Response(MC6_Anim.Units[i], &MC6_Anim);

  /* ������� ���� */
  SelectObject(MC6_Anim.hDC, GetStockObject(DC_BRUSH));
  SelectObject(MC6_Anim.hDC, GetStockObject(NULL_PEN));
  SetDCBrushColor(MC6_Anim.hDC, RGB(0, 0, 0));
  Rectangle(MC6_Anim.hDC, 0, 0, MC6_Anim.W + 1, MC6_Anim.H + 1);

  /* ��������� �������� */
  for (i = 0; i < MC6_Anim.NumOfUnits; i++)
  {
    SelectObject(MC6_Anim.hDC, GetStockObject(DC_BRUSH));
    SelectObject(MC6_Anim.hDC, GetStockObject(DC_PEN));
    SetDCBrushColor(MC6_Anim.hDC, RGB(255, 255, 255));
    SetDCPenColor(MC6_Anim.hDC, RGB(0, 0, 0));

    MC6_Anim.Units[i]->Render(MC6_Anim.Units[i], &MC6_Anim);
  }

  /*** ���������� ����� ***/

  /* ���������� */
  GetKeyboardState(MC6_Anim.Keys);
  for (i = 0; i < 256; i++)
    MC6_Anim.Keys[i] >>= 7;
  for (i = 0; i < 256; i++)
    MC6_Anim.KeysClick[i] = MC6_Anim.Keys[i] && !MC6_Anim.KeysOld[i];
  memcpy(MC6_Anim.KeysOld, MC6_Anim.Keys, sizeof(MC6_Anim.KeysOld));

  /* ���� */
  /* ������ */
  MC6_Anim.MsWheel = MC6_MouseWheel;
  MC6_MouseWheel = 0;
  /* ���������� ������� */
  GetCursorPos(&pt);
  ScreenToClient(MC6_Anim.hWnd, &pt);
  MC6_Anim.MsX = pt.x;
  MC6_Anim.MsY = pt.y;
  /* ������������� ����������� */
  MC6_Anim.MsDeltaX = pt.x - MC6_MouseOldX;
  MC6_Anim.MsDeltaY = pt.y - MC6_MouseOldY;
  MC6_MouseOldX = pt.x;
  MC6_MouseOldY = pt.y;

  /* �������� */
  if ((i = joyGetNumDevs()) > 0)
  {
    JOYCAPS jc;

    /* ��������� ����� ���������� � �������� */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      /* ��������� �������� ��������� */
      ji.dwSize = sizeof(JOYCAPS);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* ������ */
        memcpy(MC6_Anim.JButsOld, MC6_Anim.JButs, sizeof(MC6_Anim.JButs));
        for (i = 0; i < 32; i++)
          MC6_Anim.JButs[i] = (ji.dwButtons >> i) & 1;
        for (i = 0; i < 32; i++)
          MC6_Anim.JButsClick[i] = MC6_Anim.JButs[i] && !MC6_Anim.JButsOld[i];

        /* ��� */
        MC6_Anim.JX = MC6_GET_AXIS_VALUE(X);
        MC6_Anim.JY = MC6_GET_AXIS_VALUE(Y);
        if (jc.wCaps & JOYCAPS_HASZ)
          MC6_Anim.JZ = MC6_GET_AXIS_VALUE(Z);
        if (jc.wCaps & JOYCAPS_HASU)
          MC6_Anim.JU = MC6_GET_AXIS_VALUE(U);
        if (jc.wCaps & JOYCAPS_HASV)
          MC6_Anim.JV = MC6_GET_AXIS_VALUE(V);
        if (jc.wCaps & JOYCAPS_HASR)
          MC6_Anim.JR = MC6_GET_AXIS_VALUE(R);

        if (jc.wCaps & JOYCAPS_HASPOV)
        {
          if (ji.dwPOV == 0xFFFF)
            MC6_Anim.JPOV = 0;
          else
            MC6_Anim.JPOV = ji.dwPOV / 4500 + 1;
        }
      }
    }
  }
} /* End of 'MC6_AnimRender' function */

/* ������� ������ ����� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID MC6_AnimCopyFrame( VOID )
{
  HDC hDC;

  /* ����� ����� */
  hDC = GetDC(MC6_Anim.hWnd);
  BitBlt(hDC, 0, 0, MC6_Anim.W, MC6_Anim.H, MC6_Anim.hDC, 0, 0, SRCCOPY);
  ReleaseDC(MC6_Anim.hWnd, hDC);
} /* End of 'MC6_AnimCopyFrame' function */

/* ������� ���������� � ������� ������� ��������.
 * ���������:
 *   - ����������� ������ ��������:
 *       mc6UNIT *Unit;
 * ������������ ��������: ���.
 */
VOID MC6_AnimAddUnit( mc6UNIT *Unit )
{
  if (MC6_Anim.NumOfUnits < MC6_MAX_UNITS)
  {
    MC6_Anim.Units[MC6_Anim.NumOfUnits++] = Unit;
    Unit->Init(Unit, &MC6_Anim);
  }
} /* End of 'MC6_AnimAddUnit' function */


/* ������� ������������ �/�� �������������� ������
 * � ������ ���������� ���������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID MC6_AnimFlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE; /* ������� ����� */
  static RECT SaveRC;               /* ����������� ������ ���� */

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    /* ��������� ������ ������ ���� */
    GetWindowRect(MC6_Anim.hWnd, &SaveRC);

    /* ���������� � ����� �������� ��������� ���� */
    hmon = MonitorFromWindow(MC6_Anim.hWnd, MONITOR_DEFAULTTONEAREST);

    /* �������� ���������� ��� �������� */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    /* ��������� � ������ ����� */
    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(MC6_Anim.hWnd, GWL_STYLE), FALSE);

    SetWindowPos(MC6_Anim.hWnd, HWND_TOPMOST, rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    /* ��������������� ������ ���� */
    SetWindowPos(MC6_Anim.hWnd, HWND_TOP,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} /* End of 'MC6_AnimFlipFullScreen' function */

/* ������� ������ �� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID MC6_AnimDoExit( VOID )
{
  PostMessage(MC6_Anim.hWnd, WM_CLOSE, 0, 0);
} /* End of 'MC6_AnimDoExit' function */

/* END OF 'ANIM.C' FILE */
