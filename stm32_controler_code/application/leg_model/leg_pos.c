/*
 * File: leg_pos_ljw.c
 *
 * MATLAB Coder version            : 5.6
 * C/C++ source code generated on  : 28-Aug-2023 15:18:15
 */

/* Include Files */
#include "leg_pos_ljw.h"
// #include "rt_nonfinite.h"
// #include "rt_defines.h"
// #include "rt_nonfinite.h"
#include <math.h>

/**
  * 小改一下，把rt_atan2f_snf改成了atan2f
  */
 

// /* Function Declarations */
// static float rt_atan2f_snf(float u0, float u1);

// /* Function Definitions */
// /*
//  * Arguments    : float u0
//  *                float u1
//  * Return Type  : float
//  */
// static float rt_atan2f_snf(float u0, float u1)
// {
//   float y;
//   if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
//     y = rtNaNF;
//   } else if (rtIsInfF(u0) && rtIsInfF(u1)) {
//     int i;
//     int i1;
//     if (u0 > 0.0F) {
//       i = 1;
//     } else {
//       i = -1;
//     }
//     if (u1 > 0.0F) {
//       i1 = 1;
//     } else {
//       i1 = -1;
//     }
//     y = atan2f((float)i, (float)i1);
//   } else if (u1 == 0.0F) {
//     if (u0 > 0.0F) {
//       y = RT_PIF / 2.0F;
//     } else if (u0 < 0.0F) {
//       y = -(RT_PIF / 2.0F);
//     } else {
//       y = 0.0F;
//     }
//   } else {
//     y = atan2f(u0, u1);
//   }
//   return y;
// }

/*
 * LEG_POS_LJW
 *     POS = LEG_POS_LJW(L1,L2,L3,L4,L5,PHI1,PHI4)
 *
 * Arguments    : float l1
 *                float l2
 *                float l3
 *                float l4
 *                float l5
 *                float phi1
 *                float phi4
 *                float pos[2]
 * Return Type  : void
 */
void leg_pos(float l1, float l2, float l3, float l4, float l5, float phi1,
// void leg_pos_ljw(float l1, float l2, float l3, float l4, float l5, float phi1,
             float phi4, float pos[2])
{
  float t10;
  float t17;
  float t18;
  float t19;
  float t20;
  float t26;
  float t6;
  float t8;
  /*     This function was generated by the Symbolic Math Toolbox version 9.3.
   */
  /*     28-Aug-2023 22:55:54 */
  t6 = l2 * l2;
  t8 = l1 * cosf(phi1);
  t10 = l1 * sinf(phi1);
  t17 = t10 - l4 * sinf(phi4);
  t18 = (l5 + l4 * cosf(phi4)) - t8;
  t19 = t17 * t17;
  t20 = t18 * t18;
  t26 = ((t6 - l3 * l3) + t19) + t20;
  t6 = atanf(-(1.0F / (l2 * t18 * 2.0F + t26)) *
             (l2 * t17 * 2.0F -
              sqrtf((t6 * t19 * 4.0F + t6 * t20 * 4.0F) - t26 * t26))) *
       2.0F;
  t17 = (t8 - l5 / 2.0F) + l2 * cosf(t6);
  t6 = t10 + l2 * sinf(t6);
  pos[0] = sqrtf(t17 * t17 + t6 * t6);
  // pos[1] = rt_atan2f_snf(t6, t17);
  pos[1] = atan2f(t6, t17);
}

/*
 * File trailer for leg_pos_ljw.c
 *
 * [EOF]
 */
