/*T03PERM
 *MC11
 *03.06.2015
 *Create a file with all posible combinations of N elements
 */

#include <stdio.h>

#define MAX 30

int Parity = 0;
double A[MAX][MAX], P[MAX];
int N, SUM, PROD;


void Load( char *FileName )
{
  int i, j;
  FILE *F;

  if ((F = fopen(FileName, "r")) != NULL)
  {
    fscanf(F, "%d", &N);
    for (i = 0; i < N; i++)
      for (j = 0; j < N; j++)
        fscanf(F, "%lf", &A[i][j]);
    fclose(F);
  }
}




void Swap( int *A, int *B )
{
  int tmp = *A;

  *A = *B;
  *B = tmp;

  if (*A != *B)
    Parity = !Parity;
}

void GetDet( void )
{
  for (i = 0; i < N; i++)
    PROD *= A[i][P[i]];
  if (Parity == 0)
    SUM += PROD;
  else
    SUM -= PROD;
}

void Go( int Pos )
{
  int i;

  if (Pos == N)
  { 
    Write();
    return;   
  }
  else
  {
    for (i = Pos; i < N; i++)
    {
      Swap(&p[Pos], &p[i]);
      Go(Pos + 1);        
      Swap(&p[Pos], &p[i]);      
    }  
  }  
}


void main( void )
{
  int i, j;
  Load("m.txt");  
  
  for (i = 0; i < N; i++)
  {
    P[0] = A[0][i];
    Go(i);
  }


} /* End of T03PERM */