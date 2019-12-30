#############################################
#
#	USEVOLT MAKEFILE
# Builds a project adding a git hash to preprocessor symbols
# 
# * Project name is taken from the name of the git repository
# 
##############################################



### APP CONFIG ###


# Specify the CPU used. Depends on the used compiler
MCPU := cortex-m3
# Additional CPU define symbol, used for FreeRTOS comiple
CORE := CORE_M3

#Sepcify the optimizations used. Os == optimize for size, Og = optimize for debug, O3, O2, O1
O := Og

# Name of the directory where build files will be saved
BUILDDIR := release

# Name of the produced binary firmware
BINARY := tcu

# List of include directories
INCLUDEDIRS := 	-I"inc/" \
				-I"inc/modules" \
				-I"uw_can/" \
				-I"uv_hal/uv_hal/inc" \
				-I"uv_hal/uv_hal/inc/output" \
				-I"uv_hal/lpc_chip_15xx/inc" \
				-I"uv_hal/uv_hal/freertos/include" \
				-I"uv_hal/uv_hal/freertos/portable/GCC/ARM_CM3"
				
SOURCEDIRS := src \
				src/modules \
				uv_hal/uv_hal/src \
				uv_hal/uv_hal/src/output \
				uv_hal/uv_hal/freertos \
				uv_hal/uv_hal/src/canopen \
				uv_hal/uv_hal/freertos/portable/GCC/ARM_CM3 \
				uv_hal/uv_hal/src_lpc1549 \
				uv_hal/lpc_chip_15xx/src



#List of directories where to search libraries
LIB_DIRS := 	-L"uv_hal/lpc_chip_15xx/Debug"

#List of libraries
LIBS :=			-llpc_chip_15xx


### END OF APP CONFIG ###






CC := arm-none-eabi-gcc
SOURCES := $(shell find $(SOURCEDIRS) -maxdepth 1 -name '*.c')
GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always --tags)
GIT_REV_ID := $(shell git rev-list --count HEAD)
APP_NAME := $(shell basename `git rev-parse --show-toplevel`)
FULL_NAME := $(APP_NAME)_$(GIT_VERSION)


CFLAGS := -DDEBUG -D__CODE_RED -D$(CORE) -D__USE_CMSIS=$(CMSIS) -D__UV_PROJECT_NAME=$(FULL_NAME) -D__UV_PROGRAM_VERSION=$(GIT_REV_ID) -D__NEWLIB__ $(INCLUDEDIRS) -$(O) -g3 -Wall -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=$(MCPU) -mthumb


LDFLAGS := -nostdlib -Xlinker -Map="$(BUILDDIR)/$(APP_NAME).map" -Xlinker --cref -Xlinker --gc-sections -mcpu=$(MCPU) -mthumb -T "linker.ld" -D__UV_APP_VERSION=\"$(GIT_VERSION)\" -static $(LIB_DIRS) $(LIBS)


# Get list of object files, with paths
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:%.c=%.o))
# List of object dependencies
DEPS := $(OBJECTS:.o=.d)



all: $(BINARY)
	$(MAKE) post-build

$(BINARY): $(OBJECTS)
	@echo ""
	@echo "Linking target"
	@echo ""
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o "$(BINARY).axf"

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(dir $<) -MMD -MT $@ -c $< -o $@


post-build:
	-@echo ""
	-@echo 'Performing post-build steps'
	-@echo ""
	-arm-none-eabi-size "$(BINARY).axf" 
	-arm-none-eabi-objcopy -O ihex "$(BINARY).axf" "$(BINARY).hex"
	-arm-none-eabi-objcopy -v -O binary "$(BINARY).axf" "$(BINARY).bin"
	@chmod +x $(BINARY).hex
	-@echo ' '

clean:
	@rm -rf $(BUILDDIR)
	@rm -rf $(BINARY).axf
	@rm -rf $(BINARY).hex
	@rm -rf $(BINARY).bin

	
-include $(DEPS)

