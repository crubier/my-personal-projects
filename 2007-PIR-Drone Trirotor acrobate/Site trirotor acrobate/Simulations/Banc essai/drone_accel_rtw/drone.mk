# Copyright 1994-2004 The MathWorks, Inc.
#
# File    : accel_lcc.tmf   $Revision: 1.19.4.9 $
#
# Abstract:
#	Accelerator template makefile for building a PC-based,
#       RTW generated mex-file of Simulink model using generated C code. 
#	     LCC compiler version 2.4.
#
# 	This makefile attempts to conform to the guidelines specified in the
# 	IEEE Std 1003.2-1992 (POSIX) standard. It is designed to be used
#       with GNU Make (gmake) which is located in matlabroot/rtw/bin/win32.
#
# 	Note that this template is automatically customized by the Real-Time
#	Workshop build procedure to create "<model>.mk"
#
#       The following defines can be used to modify the behavior of the
#	build:
#
#         MEX_OPTS       - User specific mex options.
#	  OPT_OPTS       - Optimization options. Default is none. To enable 
#                          debugging specify as OPT_OPTS=-g. 
#	  USER_SRCS      - Additional user sources, such as files needed by
#			   S-functions.
#	  USER_INCLUDES  - Additional include paths
#			   (i.e. USER_INCLUDES="-Iwhere-ever -Iwhere-ever2")
#			   (For Lcc, have a '/'as file seperator before the 
#			   file name instead of a '\' . 
#			   i.e.,  d:\work\proj1/myfile.c - reqd for 'gmake')
#
#       This template makefile is designed to be used with a system target
#       file that contains 'rtwgensettings.BuildDirSuffix' see accel.tlc

#------------------------ Macros read by make_rtw ------------------------------
#
# The following macros are read by the Real-Time Workshop build procedure:
#
#  MAKECMD         - This is the command used to invoke the make utility
#  HOST            - What platform this template makefile is targeted for
#                    (i.e. PC or UNIX)
#  BUILD           - Invoke make from the Real-Time Workshop build procedure
#                    (yes/no)?
#  SYS_TARGET_FILE - Name of system target file.

MAKECMD         = "%MATLAB%\rtw\bin\win32\gmake"
HOST            = PC
BUILD           = yes
SYS_TARGET_FILE = accel.tlc

#---------------------- Tokens expanded by make_rtw ----------------------------
#
# The following tokens, when wrapped with "|>" and "<|" are expanded by the
# Real-Time Workshop build procedure.
#
#  MODEL_NAME      - Name of the Simulink block diagram
#  MODEL_MODULES   - Any additional generated source modules
#  MAKEFILE_NAME   - Name of makefile created from template makefile <model>.mk
#  MATLAB_ROOT     - Path to were MATLAB is installed.
#  MATLAB_BIN      - Path to MATLAB executable.
#  S_FUNCTIONS     - List of S-functions.
#  S_FUNCTIONS_LIB - List of S-functions libraries to link.
#  SOLVER          - Solver source file name
#  NUMST           - Number of sample times
#  TID01EQ         - yes (1) or no (0): Are sampling rates of continuous task
#                    (tid=0) and 1st discrete task equal.
#  NCSTATES        - Number of continuous states
#  BUILDARGS       - Options passed in at the command line.

MODEL           = drone
MODULES         = drone_acc_data.c rt_nonfinite.c 
MAKEFILE        = drone.mk
MATLAB_ROOT     = C:\MATLAB701
ALT_MATLAB_ROOT = C:\MATLAB701
MATLAB_BIN      = C:\MATLAB701\bin\win32
ALT_MATLAB_BIN  = C:\MATLAB701\bin\win32
S_FUNCTIONS     =  mech_engine.c
S_FUNCTIONS_LIB = 
SOLVER          = ode14x.c
NUMST           = 2
TID01EQ         = 1
NCSTATES        = 12
MEM_ALLOC       = RT_STATIC
BUILDARGS       = ADD_MDL_NAME_TO_GLOBALS=1

MODELREFS       = 
SHARED_SRC      = 
SHARED_SRC_DIR  = 
SHARED_BIN_DIR  = 
SHARED_LIB      = 

#--------------------------- Model and reference models -----------------------
MODELLIB                  = dronelib.lib
MODELREF_LINK_LIBS        = 
MODELREF_INC_PATH         = 
RELATIVE_PATH_TO_ANCHOR   = ..
MODELREF_TARGET_TYPE      = NONE

#-- In the case when directory name contains space ---
ifneq ($(MATLAB_ROOT),$(ALT_MATLAB_ROOT))
MATLAB_ROOT := $(ALT_MATLAB_ROOT)
endif
ifneq ($(MATLAB_BIN),$(ALT_MATLAB_BIN))
MATLAB_BIN := $(ALT_MATLAB_BIN)
endif

#--------------------------- Tool Specifications ------------------------------

LCC = $(MATLAB_ROOT)\sys\lcc
include $(MATLAB_ROOT)\rtw\c\tools\lcctools.mak

MEX = $(MATLAB_BIN)\mex.bat
CC  = $(MATLAB_BIN)\mex.bat -c

#------------------------------ Include Path -----------------------------------

# Additional includes

ADD_INCLUDES = \
	-Ic:\projets\cmd\simula~1\sim\bances~1 \
	-Ic:\projets\cmd\simula~1\sim\bances~1\drone_~1 \
	-I$(MATLAB_ROOT)\rtw\c\libsrc \
	-I$(MATLAB_ROOT)\toolbox\physmod\mech\c \


# see MATLAB_INCLUES and COMPILER_INCLUDES from lcctool.mak

SHARED_INCLUDES =
ifneq ($(SHARED_SRC_DIR),)
SHARED_INCLUDES = -I$(SHARED_SRC_DIR) 
endif

INCLUDES = -I. -I$(RELATIVE_PATH_TO_ANCHOR) $(MATLAB_INCLUDES) $(ADD_INCLUDES) \
           $(COMPILER_INCLUDES) $(USER_INCLUDES) $(MODELREF_INC_PATH) $(SHARED_INCLUDES)

#------------------------ C and MEX optimization options -----------------------
MEX_OPTS  =
OPT_OPTS  = $(DEFAULT_OPT_OPTS)
MEX_OPT_OPTS = $(OPT_OPTS)    # passed to 'mex -c'

ifeq "$(MEX_OPTS)" "-g"
MEX_OPT_OPTS =
endif

#-------------------------------- Mex Options  ---------------------------------
ifndef MEX_OPT_FILE
MEX_OPT_FILE = -f $(MATLAB_BIN)\mexopts\lccopts.bat
endif
MEX_FLAGS = $(MEX_OPT_OPTS) $(MEX_OPTS) $(MEX_OPT_FILE)

#----------------------------- Source Files -----------------------------------
USER_SRCS =

USER_OBJS       = $(USER_SRCS:.c=.obj)
LOCAL_USER_OBJS = $(notdir $(USER_OBJS))

SRCS      = $(MODEL)_acc.c $(MODULES)
OBJS      = $(SRCS:.c=.obj) $(USER_OBJS)
LINK_OBJS = $(SRCS:.c=.obj) $(LOCAL_USER_OBJS)

SHARED_OBJS := $(addsuffix .obj, $(basename $(wildcard $(SHARED_SRC))))
FMT_SHARED_OBJS = $(subst /,\,$(SHARED_OBJS))

#------------------------- Additional Libraries -------------------------------

LIBS =

ifeq ($(OPT_OPTS),$(DEFAULT_OPT_OPTS))
LIBS += $(MATLAB_ROOT)\toolbox\physmod\mech\lib\win32\mech_cg_rtwsfcn_lcc.lib
else
LIBS += mech_cg.lib
endif

ifeq ($(OPT_OPTS),$(DEFAULT_OPT_OPTS))
LIBS += $(MATLAB_ROOT)\rtw\c\lib\win32\rtwlib_rtwsfcn_lcc.lib
else
LIBS += rtwlib.lib
endif



LIBUT = $(MATLAB_ROOT)\rtw\c\lib\win32\libut_lcc.lib
LIBS += $(LIBUT)


PROGRAM = ../$(MODEL)_acc.dll

#--------------------------------- Rules --------------------------------------

$(PROGRAM) : $(OBJS) $(LIBS) $(SHARED_LIB)
	@echo ### Linking ...
	$(MEX) $(MEX_FLAGS) -outdir .. $(LINK_OBJS) $(S_FUNCTIONS_LIB) $(SHARED_LIB) $(LIBS) 
	@echo ### Created mex file: $(MODEL)_acc.dll

%.obj : %.c
	$(CC) $(MEX_FLAGS) $(INCLUDES) $<

%.obj : ../%.c
	$(CC) $(MEX_FLAGS) $(INCLUDES) $<

%.obj : $(MATLAB_ROOT)\rtw\c\libsrc/%.c
	$(CC) $(MEX_FLAGS) $(INCLUDES) $<

%.obj : $(MATLAB_ROOT)\toolbox\physmod\mech\c/%.c
	$(CC) $(MEX_FLAGS) $(INCLUDES) $<

%.obj : $(MATLAB_ROOT)\toolbox\physmod\mech\mech/%.c
	$(CC) $(MEX_FLAGS) $(INCLUDES) $<



%.obj : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) $(MEX_FLAGS) $(INCLUDES) $<

# Libraries:



MODULES_mech_cg = \
          mech0.obj \
          mech1.obj \
          mech10.obj \
          mech100.obj \
          mech101.obj \
          mech102.obj \
          mech103.obj \
          mech104.obj \
          mech105.obj \
          mech106.obj \
          mech107.obj \
          mech108.obj \
          mech109.obj \
          mech11.obj \
          mech110.obj \
          mech111.obj \
          mech112.obj \
          mech113.obj \
          mech114.obj \
          mech115.obj \
          mech116.obj \
          mech117.obj \
          mech118.obj \
          mech119.obj \
          mech12.obj \
          mech120.obj \
          mech121.obj \
          mech122.obj \
          mech123.obj \
          mech124.obj \
          mech125.obj \
          mech126.obj \
          mech127.obj \
          mech128.obj \
          mech129.obj \
          mech13.obj \
          mech130.obj \
          mech131.obj \
          mech132.obj \
          mech133.obj \
          mech134.obj \
          mech135.obj \
          mech136.obj \
          mech137.obj \
          mech138.obj \
          mech139.obj \
          mech14.obj \
          mech140.obj \
          mech141.obj \
          mech142.obj \
          mech143.obj \
          mech144.obj \
          mech145.obj \
          mech146.obj \
          mech147.obj \
          mech148.obj \
          mech149.obj \
          mech15.obj \
          mech150.obj \
          mech151.obj \
          mech152.obj \
          mech153.obj \
          mech154.obj \
          mech155.obj \
          mech156.obj \
          mech157.obj \
          mech158.obj \
          mech159.obj \
          mech16.obj \
          mech160.obj \
          mech161.obj \
          mech162.obj \
          mech163.obj \
          mech164.obj \
          mech165.obj \
          mech166.obj \
          mech167.obj \
          mech168.obj \
          mech169.obj \
          mech17.obj \
          mech170.obj \
          mech171.obj \
          mech172.obj \
          mech173.obj \
          mech174.obj \
          mech175.obj \
          mech176.obj \
          mech177.obj \
          mech178.obj \
          mech179.obj \
          mech18.obj \
          mech180.obj \
          mech181.obj \
          mech182.obj \
          mech183.obj \
          mech184.obj \
          mech185.obj \
          mech186.obj \
          mech187.obj \
          mech188.obj \
          mech189.obj \
          mech19.obj \
          mech190.obj \
          mech191.obj \
          mech192.obj \
          mech193.obj \
          mech194.obj \
          mech195.obj \
          mech196.obj \
          mech197.obj \
          mech198.obj \
          mech199.obj \
          mech2.obj \
          mech20.obj \
          mech200.obj \
          mech201.obj \
          mech202.obj \
          mech203.obj \
          mech204.obj \
          mech205.obj \
          mech206.obj \
          mech207.obj \
          mech208.obj \
          mech209.obj \
          mech21.obj \
          mech210.obj \
          mech211.obj \
          mech212.obj \
          mech213.obj \
          mech214.obj \
          mech215.obj \
          mech216.obj \
          mech217.obj \
          mech218.obj \
          mech219.obj \
          mech22.obj \
          mech220.obj \
          mech221.obj \
          mech222.obj \
          mech223.obj \
          mech224.obj \
          mech225.obj \
          mech226.obj \
          mech227.obj \
          mech228.obj \
          mech229.obj \
          mech23.obj \
          mech230.obj \
          mech231.obj \
          mech232.obj \
          mech233.obj \
          mech234.obj \
          mech235.obj \
          mech236.obj \
          mech237.obj \
          mech238.obj \
          mech239.obj \
          mech24.obj \
          mech240.obj \
          mech241.obj \
          mech242.obj \
          mech243.obj \
          mech244.obj \
          mech245.obj \
          mech246.obj \
          mech247.obj \
          mech248.obj \
          mech249.obj \
          mech25.obj \
          mech250.obj \
          mech251.obj \
          mech252.obj \
          mech253.obj \
          mech254.obj \
          mech255.obj \
          mech256.obj \
          mech257.obj \
          mech258.obj \
          mech259.obj \
          mech26.obj \
          mech260.obj \
          mech261.obj \
          mech262.obj \
          mech263.obj \
          mech264.obj \
          mech265.obj \
          mech266.obj \
          mech267.obj \
          mech268.obj \
          mech269.obj \
          mech27.obj \
          mech270.obj \
          mech271.obj \
          mech272.obj \
          mech273.obj \
          mech274.obj \
          mech275.obj \
          mech276.obj \
          mech277.obj \
          mech278.obj \
          mech279.obj \
          mech28.obj \
          mech280.obj \
          mech281.obj \
          mech282.obj \
          mech283.obj \
          mech284.obj \
          mech285.obj \
          mech286.obj \
          mech287.obj \
          mech288.obj \
          mech289.obj \
          mech29.obj \
          mech290.obj \
          mech291.obj \
          mech292.obj \
          mech293.obj \
          mech294.obj \
          mech295.obj \
          mech296.obj \
          mech297.obj \
          mech298.obj \
          mech299.obj \
          mech3.obj \
          mech30.obj \
          mech300.obj \
          mech301.obj \
          mech302.obj \
          mech303.obj \
          mech304.obj \
          mech305.obj \
          mech306.obj \
          mech307.obj \
          mech308.obj \
          mech309.obj \
          mech31.obj \
          mech310.obj \
          mech311.obj \
          mech312.obj \
          mech313.obj \
          mech314.obj \
          mech315.obj \
          mech316.obj \
          mech317.obj \
          mech318.obj \
          mech319.obj \
          mech32.obj \
          mech320.obj \
          mech321.obj \
          mech322.obj \
          mech323.obj \
          mech324.obj \
          mech325.obj \
          mech326.obj \
          mech327.obj \
          mech328.obj \
          mech329.obj \
          mech33.obj \
          mech330.obj \
          mech331.obj \
          mech332.obj \
          mech333.obj \
          mech334.obj \
          mech335.obj \
          mech336.obj \
          mech337.obj \
          mech338.obj \
          mech339.obj \
          mech34.obj \
          mech340.obj \
          mech341.obj \
          mech342.obj \
          mech343.obj \
          mech344.obj \
          mech345.obj \
          mech346.obj \
          mech347.obj \
          mech348.obj \
          mech349.obj \
          mech35.obj \
          mech350.obj \
          mech351.obj \
          mech352.obj \
          mech353.obj \
          mech354.obj \
          mech355.obj \
          mech356.obj \
          mech357.obj \
          mech358.obj \
          mech359.obj \
          mech36.obj \
          mech360.obj \
          mech361.obj \
          mech362.obj \
          mech363.obj \
          mech364.obj \
          mech365.obj \
          mech366.obj \
          mech367.obj \
          mech368.obj \
          mech369.obj \
          mech37.obj \
          mech370.obj \
          mech371.obj \
          mech372.obj \
          mech373.obj \
          mech374.obj \
          mech375.obj \
          mech376.obj \
          mech377.obj \
          mech378.obj \
          mech379.obj \
          mech38.obj \
          mech380.obj \
          mech381.obj \
          mech382.obj \
          mech383.obj \
          mech384.obj \
          mech385.obj \
          mech386.obj \
          mech387.obj \
          mech388.obj \
          mech389.obj \
          mech39.obj \
          mech390.obj \
          mech391.obj \
          mech392.obj \
          mech393.obj \
          mech394.obj \
          mech395.obj \
          mech396.obj \
          mech397.obj \
          mech398.obj \
          mech399.obj \
          mech4.obj \
          mech40.obj \
          mech400.obj \
          mech401.obj \
          mech402.obj \
          mech403.obj \
          mech404.obj \
          mech405.obj \
          mech406.obj \
          mech407.obj \
          mech408.obj \
          mech409.obj \
          mech41.obj \
          mech410.obj \
          mech411.obj \
          mech412.obj \
          mech413.obj \
          mech414.obj \
          mech415.obj \
          mech416.obj \
          mech417.obj \
          mech418.obj \
          mech419.obj \
          mech42.obj \
          mech420.obj \
          mech421.obj \
          mech422.obj \
          mech423.obj \
          mech424.obj \
          mech425.obj \
          mech426.obj \
          mech427.obj \
          mech428.obj \
          mech429.obj \
          mech43.obj \
          mech430.obj \
          mech431.obj \
          mech432.obj \
          mech433.obj \
          mech434.obj \
          mech435.obj \
          mech436.obj \
          mech437.obj \
          mech438.obj \
          mech439.obj \
          mech44.obj \
          mech440.obj \
          mech441.obj \
          mech442.obj \
          mech443.obj \
          mech444.obj \
          mech445.obj \
          mech446.obj \
          mech447.obj \
          mech448.obj \
          mech449.obj \
          mech45.obj \
          mech450.obj \
          mech451.obj \
          mech452.obj \
          mech453.obj \
          mech454.obj \
          mech455.obj \
          mech456.obj \
          mech457.obj \
          mech458.obj \
          mech459.obj \
          mech46.obj \
          mech460.obj \
          mech461.obj \
          mech462.obj \
          mech463.obj \
          mech464.obj \
          mech465.obj \
          mech466.obj \
          mech467.obj \
          mech468.obj \
          mech469.obj \
          mech47.obj \
          mech470.obj \
          mech471.obj \
          mech472.obj \
          mech473.obj \
          mech474.obj \
          mech475.obj \
          mech476.obj \
          mech477.obj \
          mech478.obj \
          mech479.obj \
          mech48.obj \
          mech480.obj \
          mech481.obj \
          mech482.obj \
          mech483.obj \
          mech484.obj \
          mech485.obj \
          mech486.obj \
          mech487.obj \
          mech488.obj \
          mech489.obj \
          mech49.obj \
          mech490.obj \
          mech491.obj \
          mech492.obj \
          mech493.obj \
          mech494.obj \
          mech495.obj \
          mech496.obj \
          mech497.obj \
          mech498.obj \
          mech499.obj \
          mech5.obj \
          mech50.obj \
          mech500.obj \
          mech501.obj \
          mech502.obj \
          mech503.obj \
          mech504.obj \
          mech505.obj \
          mech506.obj \
          mech507.obj \
          mech508.obj \
          mech509.obj \
          mech51.obj \
          mech510.obj \
          mech511.obj \
          mech512.obj \
          mech513.obj \
          mech514.obj \
          mech515.obj \
          mech516.obj \
          mech517.obj \
          mech518.obj \
          mech519.obj \
          mech52.obj \
          mech520.obj \
          mech521.obj \
          mech522.obj \
          mech523.obj \
          mech524.obj \
          mech525.obj \
          mech526.obj \
          mech527.obj \
          mech528.obj \
          mech529.obj \
          mech53.obj \
          mech530.obj \
          mech531.obj \
          mech532.obj \
          mech533.obj \
          mech534.obj \
          mech535.obj \
          mech536.obj \
          mech537.obj \
          mech538.obj \
          mech539.obj \
          mech54.obj \
          mech540.obj \
          mech541.obj \
          mech542.obj \
          mech543.obj \
          mech544.obj \
          mech545.obj \
          mech546.obj \
          mech547.obj \
          mech548.obj \
          mech55.obj \
          mech56.obj \
          mech57.obj \
          mech58.obj \
          mech59.obj \
          mech6.obj \
          mech60.obj \
          mech61.obj \
          mech62.obj \
          mech63.obj \
          mech64.obj \
          mech65.obj \
          mech66.obj \
          mech67.obj \
          mech68.obj \
          mech69.obj \
          mech7.obj \
          mech70.obj \
          mech71.obj \
          mech72.obj \
          mech73.obj \
          mech74.obj \
          mech75.obj \
          mech76.obj \
          mech77.obj \
          mech78.obj \
          mech79.obj \
          mech8.obj \
          mech80.obj \
          mech81.obj \
          mech82.obj \
          mech83.obj \
          mech84.obj \
          mech85.obj \
          mech86.obj \
          mech87.obj \
          mech88.obj \
          mech89.obj \
          mech9.obj \
          mech90.obj \
          mech91.obj \
          mech92.obj \
          mech93.obj \
          mech94.obj \
          mech95.obj \
          mech96.obj \
          mech97.obj \
          mech98.obj \
          mech99.obj \
          

mech_cg.lib :  $(MAKEFILE) rtw_proj.tmw $(MODULES_mech_cg)
	@echo ### Creating $@
	@if exist $@ del $@
	$(LIBCMD) /out:$@ $(MODULES_mech_cg)
	@echo ### $@ Created 

MODULES_rtwlib = \
          rt_atan2.obj \
          rt_atan232.obj \
          rt_backsubcc_dbl.obj \
          rt_backsubcc_sgl.obj \
          rt_backsubrc_dbl.obj \
          rt_backsubrc_sgl.obj \
          rt_backsubrr_dbl.obj \
          rt_backsubrr_sgl.obj \
          rt_enab.obj \
          rt_forwardsubcc_dbl.obj \
          rt_forwardsubcc_sgl.obj \
          rt_forwardsubcr_dbl.obj \
          rt_forwardsubcr_sgl.obj \
          rt_forwardsubrc_dbl.obj \
          rt_forwardsubrc_sgl.obj \
          rt_forwardsubrr_dbl.obj \
          rt_forwardsubrr_sgl.obj \
          rt_hypot.obj \
          rt_hypot32.obj \
          rt_i32zcfcn.obj \
          rt_intrp1flatcd.obj \
          rt_intrp1flatcf.obj \
          rt_intrp1flatd.obj \
          rt_intrp1flatf.obj \
          rt_intrp1lincd.obj \
          rt_intrp1lincf.obj \
          rt_intrp1linxd.obj \
          rt_intrp1linxf.obj \
          rt_intrp2flatcd.obj \
          rt_intrp2flatcf.obj \
          rt_intrp2flatd.obj \
          rt_intrp2flatf.obj \
          rt_intrp2lincd.obj \
          rt_intrp2lincf.obj \
          rt_intrp2lind.obj \
          rt_intrp2linf.obj \
          rt_intrp2linxd.obj \
          rt_intrp2linxf.obj \
          rt_intrp3lind.obj \
          rt_intrp3linf.obj \
          rt_intrp4lind.obj \
          rt_intrp4linf.obj \
          rt_intrp5lind.obj \
          rt_intrp5linf.obj \
          rt_intrpnflatcd.obj \
          rt_intrpnflatcf.obj \
          rt_intrpnflatd.obj \
          rt_intrpnflatf.obj \
          rt_intrpnlincd.obj \
          rt_intrpnlincf.obj \
          rt_intrpnlind.obj \
          rt_intrpnlinf.obj \
          rt_intrpnlinxd.obj \
          rt_intrpnlinxf.obj \
          rt_intrpnspld.obj \
          rt_intrpnsplf.obj \
          rt_logging.obj \
          rt_look.obj \
          rt_look1d.obj \
          rt_look1d32.obj \
          rt_look2d32_general.obj \
          rt_look2d32_normal.obj \
          rt_look2d_general.obj \
          rt_look2d_normal.obj \
          rt_look32.obj \
          rt_lookflat1bincsd.obj \
          rt_lookflat1bincsf.obj \
          rt_lookflat1binczd.obj \
          rt_lookflat1binczf.obj \
          rt_lookflat1evncsd.obj \
          rt_lookflat1evncsf.obj \
          rt_lookflat1evnczd.obj \
          rt_lookflat1evnczf.obj \
          rt_lookflat1lincsd.obj \
          rt_lookflat1lincsf.obj \
          rt_lookflat1linczd.obj \
          rt_lookflat1linczf.obj \
          rt_lookflat2bincsd.obj \
          rt_lookflat2bincsf.obj \
          rt_lookflat2binczd.obj \
          rt_lookflat2binczf.obj \
          rt_lookflat2evncsd.obj \
          rt_lookflat2evncsf.obj \
          rt_lookflat2evnczd.obj \
          rt_lookflat2evnczf.obj \
          rt_lookflat2lincsd.obj \
          rt_lookflat2lincsf.obj \
          rt_lookflat2linczd.obj \
          rt_lookflat2linczf.obj \
          rt_lookflatnbincsd.obj \
          rt_lookflatnbincsf.obj \
          rt_lookflatnbinczd.obj \
          rt_lookflatnbinczf.obj \
          rt_lookflatnevncsd.obj \
          rt_lookflatnevncsf.obj \
          rt_lookflatnevnczd.obj \
          rt_lookflatnevnczf.obj \
          rt_lookflatnlincsd.obj \
          rt_lookflatnlincsf.obj \
          rt_lookflatnlinczd.obj \
          rt_lookflatnlinczf.obj \
          rt_looklin1bincsd.obj \
          rt_looklin1bincsf.obj \
          rt_looklin1binczd.obj \
          rt_looklin1binczf.obj \
          rt_looklin1binxsd.obj \
          rt_looklin1binxsf.obj \
          rt_looklin1binxzd.obj \
          rt_looklin1binxzf.obj \
          rt_looklin1evncsd.obj \
          rt_looklin1evncsf.obj \
          rt_looklin1evnczd.obj \
          rt_looklin1evnczf.obj \
          rt_looklin1evnxsd.obj \
          rt_looklin1evnxsf.obj \
          rt_looklin1evnxzd.obj \
          rt_looklin1evnxzf.obj \
          rt_looklin1lincsd.obj \
          rt_looklin1lincsf.obj \
          rt_looklin1linczd.obj \
          rt_looklin1linczf.obj \
          rt_looklin1linxsd.obj \
          rt_looklin1linxsf.obj \
          rt_looklin1linxzd.obj \
          rt_looklin1linxzf.obj \
          rt_looklin2bincsd.obj \
          rt_looklin2bincsf.obj \
          rt_looklin2binczd.obj \
          rt_looklin2binczf.obj \
          rt_looklin2binxsd.obj \
          rt_looklin2binxsf.obj \
          rt_looklin2binxzd.obj \
          rt_looklin2binxzf.obj \
          rt_looklin2evncsd.obj \
          rt_looklin2evncsf.obj \
          rt_looklin2evnczd.obj \
          rt_looklin2evnczf.obj \
          rt_looklin2evnxsd.obj \
          rt_looklin2evnxsf.obj \
          rt_looklin2evnxzd.obj \
          rt_looklin2evnxzf.obj \
          rt_looklin2lincsd.obj \
          rt_looklin2lincsf.obj \
          rt_looklin2linczd.obj \
          rt_looklin2linczf.obj \
          rt_looklin2linxsd.obj \
          rt_looklin2linxsf.obj \
          rt_looklin2linxzd.obj \
          rt_looklin2linxzf.obj \
          rt_looklinnbincsd.obj \
          rt_looklinnbincsf.obj \
          rt_looklinnbinczd.obj \
          rt_looklinnbinczf.obj \
          rt_looklinnbinxsd.obj \
          rt_looklinnbinxsf.obj \
          rt_looklinnbinxzd.obj \
          rt_looklinnbinxzf.obj \
          rt_looklinnevncsd.obj \
          rt_looklinnevncsf.obj \
          rt_looklinnevnczd.obj \
          rt_looklinnevnczf.obj \
          rt_looklinnevnxsd.obj \
          rt_looklinnevnxsf.obj \
          rt_looklinnevnxzd.obj \
          rt_looklinnevnxzf.obj \
          rt_looklinnlincsd.obj \
          rt_looklinnlincsf.obj \
          rt_looklinnlinczd.obj \
          rt_looklinnlinczf.obj \
          rt_looklinnlinxsd.obj \
          rt_looklinnlinxsf.obj \
          rt_looklinnlinxzd.obj \
          rt_looklinnlinxzf.obj \
          rt_looksplnbincsd.obj \
          rt_looksplnbincsf.obj \
          rt_looksplnbinczd.obj \
          rt_looksplnbinczf.obj \
          rt_looksplnbinssd.obj \
          rt_looksplnbinssf.obj \
          rt_looksplnbinszd.obj \
          rt_looksplnbinszf.obj \
          rt_looksplnbinxsd.obj \
          rt_looksplnbinxsf.obj \
          rt_looksplnbinxzd.obj \
          rt_looksplnbinxzf.obj \
          rt_looksplnevncsd.obj \
          rt_looksplnevncsf.obj \
          rt_looksplnevnczd.obj \
          rt_looksplnevnczf.obj \
          rt_looksplnevnssd.obj \
          rt_looksplnevnssf.obj \
          rt_looksplnevnszd.obj \
          rt_looksplnevnszf.obj \
          rt_looksplnevnxsd.obj \
          rt_looksplnevnxsf.obj \
          rt_looksplnevnxzd.obj \
          rt_looksplnevnxzf.obj \
          rt_looksplnlincsd.obj \
          rt_looksplnlincsf.obj \
          rt_looksplnlinczd.obj \
          rt_looksplnlinczf.obj \
          rt_looksplnlinssd.obj \
          rt_looksplnlinssf.obj \
          rt_looksplnlinszd.obj \
          rt_looksplnlinszf.obj \
          rt_looksplnlinxsd.obj \
          rt_looksplnlinxsf.obj \
          rt_looksplnlinxzd.obj \
          rt_looksplnlinxzf.obj \
          rt_lu_cplx.obj \
          rt_lu_cplx_sgl.obj \
          rt_lu_real.obj \
          rt_lu_real_sgl.obj \
          rt_matdivcc_dbl.obj \
          rt_matdivcc_sgl.obj \
          rt_matdivcr_dbl.obj \
          rt_matdivcr_sgl.obj \
          rt_matdivrc_dbl.obj \
          rt_matdivrc_sgl.obj \
          rt_matdivrr_dbl.obj \
          rt_matdivrr_sgl.obj \
          rt_matmultandinccc_dbl.obj \
          rt_matmultandinccc_sgl.obj \
          rt_matmultandinccr_dbl.obj \
          rt_matmultandinccr_sgl.obj \
          rt_matmultandincrc_dbl.obj \
          rt_matmultandincrc_sgl.obj \
          rt_matmultandincrr_dbl.obj \
          rt_matmultandincrr_sgl.obj \
          rt_matmultcc_dbl.obj \
          rt_matmultcc_sgl.obj \
          rt_matmultcr_dbl.obj \
          rt_matmultcr_sgl.obj \
          rt_matmultrc_dbl.obj \
          rt_matmultrc_sgl.obj \
          rt_matmultrr_dbl.obj \
          rt_matmultrr_sgl.obj \
          rt_nrand.obj \
          rt_plookbincd.obj \
          rt_plookbincf.obj \
          rt_plookbinkcd.obj \
          rt_plookbinkcf.obj \
          rt_plookbinxd.obj \
          rt_plookbinxf.obj \
          rt_plookevncd.obj \
          rt_plookevncf.obj \
          rt_plookevnkcd.obj \
          rt_plookevnkcf.obj \
          rt_plookevnxd.obj \
          rt_plookevnxf.obj \
          rt_plooklincd.obj \
          rt_plooklincf.obj \
          rt_plooklinkcd.obj \
          rt_plooklinkcf.obj \
          rt_plooklinxd.obj \
          rt_plooklinxf.obj \
          rt_printf.obj \
          rt_sat_div_int16.obj \
          rt_sat_div_int32.obj \
          rt_sat_div_int8.obj \
          rt_sat_div_uint16.obj \
          rt_sat_div_uint32.obj \
          rt_sat_div_uint8.obj \
          rt_sat_prod_int16.obj \
          rt_sat_prod_int32.obj \
          rt_sat_prod_int8.obj \
          rt_sat_prod_uint16.obj \
          rt_sat_prod_uint32.obj \
          rt_sat_prod_uint8.obj \
          rt_tdelay.obj \
          rt_tdelayacc.obj \
          rt_urand.obj \
          rt_zcfcn.obj \
          

rtwlib.lib :  $(MAKEFILE) rtw_proj.tmw $(MODULES_rtwlib)
	@echo ### Creating $@
	@if exist $@ del $@
	$(LIBCMD) /out:$@ $(MODULES_rtwlib)
	@echo ### $@ Created 



clean :
	@echo ### Deleting the objects and $(PROGRAM)
	@del $(OBJS) ..\$(MODEL)_acc.dll $(wildcard *.obj) $(wildcard *.lib)

#----------------------------- Dependencies -------------------------------

$(OBJS) : $(MAKEFILE) rtw_proj.tmw

$(SHARED_OBJS) : $(SHARED_BIN_DIR)/%.obj : $(SHARED_SRC_DIR)/%.c 
	$(CC) -outdir $(SHARED_BIN_DIR) $(MEX_FLAGS) $(INCLUDES) $<

$(SHARED_LIB) : $(SHARED_OBJS)
	@echo ### Creating $@ 
	@if exist $@ del $@
	$(LIBCMD) /out:$@ $(FMT_SHARED_OBJS)
	@echo ### $@ Created   


