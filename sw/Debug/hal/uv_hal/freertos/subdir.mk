################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/uv_hal/freertos/croutine.c \
../hal/uv_hal/freertos/event_groups.c \
../hal/uv_hal/freertos/heap_2.c \
../hal/uv_hal/freertos/list.c \
../hal/uv_hal/freertos/queue.c \
../hal/uv_hal/freertos/tasks.c \
../hal/uv_hal/freertos/timers.c 

OBJS += \
./hal/uv_hal/freertos/croutine.o \
./hal/uv_hal/freertos/event_groups.o \
./hal/uv_hal/freertos/heap_2.o \
./hal/uv_hal/freertos/list.o \
./hal/uv_hal/freertos/queue.o \
./hal/uv_hal/freertos/tasks.o \
./hal/uv_hal/freertos/timers.o 

C_DEPS += \
./hal/uv_hal/freertos/croutine.d \
./hal/uv_hal/freertos/event_groups.d \
./hal/uv_hal/freertos/heap_2.d \
./hal/uv_hal/freertos/list.d \
./hal/uv_hal/freertos/queue.d \
./hal/uv_hal/freertos/tasks.d \
./hal/uv_hal/freertos/timers.d 


# Each subdirectory must supply rules for building sources it contributes
hal/uv_hal/freertos/%.o: ../hal/uv_hal/freertos/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


