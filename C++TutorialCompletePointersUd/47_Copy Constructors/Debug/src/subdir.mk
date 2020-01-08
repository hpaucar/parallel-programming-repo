################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Copy\ Constructors.cpp 

OBJS += \
./src/Copy\ Constructors.o 

CPP_DEPS += \
./src/Copy\ Constructors.d 


# Each subdirectory must supply rules for building sources it contributes
src/Copy\ Constructors.o: ../src/Copy\ Constructors.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Copy Constructors.d" -MT"src/Copy\ Constructors.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


