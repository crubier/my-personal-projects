################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/sbgCom/protocol/commands.c \
../src/sbgCom/protocol/commandsCalib.c \
../src/sbgCom/protocol/commandsFilter.c \
../src/sbgCom/protocol/commandsNav.c \
../src/sbgCom/protocol/commandsOrientation.c \
../src/sbgCom/protocol/protocol.c \
../src/sbgCom/protocol/protocolOutput.c \
../src/sbgCom/protocol/protocolOutputMode.c 

OBJS += \
./src/sbgCom/protocol/commands.o \
./src/sbgCom/protocol/commandsCalib.o \
./src/sbgCom/protocol/commandsFilter.o \
./src/sbgCom/protocol/commandsNav.o \
./src/sbgCom/protocol/commandsOrientation.o \
./src/sbgCom/protocol/protocol.o \
./src/sbgCom/protocol/protocolOutput.o \
./src/sbgCom/protocol/protocolOutputMode.o 

C_DEPS += \
./src/sbgCom/protocol/commands.d \
./src/sbgCom/protocol/commandsCalib.d \
./src/sbgCom/protocol/commandsFilter.d \
./src/sbgCom/protocol/commandsNav.d \
./src/sbgCom/protocol/commandsOrientation.d \
./src/sbgCom/protocol/protocol.d \
./src/sbgCom/protocol/protocolOutput.d \
./src/sbgCom/protocol/protocolOutputMode.d 


# Each subdirectory must supply rules for building sources it contributes
src/sbgCom/protocol/%.o: ../src/sbgCom/protocol/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


