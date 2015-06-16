/* FILENAME: GEOM.C
 * PROGRAMMER: MC6
 * PURPOSE: Rendering system implementation module.
 * LAST UPDATE: 13.06.2015
 */

#include <stdio.h>
#include <stdlib.h>

#include "render.h"

/* Функция добавления примитива к геометрическому объекту.
 * АРГУМЕНТЫ:
 *   - указатель на геометрический объект:
 *       mc6GEOM *G;
 *   - указатель на добавляемый примитив:
 *       mc6PRIM *Prim;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (INT) номер добавленного примитива в массиве (-1 при ошибке).
 */
INT MC6_GeomAddPrim( mc6GEOM *G, mc6PRIM *Prim )
{
  mc6PRIM *new_bulk;

  /* Выделяем память под новый массив примитивов */
  if ((new_bulk = malloc(sizeof(mc6PRIM) * (G->NumOfPrimitives + 1))) == NULL)
    return -1;

  /* Копируем старые примитивы */
  if (G->Prims != NULL)
  {
    memcpy(new_bulk, G->Prims, sizeof(mc6PRIM) * G->NumOfPrimitives);
    free(G->Prims);
  }
  /* указываем на новый массив примитивлв */
  G->Prims = new_bulk;

  /* Сохраняем новый элемент */
  G->Prims[G->NumOfPrimitives] = *Prim;
  return G->NumOfPrimitives++;
} /* End of 'MC6_GeomAddPrim' function */

/* Функция освобождения геометрического объекта.
 * АРГУМЕНТЫ:
 *   - указатель на геометрический объект:
 *       mc6GEOM *G;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_GeomFree( mc6GEOM *G )
{
  INT i;

  if (G->Prims != NULL)
  {
    for (i = 0; i < G->NumOfPrimitives; i++)
      MC6_PrimFree(&G->Prims[i]);
    free(G->Prims);
  }
  memset(G, 0, sizeof(mc6GEOM));
} /* End of 'MC6_GeomFree' function */

/* Функция отображения геометрического объекта.
 * АРГУМЕНТЫ:
 *   - указатель на геометрический объект:
 *       mc6GEOM *G;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_GeomDraw( mc6GEOM *G )
{
  INT i, loc;

  /* посылаем количество частей */
  glUseProgram(MC6_RndProg);
  loc = glGetUniformLocation(MC6_RndProg, "TotalParts");
  if (loc != -1)
    glUniform1f(loc, G->NumOfPrimitives);
  glUseProgram(0);

  /* рисуем непрозрачные объекты */
  for (i = 0; i < G->NumOfPrimitives; i++)
    if (MC6_MtlLib[G->Prims[i].MtlNo].Kt == 1)
    {
      /* посылаем номер текущей части */
      glUseProgram(MC6_RndProg);
      loc = glGetUniformLocation(MC6_RndProg, "PartNo");
      if (loc != -1)
        glUniform1f(loc, i);
      glUseProgram(0);
      MC6_PrimDraw(&G->Prims[i]);
    }

  /* рисуем прозрачные объекты */
  for (i = 0; i < G->NumOfPrimitives; i++)
    if (MC6_MtlLib[G->Prims[i].MtlNo].Kt != 1)
    {
      /* посылаем номер текущей части */
      glUseProgram(MC6_RndProg);
      loc = glGetUniformLocation(MC6_RndProg, "PartNo");
      if (loc != -1)
        glUniform1f(loc, i);
      glUseProgram(0);
      MC6_PrimDraw(&G->Prims[i]);
    }
} /* End of 'MC6_GeomDraw' function */

/* Функция загрузки геометрического объекта из G3D файла.
 * АРГУМЕНТЫ:
 *   - указатель на геометрический объект:
 *       mc6GEOM *G;
 *   - имя файла:
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (BOOL) TRUE при успехе, иначе - FALSE.
 */
BOOL MC6_GeomLoad( mc6GEOM *G, CHAR *FileName )
{
  FILE *F;
  INT i, j, n;
  CHAR Sign[4];
  MATR M;
  static CHAR MtlName[300];
  static CHAR
    path_buffer[_MAX_PATH],
    drive[_MAX_DRIVE],
    dir[_MAX_DIR],
    fname[_MAX_FNAME],
    ext[_MAX_EXT];

  _splitpath(FileName, drive, dir, fname, ext);

  memset(G, 0, sizeof(mc6GEOM));
  if ((F = fopen("avent.g3d", "rb")) == NULL)
    return FALSE;

  M = MatrTranspose(MatrInverse(MC6_RndPrimMatrConvert));

  /* читаем сигнатуру */
  fread(Sign, 1, 4, F);
  if (*(DWORD *)Sign != *(DWORD *)"G3D")
  {
    fclose(F);
    return FALSE;
  }

  /* читаем количество примитивов в объекте */
  fread(&n, 4, 1, F);
  fread(MtlName, 1, 300, F);

  /* читаем и загружаем библиотеку материалов */
  _makepath(path_buffer, drive, dir, MtlName, "");
  MC6_MtlLoad(path_buffer);

  /* читаем примитивы */
  for (i = 0; i < n; i++)
  {
    INT nv, ni, *Ind;
    mc6VERTEX *Vert;
    mc6PRIM P;

    /* читаем количество вершин и индексов */
    fread(&nv, 4, 1, F);
    fread(&ni, 4, 1, F);
    /* читаем имя материала текущего примитива */
    fread(MtlName, 1, 300, F);

    /* выделяем память под вершины и индексы */
    if ((Vert = malloc(sizeof(mc6VERTEX) * nv + sizeof(INT) * ni)) == NULL)
      break;
    Ind = (INT *)(Vert + nv);

    /* читаем данные */
    fread(Vert, sizeof(mc6VERTEX), nv, F);
    /* конвертируем геометрию */
    for (j = 0; j < nv; j++)
    {
      Vert[j].P = VecMulMatr(Vert[j].P, MC6_RndPrimMatrConvert);
      Vert[j].N = VecMulMatr3(Vert[j].N, M);
    }
    fread(Ind, sizeof(INT), ni, F);

    /* заносим в примитив */
    MC6_PrimCreate(&P, MC6_PRIM_TRIMESH, nv, ni, Vert, Ind);
    P.MtlNo = MC6_MtlFind(MtlName);

    free(Vert);

    /* добавляем примитив к объекту */
    MC6_GeomAddPrim(G, &P);
  }
  fclose(F);
  MC6_RndPrimMatrConvert = MatrIdentity();
  return TRUE;
} /* End of 'MC6_GeomDraw' function */

/* END OF 'GEOM.C' FILE */
