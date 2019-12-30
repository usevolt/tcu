################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/uv_hal/src/canopen/canopen_emcy.c \
../hal/uv_hal/src/canopen/canopen_heartbeat.c \
../hal/uv_hal/src/canopen/canopen_nmt.c \
../hal/uv_hal/src/canopen/canopen_obj_dict.c \
../hal/uv_hal/src/canopen/canopen_pdo.c \
../hal/uv_hal/src/canopen/canopen_sdo.c \
../hal/uv_hal/src/canopen/canopen_sdo_client.c \
../hal/uv_hal/src/canopen/canopen_sdo_server.c 

OBJS += \
./hal/uv_hal/src/canopen/canopen_emcy.o \
./hal/uv_hal/src/canopen/canopen_heartbeat.o \
./hal/uv_hal/src/canopen/canopen_nmt.o \
./hal/uv_hal/src/canopen/canopen_obj_dict.o \
./hal/uv_hal/src/canopen/canopen_pdo.o \
./hal/uv_hal/src/canopen/canopen_sdo.o \
./hal/uv_hal/src/canopen/canopen_sdo_client.o \
./hal/uv_hal/src/canopen/canopen_sdo_server.o 

C_DEPS += \
./hal/uv_hal/src/canopen/canopen_emcy.d \
./hal/uv_hal/src/canopen/canopen_heartbeat.d \
./hal/uv_hal/src/canopen/canopen_nmt.d \
./hal/uv_hal/src/canopen/canopen_obj_dict.d \
./hal/uv_hal/src/canopen/canopen_pdo.d \
./hal/uv_hal/src/canopen/canopen_sdo.d \
./hal/uv_hal/src/canopen/canopen_sdo_client.d \
./hal/uv_hal/src/canopen/canopen_sdo_server.d 


# Each subdirectory must supply rules for building sources it contributes
hal/uv_hal/src/canopen/%.o: ../hal/uv_hal/src/canopen/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


