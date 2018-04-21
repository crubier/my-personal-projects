################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/sbgCom/time/sbgTime.c 

OBJS += \
./src/sbgCom/time/sbgTime.o 

C_DEPS += \
./src/sbgCom/time/sbgTime.d 


# Each subdirectory must supply rules for building sources it contributes
src/sbgCom/time/%.o: ../src/sbgCom/time/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


