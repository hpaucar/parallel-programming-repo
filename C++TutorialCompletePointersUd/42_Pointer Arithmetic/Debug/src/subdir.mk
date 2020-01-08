################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Pointer\ Arithmetic.cpp 

OBJS += \
./src/Pointer\ Arithmetic.o 

CPP_DEPS += \
./src/Pointer\ Arithmetic.d 


# Each subdirectory must supply rules for building sources it contributes
src/Pointer\ Arithmetic.o: ../src/Pointer\ Arithmetic.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Pointer Arithmetic.d" -MT"src/Pointer\ Arithmetic.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


