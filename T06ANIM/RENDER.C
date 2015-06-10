/* FILENAME: RENDER.C
 * PROGRAMMER: MC6
 * PURPOSE: Rendering system module.
 * LAST UPDATE: 09.06.2015
 */

#include <stdio.h>
#include <string.h>

#include "anim.h"
#include "render.h"

/* Матрицы */
MATR
  MC6_RndMatrWorld = MC6_UNIT_MATR,
  MC6_RndMatrView = MC6_UNIT_MATR,
  MC6_RndMatrWorldView = MC6_UNIT_MATR;

/* Параметры проецирования */
DBL
  MC6_RndWp = 3, MC6_RndHp = 3,     /* размеры обрасти проецирования */
  MC6_RndProjDist = 5;              /* расстояние до плоскости проекции */

/* Функция преобразования из мировой системы координат в кадр.
 * АРГУМЕНТЫ:
 *   - исходная точка:
 *       VEC P;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (POINT) координаты в кадре.
 */
POINT MC6_RndWorldToScreen( VEC P )
{
  POINT Ps;
  VEC Pp;

  /* преобразование СК */
  P = VectorTransform(P, MC6_RndMatrWorldView);

  Pp.X = P.X * MC6_RndProjDist / P.Z;
  Pp.Y = P.Y * MC6_RndProjDist / P.Z;

  Ps.x = MC6_Anim.W / 2 + Pp.X * MC6_Anim.W / MC6_RndWp;
  Ps.y = MC6_Anim.H / 2 - Pp.Y * MC6_Anim.H / MC6_RndHp;

  return Ps;
} /* End of 'MC6_RndWorldToScreen' function */


/* Функция загрузки геометрического объекта.
 * АРГУМЕНТЫ:
 *   - структура объекта для загрузки:
 *       mc6GOBJ *GObj;
 *   - имя файла:
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (BOOL) TRUE при успехе, FALSE иначе.
 */
BOOL MC6_RndGObjLoad( mc6GOBJ *GObj, CHAR *FileName )
{
  FILE *F;
  INT nv = 0, nf = 0;
  static CHAR Buf[10000];

  memset(GObj, 0, sizeof(mc6GOBJ));
  /* Open file */
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertices */
  while (fgets(Buf, sizeof(Buf), F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      nf++;
  }

  /* Allocate memory for data */
  if ((GObj->V = malloc(sizeof(VEC) * nv + sizeof(INT [3]) * nf)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  GObj->F = (INT (*)[3])(GObj->V + nv);

  /* Read vertices */
  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf), F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      sscanf(Buf + 2, "%lf%lf%lf",
        &GObj->V[nv].X, &GObj->V[nv].Y, &GObj->V[nv].Z);
      nv++;
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT a, b, c;

      sscanf(Buf + 2, "%i/%*i/%*i %i/%*i/%*i %i/%*i/%*i", &a, &b, &c) == 3 ||
        sscanf(Buf + 2, "%i//%*i %i//%*i %i//%*i", &a, &b, &c) == 3 ||
        sscanf(Buf + 2, "%i/%*i %i/%*i %i/%*i", &a, &b, &c) == 3 ||
        sscanf(Buf + 2, "%i %i %i", &a, &b, &c);

      GObj->F[nf][0] = a - 1;
      GObj->F[nf][1] = b - 1;
      GObj->F[nf][2] = c - 1;
      nf++;
    }
  }

  fclose(F);

  GObj->NumOfV = nv;
  GObj->NumOfF = nf;
  return TRUE;
} /* End of 'MC6_RndGObjLoad' function */

/* Функция отрисовки геометрического объекта.
 * АРГУМЕНТЫ:
 *   - структура объекта для загрузки:
 *       mc6GOBJ *GObj;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_RndGObjDraw( mc6GOBJ *GObj )
{
  INT i;
  POINT *pnts;

  if ((pnts = malloc(sizeof(POINT) * GObj->NumOfV)) == NULL)
    return;

  /* проецируем все точки */
  MC6_RndMatrWorldView = MatrMulMatr(MC6_RndMatrWorld, MC6_RndMatrView);
  for (i = 0; i < GObj->NumOfV; i++)
    pnts[i] = MC6_RndWorldToScreen(GObj->V[i]);

  /* рисуем треугольники */
  for (i = 0; i < GObj->NumOfF; i++)
  {                                                             
    INT
      n1 = GObj->F[i][0],
      n2 = GObj->F[i][1],
      n3 = GObj->F[i][2];

    MoveToEx(MC6_Anim.hDC, pnts[n1].x, pnts[n1].y, NULL);
    LineTo(MC6_Anim.hDC, pnts[n2].x, pnts[n2].y);
    LineTo(MC6_Anim.hDC, pnts[n3].x, pnts[n3].y);
    LineTo(MC6_Anim.hDC, pnts[n1].x, pnts[n1].y);
  }

  free(pnts);
} /* End of 'MC6_RndGObjDraw' function */

/* Функция освобождения памяти из-под геометрического объекта.
 * АРГУМЕНТЫ:
 *   - структура объекта для загрузки:
 *       mc6GOBJ *GObj;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_RndGObjFree( mc6GOBJ *GObj )
{
  free(GObj->V);
  memset(GObj, 0, sizeof(mc6GOBJ));
} /* End of 'MC6_RndGObjFree' function */

/* END OF 'RENDER.C' FILE */

