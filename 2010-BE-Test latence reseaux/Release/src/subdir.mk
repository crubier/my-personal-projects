################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Switch.cpp \
../src/gestionMMC.cpp \
../src/gestionProtocoles.cpp \
../src/gestionTMTC.cpp \
../src/liaisonSerie.cpp \
../src/requete.cpp \
../src/serveur_embarque.cpp \
../src/telemetre.cpp \
../src/trame.cpp 

OBJS += \
./src/Switch.o \
./src/gestionMMC.o \
./src/gestionProtocoles.o \
./src/gestionTMTC.o \
./src/liaisonSerie.o \
./src/requete.o \
./src/serveur_embarque.o \
./src/telemetre.o \
./src/trame.o 

CPP_DEPS += \
./src/Switch.d \
./src/gestionMMC.d \
./src/gestionProtocoles.d \
./src/gestionTMTC.d \
./src/liaisonSerie.d \
./src/requete.d \
./src/serveur_embarque.d \
./src/telemetre.d \
./src/trame.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


