//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: test.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 23-Dec-2022 16:50:05
//

#ifndef TEST_H
#define TEST_H

// Include Files
#include "quaternion.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void test(const double b_initstate[16], double imuFs,
                 const double lla[3], const double gpsvel[3], double Rpos,
                 double Rvel, const double accel[3], const double gyro[3],
                 const double localOrigin[3], const double Qnoise[4],
                 double zCst, coder::quaternion *fusedOrient,
                 double fusedPos[3]);

#endif
//
// File trailer for test.h
//
// [EOF]
//
