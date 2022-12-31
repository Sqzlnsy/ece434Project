//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 23-Dec-2022 16:50:05
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include Files
#include "main.h"
#include "quaternion.h"
#include "rt_nonfinite.h"
#include "test.h"
#include "test_terminate.h"

// Function Declarations
static void argInit_16x1_real_T(double result[16]);

static void argInit_1x3_real_T(double result[3]);

static void argInit_1x4_real_T(double result[4]);

static double argInit_real_T();

static void main_test();

// Function Definitions
//
// Arguments    : double result[16]
// Return Type  : void
//
static void argInit_16x1_real_T(double result[16])
{
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < 16; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
  }
}

//
// Arguments    : double result[3]
// Return Type  : void
//
static void argInit_1x3_real_T(double result[3])
{
  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < 3; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = argInit_real_T();
  }
}

//
// Arguments    : double result[4]
// Return Type  : void
//
static void argInit_1x4_real_T(double result[4])
{
  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < 4; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = argInit_real_T();
  }
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_test()
{
  coder::quaternion fusedOrient;
  double dv[16];
  double dv1[4];
  double fusedPos[3];
  double lla_tmp[3];
  double imuFs_tmp;
  // Initialize function 'test' input arguments.
  // Initialize function input argument 'initstate'.
  imuFs_tmp = argInit_real_T();
  // Initialize function input argument 'lla'.
  argInit_1x3_real_T(lla_tmp);
  // Initialize function input argument 'gpsvel'.
  // Initialize function input argument 'accel'.
  // Initialize function input argument 'gyro'.
  // Initialize function input argument 'localOrigin'.
  // Initialize function input argument 'Qnoise'.
  // Call the entry-point 'test'.
  argInit_16x1_real_T(dv);
  argInit_1x4_real_T(dv1);
  test(dv, imuFs_tmp, lla_tmp, lla_tmp, imuFs_tmp, imuFs_tmp, lla_tmp, lla_tmp,
       lla_tmp, dv1, imuFs_tmp, &fusedOrient, fusedPos);
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int, char **)
{
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  main_test();
  // Terminate the application.
  // You do not need to do this more than one time.
  test_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
