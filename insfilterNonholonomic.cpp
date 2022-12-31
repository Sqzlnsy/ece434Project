//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: insfilterNonholonomic.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 23-Dec-2022 16:50:05
//

// Include Files
#include "insfilterNonholonomic.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
//
// Arguments    : double x[16]
// Return Type  : void
//
namespace coder {
void insfilterNonholonomic::repairQuaternion(double x[16]) const
{
  double b_qparts_tmp;
  double n;
  double qparts_idx_0;
  double qparts_idx_1;
  double qparts_idx_2;
  double qparts_idx_3;
  double qparts_tmp;
  signed char qparts_tmp_idx_0;
  signed char qparts_tmp_idx_1;
  signed char qparts_tmp_idx_2;
  signed char qparts_tmp_idx_3;
  qparts_tmp_idx_0 = static_cast<signed char>(OrientationIdx[0]);
  qparts_idx_3 = x[qparts_tmp_idx_0 - 1];
  qparts_tmp_idx_1 = static_cast<signed char>(OrientationIdx[1]);
  qparts_idx_2 = x[qparts_tmp_idx_1 - 1];
  qparts_tmp_idx_2 = static_cast<signed char>(OrientationIdx[2]);
  qparts_tmp = x[qparts_tmp_idx_2 - 1];
  qparts_tmp_idx_3 = static_cast<signed char>(OrientationIdx[3]);
  b_qparts_tmp = x[qparts_tmp_idx_3 - 1];
  n = std::sqrt(((qparts_idx_3 * qparts_idx_3 + qparts_idx_2 * qparts_idx_2) +
                 qparts_tmp * qparts_tmp) +
                b_qparts_tmp * b_qparts_tmp);
  qparts_idx_0 = qparts_idx_3 / n;
  qparts_idx_1 = qparts_idx_2 / n;
  qparts_idx_2 = qparts_tmp / n;
  qparts_idx_3 = b_qparts_tmp / n;
  if (qparts_idx_0 < 0.0) {
    x[static_cast<int>(OrientationIdx[0]) - 1] = -qparts_idx_0;
    x[static_cast<int>(OrientationIdx[1]) - 1] = -qparts_idx_1;
    x[static_cast<int>(OrientationIdx[2]) - 1] = -qparts_idx_2;
    x[static_cast<int>(OrientationIdx[3]) - 1] = -qparts_idx_3;
  } else {
    x[qparts_tmp_idx_0 - 1] = qparts_idx_0;
    x[qparts_tmp_idx_1 - 1] = qparts_idx_1;
    x[qparts_tmp_idx_2 - 1] = qparts_idx_2;
    x[qparts_tmp_idx_3 - 1] = qparts_idx_3;
  }
}

} // namespace coder

//
// File trailer for insfilterNonholonomic.cpp
//
// [EOF]
//
