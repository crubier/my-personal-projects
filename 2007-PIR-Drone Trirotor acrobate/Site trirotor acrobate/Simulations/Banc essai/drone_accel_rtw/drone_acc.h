/*
 * drone_acc.h
 *
 * Real-Time Workshop code generation for Simulink model "drone_acc.mdl".
 *
 * Model Version              : 1.833
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Thu Dec 28 10:01:42 2006
 */
#ifndef _RTW_HEADER_drone_acc_h_
#define _RTW_HEADER_drone_acc_h_

#include <stdlib.h>
#include <math.h>
#include <float.h>
#define S_FUNCTION_NAME                 simulink_only_sfcn
#define S_FUNCTION_LEVEL                2
#define RTW_GENERATED_S_FUNCTION

#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_nonfinite.h"
#include "rtlibsrc.h"

#include "drone_acc_types.h"

/* Block signals (auto storage) */
typedef struct _drone_BlockIO {
  real_T Gain[24];                      /* '<S1>/Gain' */
  real_T Gain2[3];                      /* '<S4>/Gain2' */
  real_T Reshape2[6];                   /* '<S5>/Reshape2' */
  real_T Block1_o1[6];                  /* '<S38>/Block#1' */
  real_T Block1_o2[6];                  /* '<S38>/Block#1' */
  real_T Block1_o3;                     /* '<S38>/Block#1' */
  real_T Reshape[6];                    /* '<S4>/Reshape' */
  real_T Gain2_l;                       /* '<S8>/Gain2' */
  real_T Gain2_a;                       /* '<S9>/Gain2' */
  real_T Gain2_h;                       /* '<S10>/Gain2' */
  real_T Reshape_h[6];                  /* '<S7>/Reshape' */
  real_T Sum2;                          /* '<S4>/Sum2' */
  real_T Gain1[3];                      /* '<S4>/Gain1' */
  real_T Sum1;                          /* '<S4>/Sum1' */
  real_T Gain3[3];                      /* '<S4>/Gain3' */
  real_T Sum;                           /* '<S4>/Sum' */
  real_T Block2_o1[6];                  /* '<S38>/Block#2' */
  real_T Block2_o2;                     /* '<S38>/Block#2' */
  real_T Reshape_e[6];                  /* '<S2>/Reshape' */
  real_T Gain1_j;                       /* '<S8>/Gain1' */
  real_T Gain1_e;                       /* '<S9>/Gain1' */
  real_T Gain1_d;                       /* '<S10>/Gain1' */
  real_T Block3;                        /* '<S38>/Block#3' */
  real_T FromWs[6];                     /* '<S43>/FromWs' */
} drone_BlockIO;

/* Block states (auto storage) for system: '<Root>' */
typedef struct drone_D_Work_tag {
  struct {
    real_T NextOutput[6];
  } RandomNumber1_RWORK;                /* '<S1>/Random Number1' */
  struct {
    real_T NextOutput[6];
  } RandomNumber_RWORK;                 /* '<S1>/Random Number' */
  struct {
    real_T NextOutput[6];
  } RandomNumber2_RWORK;                /* '<S1>/Random Number2' */
  struct {
    real_T NextOutput[6];
  } RandomNumber3_RWORK;                /* '<S1>/Random Number3' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK;                   /* '<S8>/Derivative' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_g;                 /* '<S9>/Derivative' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_i;                 /* '<S10>/Derivative' */
  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWs_PWORK;                       /* '<S43>/FromWs' */
  void *Block1_PWORK;                   /* '<S38>/Block#1' */
  void *Block2_PWORK;                   /* '<S38>/Block#2' */
  struct {
    void *LoggedData;
  } VisuConsigneDynamique_PWORK;        /* '<S3>/Visu Consigne Dynamique' */
  struct {
    void *LoggedData;
  } VisuConsigneEfforts_PWORK;          /* '<S3>/Visu Consigne Efforts' */
  struct {
    void *LoggedData;
  } VisuReponsePosition_PWORK;          /* '<S3>/Visu Reponse Position' */
  struct {
    void *LoggedData;
  } VisuReponseEfforts_PWORK;           /* '<S3>/Visu Reponse Efforts' */
  void *Block3_PWORK;                   /* '<S38>/Block#3' */
  struct {
    int_T RandSeed[6];
  } RandomNumber1_IWORK;                /* '<S1>/Random Number1' */
  struct {
    int_T RandSeed[6];
  } RandomNumber_IWORK;                 /* '<S1>/Random Number' */
  struct {
    int_T RandSeed[6];
  } RandomNumber2_IWORK;                /* '<S1>/Random Number2' */
  struct {
    int_T RandSeed[6];
  } RandomNumber3_IWORK;                /* '<S1>/Random Number3' */
  struct {
    int_T PrevIndex;
  } FromWs_IWORK;                       /* '<S43>/FromWs' */
  int_T Block1_IWORK;                   /* '<S38>/Block#1' */
  int_T Block3_IWORK;                   /* '<S38>/Block#3' */
  char pad_Block3_IWORK[4];
} drone_D_Work;

/* Continuous states (auto storage) */
typedef struct _drone_ContinuousStates {
  real_T TransferFcn2_CSTATE;           /* '<S4>/Transfer Fcn2' */
  real_T TransferFcn_CSTATE;            /* '<S4>/Transfer Fcn' */
  real_T Block1_CSTATE[6];              /* '<S38>/Block#1' */
  real_T TransferFcn1_CSTATE;           /* '<S4>/Transfer Fcn1' */
  real_T Integrator_CSTATE;             /* '<S8>/Integrator' */
  real_T Integrator_f_CSTATE;           /* '<S9>/Integrator' */
  real_T Integrator_n_CSTATE;           /* '<S10>/Integrator' */
} drone_ContinuousStates;

/* State derivatives (auto storage) */
typedef struct _drone_StateDerivatives {
  real_T TransferFcn2_CSTATE;           /* '<S4>/Transfer Fcn2' */
  real_T TransferFcn_CSTATE;            /* '<S4>/Transfer Fcn' */
  real_T Block1_CSTATE[6];              /* '<S38>/Block#1' */
  real_T TransferFcn1_CSTATE;           /* '<S4>/Transfer Fcn1' */
  real_T Integrator_CSTATE;             /* '<S8>/Integrator' */
  real_T Integrator_f_CSTATE;           /* '<S9>/Integrator' */
  real_T Integrator_n_CSTATE;           /* '<S10>/Integrator' */
} drone_StateDerivatives;

/* State disabled  */
typedef struct _drone_StateDisabled {
  boolean_T TransferFcn2_CSTATE;        /* '<S4>/Transfer Fcn2' */
  boolean_T TransferFcn_CSTATE;         /* '<S4>/Transfer Fcn' */
  boolean_T Block1_CSTATE[6];           /* '<S38>/Block#1' */
  boolean_T TransferFcn1_CSTATE;        /* '<S4>/Transfer Fcn1' */
  boolean_T Integrator_CSTATE;          /* '<S8>/Integrator' */
  boolean_T Integrator_f_CSTATE;        /* '<S9>/Integrator' */
  boolean_T Integrator_n_CSTATE;        /* '<S10>/Integrator' */
} drone_StateDisabled;

/* Invariant block signals (auto storage) */
typedef struct _drone_ConstBlockIO {
  const real_T MatriceTransformation[36]; /* '<S6>/Matrice Transformation' */
  const real_T MatriceCorrection[6];    /* '<S6>/Matrice Correction' */
  const real_T Constant;                /* '<S11>/Constant' */
  const real_T Constant1;               /* '<S12>/Constant1' */
  const real_T Constant_g;              /* '<S12>/Constant' */
  const real_T Constant2;               /* '<S12>/Constant2' */
  const real_T Constant_d;              /* '<S14>/Constant' */
  const real_T Constant1_j;             /* '<S15>/Constant1' */
  const real_T Constant_m;              /* '<S15>/Constant' */
  const real_T Constant2_m;             /* '<S15>/Constant2' */
  const real_T Constant_m4;             /* '<S17>/Constant' */
  const real_T Constant1_e;             /* '<S18>/Constant1' */
  const real_T Constant_gu;             /* '<S18>/Constant' */
  const real_T Constant2_c;             /* '<S18>/Constant2' */
  const real_T SOURCE_BLOCK[3];         /* '<S34>/SOURCE_BLOCK' */
  const real_T _gravity_conversion[3]; /* '<S38>/_gravity_conversion' */
  const real_T sensor;                  /* '<S20>/sensor' */
  const real_T sensor_j;                /* '<S21>/sensor' */
  const real_T sensor_p;                /* '<S22>/sensor' */
  const real_T sensor_f;                /* '<S35>/sensor' */
  const real_T sensor_b;                /* '<S36>/sensor' */
  const real_T sensor_e;                /* '<S37>/sensor' */
  const real_T sensor_k;                /* '<S33>/sensor' */
} drone_ConstBlockIO;
/* For easy access from the SimStruct */
#define drone_rtC(S) ((drone_ConstBlockIO *) _ssGetConstBlockIO(S))

/* Constant parameters (auto storage) */
typedef struct _ConstParam_drone_acc {
  /* Expression: [0 0 0 0 0 0]
   * Referenced by blocks:
   * '<S1>/Random Number1'
   * '<S1>/Random Number'
   * '<S1>/Random Number2'
   * '<S1>/Random Number3'
   */
  real_T pooled1[6];
  /* Computed Parameter: StdDev
   * Referenced by blocks:
   * '<S1>/Random Number1'
   * '<S1>/Random Number'
   * '<S1>/Random Number2'
   * '<S1>/Random Number3'
   */
  real_T pooled2[6];
  /* Expression: Perturbation
   * Referenced by blocks:
   * '<S1>/Gain'
   * '<S8>/Saturation'
   * '<S9>/Saturation'
   * '<S10>/Saturation'
   */
  real_T pooled3;
  /* Computed Parameter: A
   * Referenced by blocks:
   * '<S4>/Transfer Fcn2'
   * '<S4>/Transfer Fcn'
   * '<S4>/Transfer Fcn1'
   */
  real_T pooled4;
  /* Computed Parameter: B
   * Referenced by blocks:
   * '<S4>/Transfer Fcn2'
   * '<S4>/Transfer Fcn'
   * '<S4>/Transfer Fcn1'
   */
  real_T pooled5;
  /* Computed Parameter: C
   * Referenced by blocks:
   * '<S4>/Transfer Fcn2'
   * '<S4>/Transfer Fcn'
   * '<S4>/Transfer Fcn1'
   */
  real_T pooled6;
  /* Expression: [0 0 1]
   * Referenced by blocks:
   * '<S4>/Gain2'
   * '<S4>/Gain1'
   * '<S4>/Gain3'
   */
  real_T pooled9[3];
  /* Expression: (1/3)*[0 2 0 0 0 1; 0 0 1 0 2 0; -sqrt(3) -1 0 0 0 1; 0 0 1 -sqrt(3) -1 0; sqrt(3) -1 0 0 0 1; 0 0 1 sqrt(3) -1 0]
   * '<S6>/Matrice Transformation'
   */
  real_T MatriceTransformation[36];
  /* Expression: [-1 -1 1 -1/l -1/l -1/l]
   * '<S6>/Matrice Correction'
   */
  real_T MatriceCorrection_Val[6];
  /* Computed Parameter: SimMechanicsRuntimeParametersSize
   * '<S38>/Block#1'
   */
  real_T Block1_SimMechanicsRu[2];
  /* Computed Parameter: SimMechanicsRuntimeParameters
   * '<S38>/Block#1'
   */
  real_T Block1_SimMechanics_k[175];
  /* Expression: N
   * Referenced by blocks:
   * '<S11>/Constant'
   * '<S14>/Constant'
   * '<S17>/Constant'
   */
  real_T pooled10;
  /* Expression: 0
   * Referenced by blocks:
   * '<S8>/Integrator'
   * '<S9>/Integrator'
   * '<S10>/Integrator'
   */
  real_T pooled11;
  /* Expression: pi/2
   * Referenced by blocks:
   * '<S12>/Constant1'
   * '<S12>/Constant2'
   * '<S15>/Constant1'
   * '<S15>/Constant2'
   * '<S18>/Constant1'
   * '<S18>/Constant2'
   */
  real_T pooled12;
  /* Expression: pi
   * Referenced by blocks:
   * '<S12>/Constant'
   * '<S15>/Constant'
   * '<S18>/Constant'
   */
  real_T pooled13;
  /* Expression: Kp
   * Referenced by blocks:
   * '<S8>/Gain'
   * '<S9>/Gain'
   * '<S10>/Gain'
   */
  real_T pooled14;
  /* Expression: Kd
   * Referenced by blocks:
   * '<S8>/Gain2'
   * '<S9>/Gain2'
   * '<S10>/Gain2'
   */
  real_T pooled15;
  /* Expression: -0.5
   * Referenced by blocks:
   * '<S8>/Saturation'
   * '<S9>/Saturation'
   * '<S10>/Saturation'
   */
  real_T pooled16;
  /* Expression: Cfrot
   * Referenced by blocks:
   * '<S4>/Gain6'
   * '<S4>/Gain5'
   * '<S4>/Gain4'
   */
  real_T pooled17;
  /* Expression: Gravity
   * '<S34>/SOURCE_BLOCK'
   */
  real_T SOURCE_BLOCK_Value[3];
  /* Expression: -1
   * '<S38>/_gravity_conversion'
   */
  real_T _gravity_conversion_Ga;
  /* Expression: Ki
   * Referenced by blocks:
   * '<S8>/Gain1'
   * '<S9>/Gain1'
   * '<S10>/Gain1'
   */
  real_T pooled18;
} ConstParam_drone_acc;

extern drone_ConstBlockIO drone_InvariantSignals; /* constant block i/o */

/* Constant parameters (auto storage) */
extern const ConstParam_drone_acc drone_acc_rtcP;

#endif                                  /* _RTW_HEADER_drone_acc_h_ */
