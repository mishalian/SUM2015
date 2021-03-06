/* FILENAME: UCONTRL.C
 * PROGRAMMER: MC6
 * PURPOSE: Control unit handle module.
 * LAST UPDATE: 08.06.2015
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "anim.h"
#include "vec.h"

/* ��� ������������� ���� */
typedef struct tagmc6UNIT_CTRL
{
  MC6_UNIT_BASE_FIELDS;
  HFONT hFnt; /* ����� ��� ������ FPS */
} mc6UNIT_CTRL;

/* ������� ������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT_CTRL *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitInit( mc6UNIT_CTRL *Uni, mc6ANIM *Ani )
{
  Uni->hFnt = CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE,
    FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    VARIABLE_PITCH, "Bookman Old Style");
} /* End of 'MC6_AnimUnitInit' function */

/* ������� ��������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT_CTRL *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitClose( mc6UNIT_CTRL *Uni, mc6ANIM *Ani )
{
  DeleteObject(Uni->hFnt);
} /* End of 'MC6_AnimUnitClose' function */

/* ������� ���������� ����������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT_CTRL *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitResponse( mc6UNIT_CTRL *Uni, mc6ANIM *Ani )
{
  if (Ani->Keys[VK_ESCAPE])
    MC6_AnimDoExit();
  if (Ani->KeysClick['F'])
    MC6_AnimFlipFullScreen();
  if (Ani->KeysClick['P'])
    MC6_AnimSetPause(!Ani->IsPause);
} /* End of 'MC6_AnimUnitResponse' function */

/* ������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT_CTRL *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitRender( mc6UNIT_CTRL *Uni, mc6ANIM *Ani )
{
  HFONT hFntOld = SelectObject(Ani->hDC, Uni->hFnt);
  RECT rc;
  static CHAR Buf[1000];

  SetTextColor(Ani->hDC, RGB(255, 255, 255));
  SetBkMode(Ani->hDC, TRANSPARENT);

  rc.left = 0;
  rc.top = 0;
  rc.right = Ani->W;
  rc.bottom = Ani->H;
  DrawText(Ani->hDC, Buf,
    sprintf(Buf,
      "FPS: %.3f\n"
      "J: %i %i %i %i %i %i, POV:%i\n"
      "%.3f %.3f %.3f %.3f %.3f %.3f",
      Ani->FPS,
      Ani->JButs[0], Ani->JButs[1], Ani->JButs[2], Ani->JButs[3], Ani->JButs[4], Ani->JButs[5], Ani->JPOV,
      Ani->JX, Ani->JY, Ani->JZ, Ani->JR, Ani->JU, Ani->JV),
    &rc,
    DT_TOP | DT_LEFT);

  SelectObject(Ani->hDC, hFntOld);
} /* End of 'MC6_AnimUnitRender' function */

/* ������� �������� ������� �������� "����������".
 * ���������: ���.
 * ������������ ��������:
 *   (mc6UNIT *) ��������� �� ��������� ������ ��������.
 */
mc6UNIT * MC6_UnitControlCreate( VOID )
{
  mc6UNIT_CTRL *Uni;

  if ((Uni = (VOID *)MC6_AnimUnitCreate(sizeof(mc6UNIT_CTRL))) == NULL)
    return NULL;
  /* ��������� ���� */
  Uni->Init = (VOID *)MC6_AnimUnitInit;
  Uni->Close = (VOID *)MC6_AnimUnitClose;
  Uni->Response = (VOID *)MC6_AnimUnitResponse;
  Uni->Render = (VOID *)MC6_AnimUnitRender;
  return (mc6UNIT *)Uni;
} /* End of 'MC6_UnitBallCreate' function */

/* END OF 'UCONTRL.C' FILE */
