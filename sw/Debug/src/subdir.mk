################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/messages.c \
../src/pin_mappings.c \
../src/sensor.c 

OBJS += \
./src/main.o \
./src/messages.o \
./src/pin_mappings.o \
./src/sensor.o 

C_DEPS += \
./src/main.d \
./src/messages.d \
./src/pin_mappings.d \
./src/sensor.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


