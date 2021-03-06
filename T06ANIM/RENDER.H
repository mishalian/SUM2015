/* FILENAME: RENDER.H
 * PROGRAMMER: MC6
 * PURPOSE: Rendering system declaration module.
 * LAST UPDATE: 09.06.2015
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#include "anim.h"

/* ��� ������������� ������� - ����� ������ � ������������� */
typedef struct tagmc6GOBJ
{
  VEC *V;      /* ������ ������ ������� */
  INT NumOfV;  /* ���������� ������ */
  INT (*F)[3]; /* ������ ������ ������� */
  INT NumOfF;  /* ���������� ������ */
} mc6GOBJ;

/* ������� */
extern MATR
  MC6_RndMatrWorld,
  MC6_RndMatrProj,
  MC6_RndMatrView;

/* ��������� ������������� */
extern DBL
  MC6_RndWp, MC6_RndHp,    /* ������� ������� ������������� */
  MC6_RndProjDist;         /* ���������� �� ��������� �������� */

/* ������� �������������� �� ������� ������� ��������� � ����.
 * ���������:
 *   - �������� �����:
 *       VEC P;
 * ������������ ��������:
 *   (POINT) ���������� � �����.
 */
POINT MC6_RndWorldToScreen( VEC P );

/* ������� �������� ��������������� �������.
 * ���������:
 *   - ��������� ������� ��� ��������:
 *       mc6GOBJ *GObj;
 *   - ��� �����:
 *       CHAR *FileName;
 * ������������ ��������:
 *   (BOOL) TRUE ��� ������, FALSE �����.
 */
BOOL MC6_RndGObjLoad( mc6GOBJ *GObj, CHAR *FileName );

/* ������� ������������ ������ ��-��� ��������������� �������.
 * ���������:
 *   - ��������� ������� ��� ��������:
 *       mc6GOBJ *GObj;
 * ������������ ��������: ���.
 */
VOID MC6_RndGObjFree( mc6GOBJ *GObj );

/* ������� ��������� ��������������� �������.
 * ���������:
 *   - ��������� ������� ��� ��������:
 *       mc6GOBJ *GObj;
 * ������������ ��������: ���.
 */
VOID MC6_RndGObjDraw( mc6GOBJ *GObj );

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
