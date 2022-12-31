//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_test_api.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 23-Dec-2022 16:50:05
//

// Include Files
#include "_coder_test_api.h"
#include "_coder_test_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131611U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "test",                                               // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *imuFs,
                                 const char_T *identifier);

static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *lla,
                                   const char_T *identifier))[3];

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[3];

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Qnoise,
                                   const char_T *identifier))[4];

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[4];

static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[16];

static real_T (*emlrt_marshallIn(const emlrtStack *sp,
                                 const mxArray *b_initstate,
                                 const char_T *identifier))[16];

static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId))[16];

static const mxArray *emlrt_marshallOut(const real_T u[3]);

static const mxArray *emlrt_marshallOut(const emlrtStack *sp,
                                        const quaternion u);

static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3];

static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[4];

// Function Definitions
//
// Arguments    : const emlrtStack *sp
//                const mxArray *imuFs
//                const char_T *identifier
// Return Type  : real_T
//
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *imuFs,
                                 const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(imuFs), &thisId);
  emlrtDestroyArray(&imuFs);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T
//
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = f_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *lla
//                const char_T *identifier
// Return Type  : real_T (*)[3]
//
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *lla,
                                   const char_T *identifier))[3]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[3];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = c_emlrt_marshallIn(sp, emlrtAlias(lla), &thisId);
  emlrtDestroyArray(&lla);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T (*)[3]
//
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[3]
{
  real_T(*y)[3];
  y = g_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *Qnoise
//                const char_T *identifier
// Return Type  : real_T (*)[4]
//
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Qnoise,
                                   const char_T *identifier))[4]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[4];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(Qnoise), &thisId);
  emlrtDestroyArray(&Qnoise);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T (*)[4]
//
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[4]
{
  real_T(*y)[4];
  y = h_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T (*)[16]
//
static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[16]
{
  static const int32_T dims{16};
  real_T(*ret)[16];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 1U, (void *)&dims);
  ret = (real_T(*)[16])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *b_initstate
//                const char_T *identifier
// Return Type  : real_T (*)[16]
//
static real_T (*emlrt_marshallIn(const emlrtStack *sp,
                                 const mxArray *b_initstate,
                                 const char_T *identifier))[16]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[16];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = emlrt_marshallIn(sp, emlrtAlias(b_initstate), &thisId);
  emlrtDestroyArray(&b_initstate);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T (*)[16]
//
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId))[16]
{
  real_T(*y)[16];
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const real_T u[3]
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const real_T u[3])
{
  static const int32_T iv[2]{0, 0};
  static const int32_T iv1[2]{1, 3};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const quaternion u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const emlrtStack *sp,
                                        const quaternion u)
{
  const mxArray *propValues[4];
  const mxArray *b_y;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  const mxArray *m;
  const mxArray *m1;
  const mxArray *m2;
  const mxArray *m3;
  const mxArray *m4;
  const mxArray *y;
  const char_T *propClasses[4]{
      "matlabshared.rotations.internal.quaternionBase",
      "matlabshared.rotations.internal.quaternionBase",
      "matlabshared.rotations.internal.quaternionBase",
      "matlabshared.rotations.internal.quaternionBase"};
  const char_T *propNames[4]{"a", "b", "c", "d"};
  y = nullptr;
  m = nullptr;
  m1 = nullptr;
  m2 = nullptr;
  m3 = nullptr;
  emlrtAssign(
      &y,
      emlrtCreateClassInstance((
          const char_T *)"matlabshared.rotations.internal.coder.quaternioncg"));
  m = nullptr;
  b_y = nullptr;
  m4 = emlrtCreateDoubleScalar(u.a);
  emlrtAssign(&b_y, m4);
  emlrtAssign(&m, b_y);
  propValues[0] = m;
  m1 = nullptr;
  c_y = nullptr;
  m4 = emlrtCreateDoubleScalar(u.b);
  emlrtAssign(&c_y, m4);
  emlrtAssign(&m1, c_y);
  propValues[1] = m1;
  m2 = nullptr;
  d_y = nullptr;
  m4 = emlrtCreateDoubleScalar(u.c);
  emlrtAssign(&d_y, m4);
  emlrtAssign(&m2, d_y);
  propValues[2] = m2;
  m3 = nullptr;
  e_y = nullptr;
  m4 = emlrtCreateDoubleScalar(u.d);
  emlrtAssign(&e_y, m4);
  emlrtAssign(&m3, e_y);
  propValues[3] = m3;
  emlrtSetAllProperties((emlrtCTX)sp, &y, 0, 4, (const char_T **)&propNames[0],
                        (const char_T **)&propClasses[0], &propValues[0]);
  emlrtAssign(&y,
              emlrtConvertInstanceToRedirectSource(
                  (emlrtCTX)sp, y, 0,
                  (const char_T
                       *)"matlabshared.rotations.internal.coder.quaternioncg"));
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T
//
static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims{0};
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 0U, (void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T (*)[3]
//
static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3]
{
  static const int32_T dims[2]{1, 3};
  real_T(*ret)[3];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  ret = (real_T(*)[3])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T (*)[4]
//
static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[4]
{
  static const int32_T dims[2]{1, 4};
  real_T(*ret)[4];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  ret = (real_T(*)[4])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const mxArray * const prhs[11]
//                int32_T nlhs
//                const mxArray *plhs[2]
// Return Type  : void
//
void test_api(const mxArray *const prhs[11], int32_T nlhs,
              const mxArray *plhs[2])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  quaternion fusedOrient;
  real_T(*b_initstate)[16];
  real_T(*Qnoise)[4];
  real_T(*accel)[3];
  real_T(*fusedPos)[3];
  real_T(*gpsvel)[3];
  real_T(*gyro)[3];
  real_T(*lla)[3];
  real_T(*localOrigin)[3];
  real_T Rpos;
  real_T Rvel;
  real_T imuFs;
  real_T zCst;
  st.tls = emlrtRootTLSGlobal;
  fusedPos = (real_T(*)[3])mxMalloc(sizeof(real_T[3]));
  // Marshall function inputs
  b_initstate = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "initstate");
  imuFs = b_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "imuFs");
  lla = c_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "lla");
  gpsvel = c_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "gpsvel");
  Rpos = b_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "Rpos");
  Rvel = b_emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "Rvel");
  accel = c_emlrt_marshallIn(&st, emlrtAlias(prhs[6]), "accel");
  gyro = c_emlrt_marshallIn(&st, emlrtAlias(prhs[7]), "gyro");
  localOrigin = c_emlrt_marshallIn(&st, emlrtAlias(prhs[8]), "localOrigin");
  Qnoise = d_emlrt_marshallIn(&st, emlrtAlias(prhs[9]), "Qnoise");
  zCst = b_emlrt_marshallIn(&st, emlrtAliasP(prhs[10]), "zCst");
  // Invoke the target function
  test(*b_initstate, imuFs, *lla, *gpsvel, Rpos, Rvel, *accel, *gyro,
       *localOrigin, *Qnoise, zCst, &fusedOrient, *fusedPos);
  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(&st, fusedOrient);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(*fusedPos);
  }
}

//
// Arguments    : void
// Return Type  : void
//
void test_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  test_xil_terminate();
  test_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void test_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void test_terminate()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

//
// File trailer for _coder_test_api.cpp
//
// [EOF]
//
