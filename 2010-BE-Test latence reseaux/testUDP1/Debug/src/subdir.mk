################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ConnexionUDP.cpp \
../src/serveur_embarque.cpp \
../src/testTimer.cpp 

OBJS += \
./src/ConnexionUDP.o \
./src/serveur_embarque.o \
./src/testTimer.o 

CPP_DEPS += \
./src/ConnexionUDP.d \
./src/serveur_embarque.d \
./src/testTimer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	arm-linux-g++ -D_GNU_SOURCE -D_REENTRANT -D__XENO__ -I"..\src\Emaxx" -I"C:\cygwin\root\arm\usr\include" -I"C:\cygwin\root\arm\usr\arm-linux-uclibc\include\c++\4.2.1" -I"..\src" -I"..\src\tinyxml" -I"C:\cygwin\usr\xenomai\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


