/* FILE NAME: OBJ.H
 * PROGRAMMER: MC6
 * DATE: 06.06.2015
 * PURPOSE: WinAPI windowed application sample
 */

#include <stdio.h>
#include <stdlib.h>

#include "obj.h"
#include "anim.h"

VEC *ObjV; /* Vertex coordinates */
INT ObjNumOfV; /* Number of model vertices */


/* Draw object functioln.
 * ARGUMENTS:
 *   - object (*.OBJ) file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if loading is success, FALSE otherwise.
 */
VOID ObjDraw( HDC hDC, INT w, INT h )
{  
  INT i;
  
  ObjLoad("cow.object");
  
  for (i = 1; i < ObjNumOfV; i++)
  {
    ObjV[i].X = ObjV[i].X * 50;
    ObjV[i].Y = ObjV[i].Y * 50;
    ObjV[i].Z = ObjV[i].Z * 50;     

    SelectObject(hDC, GetStockObject(BLACK_BRUSH));
    Ellipse(hDC, w / 2 + (INT)ObjV[5].X - 5, h / 2 - (INT)ObjV[5].Y - 5,
      w / 2 + (INT)ObjV[5].X + 5, h / 2 - (INT)ObjV[5].Y + 5);
  }
} /* End of 'ObjDraw' function */



/* Draw object functioln.
 * ARGUMENTS:
 *   - object (*.OBJ) file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if loading is success, FALSE otherwise.
 */
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
} /* End of 'ObjLoad' function */