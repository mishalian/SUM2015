/* FILENAME: UMAP.C
 * PROGRAMMER: MC6
 * PURPOSE: Map view unit handle module.
 * LAST UPDATE: 10.06.2015
 */

#include "anim.h"

/* ��� ������������� ���� */
typedef struct tagmc6UNIT_MAP
{
  MC6_UNIT_BASE_FIELDS;

  mc6PRIM Map;
  INT TextId;  /* Id �������� */
} mc6UNIT_MAP;

/* ������� ������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT_MAP *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitInit( mc6UNIT_MAP *Uni, mc6ANIM *Ani )
{
  /* ��������� �������� */
  mc6MATERIAL Mtl = MC6_MtlLib[0];

  MC6_PrimCreateHeightField(&Uni->Map, VecSet(-50, 0, 50), VecSet(100, 0, 0), VecSet(0, 0, -100), 10, "height.bmp");
  Mtl.TexId = MC6_TextureLoad("htex.bmp");
  Uni->Map.MtlNo = Uni->TextId = MC6_MtlAdd(&Mtl);  

  MC6_RndPrimMatrConvert = MatrScale(5, 5, 5);
} /* End of 'MC6_AnimUnitInit' function */

/* ������� ��������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT_MAP *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID MC6_AnimUnitClose( mc6UNIT_MAP *Uni, mc6ANIM *Ani )
{
  MC6_PrimFree(&Uni->Map);
} /* End of 'MC6_AnimUnitClose' function */

/* ������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       mc6UNIT_MAP *Uni;
 *   - ��������� �� �������� ��������:
 *       mc6ANIM *Ani;
 * ������������ ��������: ���.
 */                                                                              
static VOID MC6_AnimUnitRender( mc6UNIT_MAP *Uni, mc6ANIM *Ani )
{
  static DBL rttX = 0, rttY = 0;

  MC6_RndMatrView = MatrView(VecSet(10, 10, 10),
                             VecSet(0, 0, 0),
                             VecSet(0, 1, 0));
  rttY += (Ani->JY - Ani->Keys[VK_UP] + Ani->Keys[VK_DOWN]) * 0.4;
  rttX += (Ani->JX + Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT]) * 0.4;
 
  MC6_RndMatrView = MatrMulMatr(MatrMulMatr(
    MC6_RndMatrView, MatrRotateY(rttX)), MatrRotateX(rttY));

// MC6_RndMatrView = CamUp(MC6_RndMatrView);

  if (Ani->KeysClick['L'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (Ani->KeysClick['O'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Uni->TextId);
  MC6_PrimDraw(&Uni->Map);
} /* End of 'MC6_AnimUnitRender' function */

/* ������� �������� ������� �������� "������".
 * ���������: ���.
 * ������������ ��������:
 *   (mc6UNIT *) ��������� �� ��������� ������ ��������.
 */
mc6UNIT * MC6_UnitMapCreate( VOID )
{
  mc6UNIT_MAP *Uni;

  if ((Uni = (VOID *)MC6_AnimUnitCreate(sizeof(mc6UNIT_MAP))) == NULL)
    return NULL;
  /* ��������� ���� */
  Uni->Init = (VOID *)MC6_AnimUnitInit;
  Uni->Close = (VOID *)MC6_AnimUnitClose;
  Uni->Render = (VOID *)MC6_AnimUnitRender;
  return (mc6UNIT *)Uni;
} /* End of 'MC6_UnitMapCreate' function */

/* END OF 'UMAP.C' FILE */
