################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Reversing\ a\ String.cpp 

OBJS += \
./src/Reversing\ a\ String.o 

CPP_DEPS += \
./src/Reversing\ a\ String.d 


# Each subdirectory must supply rules for building sources it contributes
src/Reversing\ a\ String.o: ../src/Reversing\ a\ String.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Reversing a String.d" -MT"src/Reversing\ a\ String.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


