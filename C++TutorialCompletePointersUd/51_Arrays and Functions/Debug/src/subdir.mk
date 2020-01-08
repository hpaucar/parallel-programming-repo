################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Arrays\ and\ Functions.cpp 

OBJS += \
./src/Arrays\ and\ Functions.o 

CPP_DEPS += \
./src/Arrays\ and\ Functions.d 


# Each subdirectory must supply rules for building sources it contributes
src/Arrays\ and\ Functions.o: ../src/Arrays\ and\ Functions.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Arrays and Functions.d" -MT"src/Arrays\ and\ Functions.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


