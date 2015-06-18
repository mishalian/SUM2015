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

/* Матрицы */
extern MATR
  MC6_RndMatrWorld,
  MC6_RndMatrView,
  MC6_RndMatrProj,
  MC6_RndMatrWorldViewProj;

/* Матрица изменения примитива при создании */
extern MATR MC6_RndPrimMatrConvert;

/* Параметры проецирования */
extern DBL
  MC6_RndWp, MC6_RndHp,    /* размеры обрасти проецирования */
  MC6_RndProjDist;         /* расстояние до плоскости проекции */

/* Шейдер по умолчанию */
extern UINT MC6_RndProg, MC6_SkyProg;

/* Функция загрузки шейдеров для одной программы.
 * АРНУМЕНТЫ:
 *   - префикс имени файла:
 *       CHAR *FileNamePrefix;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (UINT) номер загруженной программы.
 */
UINT MC6_ShaderLoad( CHAR *FileNamePrefix );

/* Функция уничтодения шейдеров для программы.
 * АРНУМЕНТЫ:
 *   - номер программы:
 *       UINT PrgId;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_ShaderFree( UINT PrgId );

/***
 * Работа с материалами
 ***/

/* Тип задания материала поверхности */
typedef struct tagmc6MATERIAL
{
  /* Имя материала */
  CHAR Name[300];

  /* Коэффициенты отражения */
  VEC Ka, Kd, Ks;
  FLT Kp; /* Степень "бликовости" */

  /* Коэффициент прозрачности */
  FLT Kt;

  /* Текстура поверхности */
  INT TexId;
} mc6MATERIAL;

/* Глобальная таблица материалов */
#define MC6_MATERIAL_MAX 300
extern INT MC6_MtlLibSize;
extern mc6MATERIAL MC6_MtlLib[MC6_MATERIAL_MAX];

/* Функция добавления материала в библиотеку.
 * АРГУМЕНТЫ:
 *   - структура с памаметрами материала:
 *       mc6MATERIAL *Mtl;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (INT) порядковый номер добавленного материала (0 при ошибке).
 */
INT MC6_MtlAdd( mc6MATERIAL *Mtl );

/* Функция поиска материала по имени.
 * АРГУМЕНТЫ:
 *   - имя материала:
 *       CHAR *Name;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (INT) порядковый номер найденного материала (0 при ошибке).
 */
INT MC6_MtlFind( CHAR *Name );

/* Функция загрузки материала из файла (*.MTL).
 * АРГУМЕНТЫ:
 *   - имя файла материала:
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (INT) количество загруженных материалов.
 */
INT MC6_MtlLoad( CHAR *FileName );

/***
 * Работа с примитивами
 ***/

/* Виды примитивов */
typedef enum tagmc6PRIM_TYPE
{
  MC6_PRIM_TRIMESH,  /* примитив - набор треугольников */
  MC6_PRIM_GRID      /* регулярная сетка треугольников (через triangle strip) */
} mc6PRIM_TYPE;

/* Тип хранения примитива */
typedef struct tagmc6PRIM
{
  mc6PRIM_TYPE Type; /* Тип примитива (MC6_PRIM_***) */
  INT
    VA,          /* массив вершин */
    VBuf, IBuf,  /* буфера вершин и индексов */
    NumOfI,      /* количество индексов для вывода примитива */
    MtlNo;       /* номер материала из библиотеки */
} mc6PRIM;

/* Тип хранения текстурных координат */
typedef struct tagmc6UV
{
  FLT U, V; /* текстурные координаты */
} mc6UV;

/* Функция задания текстурных координат.
 * АРГУМЕНТЫ:
 *   - новые значени координат:
 *       FLT U, V;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (mc6UV) построенные координаты.
 */
__inline mc6UV UVSet( FLT U, FLT V )
{
  mc6UV UV = {U, V};

  return UV;
} /* End of 'UVSet' function */

/* Тип хранения одной вершины паримитива */
typedef struct tagmc6VERTEX
{
  VEC P;    /* позиция вершины */
  mc6UV T;  /* текстурные координаты вершины */
  VEC N;    /* нормаль в вершине */
  COLOR C;  /* цвет вершины */
} mc6VERTEX;

/* Функция создания примитива.
 * АРГУМЕНТЫ:
 *   - указатель на примитив:
 *       mc6PRIM *Prim;
 *   - тип примитива (MC6_PRIM_***):
 *       mc6PRIM_TYPE Type;
 *   - количество вершин и индексов:
 *       INT NoofV, NoofI;
 *   - массив вершин:
 *       mc6VERTEX *Vertices;
 *   - массив индексов:
 *       INT *Indices;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_PrimCreate( mc6PRIM *Prim, mc6PRIM_TYPE Type,
                     INT NoofV, INT NoofI, mc6VERTEX *Vertices, INT *Indices);

/* Функция создания примитива карта высот.
 * АРГУМЕНТЫ:
 *   - указатель на примитив:
 *       mc6PRIM *Prim;
 *   - угловая точка:
 *       VEC Loc;
 *   - касательные вектора-стороны:
 *       VEC Du, Dv;
 *   - масштаб по высоте:
 *       DBL Scale;
 *   - имя файла с высотами:
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (BOOL) TRUE при успехе, иначе FALSE.
 */
BOOL MC6_PrimCreateHeightField( mc6PRIM *Prim, VEC Loc, VEC Du, VEC Dv, DBL Scale, CHAR *FileName );

/* Функция удаления примитива.
 * АРГУМЕНТЫ:
 *   - указатель на примитив:
 *       mc6PRIM *Prim;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_PrimFree( mc6PRIM *Prim );

/* Функция отрисовки примитива.
 * АРГУМЕНТЫ:
 *   - указатель на примитив:
 *       mc6PRIM *Prim;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_PrimDraw( mc6PRIM *Prim, INT s );

/* Функция создания примитива плоскость.
 * АРГУМЕНТЫ:
 *   - указатель на примитив:
 *       mc6PRIM *Prim;
 *   - касательные вектора-стороны:
 *       VEC Du, Dv;
 *   - разбиение:
 *       INT N, M;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (BOOL) TRUE при успехе, иначе FALSE.
 */
BOOL MC6_PrimCreatePlane( mc6PRIM *Prim, VEC Du, VEC Dv, INT N, INT M );

/* Функция создания примитива сфера.
 * АРГУМЕНТЫ:
 *   - указатель на примитив:
 *       mc6PRIM *Prim;
 *   - центр сферы:
 *       VEC С;
 *   - радиус сферы:
 *       FLT R;
 *   - разбиение:
 *       INT N, M;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (BOOL) TRUE при успехе, иначе FALSE.
 */
BOOL MC6_PrimCreateSphere( mc6PRIM *Prim, VEC C, FLT R, INT N, INT M );

/* Функция загрузки геометрического объекта.
 * АРГУМЕНТЫ:
 *   - структура объекта для загрузки:
 *       mc6PRIM *GObj;
 *   - имя файла:
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (BOOL) TRUE при успехе, FALSE иначе.
 */
BOOL MC6_PrimLoad( mc6PRIM *GObj, CHAR *FileName );

/***
 * Работа с геометрическими объектами
 ***/

/* Геометрический объект - набор примитивов */
typedef struct tagmc6GEOM
{
  INT NumOfPrimitives; /* количество примитивов */
  mc6PRIM *Prims;      /* массив примитивов */
} mc6GEOM;

/* Функция добавления примитива к геометрическому объекту.
 * АРГУМЕНТЫ:
 *   - указатель на геометрический объект:
 *       mc6GEOM *G;
 *   - указатель на добавляемый примитив:
 *       mc6PRIM *Prim;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (INT) номер добавленного примитива в массиве (-1 при ошибке).
 */
INT MC6_GeomAddPrim( mc6GEOM *G, mc6PRIM *Prim );

/* Функция освобождения геометрического объекта.
 * АРГУМЕНТЫ:
 *   - указатель на геометрический объект:
 *       mc6GEOM *G;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_GeomFree( mc6GEOM *G );

/* Функция отображения геометрического объекта.
 * АРГУМЕНТЫ:
 *   - указатель на геометрический объект:
 *       mc6GEOM *G;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_GeomDraw( mc6GEOM *G );

/* Функция загрузки геометрического объекта из G3D файла.
 * АРГУМЕНТЫ:
 *   - указатель на геометрический объект:
 *       mc6GEOM *G;
 *   - имя файла:
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (BOOL) TRUE при успехе, иначе - FALSE.
 */
BOOL MC6_GeomLoad( mc6GEOM *G, CHAR *FileName );

/* Функция загрузки текстуры.
 * АРГУМЕНТЫ:
 *   - имя файла:
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (INT ) идентификатор OpenGL для текстуры.
 */
INT MC6_TextureLoad( CHAR *FileName );

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
