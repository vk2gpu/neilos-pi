###############################################################################
#	makefile
#	 by Alex Chadwick
#
#	A makefile script for generation of raspberry pi kernel images.
###############################################################################

# The toolchain to use. arm-none-eabi works, but there does exist 
# arm-bcm2708-linux-gnueabi.
ARMGNU ?= arm-none-eabi

# Setup to build for Pi2...for now.
ASM_FLAGS = -mcpu=cortex-a7 -mfpu=neon-fp-armv8 -mfloat-abi=hard -march=armv8-a

# Setup C compiler.
C_FLAGS = -mcpu=cortex-a7 -mfloat-abi=hard -nodefaultlibs -nostdlib -nostartfiles -ffreestanding -Wall -O2

# The intermediate directory for compiled object files.
BUILD = build/

# The directory in which source files are stored.
SOURCE = source/

# The name of the output file to generate.
TARGET = kernel7.img

# The name of the assembler listing file to generate.
LIST = kernel7.list

# The name of the map file to generate.
MAP = kernel7.map

# The name of the linker script to use.
LINKER = kernel7.ld

# The names of all object files that must be generated. Deduced from the 
# assembly code files in source.
ASM_OBJECTS := $(patsubst $(SOURCE)%.s,$(BUILD)%.o,$(wildcard $(SOURCE)*.s))
C_OBJECTS := $(patsubst $(SOURCE)%.c,$(BUILD)%.o,$(wildcard $(SOURCE)*.c))

# Rule to make everything.
all: $(TARGET) $(LIST)

# Rule to remake everything. Does not include clean.
rebuild: all

# Rule to make the listing file.
$(LIST) : $(BUILD)output.elf
	@$(ARMGNU)-objdump -d $(BUILD)output.elf > $(LIST)

# Rule to make the image file.
$(TARGET) : $(BUILD)output.elf
	@echo objcopy output.elf -> $(TARGET)
	@$(ARMGNU)-objcopy $(BUILD)output.elf -O binary $(TARGET) 

# Rule to make the elf file.
$(BUILD)output.elf : $(ASM_OBJECTS) $(C_OBJECTS) $(LINKER)
	@echo Linking output.elf
	@$(ARMGNU)-ld --no-undefined $(ASM_OBJECTS) $(C_OBJECTS) -Map $(MAP) -o $(BUILD)output.elf -T $(LINKER)

# Rule to make the ASM object files.
$(BUILD)%.o : $(SOURCE)%.s $(BUILD)
	@echo Assembling $<
	@$(ARMGNU)-as ${ASM_FLAGS} -I $(SOURCE) $< -o $@

# Rule to make the C object files.
$(BUILD)%.o : $(SOURCE)%.c $(BUILD)
	@echo Compiling $<
	@$(ARMGNU)-gcc ${C_FLAGS} -c -I $(SOURCE) $< -o $@

$(BUILD):
	@mkdir -p $@

# Rule to clean files.
clean : 
	@-rm -rf $(BUILD)
	@-rm -f $(TARGET)
	@-rm -f $(LIST)
	@-rm -f $(MAP)