################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/uv_hal/src/ui/uv_ui_styles.c \
../hal/uv_hal/src/ui/uv_uibutton.c \
../hal/uv_hal/src/ui/uv_uidialog.c \
../hal/uv_hal/src/ui/uv_uidigitedit.c \
../hal/uv_hal/src/ui/uv_uidisplay.c \
../hal/uv_hal/src/ui/uv_uifonts.c \
../hal/uv_hal/src/ui/uv_uikeyboard.c \
../hal/uv_hal/src/ui/uv_uilabel.c \
../hal/uv_hal/src/ui/uv_uilayout.c \
../hal/uv_hal/src/ui/uv_uilist.c \
../hal/uv_hal/src/ui/uv_uinumpad.c \
../hal/uv_hal/src/ui/uv_uiobject.c \
../hal/uv_hal/src/ui/uv_uiprogressbar.c \
../hal/uv_hal/src/ui/uv_uislider.c \
../hal/uv_hal/src/ui/uv_uitabwindow.c \
../hal/uv_hal/src/ui/uv_uitogglebutton.c \
../hal/uv_hal/src/ui/uv_uitoucharea.c \
../hal/uv_hal/src/ui/uv_uitransition.c \
../hal/uv_hal/src/ui/uv_uitreeview.c \
../hal/uv_hal/src/ui/uv_uiwindow.c 

OBJS += \
./hal/uv_hal/src/ui/uv_ui_styles.o \
./hal/uv_hal/src/ui/uv_uibutton.o \
./hal/uv_hal/src/ui/uv_uidialog.o \
./hal/uv_hal/src/ui/uv_uidigitedit.o \
./hal/uv_hal/src/ui/uv_uidisplay.o \
./hal/uv_hal/src/ui/uv_uifonts.o \
./hal/uv_hal/src/ui/uv_uikeyboard.o \
./hal/uv_hal/src/ui/uv_uilabel.o \
./hal/uv_hal/src/ui/uv_uilayout.o \
./hal/uv_hal/src/ui/uv_uilist.o \
./hal/uv_hal/src/ui/uv_uinumpad.o \
./hal/uv_hal/src/ui/uv_uiobject.o \
./hal/uv_hal/src/ui/uv_uiprogressbar.o \
./hal/uv_hal/src/ui/uv_uislider.o \
./hal/uv_hal/src/ui/uv_uitabwindow.o \
./hal/uv_hal/src/ui/uv_uitogglebutton.o \
./hal/uv_hal/src/ui/uv_uitoucharea.o \
./hal/uv_hal/src/ui/uv_uitransition.o \
./hal/uv_hal/src/ui/uv_uitreeview.o \
./hal/uv_hal/src/ui/uv_uiwindow.o 

C_DEPS += \
./hal/uv_hal/src/ui/uv_ui_styles.d \
./hal/uv_hal/src/ui/uv_uibutton.d \
./hal/uv_hal/src/ui/uv_uidialog.d \
./hal/uv_hal/src/ui/uv_uidigitedit.d \
./hal/uv_hal/src/ui/uv_uidisplay.d \
./hal/uv_hal/src/ui/uv_uifonts.d \
./hal/uv_hal/src/ui/uv_uikeyboard.d \
./hal/uv_hal/src/ui/uv_uilabel.d \
./hal/uv_hal/src/ui/uv_uilayout.d \
./hal/uv_hal/src/ui/uv_uilist.d \
./hal/uv_hal/src/ui/uv_uinumpad.d \
./hal/uv_hal/src/ui/uv_uiobject.d \
./hal/uv_hal/src/ui/uv_uiprogressbar.d \
./hal/uv_hal/src/ui/uv_uislider.d \
./hal/uv_hal/src/ui/uv_uitabwindow.d \
./hal/uv_hal/src/ui/uv_uitogglebutton.d \
./hal/uv_hal/src/ui/uv_uitoucharea.d \
./hal/uv_hal/src/ui/uv_uitransition.d \
./hal/uv_hal/src/ui/uv_uitreeview.d \
./hal/uv_hal/src/ui/uv_uiwindow.d 


# Each subdirectory must supply rules for building sources it contributes
hal/uv_hal/src/ui/%.o: ../hal/uv_hal/src/ui/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


