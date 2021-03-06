/* FILENAME: PRIM.C
 * PROGRAMMER: MC6
 * PURPOSE: Primitive handle module.
 * LAST UPDATE: 13.06.2015
 */

#include "anim.h"
#include "render.h"

/* ������� ��������� ��������� ��� �������� */
MATR MC6_RndPrimMatrConvert = MC6_UNIT_MATR;

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
 *   (BOOL) TRUE ��� ������, ����� FALSE.
 */
VOID MC6_PrimCreate( mc6PRIM *Prim, mc6PRIM_TYPE Type,
                     INT NoofV, INT NoofI, mc6VERTEX *Vertices, INT *Indices)
{
  Prim->Type = Type;
  Prim->NumOfI = NoofI;
  /* ������� ������ OpenGL */
  glGenVertexArrays(1, &Prim->VA);
  glGenBuffers(1, &Prim->VBuf);
  glGenBuffers(1, &Prim->IBuf);

  /* ������ �������� ������ ������ */
  glBindVertexArray(Prim->VA);
  /* ������ �������� ����� ������ */
  glBindBuffer(GL_ARRAY_BUFFER, Prim->VBuf);
  /* ������� ������ */
  glBufferData(GL_ARRAY_BUFFER, sizeof(mc6VERTEX) * NoofV, Vertices, GL_STATIC_DRAW);
  /* ������ �������� ����� �������� */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Prim->IBuf);
  /* ������� ������ */
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, Indices, GL_STATIC_DRAW);

  /* ������ ������� ������ */
  /*                    layout,
   *                       ���������� ���������,
   *                          ���,
   *                                    ���� �� �����������,
   *                                           ������ � ������ ������ �������� ������,
   *                                                           �������� � ������ �� ������ ������ */
  glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(mc6VERTEX), (VOID *)0); /* ������� */
  glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(mc6VERTEX), (VOID *)sizeof(VEC)); /* �������� */
  glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(mc6VERTEX), (VOID *)(sizeof(VEC) + sizeof(mc6UV))); /* ������� */
  glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(mc6VERTEX), (VOID *)(sizeof(VEC) * 2 + sizeof(mc6UV))); /* ���� */

  /* �������� ������ ��������� (layout) */
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);

  /* ����������� �� ������� ������ */
  glBindVertexArray(0);
} /* End of 'MC6_PrimCreate' function */

/* ������� �������� ���������.
 * ���������:
 *   - ��������� �� ��������:
 *       mc6PRIM *Prim;
 * ������������ ��������: ���.
 */
VOID MC6_PrimFree( mc6PRIM *Prim )
{
  /* ������ �������� ������ ������ */
  glBindVertexArray(Prim->VA);
  /* "���������" ������ */
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Prim->VBuf);
  glDeleteBuffers(1, &Prim->IBuf);
  /* ������ ���������� ������ ������ */
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Prim->VA);

  memset(Prim, 0, sizeof(mc6PRIM));
} /* End of 'MC6_PrimFree' function */

/* ������� ��������� ���������.
 * ���������:
 *   - ��������� �� ��������:
 *       mc6PRIM *Prim;
 * ������������ ��������: ���.
 */
VOID MC6_PrimDraw( mc6PRIM *Prim )
{
  INT loc;
  MATR M;

  MC6_RndMatrWorldViewProj = MatrMulMatr(MatrMulMatr(MC6_RndMatrWorld, MC6_RndMatrView), MC6_RndMatrProj);

  /* ��������� ��� ��������, ���� ��� �������� */
  glLoadMatrixf(MC6_RndMatrWorldViewProj.A[0]);

  /* ������ ������������ */
  glBindVertexArray(Prim->VA);
  glUseProgram(MC6_RndProg);

  loc = glGetUniformLocation(MC6_RndProg, "MatrWorld");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, MC6_RndMatrWorld.A[0]);
  loc = glGetUniformLocation(MC6_RndProg, "MatrView");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, MC6_RndMatrView.A[0]);
  loc = glGetUniformLocation(MC6_RndProg, "MatrProj");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, MC6_RndMatrProj.A[0]);
  loc = glGetUniformLocation(MC6_RndProg, "MatrWVP");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, MC6_RndMatrWorldViewProj.A[0]);

  M = MatrTranspose(MatrInverse(MatrMulMatr(MC6_RndMatrWorld, MC6_RndMatrView)));
  loc = glGetUniformLocation(MC6_RndProg, "MatrWVInverse");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, M.A[0]);

  M = MatrTranspose(MatrInverse(MC6_RndMatrWorld));
  loc = glGetUniformLocation(MC6_RndProg, "MatrWInverse");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, M.A[0]);

  M = MatrMulMatr(MC6_RndMatrWorld, MC6_RndMatrView);
  loc = glGetUniformLocation(MC6_RndProg, "MatrWV");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, M.A[0]);

  loc = glGetUniformLocation(MC6_RndProg, "Time");
  if (loc != -1)
    glUniform1f(loc, MC6_Anim.Time);

  /* ���������� ��������� */
  loc = glGetUniformLocation(MC6_RndProg, "Ka");
  if (loc != -1)
    glUniform3fv(loc, 1, &MC6_MtlLib[Prim->MtlNo].Ka.X);
  loc = glGetUniformLocation(MC6_RndProg, "Kd");
  if (loc != -1)
    glUniform3fv(loc, 1, &MC6_MtlLib[Prim->MtlNo].Kd.X);
  loc = glGetUniformLocation(MC6_RndProg, "Ks");
  if (loc != -1)
    glUniform3fv(loc, 1, &MC6_MtlLib[Prim->MtlNo].Ks.X);
  loc = glGetUniformLocation(MC6_RndProg, "Kp");
  if (loc != -1)
    glUniform1f(loc, MC6_MtlLib[Prim->MtlNo].Kp);
  loc = glGetUniformLocation(MC6_RndProg, "Kt");
  if (loc != -1)
    glUniform1f(loc, MC6_MtlLib[Prim->MtlNo].Kt);

  loc = glGetUniformLocation(MC6_RndProg, "IsTextureUse");
  if (MC6_MtlLib[Prim->MtlNo].TexId == 0)
    glUniform1f(loc, 0);
  else
  {
    glUniform1f(loc, 1);
    glBindTexture(GL_TEXTURE_2D, MC6_MtlLib[Prim->MtlNo].TexId);
  }

  glPrimitiveRestartIndex(0xFFFFFFFF);
  if (Prim->Type == MC6_PRIM_GRID)
    glDrawElements(GL_TRIANGLE_STRIP, Prim->NumOfI, GL_UNSIGNED_INT, NULL);
  else
    glDrawElements(GL_TRIANGLES, Prim->NumOfI, GL_UNSIGNED_INT, NULL);

  glUseProgram(0);
  glBindVertexArray(0);
} /* End of 'MC6_PrimDraw' function */

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
/*BOOL MC6_PrimCreatePlane( mc6PRIM *Prim, VEC Du, VEC Dv, INT N, INT M )
{
} /* End of 'MC6_PrimCreatePlane' function */

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
/*BOOL MC6_PrimCreateSphere( mc6PRIM *Prim, VEC C, FLT R, INT N, INT M )
{
} /* End of 'MC6_PrimCreateSphere' function */

/* END OF 'PRIM.C' FILE */
