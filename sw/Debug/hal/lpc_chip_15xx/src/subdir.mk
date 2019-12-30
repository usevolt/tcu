################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/lpc_chip_15xx/src/acmp_15xx.c \
../hal/lpc_chip_15xx/src/adc_15xx.c \
../hal/lpc_chip_15xx/src/chip_15xx.c \
../hal/lpc_chip_15xx/src/clock_15xx.c \
../hal/lpc_chip_15xx/src/crc_15xx.c \
../hal/lpc_chip_15xx/src/dac_15xx.c \
../hal/lpc_chip_15xx/src/dma_15xx.c \
../hal/lpc_chip_15xx/src/eeprom.c \
../hal/lpc_chip_15xx/src/gpio_15xx.c \
../hal/lpc_chip_15xx/src/i2c_common_15xx.c \
../hal/lpc_chip_15xx/src/i2cm_15xx.c \
../hal/lpc_chip_15xx/src/i2cs_15xx.c \
../hal/lpc_chip_15xx/src/iap.c \
../hal/lpc_chip_15xx/src/iocon_15xx.c \
../hal/lpc_chip_15xx/src/pinint_15xx.c \
../hal/lpc_chip_15xx/src/pmu_15xx.c \
../hal/lpc_chip_15xx/src/ring_buffer.c \
../hal/lpc_chip_15xx/src/ritimer_15xx.c \
../hal/lpc_chip_15xx/src/rtc_15xx.c \
../hal/lpc_chip_15xx/src/sct_15xx.c \
../hal/lpc_chip_15xx/src/sct_pwm_15xx.c \
../hal/lpc_chip_15xx/src/sctipu_15xx.c \
../hal/lpc_chip_15xx/src/spi_15xx.c \
../hal/lpc_chip_15xx/src/stopwatch_15xx.c \
../hal/lpc_chip_15xx/src/swm_15xx.c \
../hal/lpc_chip_15xx/src/sysctl_15xx.c \
../hal/lpc_chip_15xx/src/sysinit_15xx.c \
../hal/lpc_chip_15xx/src/uart_15xx.c \
../hal/lpc_chip_15xx/src/wwdt_15xx.c 

OBJS += \
./hal/lpc_chip_15xx/src/acmp_15xx.o \
./hal/lpc_chip_15xx/src/adc_15xx.o \
./hal/lpc_chip_15xx/src/chip_15xx.o \
./hal/lpc_chip_15xx/src/clock_15xx.o \
./hal/lpc_chip_15xx/src/crc_15xx.o \
./hal/lpc_chip_15xx/src/dac_15xx.o \
./hal/lpc_chip_15xx/src/dma_15xx.o \
./hal/lpc_chip_15xx/src/eeprom.o \
./hal/lpc_chip_15xx/src/gpio_15xx.o \
./hal/lpc_chip_15xx/src/i2c_common_15xx.o \
./hal/lpc_chip_15xx/src/i2cm_15xx.o \
./hal/lpc_chip_15xx/src/i2cs_15xx.o \
./hal/lpc_chip_15xx/src/iap.o \
./hal/lpc_chip_15xx/src/iocon_15xx.o \
./hal/lpc_chip_15xx/src/pinint_15xx.o \
./hal/lpc_chip_15xx/src/pmu_15xx.o \
./hal/lpc_chip_15xx/src/ring_buffer.o \
./hal/lpc_chip_15xx/src/ritimer_15xx.o \
./hal/lpc_chip_15xx/src/rtc_15xx.o \
./hal/lpc_chip_15xx/src/sct_15xx.o \
./hal/lpc_chip_15xx/src/sct_pwm_15xx.o \
./hal/lpc_chip_15xx/src/sctipu_15xx.o \
./hal/lpc_chip_15xx/src/spi_15xx.o \
./hal/lpc_chip_15xx/src/stopwatch_15xx.o \
./hal/lpc_chip_15xx/src/swm_15xx.o \
./hal/lpc_chip_15xx/src/sysctl_15xx.o \
./hal/lpc_chip_15xx/src/sysinit_15xx.o \
./hal/lpc_chip_15xx/src/uart_15xx.o \
./hal/lpc_chip_15xx/src/wwdt_15xx.o 

C_DEPS += \
./hal/lpc_chip_15xx/src/acmp_15xx.d \
./hal/lpc_chip_15xx/src/adc_15xx.d \
./hal/lpc_chip_15xx/src/chip_15xx.d \
./hal/lpc_chip_15xx/src/clock_15xx.d \
./hal/lpc_chip_15xx/src/crc_15xx.d \
./hal/lpc_chip_15xx/src/dac_15xx.d \
./hal/lpc_chip_15xx/src/dma_15xx.d \
./hal/lpc_chip_15xx/src/eeprom.d \
./hal/lpc_chip_15xx/src/gpio_15xx.d \
./hal/lpc_chip_15xx/src/i2c_common_15xx.d \
./hal/lpc_chip_15xx/src/i2cm_15xx.d \
./hal/lpc_chip_15xx/src/i2cs_15xx.d \
./hal/lpc_chip_15xx/src/iap.d \
./hal/lpc_chip_15xx/src/iocon_15xx.d \
./hal/lpc_chip_15xx/src/pinint_15xx.d \
./hal/lpc_chip_15xx/src/pmu_15xx.d \
./hal/lpc_chip_15xx/src/ring_buffer.d \
./hal/lpc_chip_15xx/src/ritimer_15xx.d \
./hal/lpc_chip_15xx/src/rtc_15xx.d \
./hal/lpc_chip_15xx/src/sct_15xx.d \
./hal/lpc_chip_15xx/src/sct_pwm_15xx.d \
./hal/lpc_chip_15xx/src/sctipu_15xx.d \
./hal/lpc_chip_15xx/src/spi_15xx.d \
./hal/lpc_chip_15xx/src/stopwatch_15xx.d \
./hal/lpc_chip_15xx/src/swm_15xx.d \
./hal/lpc_chip_15xx/src/sysctl_15xx.d \
./hal/lpc_chip_15xx/src/sysinit_15xx.d \
./hal/lpc_chip_15xx/src/uart_15xx.d \
./hal/lpc_chip_15xx/src/wwdt_15xx.d 


# Each subdirectory must supply rules for building sources it contributes
hal/lpc_chip_15xx/src/%.o: ../hal/lpc_chip_15xx/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


