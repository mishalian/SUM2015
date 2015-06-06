/*MAIN.C
 *MC6 - spr11
 *06.06.2015
 *Load and build 3D *.obj file.
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "VEC.H"

VEC *ObjV; /* Vertex coordinates */
INT ObjNumOfV, nv = 0;
FILE *F;


BOOL ObjLoad( CHAR *FileName )
{
  FILE *F;
  INT nv = 0;
  static CHAR Buf[10000];

  /* Open file */
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertices */
  while (fgets(Buf, sizeof(Buf), F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
  }

  /* Allocate memory for data */
  if ((ObjV = malloc(sizeof(VEC) * nv)) == NULL)
  {
    fclose(F);
    return FALSE;
  }

  /* Read vertices */
  rewind(F);
  nv = 0;
  while (fgets(Buf, sizeof(Buf), F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      sscanf(Buf + 2, "%lf%lf%lf",
        &ObjV[nv].X, &ObjV[nv].Y, &ObjV[nv].Z);
      nv++;
    }
  }

  fclose(F);

  ObjNumOfV = nv;
  return TRUE;
}

VOID ObjDraw( VOID )
{  
  ObjLoad("cow.object");
  
  if ((ObjV = malloc(sizeof(VEC) * nv)) == NULL)
  {
    fclose(F);
  }
}

/* End of 'MAIN.C' file */