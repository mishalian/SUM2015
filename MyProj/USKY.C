      /* FILENAME: USKY.C
 * PROGRAMMER: MC6
 * PURPOSE: Sky view unit handle module.
 * LAST UPDATE: 10.06.2015
 */

#include "anim.h"

/* Тип представления мяча */
typedef struct tagmc6UNIT_SKY
{
  MC6_UNIT_BASE_FIELDS;

  mc6PRIM Sky;
  INT TextId;  /* Id текстуры */
} mc6UNIT_SKY;

/* Функция инициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       mc6UNIT_MAP *Uni;
 *   - указатель на контекст анимации:
 *       mc6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID MC6_AnimUnitInit( mc6UNIT_SKY *Uni, mc6ANIM *Ani )
{
  /* загружаем текстуру */
  mc6MATERIAL Mtl = MC6_MtlLib[0];

  MC6_PrimCreateSphere(&Uni->Sky, VecSet(0, 0, 0), 300, 100, 100);
  Mtl.TexId = MC6_TextureLoad("sky.bmp");
  Uni->Sky.MtlNo = Uni->TextId = MC6_MtlAdd(&Mtl);

  MC6_RndPrimMatrConvert = MatrScale(5, 5, 5);
} /* End of 'MC6_AnimUnitInit' function */

/* Функция деинициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       mc6UNIT_SKY *Uni;
 *   - указатель на контекст анимации:
 *       mc6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID MC6_AnimUnitClose( mc6UNIT_SKY *Uni, mc6ANIM *Ani )
{
  MC6_PrimFree(&Uni->Sky);
} /* End of 'MC6_AnimUnitClose' function */

/* Функция построения объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       mc6UNIT_SKY *Uni;
 *   - указатель на контекст анимации:
 *       mc6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */                                                                              
static VOID MC6_AnimUnitRender( mc6UNIT_SKY *Uni, mc6ANIM *Ani )
{
  static DBL rttX = 0, rttY = 0;

  MC6_RndMatrView = MatrView(VecSet(10, 10, 10),
                             VecSet(0, 0, 0),
                             VecSet(0, 1, 0));
  rttY += (Ani->JY - Ani->Keys[VK_UP] + Ani->Keys[VK_DOWN]) * 0.4;
  rttX += (Ani->JX + Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT]) * 0.4;
 
  MC6_RndMatrView = MatrMulMatr(MatrMulMatr(
    MC6_RndMatrView, MatrRotateY(rttX)), MatrRotateX(rttY));

// MC6_RndMatrView = CamUp(MC6_RndMatrView);

  if (Ani->KeysClick['L'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (Ani->KeysClick['O'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Uni->TextId);
  MC6_PrimDraw(&Uni->Sky);
} /* End of 'MC6_AnimUnitRender' function */

/* Функция создания объекта анимации "небо".
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (mc6UNIT *) указатель на созданный объект анимации.
 */
mc6UNIT * MC6_UnitSkyCreate( VOID )
{
  mc6UNIT_SKY *Uni;

  if ((Uni = (VOID *)MC6_AnimUnitCreate(sizeof(mc6UNIT_SKY))) == NULL)
    return NULL;
  /* заполняем поля */
  Uni->Init = (VOID *)MC6_AnimUnitInit;
  Uni->Close = (VOID *)MC6_AnimUnitClose;
  Uni->Render = (VOID *)MC6_AnimUnitRender;
  return (mc6UNIT *)Uni;
} /* End of 'MC6_UnitSkyCreate' function */

/* END OF 'USKY.C' FILE */
