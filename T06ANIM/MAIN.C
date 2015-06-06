/*MAIN.H
 *MC6 - spr11
 *06.06.2015
 *My own library of functions for animation.
 */

#include "VEC.H"

void main( void )
{
  VEC V;
  MATR A;
  int a;

  printf("What are you checking?\n0 - Vector\n1 - Matrix\n");
  scanf("%i", &a);
  if (a)
    printf("%DBL %DBL %DBL %DBL\n%DBL %DBL %DBL %DBL\n%DBL %DBL %DBL %DBL\n%DBL %DBL %DBL %DBL\n\n
    hio",
            M.A[0][0], M.A[0][1], M.A[0][2], M.A[0][3], 
            M.A[1][0], M.A[1][1], M.A[1][2], M.A[1][3], 
            M.A[2][0], M.A[2][1], M.A[2][2], M.A[2][3], 
            M.A[3][0], M.A[3][1], M.A[3][2], M.A[3][3]);
}

/* End of 'MAIN.C' file */