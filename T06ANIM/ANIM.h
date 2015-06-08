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

/* ������� ������ �� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID MC6_AnimDoExit( VOID );

#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */
