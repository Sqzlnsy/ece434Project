//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_test_info.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 23-Dec-2022 16:50:05
//

// Include Files
#include "_coder_test_info.h"
#include "emlrt.h"
#include "tmwtypes.h"

// Function Declarations
static const mxArray *emlrtMexFcnResolvedFunctionsInfo();

// Function Definitions
//
// Arguments    : void
// Return Type  : const mxArray *
//
static const mxArray *emlrtMexFcnResolvedFunctionsInfo()
{
  const mxArray *nameCaptureInfo;
  const char_T *data[5]{
      "789ced97ef4e825018c60fcd5ab5597ec9eea1b6b656abd6d60715232b8912fd90b44970"
      "fc170750c03f57511fbb842ea3dbe86e1a0222b43328cc9af87e797d"
      "f778ceeff5c13d1b8028140900c006b0ea7dcbea497b4ed97d0978cbaf13764ff866a796"
      "6d25e9d39fed2e28b20e07ba35c83c82e393a2825a322febec5085a0",
      "0b3545ea4171a4d45b12645b08962607da9cd0f984341e4cc9fc9c6b42e1a96420d06d6a"
      "ee86d2e430f6e305f37b13c05b383f76317ea47c7a35ff903be5ca1a"
      "ec6a9c66743852110c04655de38a19f63a93e5c8cc2da7434ddf439efdd488fbad07ece7"
      "e8f92b5e42bc4cd124f0f06b11f92b58bea5888af1284197f71a91b7",
      "8fe579f56a2ec4f3704db19f4ab02f9b21f7f477f7fbaba39edefe2066c94b9eed1ccf92"
      "e7d45ff10698fbc2fecfd2185ecaa767fbac5a3fec21a530bca3e97e"
      "e5922d9c7428770f268013b407c0ccb3babf86391fe4a3bf703efa7951f3702d80e7e886"
      "2af23aa498d294f951f3f82d229f0ae03b7af5e6bb0149b803e7ba17",
      "973c9977deacf2b27c4f578ea812d9a62f3ae57663c8f0078cb0c8cb2ff53ff3b2502c4f"
      "991fa7bc34dd8b4b9ecc3b6f9197d3b9bf8639ff5b79f9535ed8f7dd"
      "06d419459b9f7c2403f88e1e2d1f1dd7e2931ff3ce5be463b4fb3f01d4b8ef8e",
      ""};
  nameCaptureInfo = nullptr;
  emlrtNameCaptureMxArrayR2016a(&data[0], 5592U, &nameCaptureInfo);
  return nameCaptureInfo;
}

//
// Arguments    : void
// Return Type  : mxArray *
//
mxArray *emlrtMexFcnProperties()
{
  mxArray *xEntryPoints;
  mxArray *xInputs;
  mxArray *xResult;
  const char_T *epFieldName[6]{
      "Name",           "NumberOfInputs", "NumberOfOutputs",
      "ConstantInputs", "FullPath",       "TimeStamp"};
  const char_T *propFieldName[5]{"Version", "ResolvedFunctions", "EntryPoints",
                                 "CoverageInfo", "IsPolymorphic"};
  xEntryPoints =
      emlrtCreateStructMatrix(1, 1, 6, (const char_T **)&epFieldName[0]);
  xInputs = emlrtCreateLogicalMatrix(1, 11);
  emlrtSetField(xEntryPoints, 0, (const char_T *)"Name",
                emlrtMxCreateString((const char_T *)"test"));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"NumberOfInputs",
                emlrtMxCreateDoubleScalar(11.0));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"NumberOfOutputs",
                emlrtMxCreateDoubleScalar(2.0));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"ConstantInputs", xInputs);
  emlrtSetField(
      xEntryPoints, 0, (const char_T *)"FullPath",
      emlrtMxCreateString(
          (const char_T *)"C:\\Users\\suq\\Documents\\MATLAB\\DAQ\\test.m"));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"TimeStamp",
                emlrtMxCreateDoubleScalar(738878.7011689815));
  xResult =
      emlrtCreateStructMatrix(1, 1, 5, (const char_T **)&propFieldName[0]);
  emlrtSetField(
      xResult, 0, (const char_T *)"Version",
      emlrtMxCreateString((const char_T *)"9.11.0.1809720 (R2021b) Update 1"));
  emlrtSetField(xResult, 0, (const char_T *)"ResolvedFunctions",
                (mxArray *)emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, (const char_T *)"EntryPoints", xEntryPoints);
  return xResult;
}

//
// File trailer for _coder_test_info.cpp
//
// [EOF]
//
