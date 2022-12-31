//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EKalmanGND.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 23-Dec-2022 16:50:05
//

#ifndef EKALMANGND_H
#define EKALMANGND_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class insfilterNonholonomic;

}

// Type Definitions
class EKalmanGND {
public:
  void init(const double b_initstate[16], double imuFs, const double Rnoise[2],
            const double Qnoise[4], double zvCst, const double localOrigin[3],
            coder::insfilterNonholonomic *iobj_0);
  void updateGPS(const double lla[3], const double gpsvel[3]);
  void updateIMU(const double accel[3], const double gyro[3]);
  coder::insfilterNonholonomic *gndFusion;
  double Rvel;
  double Rpos;
};

#endif
//
// File trailer for EKalmanGND.h
//
// [EOF]
//
