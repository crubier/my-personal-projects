################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tinyxml/tinystr.cpp \
../src/tinyxml/tinyxml.cpp \
../src/tinyxml/tinyxmlerror.cpp \
../src/tinyxml/tinyxmlparser.cpp 

OBJS += \
./src/tinyxml/tinystr.o \
./src/tinyxml/tinyxml.o \
./src/tinyxml/tinyxmlerror.o \
./src/tinyxml/tinyxmlparser.o 

CPP_DEPS += \
./src/tinyxml/tinystr.d \
./src/tinyxml/tinyxml.d \
./src/tinyxml/tinyxmlerror.d \
./src/tinyxml/tinyxmlparser.d 


# Each subdirectory must supply rules for building sources it contributes
src/tinyxml/%.o: ../src/tinyxml/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


