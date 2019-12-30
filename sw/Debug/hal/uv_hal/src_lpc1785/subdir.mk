################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/uv_hal/src_lpc1785/uv_can.c \
../hal/uv_hal/src_lpc1785/uv_gpio.c \
../hal/uv_hal/src_lpc1785/uv_memory.c 

OBJS += \
./hal/uv_hal/src_lpc1785/uv_can.o \
./hal/uv_hal/src_lpc1785/uv_gpio.o \
./hal/uv_hal/src_lpc1785/uv_memory.o 

C_DEPS += \
./hal/uv_hal/src_lpc1785/uv_can.d \
./hal/uv_hal/src_lpc1785/uv_gpio.d \
./hal/uv_hal/src_lpc1785/uv_memory.d 


# Each subdirectory must supply rules for building sources it contributes
hal/uv_hal/src_lpc1785/%.o: ../hal/uv_hal/src_lpc1785/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


