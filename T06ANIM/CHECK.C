/*MAIN.H
 *MC6 - spr11
 *06.06.2015
 *My own library of functions for animation.
 */

#include "VEC.H"
#include <stdio.h>

void main( void )
{
  VEC V;
  MATR M;
  INT a, i, j;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      M.A[i][j] = 5;

  V.X = 0;
  V.Y = 0;
  V.Z = 0;

  printf("What are you checking?\n0 - Vector\n1 - Matrix\n");
  scanf("%i", &a);
  if (a)
  {
    printf("\n%lf %lf %lf %lf\n%lf %lf %lf %lf\n%lf %lf %lf %lf\n%lf %lf %lf %lf\n\n",
            M.A[0][0], M.A[0][1], M.A[0][2], M.A[0][3], 
            M.A[1][0], M.A[1][1], M.A[1][2], M.A[1][3], 
            M.A[2][0], M.A[2][1], M.A[2][2], M.A[2][3], 
            M.A[3][0], M.A[3][1], M.A[3][2], M.A[3][3]);
    printf("%lf %lf %lf %lf\n%lf %lf %lf %lf\n%lf %lf %lf %lf\n%lf %lf %lf %lf\n\n",
            M.A[0][0], M.A[0][1], M.A[0][2], M.A[0][3], 
            M.A[1][0], M.A[1][1], M.A[1][2], M.A[1][3], 
            M.A[2][0], M.A[2][1], M.A[2][2], M.A[2][3], 
            M.A[3][0], M.A[3][1], M.A[3][2], M.A[3][3]);
  }
  else
  {
    printf("\n%lf %lf %lf\n\n", V.X, V.Y, V.Z);
    printf("%lf %lf %lf\n\n", V.X, V.Y, V.Z);
  }
}

/* End of 'MAIN.C' file */