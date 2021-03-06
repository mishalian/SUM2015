/* FILENAME: GEOM.C
 * PROGRAMMER: MC6
 * PURPOSE: Rendering system implementation module.
 * LAST UPDATE: 13.06.2015
 */

#include <stdio.h>
#include <stdlib.h>

#include "render.h"

/* ������� ���������� ��������� � ��������������� �������.
 * ���������:
 *   - ��������� �� �������������� ������:
 *       mc6GEOM *G;
 *   - ��������� �� ����������� ��������:
 *       mc6PRIM *Prim;
 * ������������ ��������:
 *   (INT) ����� ������������ ��������� � ������� (-1 ��� ������).
 */
INT MC6_GeomAddPrim( mc6GEOM *G, mc6PRIM *Prim )
{
  mc6PRIM *new_bulk;

  /* �������� ������ ��� ����� ������ ���������� */
  if ((new_bulk = malloc(sizeof(mc6PRIM) * (G->NumOfPrimitives + 1))) == NULL)
    return -1;

  /* �������� ������ ��������� */
  if (G->Prims != NULL)
  {
    memcpy(new_bulk, G->Prims, sizeof(mc6PRIM) * G->NumOfPrimitives);
    free(G->Prims);
  }
  /* ��������� �� ����� ������ ���������� */
  G->Prims = new_bulk;

  /* ��������� ����� ������� */
  G->Prims[G->NumOfPrimitives] = *Prim;
  return G->NumOfPrimitives++;
} /* End of 'MC6_GeomAddPrim' function */

/* ������� ������������ ��������������� �������.
 * ���������:
 *   - ��������� �� �������������� ������:
 *       mc6GEOM *G;
 * ������������ ��������: ���.
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

/* ������� ����������� ��������������� �������.
 * ���������:
 *   - ��������� �� �������������� ������:
 *       mc6GEOM *G;
 * ������������ ��������: ���.
 */
VOID MC6_GeomDraw( mc6GEOM *G )
{
  INT i, loc;

  /* �������� ���������� ������ */
  glUseProgram(MC6_RndProg);
  loc = glGetUniformLocation(MC6_RndProg, "TotalParts");
  if (loc != -1)
    glUniform1f(loc, G->NumOfPrimitives);
  glUseProgram(0);

  /* ������ ������������ ������� */
  for (i = 0; i < G->NumOfPrimitives; i++)
    if (MC6_MtlLib[G->Prims[i].MtlNo].Kt == 1)
    {
      /* �������� ����� ������� ����� */
      glUseProgram(MC6_RndProg);
      loc = glGetUniformLocation(MC6_RndProg, "PartNo");
      if (loc != -1)
        glUniform1f(loc, i);
      glUseProgram(0);
      MC6_PrimDraw(&G->Prims[i]);
    }

  /* ������ ���������� ������� */
  for (i = 0; i < G->NumOfPrimitives; i++)
    if (MC6_MtlLib[G->Prims[i].MtlNo].Kt != 1)
    {
      /* �������� ����� ������� ����� */
      glUseProgram(MC6_RndProg);
      loc = glGetUniformLocation(MC6_RndProg, "PartNo");
      if (loc != -1)
        glUniform1f(loc, i);
      glUseProgram(0);
      MC6_PrimDraw(&G->Prims[i]);
    }
} /* End of 'MC6_GeomDraw' function */

/* ������� �������� ��������������� ������� �� G3D �����.
 * ���������:
 *   - ��������� �� �������������� ������:
 *       mc6GEOM *G;
 *   - ��� �����:
 *       CHAR *FileName;
 * ������������ ��������:
 *   (BOOL) TRUE ��� ������, ����� - FALSE.
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

  /* ������ ��������� */
  fread(Sign, 1, 4, F);
  if (*(DWORD *)Sign != *(DWORD *)"G3D")
  {
    fclose(F);
    return FALSE;
  }

  /* ������ ���������� ���������� � ������� */
  fread(&n, 4, 1, F);
  fread(MtlName, 1, 300, F);

  /* ������ � ��������� ���������� ���������� */
  _makepath(path_buffer, drive, dir, MtlName, "");
  MC6_MtlLoad(path_buffer);

  /* ������ ��������� */
  for (i = 0; i < n; i++)
  {
    INT nv, ni, *Ind;
    mc6VERTEX *Vert;
    mc6PRIM P;

    /* ������ ���������� ������ � �������� */
    fread(&nv, 4, 1, F);
    fread(&ni, 4, 1, F);
    /* ������ ��� ��������� �������� ��������� */
    fread(MtlName, 1, 300, F);

    /* �������� ������ ��� ������� � ������� */
    if ((Vert = malloc(sizeof(mc6VERTEX) * nv + sizeof(INT) * ni)) == NULL)
      break;
    Ind = (INT *)(Vert + nv);

    /* ������ ������ */
    fread(Vert, sizeof(mc6VERTEX), nv, F);
    /* ������������ ��������� */
    for (j = 0; j < nv; j++)
    {
      Vert[j].P = VecMulMatr(Vert[j].P, MC6_RndPrimMatrConvert);
      Vert[j].N = VecMulMatr3(Vert[j].N, M);
    }
    fread(Ind, sizeof(INT), ni, F);

    /* ������� � �������� */
    MC6_PrimCreate(&P, MC6_PRIM_TRIMESH, nv, ni, Vert, Ind);
    P.MtlNo = MC6_MtlFind(MtlName);

    free(Vert);

    /* ��������� �������� � ������� */
    MC6_GeomAddPrim(G, &P);
  }
  fclose(F);
  MC6_RndPrimMatrConvert = MatrIdentity();
  return TRUE;
} /* End of 'MC6_GeomDraw' function */

/* END OF 'GEOM.C' FILE */
