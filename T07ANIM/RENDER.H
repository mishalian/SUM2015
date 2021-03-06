/* FILENAME: RENDER.H
 * PROGRAMMER: MC6
 * PURPOSE: Rendering system declaration module.
 * LAST UPDATE: 13.06.2015
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#include "vec.h"

#define GLEW_STATIC
#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

/* ������� */
extern MATR
  MC6_RndMatrWorld,
  MC6_RndMatrView,
  MC6_RndMatrProj,
  MC6_RndMatrWorldViewProj;

/* ������� ��������� ��������� ��� �������� */
extern MATR MC6_RndPrimMatrConvert;

/* ��������� ������������� */
extern DBL
  MC6_RndWp, MC6_RndHp,    /* ������� ������� ������������� */
  MC6_RndProjDist;         /* ���������� �� ��������� �������� */

/* ������ �� ��������� */
extern UINT MC6_RndProg;

/* ������� �������� �������� ��� ����� ���������.
 * ���������:
 *   - ������� ����� �����:
 *       CHAR *FileNamePrefix;
 * ������������ ��������:
 *   (UINT) ����� ����������� ���������.
 */
UINT MC6_ShaderLoad( CHAR *FileNamePrefix );

/* ������� ����������� �������� ��� ���������.
 * ���������:
 *   - ����� ���������:
 *       UINT PrgId;
 * ������������ ��������: ���.
 */
VOID MC6_ShaderFree( UINT PrgId );

/***
 * ������ � �����������
 ***/

/* ��� ������� ��������� ����������� */
typedef struct tagmc6MATERIAL
{
  /* ��� ��������� */
  CHAR Name[300];

  /* ������������ ��������� */
  VEC Ka, Kd, Ks;
  FLT Kp; /* ������� "����������" */

  /* ����������� ������������ */
  FLT Kt;

  /* �������� ����������� */
  INT TexId;
} mc6MATERIAL;

/* ���������� ������� ���������� */
#define MC6_MATERIAL_MAX 300
extern INT MC6_MtlLibSize;
extern mc6MATERIAL MC6_MtlLib[MC6_MATERIAL_MAX];

/* ������� ���������� ��������� � ����������.
 * ���������:
 *   - ��������� � ����������� ���������:
 *       mc6MATERIAL *Mtl;
 * ������������ ��������:
 *   (INT) ���������� ����� ������������ ��������� (0 ��� ������).
 */
INT MC6_MtlAdd( mc6MATERIAL *Mtl );

/* ������� ������ ��������� �� �����.
 * ���������:
 *   - ��� ���������:
 *       CHAR *Name;
 * ������������ ��������:
 *   (INT) ���������� ����� ���������� ��������� (0 ��� ������).
 */
INT MC6_MtlFind( CHAR *Name );

/* ������� �������� ��������� �� ����� (*.MTL).
 * ���������:
 *   - ��� ����� ���������:
 *       CHAR *FileName;
 * ������������ ��������:
 *   (INT) ���������� ����������� ����������.
 */
INT MC6_MtlLoad( CHAR *FileName );

/***
 * ������ � �����������
 ***/

/* ���� ���������� */
typedef enum tagmc6PRIM_TYPE
{
  MC6_PRIM_TRIMESH,  /* �������� - ����� ������������� */
  MC6_PRIM_GRID      /* ���������� ����� ������������� (����� triangle strip) */
} mc6PRIM_TYPE;

/* ��� �������� ��������� */
typedef struct tagmc6PRIM
{
  mc6PRIM_TYPE Type; /* ��� ��������� (MC6_PRIM_***) */
  INT
    VA,          /* ������ ������ */
    VBuf, IBuf,  /* ������ ������ � �������� */
    NumOfI,      /* ���������� �������� ��� ������ ��������� */
    MtlNo;       /* ����� ��������� �� ���������� */
} mc6PRIM;

/* ��� �������� ���������� ��������� */
typedef struct tagmc6UV
{
  FLT U, V; /* ���������� ���������� */
} mc6UV;

/* ������� ������� ���������� ���������.
 * ���������:
 *   - ����� ������� ���������:
 *       FLT U, V;
 * ������������ ��������:
 *   (mc6UV) ����������� ����������.
 */
__inline mc6UV UVSet( FLT U, FLT V )
{
  mc6UV UV = {U, V};

  return UV;
} /* End of 'UVSet' function */

/* ��� �������� ����� ������� ���������� */
typedef struct tagmc6VERTEX
{
  VEC P;    /* ������� ������� */
  mc6UV T;  /* ���������� ���������� ������� */
  VEC N;    /* ������� � ������� */
  COLOR C;  /* ���� ������� */
} mc6VERTEX;

/* ������� �������� ���������.
 * ���������:
 *   - ��������� �� ��������:
 *       mc6PRIM *Prim;
 *   - ��� ��������� (MC6_PRIM_***):
 *       mc6PRIM_TYPE Type;
 *   - ���������� ������ � ��������:
 *       INT NoofV, NoofI;
 *   - ������ ������:
 *       mc6VERTEX *Vertices;
 *   - ������ ��������:
 *       INT *Indices;
 * ������������ ��������: ���.
 */
VOID MC6_PrimCreate( mc6PRIM *Prim, mc6PRIM_TYPE Type,
                     INT NoofV, INT NoofI, mc6VERTEX *Vertices, INT *Indices);

/* ������� �������� ���������.
 * ���������:
 *   - ��������� �� ��������:
 *       mc6PRIM *Prim;
 * ������������ ��������: ���.
 */
VOID MC6_PrimFree( mc6PRIM *Prim );

/* ������� ��������� ���������.
 * ���������:
 *   - ��������� �� ��������:
 *       mc6PRIM *Prim;
 * ������������ ��������: ���.
 */
VOID MC6_PrimDraw( mc6PRIM *Prim );

/* ������� �������� ��������� ���������.
 * ���������:
 *   - ��������� �� ��������:
 *       mc6PRIM *Prim;
 *   - ����������� �������-�������:
 *       VEC Du, Dv;
 *   - ���������:
 *       INT N, M;
 * ������������ ��������:
 *   (BOOL) TRUE ��� ������, ����� FALSE.
 */
BOOL MC6_PrimCreatePlane( mc6PRIM *Prim, VEC Du, VEC Dv, INT N, INT M );

/* ������� �������� ��������� �����.
 * ���������:
 *   - ��������� �� ��������:
 *       mc6PRIM *Prim;
 *   - ����� �����:
 *       VEC �;
 *   - ������ �����:
 *       FLT R;
 *   - ���������:
 *       INT N, M;
 * ������������ ��������:
 *   (BOOL) TRUE ��� ������, ����� FALSE.
 */
BOOL MC6_PrimCreateSphere( mc6PRIM *Prim, VEC C, FLT R, INT N, INT M );

/* ������� �������� ��������������� �������.
 * ���������:
 *   - ��������� ������� ��� ��������:
 *       mc6PRIM *GObj;
 *   - ��� �����:
 *       CHAR *FileName;
 * ������������ ��������:
 *   (BOOL) TRUE ��� ������, FALSE �����.
 */
BOOL MC6_PrimLoad( mc6PRIM *GObj, CHAR *FileName );

/***
 * ������ � ��������������� ���������
 ***/

/* �������������� ������ - ����� ���������� */
typedef struct tagmc6GEOM
{
  INT NumOfPrimitives; /* ���������� ���������� */
  mc6PRIM *Prims;      /* ������ ���������� */
} mc6GEOM;

/* ������� ���������� ��������� � ��������������� �������.
 * ���������:
 *   - ��������� �� �������������� ������:
 *       mc6GEOM *G;
 *   - ��������� �� ����������� ��������:
 *       mc6PRIM *Prim;
 * ������������ ��������:
 *   (INT) ����� ������������ ��������� � ������� (-1 ��� ������).
 */
INT MC6_GeomAddPrim( mc6GEOM *G, mc6PRIM *Prim );

/* ������� ������������ ��������������� �������.
 * ���������:
 *   - ��������� �� �������������� ������:
 *       mc6GEOM *G;
 * ������������ ��������: ���.
 */
VOID MC6_GeomFree( mc6GEOM *G );

/* ������� ����������� ��������������� �������.
 * ���������:
 *   - ��������� �� �������������� ������:
 *       mc6GEOM *G;
 * ������������ ��������: ���.
 */
VOID MC6_GeomDraw( mc6GEOM *G );

/* ������� �������� ��������������� ������� �� G3D �����.
 * ���������:
 *   - ��������� �� �������������� ������:
 *       mc6GEOM *G;
 *   - ��� �����:
 *       CHAR *FileName;
 * ������������ ��������:
 *   (BOOL) TRUE ��� ������, ����� - FALSE.
 */
BOOL MC6_GeomLoad( mc6GEOM *G, CHAR *FileName );

/* ������� �������� ��������.
 * ���������:
 *   - ��� �����:
 *       CHAR *FileName;
 * ������������ ��������:
 *   (INT ) ������������� OpenGL ��� ��������.
 */
INT MC6_TextureLoad( CHAR *FileName );

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
