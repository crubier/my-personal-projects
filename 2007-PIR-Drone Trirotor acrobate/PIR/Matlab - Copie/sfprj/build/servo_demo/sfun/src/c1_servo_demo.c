/* Include files */
#include "servo_demo_sfun.h"
#include "c1_servo_demo.h"
#define CHARTINSTANCE_CHARTNUMBER       (chartInstance.chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER    (chartInstance.instanceNumber)
#include "servo_demo_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define c1_IN_NO_ACTIVE_CHILD           (0)
#define c1_IN_energize_solenoid         (1)
#define c1_IN_pull_in_current           (1)
#define c1_IN_regulate_hold_current     (2)
#define c1_IN_freewheel                 (1)
#define c1_IN_solenoid_off              (2)
#define c1_IN_hold                      (2)

/* Variable Declarations */

/* Variable Definitions */
static SFc1_servo_demoInstanceStruct chartInstance;

/* Function Declarations */
static void initialize_c1_servo_demo(void);
static void enable_c1_servo_demo(void);
static void disable_c1_servo_demo(void);
static void finalize_c1_servo_demo(void);
static void sf_c1_servo_demo(void);
static int32_T c1__s32_uminus__(int32_T c1_b);
static real_T *c1_v(void);
static real_T *c1_duty_cycle(void);
static real_T *c1_i(void);
static void init_test_point_addr_map(void);
static void **get_test_point_address_map(void);
static rtwCAPI_ModelMappingInfo *get_test_point_mapping_info(void);

/* Function Definitions */
static void initialize_c1_servo_demo(void)
{
  chartInstance.c1_is_energize_solenoid = 0;
  chartInstance.c1_tp_energize_solenoid = 0;
  chartInstance.c1_tp_pull_in_current = 0;
  chartInstance.c1_is_regulate_hold_current = 0;
  chartInstance.c1_tp_regulate_hold_current = 0;
  chartInstance.c1_tp_freewheel = 0;
  chartInstance.c1_tp_hold = 0;
  chartInstance.c1_tp_solenoid_off = 0;
  chartInstance.c1_is_active_c1_servo_demo = 0;
  chartInstance.c1_is_c1_servo_demo = 0;
  chartInstance.c1_ton = 0.0;
  chartInstance.c1_toff = 0.0;
  if(!(cdrGetOutputPortReusable(chartInstance.S, 1) != 0)) {
    *c1_v() = 0.0;
  }
  {
    real_T c1_sf_d6;
    sf_set_error_prefix_string("Stateflow Runtime Error (chart): Error evaluating chart workspace data 'Tpwm' in the chart's parent workspace.\n");
    sf_mex_import(sf_mex_get_sfun_param(chartInstance.S, 2),
     "sf_mex_get_sfun_param", &c1_sf_d6, 0, 0U, 0, 0);
    chartInstance.c1_Tpwm = c1_sf_d6;
    sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  }
  {
    real_T c1_sf_d5;
    sf_set_error_prefix_string("Stateflow Runtime Error (chart): Error evaluating chart workspace data 'Ipull' in the chart's parent workspace.\n");
    sf_mex_import(sf_mex_get_sfun_param(chartInstance.S, 1),
     "sf_mex_get_sfun_param", &c1_sf_d5, 0, 0U, 0, 0);
    chartInstance.c1_Ipull = c1_sf_d5;
    sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  }
  {
    real_T c1_sf_d4;
    sf_set_error_prefix_string("Stateflow Runtime Error (chart): Error evaluating chart workspace data 'Ihold' in the chart's parent workspace.\n");
    sf_mex_import(sf_mex_get_sfun_param(chartInstance.S, 0),
     "sf_mex_get_sfun_param", &c1_sf_d4, 0, 0U, 0, 0);
    chartInstance.c1_Ihold = c1_sf_d4;
    sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  }
  {
    real_T c1_sf_d3;
    sf_set_error_prefix_string("Stateflow Runtime Error (chart): Error evaluating chart workspace data 'deltai' in the chart's parent workspace.\n");
    sf_mex_import(sf_mex_get_sfun_param(chartInstance.S, 6),
     "sf_mex_get_sfun_param", &c1_sf_d3, 0, 0U, 0, 0);
    chartInstance.c1_deltai = c1_sf_d3;
    sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  }
  {
    real_T c1_sf_d2;
    sf_set_error_prefix_string("Stateflow Runtime Error (chart): Error evaluating chart workspace data 'Vs' in the chart's parent workspace.\n");
    sf_mex_import(sf_mex_get_sfun_param(chartInstance.S, 4),
     "sf_mex_get_sfun_param", &c1_sf_d2, 0, 0U, 0, 0);
    chartInstance.c1_Vs = c1_sf_d2;
    sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  }
  {
    real_T c1_sf_d1;
    sf_set_error_prefix_string("Stateflow Runtime Error (chart): Error evaluating chart workspace data 'Vz' in the chart's parent workspace.\n");
    sf_mex_import(sf_mex_get_sfun_param(chartInstance.S, 5),
     "sf_mex_get_sfun_param", &c1_sf_d1, 0, 0U, 0, 0);
    chartInstance.c1_Vz = c1_sf_d1;
    sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  }
  {
    real_T c1_sf_d0;
    sf_set_error_prefix_string("Stateflow Runtime Error (chart): Error evaluating chart workspace data 'Vd' in the chart's parent workspace.\n");
    sf_mex_import(sf_mex_get_sfun_param(chartInstance.S, 3),
     "sf_mex_get_sfun_param", &c1_sf_d0, 0, 0U, 0, 0);
    chartInstance.c1_Vd = c1_sf_d0;
    sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  }
}

static void enable_c1_servo_demo(void)
{
}

static void disable_c1_servo_demo(void)
{
}

static void finalize_c1_servo_demo(void)
{
}

static void sf_c1_servo_demo(void)
{
  uint8_T c1_previousEvent;
  _sfTime_ = (real_T)ssGetT(chartInstance.S);
  _SFD_DATA_RANGE_CHECK(*c1_v(), 6U);
  _SFD_DATA_RANGE_CHECK_MIN_MAX(*c1_duty_cycle(), 0U, 0.0, 100.0);
  _SFD_DATA_RANGE_CHECK(chartInstance.c1_ton, 3U);
  _SFD_DATA_RANGE_CHECK(chartInstance.c1_toff, 7U);
  _SFD_DATA_RANGE_CHECK(chartInstance.c1_Tpwm, 5U);
  _SFD_DATA_RANGE_CHECK(chartInstance.c1_Ipull, 1U);
  _SFD_DATA_RANGE_CHECK(chartInstance.c1_Ihold, 4U);
  _SFD_DATA_RANGE_CHECK(chartInstance.c1_deltai, 11U);
  _SFD_DATA_RANGE_CHECK(chartInstance.c1_Vs, 8U);
  _SFD_DATA_RANGE_CHECK(chartInstance.c1_Vz, 9U);
  _SFD_DATA_RANGE_CHECK(chartInstance.c1_Vd, 2U);
  _SFD_DATA_RANGE_CHECK(*c1_i(), 10U);
  c1_previousEvent = _sfEvent_;
  _sfEvent_ = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG,0);
  if(chartInstance.c1_is_active_c1_servo_demo == 0) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG,0);
    chartInstance.c1_is_active_c1_servo_demo = 1;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG,0);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG,4);
    chartInstance.c1_ton = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance.c1_ton, 3U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG,0);
    chartInstance.c1_toff = chartInstance.c1_ton + *c1_duty_cycle() *
      chartInstance.c1_Tpwm / 100.0;
    _SFD_DATA_RANGE_CHECK(chartInstance.c1_toff, 7U);
    chartInstance.c1_is_c1_servo_demo = (uint8_T)c1_IN_energize_solenoid;
    _SFD_CS_CALL(STATE_ACTIVE_TAG,1);
    chartInstance.c1_tp_energize_solenoid = 1;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG,3);
    chartInstance.c1_is_energize_solenoid = (uint8_T)c1_IN_pull_in_current;
    _SFD_CS_CALL(STATE_ACTIVE_TAG,2);
    chartInstance.c1_tp_pull_in_current = 1;
    *c1_v() = chartInstance.c1_Vs;
    _SFD_DATA_RANGE_CHECK(*c1_v(), 6U);
  } else {
    switch(chartInstance.c1_is_c1_servo_demo) {
     case c1_IN_energize_solenoid:
      CV_CHART_EVAL(0,0,1);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG,1);
      if(CV_TRANSITION_EVAL(2U, (int32_T)_SFD_CCP_CALL(2,0,(_sfTime_ >
          chartInstance.c1_toff))) != 0) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG,2);
        chartInstance.c1_ton += chartInstance.c1_Tpwm;
        _SFD_DATA_RANGE_CHECK(chartInstance.c1_ton, 3U);
        switch(chartInstance.c1_is_energize_solenoid) {
         case c1_IN_pull_in_current:
          CV_STATE_EVAL(1,1,1);
          chartInstance.c1_tp_pull_in_current = 0;
          chartInstance.c1_is_energize_solenoid = (uint8_T)c1_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG,2);
          break;
         case c1_IN_regulate_hold_current:
          CV_STATE_EVAL(1,1,2);
          switch(chartInstance.c1_is_regulate_hold_current) {
           case c1_IN_freewheel:
            CV_STATE_EVAL(5,1,1);
            chartInstance.c1_tp_freewheel = 0;
            chartInstance.c1_is_regulate_hold_current =
              (uint8_T)c1_IN_NO_ACTIVE_CHILD;
            _SFD_CS_CALL(STATE_INACTIVE_TAG,4);
            break;
           case c1_IN_hold:
            CV_STATE_EVAL(5,1,2);
            chartInstance.c1_tp_hold = 0;
            chartInstance.c1_is_regulate_hold_current =
              (uint8_T)c1_IN_NO_ACTIVE_CHILD;
            _SFD_CS_CALL(STATE_INACTIVE_TAG,3);
            break;
           default:
            CV_STATE_EVAL(5,1,0);
            break;
          }
          chartInstance.c1_tp_regulate_hold_current = 0;
          chartInstance.c1_is_energize_solenoid = (uint8_T)c1_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG,5);
          break;
         default:
          CV_STATE_EVAL(1,1,0);
          break;
        }
        chartInstance.c1_tp_energize_solenoid = 0;
        chartInstance.c1_is_c1_servo_demo = (uint8_T)c1_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG,1);
        chartInstance.c1_is_c1_servo_demo = (uint8_T)c1_IN_solenoid_off;
        _SFD_CS_CALL(STATE_ACTIVE_TAG,0);
        chartInstance.c1_tp_solenoid_off = 1;
        *c1_v() = (real_T)c1__s32_uminus__(*c1_i() > 0.0) * chartInstance.c1_Vz;
        _SFD_DATA_RANGE_CHECK(*c1_v(), 6U);
      } else {
        switch(chartInstance.c1_is_energize_solenoid) {
         case c1_IN_pull_in_current:
          CV_STATE_EVAL(1,0,1);
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG,2);
          if(CV_TRANSITION_EVAL(6U, (int32_T)_SFD_CCP_CALL(6,0,(*c1_i() >=
              chartInstance.c1_Ipull))) != 0) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG,6);
            chartInstance.c1_tp_pull_in_current = 0;
            chartInstance.c1_is_energize_solenoid =
              (uint8_T)c1_IN_NO_ACTIVE_CHILD;
            _SFD_CS_CALL(STATE_INACTIVE_TAG,2);
            chartInstance.c1_is_energize_solenoid =
              (uint8_T)c1_IN_regulate_hold_current;
            _SFD_CS_CALL(STATE_ACTIVE_TAG,5);
            chartInstance.c1_tp_regulate_hold_current = 1;
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG,8);
            chartInstance.c1_is_regulate_hold_current = (uint8_T)c1_IN_freewheel;
            _SFD_CS_CALL(STATE_ACTIVE_TAG,4);
            chartInstance.c1_tp_freewheel = 1;
            *c1_v() = (real_T)c1__s32_uminus__(*c1_i() > 0.0) *
              chartInstance.c1_Vd;
            _SFD_DATA_RANGE_CHECK(*c1_v(), 6U);
          }
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG,2);
          break;
         case c1_IN_regulate_hold_current:
          CV_STATE_EVAL(1,0,2);
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG,5);
          switch(chartInstance.c1_is_regulate_hold_current) {
           case c1_IN_freewheel:
            CV_STATE_EVAL(5,0,1);
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG,4);
            if(CV_TRANSITION_EVAL(1U, (int32_T)_SFD_CCP_CALL(1,0,(*c1_i() <=
                chartInstance.c1_Ihold - chartInstance.c1_deltai))) != 0) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG,1);
              chartInstance.c1_tp_freewheel = 0;
              chartInstance.c1_is_regulate_hold_current =
                (uint8_T)c1_IN_NO_ACTIVE_CHILD;
              _SFD_CS_CALL(STATE_INACTIVE_TAG,4);
              chartInstance.c1_is_regulate_hold_current = (uint8_T)c1_IN_hold;
              _SFD_CS_CALL(STATE_ACTIVE_TAG,3);
              chartInstance.c1_tp_hold = 1;
              *c1_v() = chartInstance.c1_Vs;
              _SFD_DATA_RANGE_CHECK(*c1_v(), 6U);
            } else {
              *c1_v() = (real_T)c1__s32_uminus__(*c1_i() > 0.0) *
                chartInstance.c1_Vd;
              _SFD_DATA_RANGE_CHECK(*c1_v(), 6U);
            }
            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG,4);
            break;
           case c1_IN_hold:
            CV_STATE_EVAL(5,0,2);
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG,3);
            if(CV_TRANSITION_EVAL(5U, (int32_T)_SFD_CCP_CALL(5,0,(*c1_i() >=
                chartInstance.c1_Ihold + chartInstance.c1_deltai))) != 0) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG,5);
              chartInstance.c1_tp_hold = 0;
              chartInstance.c1_is_regulate_hold_current =
                (uint8_T)c1_IN_NO_ACTIVE_CHILD;
              _SFD_CS_CALL(STATE_INACTIVE_TAG,3);
              chartInstance.c1_is_regulate_hold_current =
                (uint8_T)c1_IN_freewheel;
              _SFD_CS_CALL(STATE_ACTIVE_TAG,4);
              chartInstance.c1_tp_freewheel = 1;
              *c1_v() = (real_T)c1__s32_uminus__(*c1_i() > 0.0) *
                chartInstance.c1_Vd;
              _SFD_DATA_RANGE_CHECK(*c1_v(), 6U);
            }
            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG,3);
            break;
           default:
            CV_STATE_EVAL(5,0,0);
            break;
          }
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG,5);
          break;
         default:
          CV_STATE_EVAL(1,0,0);
          break;
        }
      }
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG,1);
      break;
     case c1_IN_solenoid_off:
      CV_CHART_EVAL(0,0,2);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG,0);
      if(CV_TRANSITION_EVAL(7U, (int32_T)_SFD_CCP_CALL(7,0,(_sfTime_ >=
          chartInstance.c1_ton))) != 0) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG,7);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG,0);
        chartInstance.c1_toff = chartInstance.c1_ton + *c1_duty_cycle() *
          chartInstance.c1_Tpwm / 100.0;
        _SFD_DATA_RANGE_CHECK(chartInstance.c1_toff, 7U);
        chartInstance.c1_tp_solenoid_off = 0;
        chartInstance.c1_is_c1_servo_demo = (uint8_T)c1_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG,0);
        chartInstance.c1_is_c1_servo_demo = (uint8_T)c1_IN_energize_solenoid;
        _SFD_CS_CALL(STATE_ACTIVE_TAG,1);
        chartInstance.c1_tp_energize_solenoid = 1;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG,3);
        chartInstance.c1_is_energize_solenoid = (uint8_T)c1_IN_pull_in_current;
        _SFD_CS_CALL(STATE_ACTIVE_TAG,2);
        chartInstance.c1_tp_pull_in_current = 1;
        *c1_v() = chartInstance.c1_Vs;
        _SFD_DATA_RANGE_CHECK(*c1_v(), 6U);
      } else {
        *c1_v() = (real_T)c1__s32_uminus__(*c1_i() > 0.0) * chartInstance.c1_Vz;
        _SFD_DATA_RANGE_CHECK(*c1_v(), 6U);
      }
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG,0);
      break;
     default:
      CV_CHART_EVAL(0,0,0);
      break;
    }
  }
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG,0);
  _sfEvent_ = c1_previousEvent;
}

static int32_T c1__s32_uminus__(int32_T c1_b)
{
  if(c1_b < -2147483647) {
    sf_debug_overflow_detection(0);
  }
  return -c1_b;
}

static real_T *c1_v(void)
{
  return (real_T *)ssGetOutputPortSignal(chartInstance.S, 1);
}

static real_T *c1_duty_cycle(void)
{
  return (real_T *)ssGetInputPortSignal(chartInstance.S, 0);
}

static real_T *c1_i(void)
{
  return (real_T *)ssGetInputPortSignal(chartInstance.S, 1);
}

static void init_test_point_addr_map(void)
{
  chartInstance.c1_testPointAddrMap[0] = &chartInstance.c1_ton;
  chartInstance.c1_testPointAddrMap[1] = &chartInstance.c1_toff;
  chartInstance.c1_testPointAddrMap[2] = &chartInstance.c1_tp_energize_solenoid;
  chartInstance.c1_testPointAddrMap[3] = &chartInstance.c1_tp_pull_in_current;
  chartInstance.c1_testPointAddrMap[4] =
    &chartInstance.c1_tp_regulate_hold_current;
  chartInstance.c1_testPointAddrMap[5] = &chartInstance.c1_tp_freewheel;
  chartInstance.c1_testPointAddrMap[6] = &chartInstance.c1_tp_hold;
  chartInstance.c1_testPointAddrMap[7] = &chartInstance.c1_tp_solenoid_off;
}

static void **get_test_point_address_map(void)
{
  return &chartInstance.c1_testPointAddrMap[0];
}

static rtwCAPI_ModelMappingInfo *get_test_point_mapping_info(void)
{
  return &chartInstance.c1_testPointMappingInfo;
}

/* SFunction Glue Code */
static void init_test_point_mapping_info(SimStruct *S);
void sf_c1_servo_demo_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2490158668U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1102783992U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2657140794U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3802580316U);
}

mxArray *sf_c1_servo_demo_get_autoinheritance_info(void)
{
  const char *autoinheritanceInfoStructFieldNames[] =
  {"checksum","inputTypes","outputSizes","outputTypes"};
  mxArray *mxAutoinheritanceInfo = NULL;
  mxArray *mxChecksum = NULL;
  mxArray *mxInputTypes = NULL;
  mxArray *mxOutputSizes = NULL;
  mxArray *mxOutputTypes = NULL;

  mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,
   sizeof(autoinheritanceInfoStructFieldNames)/sizeof(char *),
   autoinheritanceInfoStructFieldNames);

  mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
  ((real_T *)mxGetPr((mxChecksum)))[0] = (real_T)(0U);
  ((real_T *)mxGetPr((mxChecksum)))[1] = (real_T)(0U);
  ((real_T *)mxGetPr((mxChecksum)))[2] = (real_T)(0U);
  ((real_T *)mxGetPr((mxChecksum)))[3] = (real_T)(0U);

  mxInputTypes = mxCreateDoubleMatrix(1,2,mxREAL);
  ((real_T *)mxGetPr((mxInputTypes)))[0] = (real_T)(10U);
  ((real_T *)mxGetPr((mxInputTypes)))[1] = (real_T)(10U);

  mxOutputSizes = mxCreateDoubleMatrix(2,1,mxREAL);
  mxOutputTypes = mxCreateDoubleMatrix(1,1,mxREAL);
  ((real_T *)mxGetPr((mxOutputSizes)))[0] = (real_T)(1U);
  ((real_T *)mxGetPr((mxOutputSizes)))[1] = (real_T)(1U);
  ((real_T *)mxGetPr((mxOutputTypes)))[0] = (real_T)(10U);

  mxSetFieldByNumber(mxAutoinheritanceInfo,0,0,mxChecksum);
  mxSetFieldByNumber(mxAutoinheritanceInfo,0,1,mxInputTypes);
  mxSetFieldByNumber(mxAutoinheritanceInfo,0,2,mxOutputSizes);
  mxSetFieldByNumber(mxAutoinheritanceInfo,0,3,mxOutputTypes);

  return(mxAutoinheritanceInfo);
}

static void chart_debug_initialization(SimStruct *S)
{
  if(ssIsFirstInitCond(S)) {
    /* do this only if simulation is starting */
    if(!sim_mode_is_rtw_gen(S)) {
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent =
          sf_debug_initialize_chart(_servo_demoMachineNumber_,
         1,
         6,
         9,
         12,
         0,
         0,
         0,
         0,
         &(chartInstance.chartNumber),
         &(chartInstance.instanceNumber),
         ssGetPath(S),
         (void *)S);
        if(chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting(_servo_demoMachineNumber_,chartInstance.chartNumber,0);
          sf_debug_set_chart_event_thresholds(_servo_demoMachineNumber_,
           chartInstance.chartNumber,
           0,
           0,
           0);

          _SFD_SET_DATA_PROPS(6,2,0,1,SF_DOUBLE,0,NULL,0,0.0,1.0,0,"v",0);
          _SFD_SET_DATA_PROPS(0,1,1,0,SF_DOUBLE,0,NULL,0,0.0,1.0,0,"duty_cycle",0);
          _SFD_SET_DATA_PROPS(3,0,0,0,SF_DOUBLE,0,NULL,0,0.0,1.0,0,"ton",0);
          _SFD_SET_DATA_PROPS(7,0,0,0,SF_DOUBLE,0,NULL,0,0.0,1.0,0,"toff",0);
          _SFD_SET_DATA_PROPS(5,10,0,0,SF_DOUBLE,0,NULL,0,0.0,1.0,0,"Tpwm",0);
          _SFD_SET_DATA_PROPS(1,10,0,0,SF_DOUBLE,0,NULL,0,0.0,1.0,0,"Ipull",0);
          _SFD_SET_DATA_PROPS(4,10,0,0,SF_DOUBLE,0,NULL,0,0.0,1.0,0,"Ihold",0);
          _SFD_SET_DATA_PROPS(11,10,0,0,SF_DOUBLE,0,NULL,0,0.0,1.0,0,"deltai",0);
          _SFD_SET_DATA_PROPS(8,10,0,0,SF_DOUBLE,0,NULL,0,0.0,1.0,0,"Vs",0);
          _SFD_SET_DATA_PROPS(9,10,0,0,SF_DOUBLE,0,NULL,0,0.0,1.0,0,"Vz",0);
          _SFD_SET_DATA_PROPS(2,10,0,0,SF_DOUBLE,0,NULL,0,0.0,1.0,0,"Vd",0);
          _SFD_SET_DATA_PROPS(10,1,1,0,SF_DOUBLE,0,NULL,0,0.0,1.0,0,"i",0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(0,0,0);
          _SFD_CH_SUBSTATE_COUNT(2);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,1);
          _SFD_CH_SUBSTATE_INDEX(1,0);
          _SFD_ST_SUBSTATE_COUNT(1,2);
          _SFD_ST_SUBSTATE_INDEX(1,0,2);
          _SFD_ST_SUBSTATE_INDEX(1,1,5);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(5,2);
          _SFD_ST_SUBSTATE_INDEX(5,0,4);
          _SFD_ST_SUBSTATE_INDEX(5,1,3);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(0,0);
        }
        _SFD_CV_INIT_CHART(2,1,0,0);
        {
          _SFD_CV_INIT_STATE(1,2,1,1,0,0,NULL,NULL);
        }
        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }
        {
          _SFD_CV_INIT_STATE(5,2,1,1,0,0,NULL,NULL);
        }
        {
          _SFD_CV_INIT_STATE(4,0,0,0,0,0,NULL,NULL);
        }
        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }
        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);

        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = {2};
          static unsigned int sEndGuardMap[] = {12};
          static int sPostFixPredicateTree[] = {0};
          _SFD_CV_INIT_TRANS(6,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,&(sPostFixPredicateTree[0]));
        }
        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = {2};
          static unsigned int sEndGuardMap[] = {10};
          static int sPostFixPredicateTree[] = {0};
          _SFD_CV_INIT_TRANS(7,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,&(sPostFixPredicateTree[0]));
        }
        _SFD_CV_INIT_TRANS(8,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = {2};
          static unsigned int sEndGuardMap[] = {10};
          static int sPostFixPredicateTree[] = {0};
          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,&(sPostFixPredicateTree[0]));
        }
        {
          static unsigned int sStartGuardMap[] = {2};
          static unsigned int sEndGuardMap[] = {21};
          static int sPostFixPredicateTree[] = {0};
          _SFD_CV_INIT_TRANS(1,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,&(sPostFixPredicateTree[0]));
        }
        {
          static unsigned int sStartGuardMap[] = {2};
          static unsigned int sEndGuardMap[] = {21};
          static int sPostFixPredicateTree[] = {0};
          _SFD_CV_INIT_TRANS(5,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,&(sPostFixPredicateTree[0]));
        }
        _SFD_TRANS_COV_WTS(4,0,0,1,0);
        if(chartAlreadyPresent==0)
        {
          _SFD_TRANS_COV_MAPS(4,
           0,NULL,NULL,
           0,NULL,NULL,
           1,NULL,NULL,
           0,NULL,NULL);
        }
        _SFD_TRANS_COV_WTS(3,0,0,0,0);
        if(chartAlreadyPresent==0)
        {
          _SFD_TRANS_COV_MAPS(3,
           0,NULL,NULL,
           0,NULL,NULL,
           0,NULL,NULL,
           0,NULL,NULL);
        }
        _SFD_TRANS_COV_WTS(6,0,1,0,0);
        if(chartAlreadyPresent==0)
        {
          static unsigned int sStartGuardMap[] = {2};
          static unsigned int sEndGuardMap[] = {12};
          _SFD_TRANS_COV_MAPS(6,
           0,NULL,NULL,
           1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
           0,NULL,NULL,
           0,NULL,NULL);
        }
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if(chartAlreadyPresent==0)
        {
          _SFD_TRANS_COV_MAPS(0,
           0,NULL,NULL,
           0,NULL,NULL,
           1,NULL,NULL,
           0,NULL,NULL);
        }
        _SFD_TRANS_COV_WTS(7,0,1,0,0);
        if(chartAlreadyPresent==0)
        {
          static unsigned int sStartGuardMap[] = {2};
          static unsigned int sEndGuardMap[] = {10};
          _SFD_TRANS_COV_MAPS(7,
           0,NULL,NULL,
           1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
           0,NULL,NULL,
           0,NULL,NULL);
        }
        _SFD_TRANS_COV_WTS(8,0,0,0,0);
        if(chartAlreadyPresent==0)
        {
          _SFD_TRANS_COV_MAPS(8,
           0,NULL,NULL,
           0,NULL,NULL,
           0,NULL,NULL,
           0,NULL,NULL);
        }
        _SFD_TRANS_COV_WTS(2,0,1,1,0);
        if(chartAlreadyPresent==0)
        {
          static unsigned int sStartGuardMap[] = {2};
          static unsigned int sEndGuardMap[] = {10};
          _SFD_TRANS_COV_MAPS(2,
           0,NULL,NULL,
           1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
           1,NULL,NULL,
           0,NULL,NULL);
        }
        _SFD_TRANS_COV_WTS(1,0,1,0,0);
        if(chartAlreadyPresent==0)
        {
          static unsigned int sStartGuardMap[] = {2};
          static unsigned int sEndGuardMap[] = {21};
          _SFD_TRANS_COV_MAPS(1,
           0,NULL,NULL,
           1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
           0,NULL,NULL,
           0,NULL,NULL);
        }
        _SFD_TRANS_COV_WTS(5,0,1,0,0);
        if(chartAlreadyPresent==0)
        {
          static unsigned int sStartGuardMap[] = {2};
          static unsigned int sEndGuardMap[] = {21};
          _SFD_TRANS_COV_MAPS(5,
           0,NULL,NULL,
           1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
           0,NULL,NULL,
           0,NULL,NULL);
        }
        _SFD_SET_DATA_VALUE_PTR(6U, c1_v());
        _SFD_SET_DATA_VALUE_PTR(0U, c1_duty_cycle());
        _SFD_SET_DATA_VALUE_PTR(3U, &chartInstance.c1_ton);
        _SFD_SET_DATA_VALUE_PTR(7U, &chartInstance.c1_toff);
        _SFD_SET_DATA_VALUE_PTR(5U, &chartInstance.c1_Tpwm);
        _SFD_SET_DATA_VALUE_PTR(1U, &chartInstance.c1_Ipull);
        _SFD_SET_DATA_VALUE_PTR(4U, &chartInstance.c1_Ihold);
        _SFD_SET_DATA_VALUE_PTR(11U, &chartInstance.c1_deltai);
        _SFD_SET_DATA_VALUE_PTR(8U, &chartInstance.c1_Vs);
        _SFD_SET_DATA_VALUE_PTR(9U, &chartInstance.c1_Vz);
        _SFD_SET_DATA_VALUE_PTR(2U, &chartInstance.c1_Vd);
        _SFD_SET_DATA_VALUE_PTR(10U, c1_i());
      }
    }
  } else {
    sf_debug_reset_current_state_configuration(_servo_demoMachineNumber_,chartInstance.chartNumber,chartInstance.instanceNumber);
  }
}

static void sf_opaque_initialize_c1_servo_demo(void *chartInstanceVar)
{
  chart_debug_initialization(chartInstance.S);
  initialize_c1_servo_demo();
}

static void sf_opaque_enable_c1_servo_demo(void *chartInstanceVar)
{
  enable_c1_servo_demo();
}

static void sf_opaque_disable_c1_servo_demo(void *chartInstanceVar)
{
  disable_c1_servo_demo();
}

static void sf_opaque_gateway_c1_servo_demo(void *chartInstanceVar)
{
  sf_c1_servo_demo();
}

static void sf_opaque_terminate_c1_servo_demo(void *chartInstanceVar)
{
  finalize_c1_servo_demo();
}

static void mdlSetWorkWidths_c1_servo_demo(SimStruct *S)
{
  /* Actual parameters from chart:
     Ihold Ipull Tpwm Vd Vs Vz deltai 
   */
  const char_T *rtParamNames[] = {"p1","p2","p3","p4","p5","p6","p7"};

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));
  /* registration for Ihold*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);
  /* registration for Ipull*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);
  /* registration for Tpwm*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_DOUBLE);
  /* registration for Vd*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_DOUBLE);
  /* registration for Vs*/
  ssRegDlgParamAsRunTimeParam(S, 4, 4, rtParamNames[4], SS_DOUBLE);
  /* registration for Vz*/
  ssRegDlgParamAsRunTimeParam(S, 5, 5, rtParamNames[5], SS_DOUBLE);
  /* registration for deltai*/
  ssRegDlgParamAsRunTimeParam(S, 6, 6, rtParamNames[6], SS_DOUBLE);

  if(sim_mode_is_rtw_gen(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable("servo_demo",1);
    int_T chartIsMultiInstanced =
      (int_T)sf_is_chart_multi_instanced("servo_demo",1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    if(chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"servo_demo",1,2);
      sf_mark_chart_reusable_outputs(S,"servo_demo",1,1);
    }
    if (!sf_is_chart_instance_optimized_out("servo_demo",1)) {
      int dtId;
      char *chartInstanceTypedefName =
        sf_chart_instance_typedef_name("servo_demo",1);
      dtId = ssRegisterDataType(S, chartInstanceTypedefName);
      if (dtId == INVALID_DTYPE_ID ) return;
      /* Register the size of the udt */
      if (!ssSetDataTypeSize(S, dtId, 8)) return;
      if(!ssSetNumDWork(S,1)) return;
      ssSetDWorkDataType(S, 0, dtId);
      ssSetDWorkWidth(S, 0, 1);
      ssSetDWorkName(S, 0, "ChartInstance"); /*optional name, less than 16 chars*/
      sf_set_rtw_identifier(S);
    }
    ssSetHasSubFunctions(S,!(chartIsInlinable));
    ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  }

  ssSetChecksum0(S,(2490158668U));
  ssSetChecksum1(S,(1102783992U));
  ssSetChecksum2(S,(2657140794U));
  ssSetChecksum3(S,(3802580316U));

  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c1_servo_demo(SimStruct *S)
{
  sf_write_symbol_mapping(S, "servo_demo", 1);
  ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
}

static void mdlStart_c1_servo_demo(SimStruct *S)
{
  chartInstance.chartInfo.chartInstance = NULL;
  chartInstance.chartInfo.isEMLChart = 0;
  chartInstance.chartInfo.chartInitialized = 0;
  chartInstance.chartInfo.sFunctionGateway = sf_opaque_gateway_c1_servo_demo;
  chartInstance.chartInfo.initializeChart = sf_opaque_initialize_c1_servo_demo;
  chartInstance.chartInfo.terminateChart = sf_opaque_terminate_c1_servo_demo;
  chartInstance.chartInfo.enableChart = sf_opaque_enable_c1_servo_demo;
  chartInstance.chartInfo.disableChart = sf_opaque_disable_c1_servo_demo;
  chartInstance.chartInfo.mdlRTW = mdlRTW_c1_servo_demo;
  chartInstance.chartInfo.mdlStart = mdlStart_c1_servo_demo;
  chartInstance.chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_servo_demo;
  chartInstance.chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance.chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance.chartInfo.storeCurrentConfiguration = NULL;
  chartInstance.S = S;
  ssSetUserData(S,(void *)(&(chartInstance.chartInfo))); /* register the chart instance with simstruct */

  if(!sim_mode_is_rtw_gen(S)) {
    init_test_point_mapping_info(S);
  }
}

void c1_servo_demo_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_servo_demo(S);
    break;
   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_servo_demo(S);
    break;
   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
     "Error calling c1_servo_demo_method_dispatcher.\n"
     "Can't handle method %d.\n", method);
    break;
  }
}

static const rtwCAPI_DataTypeMap dataTypeMap[] = {
  /* cName, mwName, numElements, elemMapIndex, dataSize, slDataId, isComplex, isPointer */
  {"real_T", "real_T", 0, 0, sizeof(real_T), SS_DOUBLE, 0, 0},
  {"uint8_T", "uint8_T", 0, 0, sizeof(uint8_T), SS_UINT8, 0, 0}
};

static real_T fixPtSlopeBiasVals[2] = {
  0,
  1
};

static const rtwCAPI_FixPtMap fixedPointMap[] = {
  /* *fracSlope, *bias, scaleType, exponent, isSigned */
  {NULL, NULL, rtwCAPI_FIX_RESERVED, 0, 0}
};

static const rtwCAPI_DimensionMap dimensionMap[] = {
  /* dataOrientation, dimArrayIndex, numDims*/
  {rtwCAPI_SCALAR, 0, 2}
};

static const uint_T dimensionArray[] = {
  1, 1
};

static real_T sfCAPIsampleTimeZero = 0.0;
static const rtwCAPI_SampleTimeMap sampleTimeMap[] = {
  /* *period, *offset, taskId, contextTid, mode */
  {&sfCAPIsampleTimeZero, &sfCAPIsampleTimeZero, 0, 0, 0}
};

static const rtwCAPI_Signals testPointSignals[] = {
  /* addrMapIndex, sysNum, SFRelativePath, dataName, portNumber, dataTypeIndex, dimIndex, fixPtIdx, sTimeIndex */
  {0, 0,"StateflowChart/ton", "ton", 0, 0, 0, 0, 0},
  {1, 0,"StateflowChart/toff", "toff", 0, 0, 0, 0, 0},
  {2, 0, "StateflowChart/energize_solenoid", "energize_solenoid", 0, 1, 0, 0, 0},
  {3, 0, "StateflowChart/energize_solenoid.pull_in_current", "pull_in_current",
    0, 1, 0, 0, 0},
  {4, 0, "StateflowChart/energize_solenoid.regulate_hold_current",
    "regulate_hold_current", 0, 1, 0, 0, 0},
  {5, 0, "StateflowChart/energize_solenoid.regulate_hold_current.freewheel",
    "freewheel", 0, 1, 0, 0, 0},
  {6, 0, "StateflowChart/energize_solenoid.regulate_hold_current.hold", "hold",
    0, 1, 0, 0, 0},
  {7, 0, "StateflowChart/solenoid_off", "solenoid_off", 0, 1, 0, 0, 0}
};

static rtwCAPI_ModelMappingStaticInfo testPointMappingStaticInfo = {
  /* block signal monitoring */
  {
    testPointSignals,                   /* Block signals Array  */
    8                                   /* Num Block IO signals */
  },

  /* parameter tuning */
  {
    NULL,                               /* Block parameters Array    */
    0,                                  /* Num block parameters      */
    NULL,                               /* Variable parameters Array */
    0                                   /* Num variable parameters   */
  },

  /* block states */
  {
    NULL,                               /* Block States array        */
    0                                   /* Num Block States          */
  },

  /* Static maps */
  {
    dataTypeMap,                        /* Data Type Map            */
    dimensionMap,                       /* Data Dimension Map       */
    fixedPointMap,                      /* Fixed Point Map          */
    NULL,                               /* Structure Element map    */
    sampleTimeMap,                      /* Sample Times Map         */
    dimensionArray                      /* Dimension Array          */
  },

  /* Target type */
  "float"
};

static void init_test_point_mapping_info(SimStruct *S) {
  rtwCAPI_ModelMappingInfo *testPointMappingInfo;
  void **testPointAddrMap;

  init_test_point_addr_map();
  testPointMappingInfo = get_test_point_mapping_info();
  testPointAddrMap = get_test_point_address_map();

  rtwCAPI_SetStaticMap(*testPointMappingInfo, &testPointMappingStaticInfo);
  rtwCAPI_SetPath(*testPointMappingInfo, "");
  rtwCAPI_SetFullPath(*testPointMappingInfo, NULL);
  rtwCAPI_SetDataAddressMap(*testPointMappingInfo, testPointAddrMap);
  rtwCAPI_SetChildMMIArray(*testPointMappingInfo, NULL);
  rtwCAPI_SetChildMMIArrayLen(*testPointMappingInfo, 0);

  ssSetModelMappingInfoPtr(S, testPointMappingInfo);
}

