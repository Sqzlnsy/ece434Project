//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: test.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 23-Dec-2022 16:50:05
//

// Include Files
#include "test.h"
#include "EKalmanGND.h"
#include "insfilterNonholonomic.h"
#include "quaternion.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const double b_initstate[16]
//                double imuFs
//                const double lla[3]
//                const double gpsvel[3]
//                double Rpos
//                double Rvel
//                const double accel[3]
//                const double gyro[3]
//                const double localOrigin[3]
//                const double Qnoise[4]
//                double zCst
//                coder::quaternion *fusedOrient
//                double fusedPos[3]
// Return Type  : void
//
void test(const double b_initstate[16], double imuFs, const double lla[3],
          const double gpsvel[3], double Rpos, double Rvel,
          const double accel[3], const double gyro[3],
          const double localOrigin[3], const double Qnoise[4], double zCst,
          coder::quaternion *fusedOrient, double fusedPos[3])
{
  EKalmanGND obj;
  coder::insfilterNonholonomic lobj_0;
  double st[16];
  double b_Rpos[2];
  int i;
  b_Rpos[0] = Rpos;
  b_Rpos[1] = Rvel;
  obj.init(b_initstate, imuFs, b_Rpos, Qnoise, zCst, localOrigin, &lobj_0);
  obj.updateGPS(lla, gpsvel);
  obj.updateIMU(accel, gyro);
  //  Acquire the current estimate of the filter states
  for (i = 0; i < 16; i++) {
    st[i] = obj.gndFusion->pState[i];
  }
  fusedOrient->a = st[0];
  fusedOrient->b = st[1];
  fusedOrient->c = st[2];
  fusedOrient->d = st[3];
  for (i = 0; i < 16; i++) {
    st[i] = obj.gndFusion->pState[i];
  }
  fusedPos[0] = st[7];
  fusedPos[1] = st[8];
  fusedPos[2] = st[9];
}

//
// File trailer for test.cpp
//
// [EOF]
//
