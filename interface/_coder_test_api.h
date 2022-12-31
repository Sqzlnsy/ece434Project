//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_test_api.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 23-Dec-2022 16:50:05
//

#ifndef _CODER_TEST_API_H
#define _CODER_TEST_API_H

// Include Files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Type Definitions
struct quaternion_tag_0 {
  real_T a;
  real_T b;
  real_T c;
  real_T d;
};
typedef quaternion_tag_0 quaternion;

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void test(real_T b_initstate[16], real_T imuFs, real_T lla[3], real_T gpsvel[3],
          real_T Rpos, real_T Rvel, real_T accel[3], real_T gyro[3],
          real_T localOrigin[3], real_T Qnoise[4], real_T zCst,
          quaternion *fusedOrient, real_T fusedPos[3]);

void test_api(const mxArray *const prhs[11], int32_T nlhs,
              const mxArray *plhs[2]);

void test_atexit();

void test_initialize();

void test_terminate();

void test_xil_shutdown();

void test_xil_terminate();

#endif
//
// File trailer for _coder_test_api.h
//
// [EOF]
//
