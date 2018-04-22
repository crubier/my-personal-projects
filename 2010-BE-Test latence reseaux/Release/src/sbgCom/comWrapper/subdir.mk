################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/sbgCom/comWrapper/comSerialUnix.c 

OBJS += \
./src/sbgCom/comWrapper/comSerialUnix.o 

C_DEPS += \
./src/sbgCom/comWrapper/comSerialUnix.d 


# Each subdirectory must supply rules for building sources it contributes
src/sbgCom/comWrapper/%.o: ../src/sbgCom/comWrapper/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


