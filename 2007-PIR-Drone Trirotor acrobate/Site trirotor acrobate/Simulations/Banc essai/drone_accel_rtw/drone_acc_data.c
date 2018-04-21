/*
 * drone_acc_data.c
 *
 * Real-Time Workshop code generation for Simulink model "drone_acc.mdl".
 *
 * Model Version              : 1.833
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Thu Dec 28 10:01:42 2006
 */

#include "drone_acc.h"
#include "drone_acc_private.h"

/* Invariant block signals (auto storage) */
drone_ConstBlockIO drone_InvariantSignals = {
  { 0.0, 0.0, -5.7735026918962573E-001, 0.0, 5.7735026918962573E-001, 0.0,
    6.6666666666666663E-001, 0.0, -3.3333333333333331E-001, 0.0,
    -3.3333333333333331E-001, 0.0, 0.0, 3.3333333333333331E-001, 0.0,
    3.3333333333333331E-001, 0.0, 3.3333333333333331E-001, 0.0, 0.0, 0.0,
    -5.7735026918962573E-001, 0.0, 5.7735026918962573E-001, 0.0,
    6.6666666666666663E-001, 0.0, -3.3333333333333331E-001, 0.0,
    -3.3333333333333331E-001, 3.3333333333333331E-001, 0.0,
    3.3333333333333331E-001, 0.0, 3.3333333333333331E-001, 0.0 } , /* <S6>/Matrice Transformation */
  { -1.0, -1.0, 1.0, -3.125, -3.125, -3.125 } , /* <S6>/Matrice Correction */
  17.0 ,                                /* <S11>/Constant */
  1.5707963267948966E+000 ,             /* <S12>/Constant1 */
  3.1415926535897931E+000 ,             /* <S12>/Constant */
  1.5707963267948966E+000 ,             /* <S12>/Constant2 */
  17.0 ,                                /* <S14>/Constant */
  1.5707963267948966E+000 ,             /* <S15>/Constant1 */
  3.1415926535897931E+000 ,             /* <S15>/Constant */
  1.5707963267948966E+000 ,             /* <S15>/Constant2 */
  17.0 ,                                /* <S17>/Constant */
  1.5707963267948966E+000 ,             /* <S18>/Constant1 */
  3.1415926535897931E+000 ,             /* <S18>/Constant */
  1.5707963267948966E+000 ,             /* <S18>/Constant2 */
  { 0.0, 0.0, 0.0 } ,                   /* <S34>/SOURCE_BLOCK */
  { 0.0, 0.0, 0.0 } ,                   /* <S38>/_gravity_conversion */
  0.0 ,                                 /* <S20>/sensor */
  0.0 ,                                 /* <S21>/sensor */
  0.0 ,                                 /* <S22>/sensor */
  0.0 ,                                 /* <S35>/sensor */
  0.0 ,                                 /* <S36>/sensor */
  0.0 ,                                 /* <S37>/sensor */
  0.0                                   /* <S33>/sensor */
};

/* Constant parameters (auto storage) */
const ConstParam_drone_acc drone_acc_rtcP = {
  /* Expression: [0 0 0 0 0 0]
   * Referenced by blocks:
   * '<S1>/Random Number1'
   * '<S1>/Random Number'
   * '<S1>/Random Number2'
   * '<S1>/Random Number3'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ,
  /* Computed Parameter: StdDev
   * Referenced by blocks:
   * '<S1>/Random Number1'
   * '<S1>/Random Number'
   * '<S1>/Random Number2'
   * '<S1>/Random Number3'
   */
  { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 } ,
  /* Expression: Perturbation
   * Referenced by blocks:
   * '<S1>/Gain'
   * '<S8>/Saturation'
   * '<S9>/Saturation'
   * '<S10>/Saturation'
   */
  0.5 ,
  /* Computed Parameter: A
   * Referenced by blocks:
   * '<S4>/Transfer Fcn2'
   * '<S4>/Transfer Fcn'
   * '<S4>/Transfer Fcn1'
   */
  -20.0 ,
  /* Computed Parameter: B
   * Referenced by blocks:
   * '<S4>/Transfer Fcn2'
   * '<S4>/Transfer Fcn'
   * '<S4>/Transfer Fcn1'
   */
  1.0 ,
  /* Computed Parameter: C
   * Referenced by blocks:
   * '<S4>/Transfer Fcn2'
   * '<S4>/Transfer Fcn'
   * '<S4>/Transfer Fcn1'
   */
  20.0 ,
  /* Expression: [0 0 1]
   * Referenced by blocks:
   * '<S4>/Gain2'
   * '<S4>/Gain1'
   * '<S4>/Gain3'
   */
  { 0.0, 0.0, 1.0 } ,
  /* Expression: (1/3)*[0 2 0 0 0 1; 0 0 1 0 2 0; -sqrt(3) -1 0 0 0 1; 0 0 1 -sqrt(3) -1 0; sqrt(3) -1 0 0 0 1; 0 0 1 sqrt(3) -1 0]
   * '<S6>/Matrice Transformation'
   */
  { 0.0, 0.0, -5.7735026918962573E-001, 0.0, 5.7735026918962573E-001, 0.0,
    6.6666666666666663E-001, 0.0, -3.3333333333333331E-001, 0.0,
    -3.3333333333333331E-001, 0.0, 0.0, 3.3333333333333331E-001, 0.0,
    3.3333333333333331E-001, 0.0, 3.3333333333333331E-001, 0.0, 0.0, 0.0,
    -5.7735026918962573E-001, 0.0, 5.7735026918962573E-001, 0.0,
    6.6666666666666663E-001, 0.0, -3.3333333333333331E-001, 0.0,
    -3.3333333333333331E-001, 3.3333333333333331E-001, 0.0,
    3.3333333333333331E-001, 0.0, 3.3333333333333331E-001, 0.0 } ,
  /* Expression: [-1 -1 1 -1/l -1/l -1/l]
   * '<S6>/Matrice Correction'
   */
  { -1.0, -1.0, 1.0, -3.125, -3.125, -3.125 } ,
  /* Computed Parameter: SimMechanicsRuntimeParametersSize
   * '<S38>/Block#1'
   */
  { 175.0, 0.0 } ,
  /* Computed Parameter: SimMechanicsRuntimeParameters
   * '<S38>/Block#1'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 120.0, 0.0, 0.0, 0.0, 0.0, 0.0, 240.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.32, 0.0, 0.0, 0.0, 0.0, 0.0, 0.01,
    0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.01, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.32, 0.0, 0.0, 0.0, 0.0, 0.0, 0.32, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.32, 0.0, 0.0, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0,
    0.01, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.32, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.32, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.32, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.01, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.01, 0.1, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.32, 0.0, 0.0, 0.0, 0.0, 0.0, 0.32, 0.0, 0.0, 0.0, 0.0, 0.0 } ,
  /* Expression: N
   * Referenced by blocks:
   * '<S11>/Constant'
   * '<S14>/Constant'
   * '<S17>/Constant'
   */
  17.0 ,
  /* Expression: 0
   * Referenced by blocks:
   * '<S8>/Integrator'
   * '<S9>/Integrator'
   * '<S10>/Integrator'
   */
  0.0 ,
  /* Expression: pi/2
   * Referenced by blocks:
   * '<S12>/Constant1'
   * '<S12>/Constant2'
   * '<S15>/Constant1'
   * '<S15>/Constant2'
   * '<S18>/Constant1'
   * '<S18>/Constant2'
   */
  1.5707963267948966E+000 ,
  /* Expression: pi
   * Referenced by blocks:
   * '<S12>/Constant'
   * '<S15>/Constant'
   * '<S18>/Constant'
   */
  3.1415926535897931E+000 ,
  /* Expression: Kp
   * Referenced by blocks:
   * '<S8>/Gain'
   * '<S9>/Gain'
   * '<S10>/Gain'
   */
  60.0 ,
  /* Expression: Kd
   * Referenced by blocks:
   * '<S8>/Gain2'
   * '<S9>/Gain2'
   * '<S10>/Gain2'
   */
  0.08 ,
  /* Expression: -0.5
   * Referenced by blocks:
   * '<S8>/Saturation'
   * '<S9>/Saturation'
   * '<S10>/Saturation'
   */
  -0.5 ,
  /* Expression: Cfrot
   * Referenced by blocks:
   * '<S4>/Gain6'
   * '<S4>/Gain5'
   * '<S4>/Gain4'
   */
  0.05 ,
  /* Expression: Gravity
   * '<S34>/SOURCE_BLOCK'
   */
  { 0.0, 0.0, 0.0 } ,
  /* Expression: -1
   * '<S38>/_gravity_conversion'
   */
  -1.0 ,
  /* Expression: Ki
   * Referenced by blocks:
   * '<S8>/Gain1'
   * '<S9>/Gain1'
   * '<S10>/Gain1'
   */
  0.02
};

