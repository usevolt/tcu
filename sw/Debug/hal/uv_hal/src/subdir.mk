################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/uv_hal/src/crp.c \
../hal/uv_hal/src/printf.c \
../hal/uv_hal/src/uv_adc.c \
../hal/uv_hal/src/uv_button.c \
../hal/uv_hal/src/uv_canopen.c \
../hal/uv_hal/src/uv_eeprom.c \
../hal/uv_hal/src/uv_emc.c \
../hal/uv_hal/src/uv_errors.c \
../hal/uv_hal/src/uv_filters.c \
../hal/uv_hal/src/uv_ft81x.c \
../hal/uv_hal/src/uv_i2c.c \
../hal/uv_hal/src/uv_json.c \
../hal/uv_hal/src/uv_l6470.c \
../hal/uv_hal/src/uv_lcd.c \
../hal/uv_hal/src/uv_pid.c \
../hal/uv_hal/src/uv_pwm.c \
../hal/uv_hal/src/uv_reset.c \
../hal/uv_hal/src/uv_rtc.c \
../hal/uv_hal/src/uv_rtos.c \
../hal/uv_hal/src/uv_servo.c \
../hal/uv_hal/src/uv_spi.c \
../hal/uv_hal/src/uv_stdout.c \
../hal/uv_hal/src/uv_terminal.c \
../hal/uv_hal/src/uv_timer.c \
../hal/uv_hal/src/uv_uart.c \
../hal/uv_hal/src/uv_utilities.c \
../hal/uv_hal/src/uv_w25q128.c \
../hal/uv_hal/src/uv_wdt.c 

OBJS += \
./hal/uv_hal/src/crp.o \
./hal/uv_hal/src/printf.o \
./hal/uv_hal/src/uv_adc.o \
./hal/uv_hal/src/uv_button.o \
./hal/uv_hal/src/uv_canopen.o \
./hal/uv_hal/src/uv_eeprom.o \
./hal/uv_hal/src/uv_emc.o \
./hal/uv_hal/src/uv_errors.o \
./hal/uv_hal/src/uv_filters.o \
./hal/uv_hal/src/uv_ft81x.o \
./hal/uv_hal/src/uv_i2c.o \
./hal/uv_hal/src/uv_json.o \
./hal/uv_hal/src/uv_l6470.o \
./hal/uv_hal/src/uv_lcd.o \
./hal/uv_hal/src/uv_pid.o \
./hal/uv_hal/src/uv_pwm.o \
./hal/uv_hal/src/uv_reset.o \
./hal/uv_hal/src/uv_rtc.o \
./hal/uv_hal/src/uv_rtos.o \
./hal/uv_hal/src/uv_servo.o \
./hal/uv_hal/src/uv_spi.o \
./hal/uv_hal/src/uv_stdout.o \
./hal/uv_hal/src/uv_terminal.o \
./hal/uv_hal/src/uv_timer.o \
./hal/uv_hal/src/uv_uart.o \
./hal/uv_hal/src/uv_utilities.o \
./hal/uv_hal/src/uv_w25q128.o \
./hal/uv_hal/src/uv_wdt.o 

C_DEPS += \
./hal/uv_hal/src/crp.d \
./hal/uv_hal/src/printf.d \
./hal/uv_hal/src/uv_adc.d \
./hal/uv_hal/src/uv_button.d \
./hal/uv_hal/src/uv_canopen.d \
./hal/uv_hal/src/uv_eeprom.d \
./hal/uv_hal/src/uv_emc.d \
./hal/uv_hal/src/uv_errors.d \
./hal/uv_hal/src/uv_filters.d \
./hal/uv_hal/src/uv_ft81x.d \
./hal/uv_hal/src/uv_i2c.d \
./hal/uv_hal/src/uv_json.d \
./hal/uv_hal/src/uv_l6470.d \
./hal/uv_hal/src/uv_lcd.d \
./hal/uv_hal/src/uv_pid.d \
./hal/uv_hal/src/uv_pwm.d \
./hal/uv_hal/src/uv_reset.d \
./hal/uv_hal/src/uv_rtc.d \
./hal/uv_hal/src/uv_rtos.d \
./hal/uv_hal/src/uv_servo.d \
./hal/uv_hal/src/uv_spi.d \
./hal/uv_hal/src/uv_stdout.d \
./hal/uv_hal/src/uv_terminal.d \
./hal/uv_hal/src/uv_timer.d \
./hal/uv_hal/src/uv_uart.d \
./hal/uv_hal/src/uv_utilities.d \
./hal/uv_hal/src/uv_w25q128.d \
./hal/uv_hal/src/uv_wdt.d 


# Each subdirectory must supply rules for building sources it contributes
hal/uv_hal/src/%.o: ../hal/uv_hal/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


