/* FILENAME: UMODEL.C
 * PROGRAMMER: MC6
 * PURPOSE: Model view unit handle module.
 * LAST UPDATE: 10.06.2015
 */

#include "anim.h"

/* Тип представления мяча */
typedef struct tagmc6UNIT_MODEL
{
  MC6_UNIT_BASE_FIELDS;

  mc6GOBJ Model; /* Модель для отображения */
} mc6UNIT_MODEL;

/* Функция инициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       mc6UNIT_MODEL *Uni;
 *   - указатель на контекст анимации:
 *       mc6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID MC6_AnimUnitInit( mc6UNIT_MODEL *Uni, mc6ANIM *Ani )
{
  MC6_RndGObjLoad(&Uni->Model, "cow.object");
} /* End of 'MC6_AnimUnitInit' function */

/* Функция деинициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       mc6UNIT_MODEL *Uni;
 *   - указатель на контекст анимации:
 *       mc6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID MC6_AnimUnitClose( mc6UNIT_MODEL *Uni, mc6ANIM *Ani )
{
  MC6_RndGObjFree(&Uni->Model);
} /* End of 'MC6_AnimUnitClose' function */

/* Функция построения объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       mc6UNIT_MODEL *Uni;
 *   - указатель на контекст анимации:
 *       mc6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID MC6_AnimUnitRender( mc6UNIT_MODEL *Uni, mc6ANIM *Ani )
{
  INT i, j;
  static DBL rtte = 1;

  MC6_RndMatrView = MatrView(VecSet(8, 8, 8),
                             VecSet(0, 0, 0),
                             VecSet(0, 1, 0));

  if (Ani->KeysClick['W'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (Ani->KeysClick['Q'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);

  if (Ani->JButs[6])
    rtte++;
  if (Ani->JButs[7])
    rtte--;

  for (i = 0; i < 1; i++)
    for (j = 0; j < 1; j++)
    {
      MC6_RndMatrWorld =
        MatrMulMatr(MatrMulMatr(MatrMulMatr(
          MatrTranslate(Ani->JX * 59, Ani->JZ * 88, 0),
          MatrScale(0.1, 0.1, 0.1)),
          MatrRotateY(rtte)),
          MatrTranslate(j * 1.30, 0, i * 1.30 + 100 * Ani->JY));
      glColor3d(i & 1, j & 1, 1 - ((i & 1) + (j & 1)) / 2);
      MC6_RndGObjDraw(&Uni->Model);
    }
} /* End of 'MC6_AnimUnitRender' function */

/* Функция создания объекта анимации "модель".
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (mc6UNIT *) указатель на созданный объект анимации.
 */
mc6UNIT * MC6_UnitModelCreate( VOID )
{
  mc6UNIT_MODEL *Uni;

  if ((Uni = (VOID *)MC6_AnimUnitCreate(sizeof(mc6UNIT_MODEL))) == NULL)
    return NULL;
  /* заполняем поля */
  Uni->Init = (VOID *)MC6_AnimUnitInit;
  Uni->Close = (VOID *)MC6_AnimUnitClose;
  Uni->Render = (VOID *)MC6_AnimUnitRender;
  return (mc6UNIT *)Uni;
} /* End of 'MC6_UnitModelCreate' function */

/* END OF 'UMODEL.C' FILE */
