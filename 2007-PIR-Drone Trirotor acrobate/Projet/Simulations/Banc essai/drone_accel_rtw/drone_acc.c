/*
 * This file is not available for use in any application other than as a
 * MATLAB(R) MEX file for use with the Simulink(R) Accelerator product.
 */

/*
 * drone_acc.c
 * 
 * Real-Time Workshop code generation for Simulink model "drone_acc.mdl".
 *
 * Model Version              : 1.833
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Thu Dec 28 10:01:42 2006
 */

#include <math.h>
#include <string.h>
#include "drone_acc.h"
#include "drone_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"

#define CodeFormat                      S-Function
#define AccDefine1                      Accelerator_S-Function

/* Outputs for root system: '<Root>' */
static void mdlOutputs(SimStruct *S, int_T tid)
{
  /* simstruct variables */
  drone_BlockIO *drone_B = (drone_BlockIO *) _ssGetBlockIO(S);
  drone_ContinuousStates *drone_X = (drone_ContinuousStates*) ssGetContStates(S);
  drone_D_Work *drone_DWork = (drone_D_Work *) ssGetRootDWork(S);

  /* local block i/o variables */

  real_T rtb_Reshape_k[24];
  real_T rtb_TransferFcn2;
  real_T rtb_Product1[6];
  real_T rtb_Product[6];
  real_T rtb_Add;
  real_T rtb_MathFunction2;
  real_T rtb_TransferFcn;
  real_T rtb_TransferFcn1;
  real_T rtb_Sum_c;
  real_T rtb_CosErreurAngle;
  real_T rtb_Product_g;
  real_T rtb_Integrator;
  real_T rtb_Sum_cb;
  real_T rtb_MathFunction_cu;
  real_T rtb_Gain_p;
  real_T rtb_Derivative;
  real_T rtb_Sum1_p;
  real_T rtb_Saturation;
  real_T rtb_Add_k;
  real_T rtb_MathFunction2_e;
  real_T rtb_Sum_j;
  real_T rtb_CosErreurAngle_p;
  real_T rtb_Product_h;
  real_T rtb_Integrator_k;
  real_T rtb_Sum_h;
  real_T rtb_MathFunction_k;
  real_T rtb_Gain_l;
  real_T rtb_Derivative_f;
  real_T rtb_Sum1_c;
  real_T rtb_Saturation_b;
  real_T rtb_Add_f;
  real_T rtb_MathFunction2_h;
  real_T rtb_Sum_p;
  real_T rtb_CosErreurAngle_l;
  real_T rtb_Product_f;
  real_T rtb_Integrator_o;
  real_T rtb_Sum_m;
  real_T rtb_MathFunction_ky;
  real_T rtb_Gain_o;
  real_T rtb_Derivative_h;
  real_T rtb_Sum1_op;
  real_T rtb_Saturation_ba;
  real_T rtb_perturbation_cellule[6];
  real_T rtb_perturbation_rotor_1[6];
  real_T rtb_perturbation_rotor_2[6];
  real_T rtb_perturbation_rotor_3[6];

  if (ssIsSampleHit(S, 1, tid)) {       /* Sample time: [0.0001s, 0.0s] */

    /* RandomNumber: '<S1>/Random Number1' */
    {
      int_T i1;

      real_T *y0 = rtb_perturbation_cellule;
      real_T *rw_NextOutput = &drone_DWork->RandomNumber1_RWORK.NextOutput[0];

      for (i1=0; i1 < 6; i1++) {
        y0[i1] = rw_NextOutput[i1];
      }
    }

    /* RandomNumber: '<S1>/Random Number' */
    {
      int_T i1;

      real_T *y0 = rtb_perturbation_rotor_1;
      real_T *rw_NextOutput = &drone_DWork->RandomNumber_RWORK.NextOutput[0];

      for (i1=0; i1 < 6; i1++) {
        y0[i1] = rw_NextOutput[i1];
      }
    }

    /* RandomNumber: '<S1>/Random Number2' */
    {
      int_T i1;

      real_T *y0 = rtb_perturbation_rotor_2;
      real_T *rw_NextOutput = &drone_DWork->RandomNumber2_RWORK.NextOutput[0];

      for (i1=0; i1 < 6; i1++) {
        y0[i1] = rw_NextOutput[i1];
      }
    }

    /* RandomNumber: '<S1>/Random Number3' */
    {
      int_T i1;

      real_T *y0 = rtb_perturbation_rotor_3;
      real_T *rw_NextOutput = &drone_DWork->RandomNumber3_RWORK.NextOutput[0];

      for (i1=0; i1 < 6; i1++) {
        y0[i1] = rw_NextOutput[i1];
      }
    }

    /* S-Function Block: <S1>/Reshape */
    {
      int_T i1;

      const real_T *u0 = &rtb_perturbation_cellule[0];
      real_T *y0 = rtb_Reshape_k;

      for (i1=0; i1 < 6; i1++) {
        y0[i1] = u0[i1];
      }

      u0 = &rtb_perturbation_rotor_1[0];
      y0 = &rtb_Reshape_k[6];

      for (i1=0; i1 < 6; i1++) {
        y0[i1] = u0[i1];
      }

      u0 = &rtb_perturbation_rotor_2[0];
      y0 = &rtb_Reshape_k[12];

      for (i1=0; i1 < 6; i1++) {
        y0[i1] = u0[i1];
      }

      u0 = &rtb_perturbation_rotor_3[0];
      y0 = &rtb_Reshape_k[18];

      for (i1=0; i1 < 6; i1++) {
        y0[i1] = u0[i1];
      }
    }

    {
      int32_T i1;

      for(i1=0; i1<24; i1++) {
        drone_B->Gain[i1] = rtb_Reshape_k[i1] * 0.5;
      }
    }
  }

  /* TransferFcn Block: <S4>/Transfer Fcn2 */
  rtb_TransferFcn2 = 20.0*drone_X->TransferFcn2_CSTATE;

  drone_B->Gain2[0] = rtb_TransferFcn2 * (0.0);
  drone_B->Gain2[1] = rtb_TransferFcn2 * (0.0);
  drone_B->Gain2[2] = rtb_TransferFcn2 * (1.0);

  /* FromWorkspace: '<S43>/FromWs' */
  /* Call into Simulink for From Workspace */
  ssCallAccelRunBlock(S, 0, 9, SS_CALL_MDL_OUTPUTS);

  /* S-Function Block: <S5>/Reshape2 */
  {
    int_T i1;

    const real_T *u0 = drone_B->FromWs;
    real_T *y0 = drone_B->Reshape2;

    for (i1=0; i1 < 6; i1++) {
      y0[i1] = u0[i1];
    }
  }

  {
    int32_T i1;

    for(i1=0; i1<6; i1++) {
      rtb_Product1[i1] = drone_B->Reshape2[i1] *
        drone_rtC(S)->MatriceCorrection[i1];
    }
  }

  /* Product: '<S6>/Product' */
  {
    static const int dims[3] = { 6, 6, 1 };
    rt_MatMultRR_Dbl(rtb_Product,
     (real_T*)&drone_rtC(S)->MatriceTransformation[0],
     rtb_Product1, &dims[0]);
  }

  rtb_Add = rtb_Product[1] * rtb_Product[1] + rtb_Product[0] * rtb_Product[0];

  /* Math: '<S13>/Math Function2' */
  /* Operator : sqrt */
  if (rtb_Add < 0.0) {
    rtb_MathFunction2 = -sqrt(-rtb_Add);
  } else {
    rtb_MathFunction2 = sqrt(rtb_Add);
  }

  /* TransferFcn Block: <S4>/Transfer Fcn */
  rtb_TransferFcn = 20.0*drone_X->TransferFcn_CSTATE;

  /* Level2 S-Function Block: <S38>/Block#1 (mech_engine) */
  /* Call into Simulink for MEX-version of S-function */
  ssCallAccelRunBlock(S, 0, 20, SS_CALL_MDL_OUTPUTS);

  /* TransferFcn Block: <S4>/Transfer Fcn1 */
  rtb_TransferFcn1 = 20.0*drone_X->TransferFcn1_CSTATE;

  /* S-Function Block: <S4>/Reshape */
  drone_B->Reshape[0] = rtb_TransferFcn;
  drone_B->Reshape[1] = drone_B->Block1_o1[5];
  drone_B->Reshape[2] = rtb_TransferFcn1;
  drone_B->Reshape[3] = drone_B->Block1_o1[3];
  drone_B->Reshape[4] = rtb_TransferFcn2;
  drone_B->Reshape[5] = drone_B->Block1_o1[1];

  rtb_Sum_c = (rt_atan2(rtb_Product[0], rtb_Product[1])) - drone_B->Reshape[1];

  rtb_CosErreurAngle = cos(rtb_Sum_c);

  if((rtb_CosErreurAngle < 0.0) && (17.0 != floor(17.0))) {
    rtb_CosErreurAngle = -pow(-rtb_CosErreurAngle, 17.0);
  } else {
    rtb_CosErreurAngle = pow(rtb_CosErreurAngle, 17.0);
  }

  rtb_Product_g = rtb_MathFunction2 * rtb_CosErreurAngle;

  /* Integrator: '<S8>/Integrator' */
  rtb_Integrator = drone_X->Integrator_CSTATE;

  rtb_Sum_cb = rtb_Sum_c + 1.5707963267948966E+000;

  /* Math: '<S12>/Math Function' */
  /* Operator : mod */
  if (drone_rtC(S)->Constant_g == 0.0) {
    rtb_MathFunction_cu = rtb_Sum_cb;
  } else if (drone_rtC(S)->Constant_g == floor(drone_rtC(S)->Constant_g)) {
    /* Integer denominator.  Use conventional formula.*/
    rtb_MathFunction_cu = (rtb_Sum_cb - drone_rtC(S)->Constant_g *
      floor((rtb_Sum_cb) / (drone_rtC(S)->Constant_g)));
  } else {
    /* Noninteger denominator. Check for nearly integer quotient.*/
    real_T uDivRound;
    real_T uDiv = rtb_Sum_cb / drone_rtC(S)->Constant_g;
    {
      real_T t;
      t = floor((fabs(uDiv) + 0.5));
      uDivRound = ((uDiv < 0.0) ? -t : t);
    }

    if (fabs((uDiv - uDivRound)) <= DBL_EPSILON * fabs(uDiv)) {
      rtb_MathFunction_cu = 0.0;
    } else {
      rtb_MathFunction_cu = (uDiv - floor(uDiv)) * drone_rtC(S)->Constant_g;
    }
  }

  rtb_Gain_p = (rtb_MathFunction_cu - 1.5707963267948966E+000) * 60.0;

  drone_B->Gain2_l = rtb_Gain_p * 0.08;

  /* Derivative Block: <S8>/Derivative */
  {
    real_T t = ssGetTaskTime(S,tid);
    real_T timeStampA = drone_DWork->Derivative_RWORK.TimeStampA;
    real_T timeStampB = drone_DWork->Derivative_RWORK.TimeStampB;

    if (timeStampA >= t && timeStampB >= t) {
      rtb_Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T *lastBank = &drone_DWork->Derivative_RWORK.TimeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastBank += 2;
        }
      } else if (timeStampA >= t) {
        lastBank += 2;
      }
      deltaT = t - *lastBank++;
      rtb_Derivative = (drone_B->Gain2_l - *lastBank++) / deltaT;
    }
  }

  rtb_Sum1_p = (rtb_Integrator + rtb_Gain_p) + rtb_Derivative;

  rtb_Saturation = rt_SATURATE(rtb_Sum1_p, -0.5, 0.5);

  rtb_Add_k = rtb_Product[3] * rtb_Product[3] + rtb_Product[2] * rtb_Product[2];

  /* Math: '<S16>/Math Function2' */
  /* Operator : sqrt */
  if (rtb_Add_k < 0.0) {
    rtb_MathFunction2_e = -sqrt(-rtb_Add_k);
  } else {
    rtb_MathFunction2_e = sqrt(rtb_Add_k);
  }

  rtb_Sum_j = rt_atan2(rtb_Product[2], rtb_Product[3]) - drone_B->Reshape[3];

  rtb_CosErreurAngle_p = cos(rtb_Sum_j);

  if((rtb_CosErreurAngle_p < 0.0) && (17.0 != floor(17.0))) {
    rtb_CosErreurAngle_p = -pow(-rtb_CosErreurAngle_p, 17.0);
  } else {
    rtb_CosErreurAngle_p = pow(rtb_CosErreurAngle_p, 17.0);
  }

  rtb_Product_h = rtb_MathFunction2_e * rtb_CosErreurAngle_p;

  /* Integrator: '<S9>/Integrator' */
  rtb_Integrator_k = drone_X->Integrator_f_CSTATE;

  rtb_Sum_h = rtb_Sum_j + 1.5707963267948966E+000;

  /* Math: '<S15>/Math Function' */
  /* Operator : mod */
  if (drone_rtC(S)->Constant_m == 0.0) {
    rtb_MathFunction_k = rtb_Sum_h;
  } else if (drone_rtC(S)->Constant_m == floor(drone_rtC(S)->Constant_m)) {
    /* Integer denominator.  Use conventional formula.*/
    rtb_MathFunction_k = (rtb_Sum_h - drone_rtC(S)->Constant_m *
      floor((rtb_Sum_h) / (drone_rtC(S)->Constant_m)));
  } else {
    /* Noninteger denominator. Check for nearly integer quotient.*/
    real_T uDivRound;
    real_T uDiv = rtb_Sum_h / drone_rtC(S)->Constant_m;
    {
      real_T t;
      t = floor((fabs(uDiv) + 0.5));
      uDivRound = ((uDiv < 0.0) ? -t : t);
    }

    if (fabs((uDiv - uDivRound)) <= DBL_EPSILON * fabs(uDiv)) {
      rtb_MathFunction_k = 0.0;
    } else {
      rtb_MathFunction_k = (uDiv - floor(uDiv)) * drone_rtC(S)->Constant_m;
    }
  }

  rtb_Gain_l = (rtb_MathFunction_k - 1.5707963267948966E+000) * 60.0;

  drone_B->Gain2_a = rtb_Gain_l * 0.08;

  /* Derivative Block: <S9>/Derivative */
  {
    real_T t = ssGetTaskTime(S,tid);
    real_T timeStampA = drone_DWork->Derivative_RWORK_g.TimeStampA;
    real_T timeStampB = drone_DWork->Derivative_RWORK_g.TimeStampB;

    if (timeStampA >= t && timeStampB >= t) {
      rtb_Derivative_f = 0.0;
    } else {
      real_T deltaT;
      real_T *lastBank = &drone_DWork->Derivative_RWORK_g.TimeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastBank += 2;
        }
      } else if (timeStampA >= t) {
        lastBank += 2;
      }
      deltaT = t - *lastBank++;
      rtb_Derivative_f = (drone_B->Gain2_a - *lastBank++) / deltaT;
    }
  }

  rtb_Sum1_c = (rtb_Integrator_k + rtb_Gain_l) + rtb_Derivative_f;

  rtb_Saturation_b = rt_SATURATE(rtb_Sum1_c, -0.5, 0.5);

  rtb_Add_f = rtb_Product[5] * rtb_Product[5] + rtb_Product[4] * rtb_Product[4];

  /* Math: '<S19>/Math Function2' */
  /* Operator : sqrt */
  if (rtb_Add_f < 0.0) {
    rtb_MathFunction2_h = -sqrt(-rtb_Add_f);
  } else {
    rtb_MathFunction2_h = sqrt(rtb_Add_f);
  }

  rtb_Sum_p = rt_atan2(rtb_Product[4], rtb_Product[5]) - drone_B->Reshape[5];

  rtb_CosErreurAngle_l = cos(rtb_Sum_p);

  if((rtb_CosErreurAngle_l < 0.0) && (17.0 != floor(17.0))) {
    rtb_CosErreurAngle_l = -pow(-rtb_CosErreurAngle_l, 17.0);
  } else {
    rtb_CosErreurAngle_l = pow(rtb_CosErreurAngle_l, 17.0);
  }

  rtb_Product_f = rtb_MathFunction2_h * rtb_CosErreurAngle_l;

  /* Integrator: '<S10>/Integrator' */
  rtb_Integrator_o = drone_X->Integrator_n_CSTATE;

  rtb_Sum_m = rtb_Sum_p + 1.5707963267948966E+000;

  /* Math: '<S18>/Math Function' */
  /* Operator : mod */
  if (drone_rtC(S)->Constant_gu == 0.0) {
    rtb_MathFunction_ky = rtb_Sum_m;
  } else if (drone_rtC(S)->Constant_gu == floor(drone_rtC(S)->Constant_gu)) {
    /* Integer denominator.  Use conventional formula.*/
    rtb_MathFunction_ky = (rtb_Sum_m - drone_rtC(S)->Constant_gu *
      floor((rtb_Sum_m) / (drone_rtC(S)->Constant_gu)));
  } else {
    /* Noninteger denominator. Check for nearly integer quotient.*/
    real_T uDivRound;
    real_T uDiv = rtb_Sum_m / drone_rtC(S)->Constant_gu;
    {
      real_T t;
      t = floor((fabs(uDiv) + 0.5));
      uDivRound = ((uDiv < 0.0) ? -t : t);
    }

    if (fabs((uDiv - uDivRound)) <= DBL_EPSILON * fabs(uDiv)) {
      rtb_MathFunction_ky = 0.0;
    } else {
      rtb_MathFunction_ky = (uDiv - floor(uDiv)) * drone_rtC(S)->Constant_gu;
    }
  }

  rtb_Gain_o = (rtb_MathFunction_ky - 1.5707963267948966E+000) * 60.0;

  drone_B->Gain2_h = rtb_Gain_o * 0.08;

  /* Derivative Block: <S10>/Derivative */
  {
    real_T t = ssGetTaskTime(S,tid);
    real_T timeStampA = drone_DWork->Derivative_RWORK_i.TimeStampA;
    real_T timeStampB = drone_DWork->Derivative_RWORK_i.TimeStampB;

    if (timeStampA >= t && timeStampB >= t) {
      rtb_Derivative_h = 0.0;
    } else {
      real_T deltaT;
      real_T *lastBank = &drone_DWork->Derivative_RWORK_i.TimeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastBank += 2;
        }
      } else if (timeStampA >= t) {
        lastBank += 2;
      }
      deltaT = t - *lastBank++;
      rtb_Derivative_h = (drone_B->Gain2_h - *lastBank++) / deltaT;
    }
  }

  rtb_Sum1_op = (rtb_Integrator_o + rtb_Gain_o) + rtb_Derivative_h;

  rtb_Saturation_ba = rt_SATURATE(rtb_Sum1_op, -0.5, 0.5);

  /* S-Function Block: <S7>/Reshape */
  drone_B->Reshape_h[0] = rtb_Product_g;
  drone_B->Reshape_h[1] = rtb_Saturation;
  drone_B->Reshape_h[2] = rtb_Product_h;
  drone_B->Reshape_h[3] = rtb_Saturation_b;
  drone_B->Reshape_h[4] = rtb_Product_f;
  drone_B->Reshape_h[5] = rtb_Saturation_ba;

  drone_B->Sum2 = drone_B->Reshape_h[5] - drone_B->Block1_o1[0] * 0.05;

  drone_B->Gain1[0] = rtb_TransferFcn1 * (0.0);
  drone_B->Gain1[1] = rtb_TransferFcn1 * (0.0);
  drone_B->Gain1[2] = rtb_TransferFcn1 * (1.0);

  drone_B->Sum1 = drone_B->Reshape_h[3] - drone_B->Block1_o1[2] * 0.05;

  drone_B->Gain3[0] = rtb_TransferFcn * (0.0);
  drone_B->Gain3[1] = rtb_TransferFcn * (0.0);
  drone_B->Gain3[2] = rtb_TransferFcn * (1.0);

  drone_B->Sum = drone_B->Reshape_h[1] - drone_B->Block1_o1[4] * 0.05;

  /* Level2 S-Function Block: <S38>/Block#2 (mech_engine) */
  /* Call into Simulink for MEX-version of S-function */
  ssCallAccelRunBlock(S, 0, 95, SS_CALL_MDL_OUTPUTS);

  /* S-Function Block: <S2>/Reshape */
  drone_B->Reshape_e[0] = drone_B->Block2_o1[3];
  drone_B->Reshape_e[1] = drone_B->Block2_o1[4];
  drone_B->Reshape_e[2] = drone_B->Block2_o1[5];
  drone_B->Reshape_e[3] = drone_B->Block2_o1[0];
  drone_B->Reshape_e[4] = drone_B->Block2_o1[1];
  drone_B->Reshape_e[5] = drone_B->Block2_o1[2];

  if (ssIsSampleHit(S, 1, tid)) {       /* Sample time: [0.0001s, 0.0s] */

    /* Scope: '<S3>/Visu Consigne Dynamique' */
    /* Call into Simulink for Scope */
    ssCallAccelRunBlock(S, 0, 97, SS_CALL_MDL_OUTPUTS);

    /* Scope: '<S3>/Visu Consigne Efforts' */
    /* Call into Simulink for Scope */
    ssCallAccelRunBlock(S, 0, 98, SS_CALL_MDL_OUTPUTS);

    /* Scope: '<S3>/Visu Reponse Position' */
    /* Call into Simulink for Scope */
    ssCallAccelRunBlock(S, 0, 99, SS_CALL_MDL_OUTPUTS);
  }

  drone_B->Gain1_j = rtb_Gain_p * 0.02;

  drone_B->Gain1_e = rtb_Gain_l * 0.02;

  drone_B->Gain1_d = rtb_Gain_o * 0.02;

  if (ssIsSampleHit(S, 1, tid)) {       /* Sample time: [0.0001s, 0.0s] */

    /* Scope: '<S3>/Visu Reponse Efforts' */
    /* Call into Simulink for Scope */
    ssCallAccelRunBlock(S, 0, 103, SS_CALL_MDL_OUTPUTS);
  }

  /* Level2 S-Function Block: <S38>/Block#3 (mech_engine) */
  /* Call into Simulink for MEX-version of S-function */
  ssCallAccelRunBlock(S, 0, 136, SS_CALL_MDL_OUTPUTS);
}

/* Update for root system: '<Root>' */
#define MDL_UPDATE
static void mdlUpdate(SimStruct *S, int_T tid)
{

  /* simstruct variables */
  drone_BlockIO *drone_B = (drone_BlockIO *) _ssGetBlockIO(S);
  drone_D_Work *drone_DWork = (drone_D_Work *) ssGetRootDWork(S);

  if (ssIsSampleHit(S, 1, tid)) {       /* Sample time: [0.0001s, 0.0s] */

    /* RandomNumber Block: <S1>/Random Number1 */
    {
      int_T i1;

      const real_T *p_Mean = &drone_acc_rtcP.pooled1[0];

      const real_T *p_StdDev = &drone_acc_rtcP.pooled2[0];

      int_T *iw_RandSeed = &drone_DWork->RandomNumber1_IWORK.RandSeed[0];
      real_T *rw_NextOutput = &drone_DWork->RandomNumber1_RWORK.NextOutput[0];

      for (i1=0; i1 < 6; i1++) {
        rw_NextOutput[i1] = rt_NormalRand((uint32_T
          *)&iw_RandSeed[i1])*(p_StdDev[i1])+(p_Mean[i1]);
      }
    }

    /* RandomNumber Block: <S1>/Random Number */
    {
      int_T i1;

      const real_T *p_Mean = &drone_acc_rtcP.pooled1[0];

      const real_T *p_StdDev = &drone_acc_rtcP.pooled2[0];

      int_T *iw_RandSeed = &drone_DWork->RandomNumber_IWORK.RandSeed[0];
      real_T *rw_NextOutput = &drone_DWork->RandomNumber_RWORK.NextOutput[0];

      for (i1=0; i1 < 6; i1++) {
        rw_NextOutput[i1] = rt_NormalRand((uint32_T
          *)&iw_RandSeed[i1])*(p_StdDev[i1])+(p_Mean[i1]);
      }
    }

    /* RandomNumber Block: <S1>/Random Number2 */
    {
      int_T i1;

      const real_T *p_Mean = &drone_acc_rtcP.pooled1[0];

      const real_T *p_StdDev = &drone_acc_rtcP.pooled2[0];

      int_T *iw_RandSeed = &drone_DWork->RandomNumber2_IWORK.RandSeed[0];
      real_T *rw_NextOutput = &drone_DWork->RandomNumber2_RWORK.NextOutput[0];

      for (i1=0; i1 < 6; i1++) {
        rw_NextOutput[i1] = rt_NormalRand((uint32_T
          *)&iw_RandSeed[i1])*(p_StdDev[i1])+(p_Mean[i1]);
      }
    }

    /* RandomNumber Block: <S1>/Random Number3 */
    {
      int_T i1;

      const real_T *p_Mean = &drone_acc_rtcP.pooled1[0];

      const real_T *p_StdDev = &drone_acc_rtcP.pooled2[0];

      int_T *iw_RandSeed = &drone_DWork->RandomNumber3_IWORK.RandSeed[0];
      real_T *rw_NextOutput = &drone_DWork->RandomNumber3_RWORK.NextOutput[0];

      for (i1=0; i1 < 6; i1++) {
        rw_NextOutput[i1] = rt_NormalRand((uint32_T
          *)&iw_RandSeed[i1])*(p_StdDev[i1])+(p_Mean[i1]);
      }
    }
  }

  /* Level2 S-Function Block: <S38>/Block#1 (mech_engine) */
  /* Call into Simulink for MEX-version of S-function */
  ssCallAccelRunBlock(S, 0, 20, SS_CALL_MDL_UPDATE);

  /* Derivative Block: <S8>/Derivative */
  {
    real_T timeStampA = drone_DWork->Derivative_RWORK.TimeStampA;
    real_T timeStampB = drone_DWork->Derivative_RWORK.TimeStampB;
    real_T *lastBank = &drone_DWork->Derivative_RWORK.TimeStampA;

    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastBank += 2;
      } else if (timeStampA >= timeStampB) {
        lastBank += 2;
      }
    }
    *lastBank++ = ssGetTaskTime(S,tid);
    *lastBank++ = drone_B->Gain2_l;
  }

  /* Derivative Block: <S9>/Derivative */
  {
    real_T timeStampA = drone_DWork->Derivative_RWORK_g.TimeStampA;
    real_T timeStampB = drone_DWork->Derivative_RWORK_g.TimeStampB;
    real_T *lastBank = &drone_DWork->Derivative_RWORK_g.TimeStampA;

    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastBank += 2;
      } else if (timeStampA >= timeStampB) {
        lastBank += 2;
      }
    }
    *lastBank++ = ssGetTaskTime(S,tid);
    *lastBank++ = drone_B->Gain2_a;
  }

  /* Derivative Block: <S10>/Derivative */
  {
    real_T timeStampA = drone_DWork->Derivative_RWORK_i.TimeStampA;
    real_T timeStampB = drone_DWork->Derivative_RWORK_i.TimeStampB;
    real_T *lastBank = &drone_DWork->Derivative_RWORK_i.TimeStampA;

    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastBank += 2;
      } else if (timeStampA >= timeStampB) {
        lastBank += 2;
      }
    }
    *lastBank++ = ssGetTaskTime(S,tid);
    *lastBank++ = drone_B->Gain2_h;
  }

  /* Level2 S-Function Block: <S38>/Block#2 (mech_engine) */
  /* Call into Simulink for MEX-version of S-function */
  ssCallAccelRunBlock(S, 0, 95, SS_CALL_MDL_UPDATE);

  /* Level2 S-Function Block: <S38>/Block#3 (mech_engine) */
  /* Call into Simulink for MEX-version of S-function */
  ssCallAccelRunBlock(S, 0, 136, SS_CALL_MDL_UPDATE);
}

/* Derivatives for root system: '<Root>' */
#define MDL_DERIVATIVES
static void mdlDerivatives(SimStruct *S)
{
  /* simstruct variables */
  drone_BlockIO *drone_B = (drone_BlockIO *) _ssGetBlockIO(S);
  drone_ContinuousStates *drone_X = (drone_ContinuousStates*) ssGetContStates(S);
  drone_StateDerivatives *drone_Xdot = (drone_StateDerivatives*) ssGetdX(S);

  /* TransferFcn Block: <S4>/Transfer Fcn2 */
  {

    drone_Xdot->TransferFcn2_CSTATE = 1.0*drone_B->Reshape_h[4];
    drone_Xdot->TransferFcn2_CSTATE += (-20.0)*drone_X->TransferFcn2_CSTATE;
  }

  /* TransferFcn Block: <S4>/Transfer Fcn */
  {

    drone_Xdot->TransferFcn_CSTATE = 1.0*drone_B->Reshape_h[0];
    drone_Xdot->TransferFcn_CSTATE += (-20.0)*drone_X->TransferFcn_CSTATE;
  }

  /* Level2 S-Function Block: <S38>/Block#1 (mech_engine) */
  /* Call into Simulink for MEX-version of S-function */
  ssCallAccelRunBlock(S, 0, 20, SS_CALL_MDL_DERIVATIVES);

  /* TransferFcn Block: <S4>/Transfer Fcn1 */
  {

    drone_Xdot->TransferFcn1_CSTATE = 1.0*drone_B->Reshape_h[2];
    drone_Xdot->TransferFcn1_CSTATE += (-20.0)*drone_X->TransferFcn1_CSTATE;
  }

  /* Integrator Block: <S8>/Integrator */
  {

    drone_Xdot->Integrator_CSTATE = drone_B->Gain1_j;
  }

  /* Integrator Block: <S9>/Integrator */
  {

    drone_Xdot->Integrator_f_CSTATE = drone_B->Gain1_e;
  }

  /* Integrator Block: <S10>/Integrator */
  {

    drone_Xdot->Integrator_n_CSTATE = drone_B->Gain1_d;
  }
}

/* Projection for root system: '<Root>' */
#define MDL_PROJECTION
static void mdlProjection(SimStruct *S)
{

  /* Level2 S-Function Block: <S38>/Block#1 (mech_engine) */
  /* Call into Simulink for MEX-version of S-function */
  ssCallAccelRunBlock(S, 0, 20, SS_CALL_MDL_PROJECTION);
}

/* Function to initialize sizes */
static void mdlInitializeSizes(SimStruct *S)
{

  /* checksum */
  ssSetChecksumVal(S, 0, 2112364656U);
  ssSetChecksumVal(S, 1, 3982252924U);
  ssSetChecksumVal(S, 2, 4263911557U);
  ssSetChecksumVal(S, 3, 3983186590U);

  /* options */
  ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);

  /* Accelerator check memory map size match for DWork */
  if (ssGetSizeofDWork(S) != sizeof(drone_D_Work)) {
    ssSetErrorStatus(S,"Unexpected error: Internal DWork sizes do "
     "not match for accelerator mex file.");
  }

  /* Accelerator check memory map size match for BlockIO */
  if (ssGetSizeofGlobalBlockIO(S) != sizeof(drone_BlockIO)) {
    ssSetErrorStatus(S,"Unexpected error: Internal BlockIO sizes do "
     "not match for accelerator mex file.");
  }

  /* constant block I/O */
  _ssSetConstBlockIO(S, &drone_InvariantSignals);

  /* non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
}

/* Empty mdlInitializeSampleTimes function (never called) */
static void mdlInitializeSampleTimes(SimStruct *S) { }

/* Empty mdlTerminate function (never called) */
static void mdlTerminate(SimStruct *S) { }

/* MATLAB MEX Glue */
#include "simulink.c"
