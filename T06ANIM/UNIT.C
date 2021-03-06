/* FILENAME: UNIT.C
 * PROGRAMMER: MC6
 * PURPOSE: Animation unit handle module.
 * LAST UPDATE: 08.06.2015
 */

#include <string.h>

#include "anim.h"

/* ������� ��-��������� ������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitInit( mc6UNIT *Uni, mc6ANIM *Ani )
{
} /* End of 'MC6_AnimUnitInit' function */

/* ������� ��-��������� ��������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitClose( mc6UNIT *Uni, mc6ANIM *Ani )
{
} /* End of 'MC6_AnimUnitClose' function */

/* ������� ��-��������� ���������� ����������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitResponse( mc6UNIT *Uni, mc6ANIM *Ani )
{
} /* End of 'MC6_AnimUnitResponse' function */

/* ������� ��-��������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitRender( mc6UNIT *Uni, mc6ANIM *Ani )
{
} /* End of 'MC6_AnimUnitRender' function */

/* ������� �������� ������� ��������.
 * ���������:
 *   - ������ ��������� ������� ��������:
 *       INT Size;
 * ������������ ��������:
 *   (mc6UNIT *) ��������� �� ��������� ������ ��������.
 */
mc6UNIT * MC6_AnimUnitCreate( INT Size )
{
  mc6UNIT *Uni;

  if (Size < sizeof(mc6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* ��������� ���� ��-��������� */
  Uni->Size = Size;
  Uni->Init = MC6_AnimUnitInit;
  Uni->Close = MC6_AnimUnitClose;
  Uni->Response = MC6_AnimUnitResponse;
  Uni->Render = MC6_AnimUnitRender;
  return Uni;
} /* End of 'MC6_AnimUnitCreate' function */

/* END OF 'UNIT.C' FILE */
