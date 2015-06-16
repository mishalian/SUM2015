/* FILENAME: UNIT.C
 * PROGRAMMER: MC6
 * PURPOSE: Animation unit handle module.
 * LAST UPDATE: 10.06.2015
 */

#include <string.h>

#include "anim.h"

/* Функция по-умолчанию инициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       mc6UNIT *Uni;
 *   - указатель на контекст анимации:
 *       mc6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID MC6_AnimUnitInit( mc6UNIT *Uni, mc6ANIM *Ani )
{
} /* End of 'MC6_AnimUnitInit' function */

/* Функция по-умолчанию деинициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       mc6UNIT *Uni;
 *   - указатель на контекст анимации:
 *       mc6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID MC6_AnimUnitClose( mc6UNIT *Uni, mc6ANIM *Ani )
{
} /* End of 'MC6_AnimUnitClose' function */

/* Функция по-умолчанию обновления межкадровых параметров объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       mc6UNIT *Uni;
 *   - указатель на контекст анимации:
 *       mc6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID MC6_AnimUnitResponse( mc6UNIT *Uni, mc6ANIM *Ani )
{
} /* End of 'MC6_AnimUnitResponse' function */

/* Функция по-умолчанию построения объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       mc6UNIT *Uni;
 *   - указатель на контекст анимации:
 *       mc6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID MC6_AnimUnitRender( mc6UNIT *Uni, mc6ANIM *Ani )
{
} /* End of 'MC6_AnimUnitRender' function */

/* Функция создания объекта анимации.
 * АРГУМЕНТЫ:
 *   - размер структуры объекта анимации:
 *       INT Size;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (mc6UNIT *) указатель на созданный объект анимации.
 */
mc6UNIT * MC6_AnimUnitCreate( INT Size )
{
  mc6UNIT *Uni;

  if (Size < sizeof(mc6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* заполняем поля по-умолчанию */
  Uni->Size = Size;
  Uni->Init = MC6_AnimUnitInit;
  Uni->Close = MC6_AnimUnitClose;
  Uni->Response = MC6_AnimUnitResponse;
  Uni->Render = MC6_AnimUnitRender;
  return Uni;
} /* End of 'MC6_AnimUnitCreate' function */

/* END OF 'UNIT.C' FILE */
