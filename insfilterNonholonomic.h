//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: insfilterNonholonomic.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 23-Dec-2022 16:50:05
//

#ifndef INSFILTERNONHOLONOMIC_H
#define INSFILTERNONHOLONOMIC_H

// Include Files
#include "ENU.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
class insfilterNonholonomic {
public:
  void repairQuaternion(double x[16]) const;
  double OrientationIdx[4];
  fusion::internal::frames::ENU ReferenceFrameObject;
  double ReferenceLocation[3];
  double IMUSampleRate;
  int DecimationFactor;
  double GyroscopeNoise[3];
  double AccelerometerNoise[3];
  double GyroscopeBiasNoise[3];
  double GyroscopeBiasDecayFactor;
  double AccelerometerBiasNoise[3];
  double AccelerometerBiasDecayFactor;
  double ZeroVelocityConstraintNoise;
  int applyConstraintCount;
  double pState[16];
  double pStateCovariance[256];
};

} // namespace coder

#endif
//
// File trailer for insfilterNonholonomic.h
//
// [EOF]
//
