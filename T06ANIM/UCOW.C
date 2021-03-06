/* FILENAME: UBALL.C
 * PROGRAMMER: MC6
 * PURPOSE: Cow unit handle module.
 * LAST UPDATE: 08.06.2015
 */

#include <string.h>
#include <time.h>

#include "anim.h"
#include "vec.h"

/* ��� ������������� ���� */
typedef struct tagmc6UNIT_COW
{
  MC6_UNIT_BASE_FIELDS;
  mc6GOBJ Cow;
} mc6UNIT_COW;


/* ������� ������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT_BALL *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitInit( mc6UNIT_COW *Uni, mc6ANIM *Ani )
{
  MC6_RndGObjLoad(&Uni->Cow, "cow.object");
} /* End of 'MC6_AnimUnitInit' function */

/* ������� ��������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT_BALL *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitClose( mc6UNIT_COW *Uni, mc6ANIM *Ani )
{
} /* End of 'MC6_AnimUnitClose' function */

/* ������� ���������� ����������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT_BALL *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitResponse( mc6UNIT_COW *Uni, mc6ANIM *Ani )
{
  if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    MC6_AnimDoExit();
} /* End of 'MC6_AnimUnitResponse' function */

/* ������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT_BALL *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitRender( mc6UNIT_COW *Uni, mc6ANIM *Ani )
{
//  ObjDraw(Ani->hDC, Ani->W, Ani->H);
  MC6_RndMatrView = MatrView(VecSet(8, 8, 8),
                             VecSet(0, 0, 0),
                             VecSet(0, 1, 0));
 /* MC6_RndMatrWorld =
    MatrMulMatr(MatrMulMatr(MatrMulMatr(
      MatrTranslate(Ani->JX * 59, Ani->JY * 88, 0),
      MatrScale(0.1, 0.1, 0.1)),
      MatrRotateY(30 * Ani->Time + Ani->JR * 180)),
      MatrTranslate(0, 0, 100 * Ani->JZ)); */
  SelectObject(Ani->hDC, GetStockObject(DC_PEN)); 
  SetDCPenColor(Ani->hDC, RGB(rand() / 255, rand() / 255, rand() / 255));

  MC6_RndGObjDraw(&Uni->Cow);
} /* End of 'MC6_AnimUnitRender' function */

/* ������� �������� ������� �������� "������".
 * ���������: ���.
 * ������������ ��������:
 *   (mc6UNIT *) ��������� �� ��������� ������ ��������.
 */
mc6UNIT * MC6_UnitCowCreate( VOID )
{
  mc6UNIT_COW *Uni;

  if ((Uni = (VOID *)MC6_AnimUnitCreate(sizeof(mc6UNIT_COW))) == NULL)
    return NULL;
  /* ��������� ���� */
  Uni->Init = (VOID *)MC6_AnimUnitInit;
  Uni->Close = (VOID *)MC6_AnimUnitClose;
  Uni->Response = (VOID *)MC6_AnimUnitResponse;
  Uni->Render = (VOID *)MC6_AnimUnitRender;
  return (mc6UNIT *)Uni;
} /* End of 'MC6_UnitBallCreate' function */

/* END OF 'UBALL.C' FILE */
