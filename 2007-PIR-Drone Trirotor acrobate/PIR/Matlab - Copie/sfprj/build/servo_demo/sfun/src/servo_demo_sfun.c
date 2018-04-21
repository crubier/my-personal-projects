/* Include files */
#define IN_SF_MACHINE_SOURCE            1
#include "servo_demo_sfun.h"
#include "c1_servo_demo.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint8_T _sfEvent_;
uint32_T _servo_demoMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void servo_demo_initializer(void)
{
  _sfEvent_ = CALL_EVENT;
}

void servo_demo_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_servo_demo_method_dispatcher(SimStruct *simstructPtr, const char
 *chartName, int_T method, void *data)
{
  if(!strcmp_ignore_ws(chartName,"servo_demo/PWM_driver_ckt/ SFunction ")) {
    c1_servo_demo_method_dispatcher(simstructPtr, method, data);
    return 1;
  }
  return 0;
}
unsigned int sf_servo_demo_process_check_sum_call( int nlhs, mxArray * plhs[],
 int nrhs, const mxArray * prhs[] )
{
#ifdef MATLAB_MEX_FILE
  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) ) return 0;
  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if(strcmp(commandName,"sf_get_check_sum")) return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if(nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if(!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3001779515U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3093288751U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(870329323U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3241469047U);
    }else if(!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    }else if(!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2703224572U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3542450069U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4094587722U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(524858718U);
    }else if(nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch(chartFileNumber) {
       case 1:
        {
          extern void sf_c1_servo_demo_get_check_sum(mxArray *plhs[]);
          sf_c1_servo_demo_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    }else if(!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1099933135U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3099773274U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1123725778U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3891239738U);
    }else {
      return 0;
    }
  } else{
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1838742911U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3048058178U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3021245786U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1241392195U);
  }
  return 1;
#else
  return 0;
#endif
}

unsigned int sf_servo_demo_autoinheritance_info( int nlhs, mxArray * plhs[], int
 nrhs, const mxArray * prhs[] )
{
#ifdef MATLAB_MEX_FILE
  char commandName[32];
  if (nrhs<2 || !mxIsChar(prhs[0]) ) return 0;
  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if(strcmp(commandName,"get_autoinheritance_info")) return 0;
  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch(chartFileNumber) {
     case 1:
      {
        extern mxArray *sf_c1_servo_demo_get_autoinheritance_info(void);
        plhs[0] = sf_c1_servo_demo_get_autoinheritance_info();
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }
  return 1;
#else
  return 0;
#endif
}
void servo_demo_debug_initialize(void)
{
  _servo_demoMachineNumber_ =
  sf_debug_initialize_machine("servo_demo","sfun",0,1,0,0,0);
  sf_debug_set_machine_event_thresholds(_servo_demoMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(_servo_demoMachineNumber_,0);
}

