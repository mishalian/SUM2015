/* FILENAME: UBALL.C
 * PROGRAMMER: MC6
 * PURPOSE: Bounce ball unit handle module.
 * LAST UPDATE: 08.06.2015
 */

#include <string.h>
#include <time.h>

#include "anim.h"
#include "vec.h"

/* ��� ������������� ���� */
typedef struct tagmc6UNIT_BALL
{
  MC6_UNIT_BASE_FIELDS;

  VEC Pos;     /* ������� ���� */
  DWORD Color; /* ���� ���� */
  DBL
    Amplitude,  /* ��������� */
    PhaseShift, /* ����� �� ���� */
    ScaleShift; /* ������� ������� */
} mc6UNIT_BALL;

/* ������� ������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT_BALL *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitInit( mc6UNIT_BALL *Uni, mc6ANIM *Ani )
{
  Uni->Pos = VecSet(rand() % 1000, rand() % 700, 0);
  Uni->Color = RGB(rand() % 256, rand() % 256, rand() % 256);
  Uni->PhaseShift = rand() % 3000;
  Uni->ScaleShift = 5 + 0.30 * rand() / RAND_MAX;
  Uni->Amplitude = 30 + 59.0 * rand() / RAND_MAX;
} /* End of 'MC6_AnimUnitInit' function */

/* ������� ��������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT_BALL *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitClose( mc6UNIT_BALL *Uni, mc6ANIM *Ani )
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
static VOID MC6_AnimUnitResponse( mc6UNIT_BALL *Uni, mc6ANIM *Ani )
{
} /* End of 'MC6_AnimUnitResponse' function */

/* ������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT_BALL *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitRender( mc6UNIT_BALL *Uni, mc6ANIM *Ani )
{
  DBL shift = Uni->Amplitude * fabs(sin(Uni->ScaleShift * Ani->Time + Uni->PhaseShift));

  SetDCBrushColor(Ani->hDC, Uni->Color);
  Ellipse(Ani->hDC, Uni->Pos.X - 5, Uni->Pos.Y - 5 - shift, Uni->Pos.X + 5, Uni->Pos.Y + 5 - shift);
} /* End of 'MC6_AnimUnitRender' function */

/* ������� �������� ������� �������� "���".
 * ���������: ���.
 * ������������ ��������:
 *   (mc6UNIT *) ��������� �� ��������� ������ ��������.
 */
mc6UNIT * MC6_UnitBallCreate( VOID )
{
  mc6UNIT_BALL *Uni;

  if ((Uni = (VOID *)MC6_AnimUnitCreate(sizeof(mc6UNIT_BALL))) == NULL)
    return NULL;
  /* ��������� ���� */
  Uni->Init = (VOID *)MC6_AnimUnitInit;
  Uni->Close = (VOID *)MC6_AnimUnitClose;
  Uni->Response = (VOID *)MC6_AnimUnitResponse;
  Uni->Render = (VOID *)MC6_AnimUnitRender;
  return (mc6UNIT *)Uni;
} /* End of 'MC6_UnitBallCreate' function */


/* END OF 'UBALL.C' FILE */
