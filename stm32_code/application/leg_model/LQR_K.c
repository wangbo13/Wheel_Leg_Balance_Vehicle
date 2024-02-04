/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: LQR_K.c
 *
 * MATLAB Coder version            : 5.6
 * C/C++ source code generated on  : 28-Jan-2024 23:04:52
 */

/* Include Files */
#include "LQR_K.h"
#include <math.h>

/* Function Definitions */

/*
 * LQR_K
 *     K = LQR_K(L0)
 *
 * Arguments    : double L0
 *                double K[12]
 * Return Type  : void
 */
void LQR_K(float L0, float K[12])
{
  float t2;
  float t3;
  /*     This function was generated by the Symbolic Math Toolbox version 9.3.
   */
  /*     2024-01-28 22:57:58 */
  t2 = L0 * L0;
  t3 = L0 * L0 * L0;
  K[0] = ((L0 * -206.18526870643271 + t2 * 559.80501544035212) -
          t3 * 675.859318129557) +
         5.9467306649301284;
  K[1] = ((L0 * 55.558778538258437 - t2 * 268.75940701624211) +
          t3 * 398.477186543132) -
         0.25110271498387621;
  K[2] = ((L0 * -34.431076401868388 + t2 * 80.536217377588713) -
          t3 * 105.9817283020235) +
         0.9838792125417114;
  K[3] = ((L0 * 9.5892373401100759 - t2 * 45.177251881858467) +
          t3 * 66.619481849787391) +
         0.0419468267521319;
  K[4] = ((L0 * -94.933786703806192 + t2 * 321.76673551384749) -
          t3 * 407.17643133698419) +
         2.3527511293681349;
  K[5] = ((L0 * 18.163250173694049 - t2 * 107.4899738376856) +
          t3 * 171.95617007579429) +
         0.82394641504814559;
  K[6] = ((L0 * -81.365214366504517 + t2 * 273.08216572697182) -
          t3 * 352.0714199781566) +
         1.576386082492194;
  K[7] = ((L0 * 15.107823913016 - t2 * 90.493196317185578) +
          t3 * 145.74157469805911) +
         0.77881611287744346;
  K[8] = ((L0 * -111.8450222223951 + t2 * 302.41682689605631) -
          t3 * 331.05486769210921) +
         19.764375296877951;
  K[9] = ((L0 * 51.959869160832191 - t2 * 184.15923211508391) +
          t3 * 238.56478031136291) +
         23.529134542329071;
  K[10] = ((L0 * -3.4481460384458011 + t2 * 4.7915423043224026) -
           t3 * 1.281298165352478) +
          1.0560885192987131;
  K[11] = ((L0 * 1.8188279846387789 - t2 * 4.8650106466689564) +
           t3 * 4.826971664619653) +
          1.1270554718470751;
}

/*
 * File trailer for LQR_K.c
 *
 * [EOF]
 */
