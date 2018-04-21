#ifndef __c1_servo_demo_h__
#define __c1_servo_demo_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtw_capi.h"
#include "rtw_modelmap.h"

/* Type Definitions */
typedef struct {
  real_T c1_Ihold;
  real_T c1_Ipull;
  real_T c1_Tpwm;
  real_T c1_Vd;
  real_T c1_Vs;
  real_T c1_Vz;
  real_T c1_deltai;
  real_T c1_toff;
  real_T c1_ton;
  SimStruct *S;
  void *c1_testPointAddrMap[8];
  uint32_T chartNumber;
  uint32_T instanceNumber;
  uint8_T c1_is_active_c1_servo_demo;
  uint8_T c1_is_c1_servo_demo;
  uint8_T c1_is_energize_solenoid;
  uint8_T c1_is_regulate_hold_current;
  uint8_T c1_tp_energize_solenoid;
  uint8_T c1_tp_freewheel;
  uint8_T c1_tp_hold;
  uint8_T c1_tp_pull_in_current;
  uint8_T c1_tp_regulate_hold_current;
  uint8_T c1_tp_solenoid_off;
  rtwCAPI_ModelMappingInfo c1_testPointMappingInfo;
  ChartInfoStruct chartInfo;
} SFc1_servo_demoInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */

extern void sf_c1_servo_demo_get_check_sum(mxArray *plhs[]);
extern void c1_servo_demo_method_dispatcher(SimStruct *S, int_T method, void
 *data);

#endif

