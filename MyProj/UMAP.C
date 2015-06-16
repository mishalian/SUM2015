/* FILENAME: UMAP.C
 * PROGRAMMER: MC6
 * PURPOSE: Map view unit handle module.
 * LAST UPDATE: 10.06.2015
 */

#include "anim.h"

/* Тип представления мяча */
typedef struct tagmc6UNIT_MAP
{
  MC6_UNIT_BASE_FIELDS;

  mc6PRIM Map;
  INT TextId;  /* Id текстуры */
} mc6UNIT_MAP;

/* Функция инициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       mc6UNIT_MAP *Uni;
 *   - указатель на контекст анимации:
 *       mc6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID MC6_AnimUnitInit( mc6UNIT_MAP *Uni, mc6ANIM *Ani )
{
  VEC
    Du = {1, 0, 0}, Dv = {0, 0, -1};
  DBL Scale = 1;
  INT I[] = {0, 1, 2, 2, 1, 3};
  BYTE txt[2][2][3] =
  {
    {{255, 255, 255}, {0, 0, 0}},
    {{0, 0, 0}, {255, 255, 255}}
  };

  /* загружаем текстуру */
  Uni->TextId = MC6_TextureLoad("htex.bmp");

  MC6_PrimCreateHeightField(mc6UNIT_MAP, Loc, Du, Dv, Scale, "heigt.bmp");

  MC6_RndPrimMatrConvert = MatrScale(5, 5, 5);
} /* End of 'MC6_AnimUnitInit' function */

/* Функция деинициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       mc6UNIT_MAP *Uni;
 *   - указатель на контекст анимации:
 *       mc6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID MC6_AnimUnitClose( mc6UNIT_MAP *Uni, mc6ANIM *Ani )
{
  MC6_GeomFree(&Uni->Map);
  MC6_GeomFree(&Uni->Geom);
  MC6_PrimFree(&Uni->Pr);
} /* End of 'MC6_AnimUnitClose' function */

/* Функция построения объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       mc6UNIT_MAP *Uni;
 *   - указатель на контекст анимации:
 *       mc6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID MC6_AnimUnitRender( mc6UNIT_MAP *Uni, mc6ANIM *Ani )
{
  INT i, j;

  MC6_RndMatrView = MatrView(VecSet(50, 50, 50),
                             VecSet(0, 0, 0),
                             VecSet(0, 1, 0));

  if (Ani->KeysClick['W'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (Ani->KeysClick['Q'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);

  for (i = 0; i < 1; i++)
    for (j = 0; j < 1; j++)
    {
      MC6_RndMatrWorld =
        MatrMulMatr(MatrMulMatr(MatrMulMatr(
          MatrTranslate(Ani->JX * 59, Ani->JY * 88, 0),
          MatrScale(0.1, 0.1, 0.1)),
          MatrRotateY(30 * Ani->Time + Ani->JR * 180)),
          MatrTranslate(j * 1.30, 0, i * 1.30 + 100 * Ani->JZ));
      glColor3d(i & 1, j & 1, 1 - ((i & 1) + (j & 1)) / 2);
      MC6_GeomDraw(&Uni->Map);
    }
  MC6_RndMatrWorld = MatrRotateY(30 * Ani->Time);
  //MatrMulMatr(MatrRotateZ(30 * sin(Ani->Time * 3.0)), MatrRotateY(30 * Ani->Time));
  MC6_GeomDraw(&Uni->Geom);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Uni->TextId);
  MC6_PrimDraw(&Uni->Pr);
} /* End of 'MC6_AnimUnitRender' function */

/* Функция создания объекта анимации "модель".
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (mc6UNIT *) указатель на созданный объект анимации.
 */
mc6UNIT * MC6_UnitMapCreate( VOID )
{
  mc6UNIT_MAP *Uni;

  if ((Uni = (VOID *)MC6_AnimUnitCreate(sizeof(mc6UNIT_MAP))) == NULL)
    return NULL;
  /* заполняем поля */
  Uni->Init = (VOID *)MC6_AnimUnitInit;
  Uni->Close = (VOID *)MC6_AnimUnitClose;
  Uni->Render = (VOID *)MC6_AnimUnitRender;
  return (mc6UNIT *)Uni;
} /* End of 'MC6_UnitMapCreate' function */

/* END OF 'UMAP.C' FILE */
