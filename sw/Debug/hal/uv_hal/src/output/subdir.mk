################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/uv_hal/src/output/uv_dual_output.c \
../hal/uv_hal/src/output/uv_dual_solenoid_output.c \
../hal/uv_hal/src/output/uv_output.c \
../hal/uv_hal/src/output/uv_solenoid_output.c 

OBJS += \
./hal/uv_hal/src/output/uv_dual_output.o \
./hal/uv_hal/src/output/uv_dual_solenoid_output.o \
./hal/uv_hal/src/output/uv_output.o \
./hal/uv_hal/src/output/uv_solenoid_output.o 

C_DEPS += \
./hal/uv_hal/src/output/uv_dual_output.d \
./hal/uv_hal/src/output/uv_dual_solenoid_output.d \
./hal/uv_hal/src/output/uv_output.d \
./hal/uv_hal/src/output/uv_solenoid_output.d 


# Each subdirectory must supply rules for building sources it contributes
hal/uv_hal/src/output/%.o: ../hal/uv_hal/src/output/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


