/*VEC.H
 *MC6 - spr11
 *06.06.2015
 *My own library of functions for animation.
 */

#ifndef __VEC_H_
#define __VEC_H_

#include <math.h>

#include "def.h"

#define SQR(X) (X) * (X)
#define PI 3.14159265358979323846
#define DEGREE2RADIANL 0.01745329251994329576L
#define D2R(X) ((X) * DEGREE2RADIANL)
#define NOR(M)(MatrTranspose(MatrInverse(M)))

extern long double MultiplierDegree2Radian;

typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

typedef struct tagMatr
{
  DBL A[4][4];
}MATR;

MATR M;
VEC A;

/*_________________
MATRIX functions */

/*  */
__inline MATR MatrTranslate( DBL Dx, DBL Dy, DBL Dz )
{
  MATR M =
  {
    {
      { 1,  0,  0, 0},
      { 0,  1,  0, 0},
      { 0,  0,  1, 0},
      {Dx, Dy, Dz, 1}
    }
  };

  return M;
}


/*  */
__inline MATR MatrScale( DBL Sx, DBL Sy, DBL Sz )
{
  M.A[0][0] = Sx;
  M.A[0][1] = 0;
  M.A[0][2] = 0;
  M.A[0][3] = 0;

  M.A[1][0] = 0;
  M.A[1][1] = Sy;
  M.A[1][2] = 0;
  M.A[1][3] = 0;

  M.A[2][0] = 0;
  M.A[2][1] = 0;
  M.A[2][2] = Sz;
  M.A[2][3] = 0;

  M.A[3][0] = 0;
  M.A[3][1] = 0;
  M.A[3][2] = 0;
  M.A[3][3] = 1;
  return M;
}


/*  */
__inline MATR MatrRotateX( DBL AngleDegree )
{
  MATR M =
  {
    {
      {1, 0,                      0,                     0},
      {0, cos(D2R(AngleDegree)) , sin(D2R(AngleDegree)), 0},
      {0, -sin(D2R(AngleDegree)), cos(D2R(AngleDegree)), 0},
      {0, 0,                      0,                     1}
    }
  };
  return M;
}

/*  */
__inline MATR MatrRotateY( DBL AngleDegree )
{
  MATR M =
  {
    {
      {cos(D2R(AngleDegree)), 0, -sin(D2R(AngleDegree)), 0},
      {0,                     1, 0,                      0},
      {sin(D2R(AngleDegree)), 0, cos(D2R(AngleDegree)),  0},
      {0,                     0, 0,                      1}
    }
  };
  return M;
}


/*  */
__inline MATR MatrRotateZ( DBL AngleDegree )
{
  MATR M =
  {
    {
      {cos(D2R(AngleDegree)),  sin(D2R(AngleDegree)), 0, 0},
      {-sin(D2R(AngleDegree)), cos(D2R(AngleDegree)), 0, 0},
      {0,                      0,                     1, 0},
      {0,                      0,                     0, 1}
    }
  };
  return M;
}


/*  */
__inline MATR MatrRotate( DBL AngleDegree, DBL X, DBL Y, DBL Z )
{
  DBL a, si, co, len;
  MATR M;

  /* correct source parameters */
  a = D2R(AngleDegree);
  si = sin(a);
  co = cos(a);
  len = X * X + Y * Y + Z * Z;
  if (len != 0 && len != 1)
    len = sqrt(len), X /= len, Y /= len, Z /= len;

  /* Build quaternion matrix */
  X *= si;
  Y *= si;
  Z *= si;

  M.A[0][0] = 1 - 2 * (Y * Y + Z * Z);
  M.A[0][1] = 2 * X * Y - 2 * co * Z;
  M.A[0][2] = 2 * co * Y + 2 * X * Z;
  M.A[0][3] = 0;

  M.A[1][0] = 2 * X * Y + 2 * co * Z;
  M.A[1][1] = 1 - 2 * (X * X + Z * Z);
  M.A[1][2] = 2 * Y * Z - 2 * co * X;
  M.A[1][3] = 0;

  M.A[2][0] = 2 * X * Z - 2 * co * Y;
  M.A[2][1] = 2 * co * X + 2 * Y * Z;
  M.A[2][2] = 1 - 2 * (X * X + Y * Y);
  M.A[2][3] = 0;

  M.A[3][0] = 0;
  M.A[3][1] = 0;
  M.A[3][2] = 0;
  M.A[3][3] = 1;
  return M;
}


/*  */
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR M;
  INT i, j, k;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (M.A[i][j] = 0, k = 0; k < 4; k++)
        M.A[i][j] += M1.A[i][k] * M2.A[k][j];
  return M;
}


/*  */
__inline MATR MatrTranspose( MATR M )
{
  MATR M1;
  int i, j;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      M1.A[i][j] = M.A[j][i];
  return M1;
}


/*  */
__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                   DBL A21, DBL A22, DBL A23,
                   DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 +
        -A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
}


/*  */
__inline DBL MatrDeterm( MATR M )
{
  return
    M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                              M.A[2][1], M.A[2][2], M.A[2][3],
                              M.A[3][1], M.A[3][2], M.A[3][3]) -
    M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                              M.A[2][0], M.A[2][2], M.A[2][3],
                              M.A[3][0], M.A[3][2], M.A[3][3]) +
    M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                              M.A[2][0], M.A[2][1], M.A[2][3],
                              M.A[3][0], M.A[3][1], M.A[3][3]) -
    M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                              M.A[2][0], M.A[2][1], M.A[2][2],
                              M.A[3][0], M.A[3][1], M.A[3][2]);
}


/*  */
__inline MATR MatrIdentity( VOID )
{
  MATR M =
  {
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    }
  };

  return M;
}


/*  */
__inline MATR MatrInverse( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);
  INT p[4][3] =
  {
    {1, 2, 3},
    {0, 2, 3},
    {0, 1, 3},
    {0, 1, 2}
  }, i, j;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)  
      r.A[j][i] =
        (1 - ((i + j) % 2 * 2)) *
        MatrDeterm3x3(M.A[p[i][0]][p[j][0]], M.A[p[i][0]][p[j][1]], M.A[p[i][0]][p[j][2]],
                      M.A[p[i][1]][p[j][0]], M.A[p[i][1]][p[j][1]], M.A[p[i][1]][p[j][2]],
                      M.A[p[i][2]][p[j][0]], M.A[p[i][2]][p[j][1]], M.A[p[i][2]][p[j][2]]) / det;

  return r;
}


/*_________________ 
VECTOR functions */


/* Converts three coordinates into VEC */
__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC r = {X, Y, Z};

  return r;
} 


/* Addition of vectors */
__inline VEC VecAddVec( VEC A, VEC B )
{
  return VecSet(A.X + B.X, A.Y + B.Y, A.Z + B.Z);
}


/* Subtracts two original vectors (A - B) */
__inline VEC VecSubVec( VEC A, VEC B )
{
  return VecSet(A.X - B.X, A.Y - B.Y, A.Z - B.Z);
}


/* Multiplies vector by number */
__inline VEC VecMulNum( VEC A, DBL N )
{
  return VecSet(A.X * N, A.Y * N, A.Z * N);
}


/* Devides vector by number */
__inline VEC VecDivNum( VEC A, DBL N )
{
  return VecSet(A.X / N, A.Y / N, A.Z / N);
}


/* Returns vector,  negative to original */
__inline VEC VecNeg( VEC A )
{
  return VecSet(-A.X, -A.Y, -A.Z);
}


/* Dot production of vectors */
__inline DBL VecDotVec( VEC A, VEC B )
{
  return A.X * B.X + A.Y * B.Y + A.Z * B.Z;
}


/* Cross production of vectors */
__inline VEC VecCrossVec( VEC A, VEC B )
{
  VEC r;

  r.X = A.Y * B.Z - A.Z * B.Y;
  r.Y = A.Z * B.X - A.X * B.Z;
  r.Z = A.X * B.Y - A.Y * B.X;
  return r;
} 


/* Returns length of the vector */
__inline DBL VecLen( VEC V )
{
  return sqrt(SQR(V.X) + SQR(V.Y) + SQR(V.Z));
}  


/* Returns squared length of the vector */
__inline DBL VecLen2( VEC V )
{
  return SQR(VecLen(V));
}


/* Bringing vector to length of 1 */
__inline VEC VecNormalize( VEC V )
{
  return VecSet(A.X / VecLen(V),
                A.Y / VecLen(V),
                A.Z / VecLen(V));
}



/* Gets point after transformation */
__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(
    V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0],
    V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1],
    V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]);
}


/* Gets vector after transformation */
__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(
    V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
    V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
    V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
}


/* Rotates vector over 'X' axis */
__inline VEC VecRotateX( VEC V, DBL AngleInDegree )
{
  DBL sine, cosine, tmp;

  __asm {
    /* FST(0) Angle (from degree to radian) */
    fld  AngleInDegree
    fmul MultiplierDegree2Radian
    
    /* FST(0) - cos, FST(1) - sin */
    fsincos
    fstp cosine /* cos -> cosine */
    fstp sine   /* sin -> sine */
  }
  tmp = V.Y * cosine - V.Z * sine;
  V.Z = V.Y * sine + V.Z * cosine;
  V.Y = tmp;
  return V;
}


/* Rotates vector over 'Y' axis */
__inline VEC VecRotateY( VEC V, DBL AngleInDegree )
{
  DBL sine, cosine, tmp;

  __asm {
    /* FST(0) Angle (from degree to radian) */
    fld  AngleInDegree
    fmul MultiplierDegree2Radian
    
    /* FST(0) - cos, FST(1) - sin */
    fsincos
    fstp cosine /* cos -> cosine */
    fstp sine   /* sin -> sine */
  }
  tmp = V.Z * cosine - V.X * sine;
  V.X = V.Z * sine + V.X * cosine;
  V.Z = tmp;
  return V;
}


/* Rotates vector over 'Z' axis */
__inline VEC VecRotateZ( VEC V, DBL AngleInDegree )
{
  DBL sine, cosine, tmp;

  __asm {
    /* FST(0) Angle (from degree to radian) */
    fld  AngleInDegree
    fmul MultiplierDegree2Radian
    
    /* FST(0) - cos, FST(1) - sin */
    fsincos
    fstp cosine /* cos -> cosine */
    fstp sine   /* sin -> sine */
  }
  tmp = V.X * cosine - V.Y * sine;
  V.Y = V.X * sine + V.Y * cosine;
  V.X = tmp;
  return V;
}

#endif /* __VEC_H_ */
/* End of 'VEC.H' file */