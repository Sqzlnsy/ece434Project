//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EKalmanGND.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 23-Dec-2022 16:50:05
//

// Include Files
#include "EKalmanGND.h"
#include "ENU.h"
#include "cosd.h"
#include "insfilterNonholonomic.h"
#include "rt_nonfinite.h"
#include "sind.h"
#include "rt_defines.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Declarations
static double rt_atan2d_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else if (std::isinf(u0) && std::isinf(u1)) {
    int b_u0;
    int b_u1;
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }
    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }
    y = std::atan2(static_cast<double>(b_u0), static_cast<double>(b_u1));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }
  return y;
}

//
// Arguments    : const double b_initstate[16]
//                double imuFs
//                const double Rnoise[2]
//                const double Qnoise[4]
//                double zvCst
//                const double localOrigin[3]
//                coder::insfilterNonholonomic *iobj_0
// Return Type  : void
//
void EKalmanGND::init(const double b_initstate[16], double imuFs,
                      const double Rnoise[2], const double Qnoise[4],
                      double zvCst, const double localOrigin[3],
                      coder::insfilterNonholonomic *iobj_0)
{
  coder::fusion::internal::frames::ENU r;
  int i;
  iobj_0->GyroscopeBiasDecayFactor = 0.999;
  iobj_0->AccelerometerBiasDecayFactor = 0.9999;
  iobj_0->applyConstraintCount = 0;
  iobj_0->OrientationIdx[0] = 1.0;
  iobj_0->OrientationIdx[1] = 2.0;
  iobj_0->OrientationIdx[2] = 3.0;
  iobj_0->OrientationIdx[3] = 4.0;
  iobj_0->IMUSampleRate = imuFs;
  iobj_0->ReferenceLocation[0] = localOrigin[0];
  iobj_0->ReferenceLocation[1] = localOrigin[1];
  iobj_0->ReferenceLocation[2] = localOrigin[2];
  iobj_0->DecimationFactor = 2;
  iobj_0->ReferenceFrameObject = r;
  gndFusion = iobj_0;
  for (i = 0; i < 16; i++) {
    iobj_0->pState[i] = b_initstate[i];
  }
  Rpos = Rnoise[0];
  Rvel = Rnoise[1];
  //  The dynamic model of the ground vehicle for this filter assumes there is
  //  no side slip or skid during movement. This means that the velocity is
  //  constrained to only the forward body axis. The other two velocity axis
  //  readings are corrected with a zero measurement weighted by the
  //  |ZeroVelocityConstraintNoise| parameter.
  iobj_0->ZeroVelocityConstraintNoise = zvCst;
  //  Process noises
  iobj_0->GyroscopeNoise[0] = Qnoise[0];
  iobj_0->GyroscopeNoise[1] = Qnoise[0];
  iobj_0->GyroscopeNoise[2] = Qnoise[0];
  iobj_0->GyroscopeBiasNoise[0] = Qnoise[1];
  iobj_0->GyroscopeBiasNoise[1] = Qnoise[1];
  iobj_0->GyroscopeBiasNoise[2] = Qnoise[1];
  iobj_0->AccelerometerNoise[0] = Qnoise[2];
  iobj_0->AccelerometerNoise[1] = Qnoise[2];
  iobj_0->AccelerometerNoise[2] = Qnoise[2];
  iobj_0->AccelerometerBiasNoise[0] = Qnoise[3];
  iobj_0->AccelerometerBiasNoise[1] = Qnoise[3];
  iobj_0->AccelerometerBiasNoise[2] = Qnoise[3];
  //  Initial error covariance
  for (i = 0; i < 256; i++) {
    iobj_0->pStateCovariance[i] = 1.0E-9;
  }
}

//
// Correct the filter states based on the GPS data and magnetic
//  field measurements.
//
// Arguments    : const double lla[3]
//                const double gpsvel[3]
// Return Type  : void
//
void EKalmanGND::updateGPS(const double lla[3], const double gpsvel[3])
{
  static const signed char iv[16]{0, 0, 0, 0, 0, 0, 0, 1,
                                  0, 0, 0, 0, 0, 0, 0, 0};
  static const signed char iv1[16]{0, 0, 0, 0, 0, 0, 0, 0,
                                   1, 0, 0, 0, 0, 0, 0, 0};
  static const signed char iv2[16]{0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 1, 0, 0, 0, 0, 0, 0};
  double b_W[256];
  double obj[256];
  double H[64];
  double W[64];
  double b_H[64];
  double y_tmp[64];
  double A[16];
  double R[16];
  double b_Rpos[9];
  double N;
  double a;
  double absxk_tmp;
  double b_a;
  double b_sinphi;
  double c_a;
  double c_sinphi;
  double coslambda;
  double cosphi;
  double course;
  double d;
  double d1;
  double d_a;
  double e_a;
  double ecefPosWithENUOrigin_idx_0;
  double ecefPosWithENUOrigin_idx_1;
  double ecefPosWithENUOrigin_idx_2;
  double f_a;
  double g_a;
  double groundspeedR;
  double h_a;
  double h_idx_0;
  double h_idx_1;
  double h_idx_2;
  double i_a;
  double j_a;
  double k_a;
  double l_a;
  double m_a;
  double scale;
  double sinlambda;
  double sinphi;
  double t;
  double tmp;
  int W_tmp;
  int b_i;
  int i;
  int j;
  int jA;
  int jBcol;
  int jp1j;
  int k;
  signed char ipiv[4];
  std::memset(&b_Rpos[0], 0, 9U * sizeof(double));
  b_Rpos[0] = Rpos;
  b_Rpos[4] = Rpos;
  b_Rpos[8] = Rpos;
  d = rt_atan2d_snf(gndFusion->pState[0] * gndFusion->pState[3] * 2.0 +
                        gndFusion->pState[1] * gndFusion->pState[2] * 2.0,
                    (gndFusion->pState[0] * gndFusion->pState[0] * 2.0 - 1.0) +
                        gndFusion->pState[1] * gndFusion->pState[1] * 2.0);
  h_idx_0 = gndFusion->pState[7];
  h_idx_1 = gndFusion->pState[8];
  h_idx_2 = gndFusion->pState[9];
  a = (2.0 * (gndFusion->pState[0] * gndFusion->pState[0]) +
       2.0 * (gndFusion->pState[1] * gndFusion->pState[1])) -
      1.0;
  b_a = (2.0 * (gndFusion->pState[0] * gndFusion->pState[0]) +
         2.0 * (gndFusion->pState[1] * gndFusion->pState[1])) -
        1.0;
  c_a = (2.0 * (gndFusion->pState[0] * gndFusion->pState[0]) +
         2.0 * (gndFusion->pState[1] * gndFusion->pState[1])) -
        1.0;
  d_a = 2.0 * gndFusion->pState[0] * gndFusion->pState[3] +
        2.0 * gndFusion->pState[1] * gndFusion->pState[2];
  e_a = (2.0 * (gndFusion->pState[0] * gndFusion->pState[0]) +
         2.0 * (gndFusion->pState[1] * gndFusion->pState[1])) -
        1.0;
  f_a = (2.0 * (gndFusion->pState[0] * gndFusion->pState[0]) +
         2.0 * (gndFusion->pState[1] * gndFusion->pState[1])) -
        1.0;
  g_a = (2.0 * (gndFusion->pState[0] * gndFusion->pState[0]) +
         2.0 * (gndFusion->pState[1] * gndFusion->pState[1])) -
        1.0;
  h_a = 2.0 * gndFusion->pState[0] * gndFusion->pState[3] +
        2.0 * gndFusion->pState[1] * gndFusion->pState[2];
  i_a = (2.0 * (gndFusion->pState[0] * gndFusion->pState[0]) +
         2.0 * (gndFusion->pState[1] * gndFusion->pState[1])) -
        1.0;
  j_a = 2.0 * gndFusion->pState[0] * gndFusion->pState[3] +
        2.0 * gndFusion->pState[1] * gndFusion->pState[2];
  k_a = (2.0 * (gndFusion->pState[0] * gndFusion->pState[0]) +
         2.0 * (gndFusion->pState[1] * gndFusion->pState[1])) -
        1.0;
  l_a = 2.0 * gndFusion->pState[0] * gndFusion->pState[3] +
        2.0 * gndFusion->pState[1] * gndFusion->pState[2];
  m_a = std::sqrt(gpsvel[0] * gpsvel[0] + gpsvel[1] * gpsvel[1]);
  scale = 3.3121686421112381E-170;
  absxk_tmp = std::abs(Rvel);
  if (absxk_tmp > 3.3121686421112381E-170) {
    groundspeedR = 1.0;
    scale = absxk_tmp;
  } else {
    t = absxk_tmp / 3.3121686421112381E-170;
    groundspeedR = t * t;
  }
  if (absxk_tmp > scale) {
    t = scale / absxk_tmp;
    groundspeedR = groundspeedR * t * t + 1.0;
    scale = absxk_tmp;
  } else {
    t = absxk_tmp / scale;
    groundspeedR += t * t;
  }
  groundspeedR = scale * std::sqrt(groundspeedR);
  course = rt_atan2d_snf(gpsvel[1], gpsvel[0]);
  if (course < 0.0) {
    course += 6.2831853071795862;
  }
  if (course - d > 3.1415926535897931) {
    course -= 6.2831853071795862;
  }
  cosphi = gndFusion->ReferenceLocation[0];
  coder::b_cosd(&cosphi);
  sinphi = gndFusion->ReferenceLocation[0];
  coder::b_sind(&sinphi);
  coslambda = gndFusion->ReferenceLocation[1];
  coder::b_cosd(&coslambda);
  sinlambda = gndFusion->ReferenceLocation[1];
  coder::b_sind(&sinlambda);
  b_sinphi = lla[0];
  coder::b_sind(&b_sinphi);
  N = 6.378137E+6 /
      std::sqrt(1.0 - 0.0066943799901413165 * (b_sinphi * b_sinphi));
  d1 = lla[0];
  coder::b_cosd(&d1);
  t = (N + lla[2]) * d1;
  c_sinphi = gndFusion->ReferenceLocation[0];
  coder::b_sind(&c_sinphi);
  scale = 6.378137E+6 /
          std::sqrt(1.0 - 0.0066943799901413165 * (c_sinphi * c_sinphi));
  d1 = gndFusion->ReferenceLocation[0];
  coder::b_cosd(&d1);
  ecefPosWithENUOrigin_idx_2 = (scale + gndFusion->ReferenceLocation[2]) * d1;
  d1 = lla[1];
  coder::b_cosd(&d1);
  tmp = lla[1];
  coder::b_sind(&tmp);
  absxk_tmp = gndFusion->ReferenceLocation[1];
  coder::b_cosd(&absxk_tmp);
  ecefPosWithENUOrigin_idx_1 = gndFusion->ReferenceLocation[1];
  coder::b_sind(&ecefPosWithENUOrigin_idx_1);
  scale = (scale * 0.99330562000985867 + gndFusion->ReferenceLocation[2]) *
          c_sinphi;
  ecefPosWithENUOrigin_idx_0 = t * d1 - ecefPosWithENUOrigin_idx_2 * absxk_tmp;
  ecefPosWithENUOrigin_idx_1 =
      t * tmp - ecefPosWithENUOrigin_idx_2 * ecefPosWithENUOrigin_idx_1;
  ecefPosWithENUOrigin_idx_2 =
      (N * 0.99330562000985867 + lla[2]) * b_sinphi - scale;
  tmp = coslambda * ecefPosWithENUOrigin_idx_0 +
        sinlambda * ecefPosWithENUOrigin_idx_1;
  std::memset(&R[0], 0, 16U * sizeof(double));
  for (i = 0; i < 3; i++) {
    jA = i << 2;
    R[jA] = b_Rpos[3 * i];
    R[jA + 1] = b_Rpos[3 * i + 1];
    R[jA + 2] = b_Rpos[3 * i + 2];
  }
  R[15] = groundspeedR / (m_a * m_a);
  for (i = 0; i < 16; i++) {
    jA = i << 2;
    H[jA] = iv[i];
    H[jA + 1] = iv1[i];
    H[jA + 2] = iv2[i];
  }
  H[3] = (2.0 * gndFusion->pState[3] /
              ((2.0 * (gndFusion->pState[0] * gndFusion->pState[0]) +
                2.0 * (gndFusion->pState[1] * gndFusion->pState[1])) -
               1.0) -
          4.0 * gndFusion->pState[0] *
              (2.0 * gndFusion->pState[0] * gndFusion->pState[3] +
               2.0 * gndFusion->pState[1] * gndFusion->pState[2]) /
              (a * a)) *
         (b_a * b_a) / (c_a * c_a + d_a * d_a);
  H[7] = (2.0 * gndFusion->pState[2] /
              ((2.0 * (gndFusion->pState[0] * gndFusion->pState[0]) +
                2.0 * (gndFusion->pState[1] * gndFusion->pState[1])) -
               1.0) -
          4.0 * gndFusion->pState[1] *
              (2.0 * gndFusion->pState[0] * gndFusion->pState[3] +
               2.0 * gndFusion->pState[1] * gndFusion->pState[2]) /
              (e_a * e_a)) *
         (f_a * f_a) / (g_a * g_a + h_a * h_a);
  H[11] = 2.0 * gndFusion->pState[1] *
          ((2.0 * (gndFusion->pState[0] * gndFusion->pState[0]) +
            2.0 * (gndFusion->pState[1] * gndFusion->pState[1])) -
           1.0) /
          (i_a * i_a + j_a * j_a);
  H[15] = 2.0 * gndFusion->pState[0] *
          ((2.0 * (gndFusion->pState[0] * gndFusion->pState[0]) +
            2.0 * (gndFusion->pState[1] * gndFusion->pState[1])) -
           1.0) /
          (k_a * k_a + l_a * l_a);
  H[19] = 0.0;
  H[23] = 0.0;
  H[27] = 0.0;
  H[31] = 0.0;
  H[35] = 0.0;
  H[39] = 0.0;
  H[43] = 0.0;
  H[47] = 0.0;
  H[51] = 0.0;
  H[55] = 0.0;
  H[59] = 0.0;
  H[63] = 0.0;
  for (i = 0; i < 4; i++) {
    for (W_tmp = 0; W_tmp < 16; W_tmp++) {
      y_tmp[W_tmp + (i << 4)] = H[i + (W_tmp << 2)];
    }
  }
  for (i = 0; i < 16; i++) {
    for (W_tmp = 0; W_tmp < 4; W_tmp++) {
      d1 = 0.0;
      for (jA = 0; jA < 16; jA++) {
        d1 += gndFusion->pStateCovariance[i + (jA << 4)] *
              y_tmp[jA + (W_tmp << 4)];
      }
      W[i + (W_tmp << 4)] = d1;
    }
  }
  for (i = 0; i < 4; i++) {
    for (W_tmp = 0; W_tmp < 16; W_tmp++) {
      d1 = 0.0;
      for (jA = 0; jA < 16; jA++) {
        d1 += H[i + (jA << 2)] * gndFusion->pStateCovariance[jA + (W_tmp << 4)];
      }
      b_H[i + (W_tmp << 2)] = d1;
    }
    for (W_tmp = 0; W_tmp < 4; W_tmp++) {
      d1 = 0.0;
      for (jA = 0; jA < 16; jA++) {
        d1 += b_H[i + (jA << 2)] * y_tmp[jA + (W_tmp << 4)];
      }
      jA = i + (W_tmp << 2);
      A[jA] = d1 + R[jA];
    }
    ipiv[i] = static_cast<signed char>(i + 1);
  }
  for (j = 0; j < 3; j++) {
    int b_tmp;
    int mmj_tmp;
    mmj_tmp = 2 - j;
    b_tmp = j * 5;
    jp1j = b_tmp + 2;
    jA = 4 - j;
    jBcol = 0;
    t = std::abs(A[b_tmp]);
    for (k = 2; k <= jA; k++) {
      c_sinphi = std::abs(A[(b_tmp + k) - 1]);
      if (c_sinphi > t) {
        jBcol = k - 1;
        t = c_sinphi;
      }
    }
    if (A[b_tmp + jBcol] != 0.0) {
      if (jBcol != 0) {
        jA = j + jBcol;
        ipiv[j] = static_cast<signed char>(jA + 1);
        scale = A[j];
        A[j] = A[jA];
        A[jA] = scale;
        scale = A[j + 4];
        A[j + 4] = A[jA + 4];
        A[jA + 4] = scale;
        scale = A[j + 8];
        A[j + 8] = A[jA + 8];
        A[jA + 8] = scale;
        scale = A[j + 12];
        A[j + 12] = A[jA + 12];
        A[jA + 12] = scale;
      }
      i = (b_tmp - j) + 4;
      for (b_i = jp1j; b_i <= i; b_i++) {
        A[b_i - 1] /= A[b_tmp];
      }
    }
    jA = b_tmp;
    for (jBcol = 0; jBcol <= mmj_tmp; jBcol++) {
      absxk_tmp = A[(b_tmp + (jBcol << 2)) + 4];
      if (absxk_tmp != 0.0) {
        i = jA + 6;
        W_tmp = (jA - j) + 8;
        for (jp1j = i; jp1j <= W_tmp; jp1j++) {
          A[jp1j - 1] += A[((b_tmp + jp1j) - jA) - 5] * -absxk_tmp;
        }
      }
      jA += 4;
    }
  }
  for (j = 0; j < 4; j++) {
    jBcol = (j << 4) - 1;
    jA = j << 2;
    for (k = 0; k < j; k++) {
      jp1j = k << 4;
      d1 = A[k + jA];
      if (d1 != 0.0) {
        for (b_i = 0; b_i < 16; b_i++) {
          W_tmp = (b_i + jBcol) + 1;
          W[W_tmp] -= d1 * W[b_i + jp1j];
        }
      }
    }
    scale = 1.0 / A[j + jA];
    for (b_i = 0; b_i < 16; b_i++) {
      W_tmp = (b_i + jBcol) + 1;
      W[W_tmp] *= scale;
    }
  }
  for (j = 3; j >= 0; j--) {
    jBcol = (j << 4) - 1;
    jA = (j << 2) - 1;
    i = j + 2;
    for (k = i; k < 5; k++) {
      jp1j = (k - 1) << 4;
      d1 = A[k + jA];
      if (d1 != 0.0) {
        for (b_i = 0; b_i < 16; b_i++) {
          W_tmp = (b_i + jBcol) + 1;
          W[W_tmp] -= d1 * W[b_i + jp1j];
        }
      }
    }
  }
  for (j = 2; j >= 0; j--) {
    signed char i1;
    i1 = ipiv[j];
    if (i1 != j + 1) {
      for (b_i = 0; b_i < 16; b_i++) {
        jA = b_i + (j << 4);
        scale = W[jA];
        W_tmp = b_i + ((i1 - 1) << 4);
        W[jA] = W[W_tmp];
        W[W_tmp] = scale;
      }
    }
  }
  c_sinphi = (-sinlambda * ecefPosWithENUOrigin_idx_0 +
              coslambda * ecefPosWithENUOrigin_idx_1) -
             h_idx_0;
  t = (-sinphi * tmp + cosphi * ecefPosWithENUOrigin_idx_2) - h_idx_1;
  absxk_tmp = (cosphi * tmp + sinphi * ecefPosWithENUOrigin_idx_2) - h_idx_2;
  scale = course - d;
  for (i = 0; i < 16; i++) {
    d = gndFusion->pState[i] +
        (((W[i] * c_sinphi + W[i + 16] * t) + W[i + 32] * absxk_tmp) +
         W[i + 48] * scale);
    R[i] = d;
  }
  gndFusion->repairQuaternion(R);
  for (i = 0; i < 16; i++) {
    d = W[i];
    d1 = W[i + 16];
    tmp = W[i + 32];
    absxk_tmp = W[i + 48];
    for (W_tmp = 0; W_tmp < 16; W_tmp++) {
      jA = W_tmp << 2;
      b_W[i + (W_tmp << 4)] = ((d * H[jA] + d1 * H[jA + 1]) + tmp * H[jA + 2]) +
                              absxk_tmp * H[jA + 3];
    }
    for (W_tmp = 0; W_tmp < 16; W_tmp++) {
      d = 0.0;
      for (jA = 0; jA < 16; jA++) {
        d +=
            b_W[i + (jA << 4)] * gndFusion->pStateCovariance[jA + (W_tmp << 4)];
      }
      jA = i + (W_tmp << 4);
      obj[jA] = gndFusion->pStateCovariance[jA] - d;
    }
  }
  std::copy(&obj[0], &obj[256], &gndFusion->pStateCovariance[0]);
  std::copy(&R[0], &R[16], &gndFusion->pState[0]);
}

//
// Use the |predict| method to estimate the filter state based
//  on the simulated accelerometer and gyroscope signals.
//
// Arguments    : const double accel[3]
//                const double gyro[3]
// Return Type  : void
//
void EKalmanGND::updateIMU(const double accel[3], const double gyro[3])
{
  double F[256];
  double b_F[256];
  double b_G[256];
  double c_F[256];
  double G[192];
  double c_G[192];
  double U[144];
  double H[32];
  double W[32];
  double b_H[32];
  double b_x[16];
  double x[16];
  double accelBiasVar[9];
  double accelVar[9];
  double gyroBiasVar[9];
  double gyroVar[9];
  double innovCov[4];
  double zeroVelVar[4];
  double a21;
  double accelBiasDecayFactor;
  double b_x_tmp;
  double c_x_tmp;
  double d_x_tmp;
  double e_x_tmp;
  double f_x_tmp;
  double gyroBiasDecayFactor;
  double h_x_tmp;
  double k_x_tmp;
  double l_x_tmp;
  double x_tmp;
  double x_tmp_tmp;
  int G_tmp;
  int U_tmp;
  int i;
  int i1;
  int r1;
  int r2;
  for (i = 0; i < 16; i++) {
    x[i] = gndFusion->pState[i];
  }
  double F_tmp;
  double b_F_tmp;
  double b_x_tmp_tmp;
  double c_F_tmp;
  double d_F_tmp;
  double dt;
  double e_F_tmp;
  double f_F_tmp;
  double g_F_tmp;
  double g_x_tmp;
  double h_F_tmp;
  double i_F_tmp;
  double i_x_tmp;
  double j_F_tmp;
  double j_x_tmp;
  dt = 1.0 / gndFusion->IMUSampleRate;
  accelBiasDecayFactor = gndFusion->AccelerometerBiasDecayFactor;
  gyroBiasDecayFactor = gndFusion->GyroscopeBiasDecayFactor;
  x_tmp = x[4] / 2.0 - gyro[0] / 2.0;
  b_x_tmp = dt * x[3];
  c_x_tmp = x[5] / 2.0 - gyro[1] / 2.0;
  d_x_tmp = dt * x[2];
  e_x_tmp = x[6] / 2.0 - gyro[2] / 2.0;
  f_x_tmp = dt * x[1];
  b_x[0] = ((x[0] + f_x_tmp * x_tmp) + d_x_tmp * c_x_tmp) + b_x_tmp * e_x_tmp;
  g_x_tmp = dt * x[0];
  b_x[1] = ((x[1] - g_x_tmp * x_tmp) + b_x_tmp * c_x_tmp) - d_x_tmp * e_x_tmp;
  b_x[2] = ((x[2] - b_x_tmp * x_tmp) - g_x_tmp * c_x_tmp) + f_x_tmp * e_x_tmp;
  b_x[3] = ((x[3] + d_x_tmp * x_tmp) - f_x_tmp * c_x_tmp) - g_x_tmp * e_x_tmp;
  x_tmp_tmp = dt * (1.0 - gyroBiasDecayFactor);
  b_x[4] = -x[4] * (x_tmp_tmp - 1.0);
  b_x[5] = -x[5] * (x_tmp_tmp - 1.0);
  b_x[6] = -x[6] * (x_tmp_tmp - 1.0);
  b_x[7] = x[7] + dt * x[10];
  b_x[8] = x[8] + dt * x[11];
  b_x[9] = x[9] + dt * x[12];
  h_x_tmp = x[14] - accel[1];
  i_x_tmp = x[13] - accel[0];
  j_x_tmp = x[15] - accel[2];
  k_x_tmp = (x[3] * i_x_tmp + x[0] * h_x_tmp) - x[1] * j_x_tmp;
  l_x_tmp = (x[1] * h_x_tmp - x[2] * i_x_tmp) + x[0] * j_x_tmp;
  gyroBiasDecayFactor = (x[1] * i_x_tmp + x[2] * h_x_tmp) + x[3] * j_x_tmp;
  a21 = (x[0] * i_x_tmp - x[3] * h_x_tmp) + x[2] * j_x_tmp;
  b_x[10] = x[10] +
            dt * (((x[0] * a21 + x[2] * l_x_tmp) + x[1] * gyroBiasDecayFactor) -
                  x[3] * k_x_tmp);
  b_x[11] =
      x[11] +
      dt * (((x[0] * k_x_tmp - x[1] * l_x_tmp) + x[2] * gyroBiasDecayFactor) +
            x[3] * a21);
  b_x[12] =
      x[12] + dt * ((((x[0] * l_x_tmp - 9.81) + x[1] * k_x_tmp) - x[2] * a21) +
                    x[3] * gyroBiasDecayFactor);
  b_x_tmp_tmp = dt * (1.0 - accelBiasDecayFactor);
  b_x[13] = -x[13] * (b_x_tmp_tmp - 1.0);
  b_x[14] = -x[14] * (b_x_tmp_tmp - 1.0);
  b_x[15] = -x[15] * (b_x_tmp_tmp - 1.0);
  gndFusion->repairQuaternion(b_x);
  std::copy(&b_x[0], &b_x[16], &gndFusion->pState[0]);
  F[0] = 1.0;
  F_tmp = dt * x_tmp;
  F[16] = F_tmp;
  b_F_tmp = dt * c_x_tmp;
  F[32] = b_F_tmp;
  c_F_tmp = dt * e_x_tmp;
  F[48] = c_F_tmp;
  d_F_tmp = f_x_tmp / 2.0;
  F[64] = d_F_tmp;
  e_F_tmp = d_x_tmp / 2.0;
  F[80] = e_F_tmp;
  f_F_tmp = b_x_tmp / 2.0;
  F[96] = f_F_tmp;
  F[112] = 0.0;
  F[128] = 0.0;
  F[144] = 0.0;
  F[160] = 0.0;
  F[176] = 0.0;
  F[192] = 0.0;
  F[208] = 0.0;
  F[224] = 0.0;
  F[240] = 0.0;
  g_F_tmp = -dt * x_tmp;
  F[1] = g_F_tmp;
  F[17] = 1.0;
  h_F_tmp = -dt * e_x_tmp;
  F[33] = h_F_tmp;
  F[49] = b_F_tmp;
  b_F_tmp = -g_x_tmp / 2.0;
  F[65] = b_F_tmp;
  F[81] = f_F_tmp;
  i_F_tmp = -d_x_tmp / 2.0;
  F[97] = i_F_tmp;
  F[113] = 0.0;
  F[129] = 0.0;
  F[145] = 0.0;
  F[161] = 0.0;
  F[177] = 0.0;
  F[193] = 0.0;
  F[209] = 0.0;
  F[225] = 0.0;
  F[241] = 0.0;
  j_F_tmp = -dt * c_x_tmp;
  F[2] = j_F_tmp;
  F[18] = c_F_tmp;
  F[34] = 1.0;
  F[50] = g_F_tmp;
  c_F_tmp = -b_x_tmp / 2.0;
  F[66] = c_F_tmp;
  F[82] = b_F_tmp;
  F[98] = d_F_tmp;
  F[114] = 0.0;
  F[130] = 0.0;
  F[146] = 0.0;
  F[162] = 0.0;
  F[178] = 0.0;
  F[194] = 0.0;
  F[210] = 0.0;
  F[226] = 0.0;
  F[242] = 0.0;
  F[3] = h_F_tmp;
  F[19] = j_F_tmp;
  F[35] = F_tmp;
  F[51] = 1.0;
  F[67] = e_F_tmp;
  F_tmp = -f_x_tmp / 2.0;
  F[83] = F_tmp;
  F[99] = b_F_tmp;
  F[115] = 0.0;
  F[131] = 0.0;
  F[147] = 0.0;
  F[163] = 0.0;
  F[179] = 0.0;
  F[195] = 0.0;
  F[211] = 0.0;
  F[227] = 0.0;
  F[243] = 0.0;
  F[4] = 0.0;
  F[20] = 0.0;
  F[36] = 0.0;
  F[52] = 0.0;
  F[68] = 1.0 - x_tmp_tmp;
  F[84] = 0.0;
  F[100] = 0.0;
  F[116] = 0.0;
  F[132] = 0.0;
  F[148] = 0.0;
  F[164] = 0.0;
  F[180] = 0.0;
  F[196] = 0.0;
  F[212] = 0.0;
  F[228] = 0.0;
  F[244] = 0.0;
  F[5] = 0.0;
  F[21] = 0.0;
  F[37] = 0.0;
  F[53] = 0.0;
  F[69] = 0.0;
  F[85] = 1.0 - x_tmp_tmp;
  F[101] = 0.0;
  F[117] = 0.0;
  F[133] = 0.0;
  F[149] = 0.0;
  F[165] = 0.0;
  F[181] = 0.0;
  F[197] = 0.0;
  F[213] = 0.0;
  F[229] = 0.0;
  F[245] = 0.0;
  F[6] = 0.0;
  F[22] = 0.0;
  F[38] = 0.0;
  F[54] = 0.0;
  F[70] = 0.0;
  F[86] = 0.0;
  F[102] = 1.0 - x_tmp_tmp;
  F[118] = 0.0;
  F[134] = 0.0;
  F[150] = 0.0;
  F[166] = 0.0;
  F[182] = 0.0;
  F[198] = 0.0;
  F[214] = 0.0;
  F[230] = 0.0;
  F[246] = 0.0;
  F[7] = 0.0;
  F[23] = 0.0;
  F[39] = 0.0;
  F[55] = 0.0;
  F[71] = 0.0;
  F[87] = 0.0;
  F[103] = 0.0;
  F[119] = 1.0;
  F[135] = 0.0;
  F[151] = 0.0;
  F[167] = dt;
  F[183] = 0.0;
  F[199] = 0.0;
  F[215] = 0.0;
  F[231] = 0.0;
  F[247] = 0.0;
  F[8] = 0.0;
  F[24] = 0.0;
  F[40] = 0.0;
  F[56] = 0.0;
  F[72] = 0.0;
  F[88] = 0.0;
  F[104] = 0.0;
  F[120] = 0.0;
  F[136] = 1.0;
  F[152] = 0.0;
  F[168] = 0.0;
  F[184] = dt;
  F[200] = 0.0;
  F[216] = 0.0;
  F[232] = 0.0;
  F[248] = 0.0;
  F[9] = 0.0;
  F[25] = 0.0;
  F[41] = 0.0;
  F[57] = 0.0;
  F[73] = 0.0;
  F[89] = 0.0;
  F[105] = 0.0;
  F[121] = 0.0;
  F[137] = 0.0;
  F[153] = 1.0;
  F[169] = 0.0;
  F[185] = 0.0;
  F[201] = dt;
  F[217] = 0.0;
  F[233] = 0.0;
  F[249] = 0.0;
  d_x_tmp =
      (2.0 * x[0] * i_x_tmp - 2.0 * x[3] * h_x_tmp) + 2.0 * x[2] * j_x_tmp;
  b_F_tmp = dt * d_x_tmp;
  F[10] = b_F_tmp;
  g_F_tmp = dt * ((2.0 * x[1] * i_x_tmp + 2.0 * x[2] * h_x_tmp) +
                  2.0 * x[3] * j_x_tmp);
  F[26] = g_F_tmp;
  h_F_tmp =
      (2.0 * x[1] * h_x_tmp - 2.0 * x[2] * i_x_tmp) + 2.0 * x[0] * j_x_tmp;
  j_F_tmp = dt * h_F_tmp;
  F[42] = j_F_tmp;
  gyroBiasDecayFactor =
      (2.0 * x[3] * i_x_tmp + 2.0 * x[0] * h_x_tmp) - 2.0 * x[1] * j_x_tmp;
  F[58] = -dt * gyroBiasDecayFactor;
  F[74] = 0.0;
  F[90] = 0.0;
  F[106] = 0.0;
  F[122] = 0.0;
  F[138] = 0.0;
  F[154] = 0.0;
  F[170] = 1.0;
  F[186] = 0.0;
  F[202] = 0.0;
  k_x_tmp = x[0] * x[0];
  a21 = x[1] * x[1];
  c_x_tmp = x[2] * x[2];
  x_tmp_tmp = x[3] * x[3];
  l_x_tmp = ((k_x_tmp + a21) - c_x_tmp) - x_tmp_tmp;
  F[218] = dt * l_x_tmp;
  b_x_tmp = 2.0 * x[0] * x[3];
  accelBiasDecayFactor = 2.0 * x[1] * x[2];
  x_tmp = b_x_tmp - accelBiasDecayFactor;
  F[234] = -dt * x_tmp;
  f_x_tmp = 2.0 * x[0] * x[2];
  h_x_tmp = 2.0 * x[1] * x[3];
  e_x_tmp = f_x_tmp + h_x_tmp;
  F[250] = dt * e_x_tmp;
  gyroBiasDecayFactor *= dt;
  F[11] = gyroBiasDecayFactor;
  F[27] = -dt * h_F_tmp;
  F[43] = g_F_tmp;
  F[59] = b_F_tmp;
  F[75] = 0.0;
  F[91] = 0.0;
  F[107] = 0.0;
  F[123] = 0.0;
  F[139] = 0.0;
  F[155] = 0.0;
  F[171] = 0.0;
  F[187] = 1.0;
  F[203] = 0.0;
  b_F_tmp = b_x_tmp + accelBiasDecayFactor;
  F[219] = dt * b_F_tmp;
  h_F_tmp = k_x_tmp - a21;
  k_x_tmp = (h_F_tmp + c_x_tmp) - x_tmp_tmp;
  F[235] = dt * k_x_tmp;
  a21 = 2.0 * x[0] * x[1];
  b_x_tmp = 2.0 * x[2] * x[3];
  accelBiasDecayFactor = a21 - b_x_tmp;
  F[251] = -dt * accelBiasDecayFactor;
  F[12] = j_F_tmp;
  F[28] = gyroBiasDecayFactor;
  F[44] = -dt * d_x_tmp;
  F[60] = g_F_tmp;
  F[76] = 0.0;
  F[92] = 0.0;
  F[108] = 0.0;
  F[124] = 0.0;
  F[140] = 0.0;
  F[156] = 0.0;
  F[172] = 0.0;
  F[188] = 0.0;
  F[204] = 1.0;
  g_F_tmp = f_x_tmp - h_x_tmp;
  F[220] = -dt * g_F_tmp;
  j_F_tmp = a21 + b_x_tmp;
  F[236] = dt * j_F_tmp;
  h_F_tmp = (h_F_tmp - c_x_tmp) + x_tmp_tmp;
  F[252] = dt * h_F_tmp;
  F[13] = 0.0;
  F[29] = 0.0;
  F[45] = 0.0;
  F[61] = 0.0;
  F[77] = 0.0;
  F[93] = 0.0;
  F[109] = 0.0;
  F[125] = 0.0;
  F[141] = 0.0;
  F[157] = 0.0;
  F[173] = 0.0;
  F[189] = 0.0;
  F[205] = 0.0;
  F[221] = 1.0 - b_x_tmp_tmp;
  F[237] = 0.0;
  F[253] = 0.0;
  F[14] = 0.0;
  F[30] = 0.0;
  F[46] = 0.0;
  F[62] = 0.0;
  F[78] = 0.0;
  F[94] = 0.0;
  F[110] = 0.0;
  F[126] = 0.0;
  F[142] = 0.0;
  F[158] = 0.0;
  F[174] = 0.0;
  F[190] = 0.0;
  F[206] = 0.0;
  F[222] = 0.0;
  F[238] = 1.0 - b_x_tmp_tmp;
  F[254] = 0.0;
  F[15] = 0.0;
  F[31] = 0.0;
  F[47] = 0.0;
  F[63] = 0.0;
  F[79] = 0.0;
  F[95] = 0.0;
  F[111] = 0.0;
  F[127] = 0.0;
  F[143] = 0.0;
  F[159] = 0.0;
  F[175] = 0.0;
  F[191] = 0.0;
  F[207] = 0.0;
  F[223] = 0.0;
  F[239] = 0.0;
  F[255] = 1.0 - b_x_tmp_tmp;
  G[0] = F_tmp;
  G[16] = i_F_tmp;
  G[32] = c_F_tmp;
  G[48] = 0.0;
  G[64] = 0.0;
  G[80] = 0.0;
  G[96] = 0.0;
  G[112] = 0.0;
  G[128] = 0.0;
  G[144] = 0.0;
  G[160] = 0.0;
  G[176] = 0.0;
  gyroBiasDecayFactor = g_x_tmp / 2.0;
  G[1] = gyroBiasDecayFactor;
  G[17] = c_F_tmp;
  G[33] = e_F_tmp;
  G[49] = 0.0;
  G[65] = 0.0;
  G[81] = 0.0;
  G[97] = 0.0;
  G[113] = 0.0;
  G[129] = 0.0;
  G[145] = 0.0;
  G[161] = 0.0;
  G[177] = 0.0;
  G[2] = f_F_tmp;
  G[18] = gyroBiasDecayFactor;
  G[34] = F_tmp;
  G[50] = 0.0;
  G[66] = 0.0;
  G[82] = 0.0;
  G[98] = 0.0;
  G[114] = 0.0;
  G[130] = 0.0;
  G[146] = 0.0;
  G[162] = 0.0;
  G[178] = 0.0;
  G[3] = i_F_tmp;
  G[19] = d_F_tmp;
  G[35] = gyroBiasDecayFactor;
  G[51] = 0.0;
  G[67] = 0.0;
  G[83] = 0.0;
  G[99] = 0.0;
  G[115] = 0.0;
  G[131] = 0.0;
  G[147] = 0.0;
  G[163] = 0.0;
  G[179] = 0.0;
  G[10] = 0.0;
  G[26] = 0.0;
  G[42] = 0.0;
  G[58] = 0.0;
  G[74] = 0.0;
  G[90] = 0.0;
  G[106] = -dt * l_x_tmp;
  G[122] = dt * x_tmp;
  G[138] = -dt * e_x_tmp;
  G[154] = 0.0;
  G[170] = 0.0;
  G[186] = 0.0;
  G[11] = 0.0;
  G[27] = 0.0;
  G[43] = 0.0;
  G[59] = 0.0;
  G[75] = 0.0;
  G[91] = 0.0;
  G[107] = -dt * b_F_tmp;
  G[123] = -dt * k_x_tmp;
  G[139] = dt * accelBiasDecayFactor;
  G[155] = 0.0;
  G[171] = 0.0;
  G[187] = 0.0;
  G[12] = 0.0;
  G[28] = 0.0;
  G[44] = 0.0;
  G[60] = 0.0;
  G[76] = 0.0;
  G[92] = 0.0;
  G[108] = dt * g_F_tmp;
  G[124] = -dt * j_F_tmp;
  G[140] = -dt * h_F_tmp;
  G[156] = 0.0;
  G[172] = 0.0;
  G[188] = 0.0;
  for (i = 0; i < 12; i++) {
    G_tmp = i << 4;
    G[G_tmp + 4] = 0.0;
    G[G_tmp + 5] = 0.0;
    G[G_tmp + 6] = 0.0;
    G[G_tmp + 7] = 0.0;
    G[G_tmp + 8] = 0.0;
    G[G_tmp + 9] = 0.0;
    G[G_tmp + 13] = 0.0;
    G[G_tmp + 14] = 0.0;
    G[G_tmp + 15] = 0.0;
  }
  gyroBiasDecayFactor = gndFusion->GyroscopeNoise[0];
  k_x_tmp = gndFusion->GyroscopeNoise[1];
  l_x_tmp = gndFusion->GyroscopeNoise[2];
  std::memset(&gyroVar[0], 0, 9U * sizeof(double));
  gyroVar[0] = gyroBiasDecayFactor;
  gyroVar[4] = k_x_tmp;
  gyroVar[8] = l_x_tmp;
  gyroBiasDecayFactor = gndFusion->GyroscopeBiasNoise[0];
  k_x_tmp = gndFusion->GyroscopeBiasNoise[1];
  l_x_tmp = gndFusion->GyroscopeBiasNoise[2];
  std::memset(&gyroBiasVar[0], 0, 9U * sizeof(double));
  gyroBiasVar[0] = gyroBiasDecayFactor;
  gyroBiasVar[4] = k_x_tmp;
  gyroBiasVar[8] = l_x_tmp;
  gyroBiasDecayFactor = gndFusion->AccelerometerNoise[0];
  k_x_tmp = gndFusion->AccelerometerNoise[1];
  l_x_tmp = gndFusion->AccelerometerNoise[2];
  std::memset(&accelVar[0], 0, 9U * sizeof(double));
  accelVar[0] = gyroBiasDecayFactor;
  accelVar[4] = k_x_tmp;
  accelVar[8] = l_x_tmp;
  gyroBiasDecayFactor = gndFusion->AccelerometerBiasNoise[0];
  k_x_tmp = gndFusion->AccelerometerBiasNoise[1];
  l_x_tmp = gndFusion->AccelerometerBiasNoise[2];
  std::memset(&accelBiasVar[0], 0, 9U * sizeof(double));
  accelBiasVar[0] = gyroBiasDecayFactor;
  accelBiasVar[4] = k_x_tmp;
  accelBiasVar[8] = l_x_tmp;
  std::memset(&U[0], 0, 144U * sizeof(double));
  for (i = 0; i < 3; i++) {
    U[12 * i] = gyroVar[3 * i];
    G_tmp = 12 * (i + 3);
    U[G_tmp + 3] = gyroBiasVar[3 * i];
    r1 = 12 * (i + 6);
    U[r1 + 6] = accelVar[3 * i];
    U_tmp = 12 * (i + 9);
    U[U_tmp + 9] = accelBiasVar[3 * i];
    r2 = 3 * i + 1;
    U[12 * i + 1] = gyroVar[r2];
    U[G_tmp + 4] = gyroBiasVar[r2];
    U[r1 + 7] = accelVar[r2];
    U[U_tmp + 10] = accelBiasVar[r2];
    r2 = 3 * i + 2;
    U[12 * i + 2] = gyroVar[r2];
    U[G_tmp + 5] = gyroBiasVar[r2];
    U[r1 + 8] = accelVar[r2];
    U[U_tmp + 11] = accelBiasVar[r2];
  }
  for (i = 0; i < 16; i++) {
    for (i1 = 0; i1 < 16; i1++) {
      gyroBiasDecayFactor = 0.0;
      for (r1 = 0; r1 < 16; r1++) {
        gyroBiasDecayFactor +=
            F[i + (r1 << 4)] * gndFusion->pStateCovariance[r1 + (i1 << 4)];
      }
      c_F[i + (i1 << 4)] = gyroBiasDecayFactor;
    }
    for (i1 = 0; i1 < 12; i1++) {
      gyroBiasDecayFactor = 0.0;
      for (r1 = 0; r1 < 12; r1++) {
        gyroBiasDecayFactor += G[i + (r1 << 4)] * U[r1 + 12 * i1];
      }
      c_G[i + (i1 << 4)] = gyroBiasDecayFactor;
    }
    for (i1 = 0; i1 < 16; i1++) {
      gyroBiasDecayFactor = 0.0;
      for (r1 = 0; r1 < 16; r1++) {
        G_tmp = r1 << 4;
        gyroBiasDecayFactor += c_F[i + G_tmp] * F[i1 + G_tmp];
      }
      U_tmp = i + (i1 << 4);
      b_F[U_tmp] = gyroBiasDecayFactor;
      gyroBiasDecayFactor = 0.0;
      for (r1 = 0; r1 < 12; r1++) {
        G_tmp = r1 << 4;
        gyroBiasDecayFactor += c_G[i + G_tmp] * G[i1 + G_tmp];
      }
      b_G[U_tmp] = gyroBiasDecayFactor;
    }
  }
  for (i = 0; i < 256; i++) {
    gndFusion->pStateCovariance[i] = b_F[i] + b_G[i];
  }
  G_tmp = gndFusion->applyConstraintCount;
  if (G_tmp > 2147483646) {
    G_tmp = MAX_int32_T;
  } else {
    G_tmp++;
  }
  gndFusion->applyConstraintCount = G_tmp;
  if (gndFusion->applyConstraintCount == gndFusion->DecimationFactor) {
    for (i = 0; i < 16; i++) {
      x[i] = gndFusion->pState[i];
    }
    for (i = 0; i < 256; i++) {
      F[i] = gndFusion->pStateCovariance[i];
    }
    k_x_tmp = 2.0 * x[3] * x[10];
    l_x_tmp = 2.0 * x[0] * x[11];
    x_tmp = 2.0 * x[1] * x[12];
    H[0] = (x_tmp + l_x_tmp) - k_x_tmp;
    gyroBiasDecayFactor =
        (2.0 * x[0] * x[12] - 2.0 * x[1] * x[11]) + 2.0 * x[2] * x[10];
    H[2] = gyroBiasDecayFactor;
    a21 = (2.0 * x[3] * x[12] + 2.0 * x[2] * x[11]) + 2.0 * x[1] * x[10];
    H[4] = a21;
    e_x_tmp = 2.0 * x[3] * x[11];
    accelBiasDecayFactor = 2.0 * x[2] * x[12];
    c_x_tmp = 2.0 * x[0] * x[10];
    H[6] = (accelBiasDecayFactor - e_x_tmp) - c_x_tmp;
    H[8] = 0.0;
    H[10] = 0.0;
    H[12] = 0.0;
    H[14] = 0.0;
    H[16] = 0.0;
    H[18] = 0.0;
    H[20] = 2.0 * x[1] * x[2] - 2.0 * x[0] * x[3];
    x_tmp_tmp = x[0] * x[0] - x[1] * x[1];
    b_x_tmp = x[2] * x[2];
    f_x_tmp = x[3] * x[3];
    H[22] = (x_tmp_tmp + b_x_tmp) - f_x_tmp;
    h_x_tmp = 2.0 * x[2] * x[3];
    d_x_tmp = 2.0 * x[0] * x[1];
    H[24] = d_x_tmp + h_x_tmp;
    H[26] = 0.0;
    H[28] = 0.0;
    H[30] = 0.0;
    H[1] = gyroBiasDecayFactor;
    H[3] = (k_x_tmp - l_x_tmp) - x_tmp;
    H[5] = (e_x_tmp - accelBiasDecayFactor) + c_x_tmp;
    H[7] = a21;
    H[9] = 0.0;
    H[11] = 0.0;
    H[13] = 0.0;
    H[15] = 0.0;
    H[17] = 0.0;
    H[19] = 0.0;
    H[21] = 2.0 * x[0] * x[2] + 2.0 * x[1] * x[3];
    H[23] = h_x_tmp - d_x_tmp;
    H[25] = (x_tmp_tmp - b_x_tmp) + f_x_tmp;
    H[27] = 0.0;
    H[29] = 0.0;
    H[31] = 0.0;
    zeroVelVar[0] = gndFusion->ZeroVelocityConstraintNoise;
    zeroVelVar[1] = gndFusion->ZeroVelocityConstraintNoise * 0.0;
    zeroVelVar[2] = gndFusion->ZeroVelocityConstraintNoise * 0.0;
    zeroVelVar[3] = gndFusion->ZeroVelocityConstraintNoise;
    for (i = 0; i < 2; i++) {
      for (i1 = 0; i1 < 16; i1++) {
        U_tmp = i + (i1 << 1);
        W[i1 + (i << 4)] = H[U_tmp];
        gyroBiasDecayFactor = 0.0;
        for (r1 = 0; r1 < 16; r1++) {
          gyroBiasDecayFactor += H[i + (r1 << 1)] * F[r1 + (i1 << 4)];
        }
        b_H[U_tmp] = gyroBiasDecayFactor;
      }
    }
    for (i = 0; i < 2; i++) {
      for (i1 = 0; i1 < 2; i1++) {
        gyroBiasDecayFactor = 0.0;
        for (r1 = 0; r1 < 16; r1++) {
          gyroBiasDecayFactor += b_H[i + (r1 << 1)] * W[r1 + (i1 << 4)];
        }
        G_tmp = i + (i1 << 1);
        innovCov[G_tmp] = gyroBiasDecayFactor + zeroVelVar[G_tmp];
      }
    }
    for (i = 0; i < 16; i++) {
      for (i1 = 0; i1 < 2; i1++) {
        gyroBiasDecayFactor = 0.0;
        for (r1 = 0; r1 < 16; r1++) {
          gyroBiasDecayFactor += F[i + (r1 << 4)] * W[r1 + (i1 << 4)];
        }
        b_H[i + (i1 << 4)] = gyroBiasDecayFactor;
      }
    }
    if (std::abs(innovCov[1]) > std::abs(innovCov[0])) {
      r1 = 1;
      r2 = 0;
    } else {
      r1 = 0;
      r2 = 1;
    }
    a21 = innovCov[r2] / innovCov[r1];
    e_x_tmp = innovCov[r1 + 2];
    accelBiasDecayFactor = innovCov[r2 + 2] - a21 * e_x_tmp;
    gyroBiasDecayFactor = (x[0] * x[12] - x[1] * x[11]) + x[2] * x[10];
    k_x_tmp = (x[1] * x[12] + x[0] * x[11]) - x[3] * x[10];
    l_x_tmp = (x[3] * x[11] - x[2] * x[12]) + x[0] * x[10];
    x_tmp = (x[3] * x[12] + x[2] * x[11]) + x[1] * x[10];
    c_x_tmp =
        0.0 - (((x[0] * k_x_tmp + x[1] * gyroBiasDecayFactor) + x[2] * x_tmp) -
               x[3] * l_x_tmp);
    k_x_tmp =
        0.0 -
        (((x[0] * gyroBiasDecayFactor - x[1] * k_x_tmp) + x[2] * l_x_tmp) +
         x[3] * x_tmp);
    for (int k{0}; k < 16; k++) {
      U_tmp = k + (r1 << 4);
      W[U_tmp] = b_H[k] / innovCov[r1];
      G_tmp = k + (r2 << 4);
      W[G_tmp] = (b_H[k + 16] - W[U_tmp] * e_x_tmp) / accelBiasDecayFactor;
      W[U_tmp] -= W[G_tmp] * a21;
      gyroBiasDecayFactor = W[k + 16];
      x[k] += W[k] * c_x_tmp + gyroBiasDecayFactor * k_x_tmp;
      for (i = 0; i < 16; i++) {
        i1 = i << 1;
        b_G[k + (i << 4)] = W[k] * H[i1] + gyroBiasDecayFactor * H[i1 + 1];
      }
      for (i = 0; i < 16; i++) {
        gyroBiasDecayFactor = 0.0;
        for (i1 = 0; i1 < 16; i1++) {
          gyroBiasDecayFactor += b_G[k + (i1 << 4)] * F[i1 + (i << 4)];
        }
        U_tmp = k + (i << 4);
        c_F[U_tmp] = F[U_tmp] - gyroBiasDecayFactor;
      }
    }
    std::copy(&c_F[0], &c_F[256], &F[0]);
    gndFusion->repairQuaternion(x);
    std::copy(&F[0], &F[256], &gndFusion->pStateCovariance[0]);
    std::copy(&x[0], &x[16], &gndFusion->pState[0]);
    gndFusion->applyConstraintCount = 0;
  }
}

//
// File trailer for EKalmanGND.cpp
//
// [EOF]
//
