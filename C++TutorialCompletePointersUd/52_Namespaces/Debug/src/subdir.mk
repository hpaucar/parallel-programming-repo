################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Animals.cpp \
../src/Cat.cpp \
../src/Namespaces.cpp 

OBJS += \
./src/Animals.o \
./src/Cat.o \
./src/Namespaces.o 

CPP_DEPS += \
./src/Animals.d \
./src/Cat.d \
./src/Namespaces.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


