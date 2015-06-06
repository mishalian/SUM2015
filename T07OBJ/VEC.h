/*LOAD_OBJ.C
 *MC6 - spr11
 *06.06.2015
 *Load and build 3D *.obj file.
 */

#include <windows.h>
#include <math.h>

#ifndef __VEC_H_
#define __VEC_H_

#define SQR(X) (X) * (X)
#define PI 3.14159265358979323846
#define DEGREE2RADIANL 0.01745329251994329576L
#define D2R(X) ((X) * DEGREE2RADIANL)
#define NOR(M)(MatrTranspose(MatrInverse(M)))

typedef double DBL;

typedef struct tagVEC
{
  DBL X, Y, Z;
}VEC;

VOID ObjDraw( VOID );

#endif /* __VEC_H_ */ 