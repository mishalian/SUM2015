/* FILENAME: ANIM.H
 * PROGRAMMER: MC6
 * PURPOSE: Animation system declaration module.
 * LAST UPDATE: 08.06.2015
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "def.h"
#include "vec.h"

#include <windows.h>
#include <stdlib.h>
#include <time.h>

/* ������������ ���������� ��������� �������� */
#define MC6_MAX_UNITS 3000

/* ���������� ���� �������� �������� "������" */
typedef struct tagmc6UNIT mc6UNIT;

/* ��������� �������� ��������� �������� */
typedef struct
{
  HWND hWnd;          /* ���� ������ */
  INT W, H;           /* ������ ���� ������ */
  HBITMAP hBmFrame;   /* ����� ����� */
  HDC hDC;            /* �������� ������ */
  BOOL IsPause; 
  DBL GlobalTime, GlobalDeltaTime, DeltaTime, Time, FPS;

  /* ������ ��������� �������� � �� ���������� */
  mc6UNIT *Units[MC6_MAX_UNITS]; 
  INT NumOfUnits;

    /* ���������� ����� */
  BYTE
    Keys[256],       /* �������� ������ ���������� � ���� */
    KeysOld[256],    /* �������� ������ �� ���������� ����� */
    KeysClick[256];  /* ����� ������������ ������� */
  INT
    MsDeltaX, MsDeltaY, /* ������������� ���������� ������� ���� */
    MsX, MsY,        /* ���������� ���������� ������� ���� */
    MsWheel;         /* ��������� ������ ���� */
  BYTE
    JButs[32],       /* �������� ������ ��������� */
    JButsOld[32],    /* �������� ������ ��������� �� ���������� ����� */
    JButsClick[32],  /* ����� ������������ ������� ������ ��������� */
    JPOV;            /* ������������� POV - 0..8 */
  DBL
    JX, JY, JZ, JR, JU, JV; /* ��� ��������� (-1.0 .. 1.0 */
} mc6ANIM;

/* ������� ���� ������� ��������:
 * - ������ ��������� ��� ������������
 *     INT Size;
 * - ������������� ��������:
 *     INT Id;
 * - ��������� �� ������� �������������
 *     VOID (*Init)( mc6UNIT *Unit, mc6ANIM *Ani );
 * - ��������� �� ������� ���������������
 *     VOID (*Close)( mc6UNIT *Unit, mc6ANIM *Ani );
 * - ��������� �� ������� ���������� ����������� ����������
 *     VOID (*Response)( mc6UNIT *Unit, mc6ANIM *Ani );
 * - ��������� �� ������� ����������
 *     VOID (*Render)( mc6UNIT *Unit, mc6ANIM *Ani );
 */
#define MC6_UNIT_BASE_FIELDS \
  INT Size;                                          \
  VOID (*Init)( mc6UNIT *Unit, mc6ANIM *Ani );       \
  VOID (*Close)( mc6UNIT *Unit, mc6ANIM *Ani );      \
  VOID (*Response)( mc6UNIT *Unit, mc6ANIM *Ani );   \
  VOID (*Render)( mc6UNIT *Unit, mc6ANIM *Ani )

/* ������� ��� ������� �������� */
struct tagmc6UNIT
{
  MC6_UNIT_BASE_FIELDS;
};

/* ���������� ���������� - ������� ��������� ������ ���� */
extern INT MC6_MouseWheel;


/* ������� ������������� ��������.
 * ���������:
 *   - ���������� ����:
 *       HWND hWnd;
 * ������������ ��������: ���.
 */
VOID MC6_AnimInit( HWND hWnd );

/* ������� ��������������� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID MC6_AnimClose( VOID );

/* ������� ��������� ��������� ������� ������� ������.
 * ���������:
 *   - ����� ������ ������� ������:
 *       INT W, H;
 * ������������ ��������: ���.
 */
VOID MC6_AnimResize( INT W, INT H );

/* ������� ���������� ����� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID MC6_AnimRender( VOID );

/* ������� ������ ����� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID MC6_AnimCopyFrame( VOID );

/* ������� ���������� � ������� ������� ��������.
 * ���������:
 *   - ����������� ������ ��������:
 *       mc6UNIT *Unit;
 * ������������ ��������: ���.
 */
VOID MC6_AnimAddUnit( mc6UNIT *Unit );

/* ������� ������������ �/�� �������������� ������
 * � ������ ���������� ���������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID MC6_AnimFlipFullScreen( VOID );

/* ������� �������� ������� ��������.
 * ���������:
 *   - ������ ��������� ������� ��������:
 *       INT Size;
 * ������������ ��������:
 *   (mc6UNIT *) ��������� �� ��������� ������ ��������.
 */
mc6UNIT * MC6_AnimUnitCreate( INT Size );

/* ������� ��������� ����� ��������.
 * ���������:
 *   - ���� �����:
 *       BOOL NewPauseFlag;
 * ������������ ��������: ���.
 */
VOID MC6_AnimSetPause( BOOL NewPauseFlag );

/* ������� ������ �� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID MC6_AnimDoExit( VOID );

#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */
