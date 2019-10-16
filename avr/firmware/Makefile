################################################################################
# Makefile for AVR
#
# How to use:
# 	-Edit Project Settings
#	-This file should be at the root dir of the project
#
# 	-Commans:
#		make				to compile
#		make clean	        to clean
#	-TODO:
#		make up				to upload
#		make doc			to generate docs w/ doxygen
#
################################################################################



################################################################################
################################################################################
################################################################################
########### Project Settings starts here

# project root dir
PRJDIR      :=  $(shell pwd)
# binaries (.elf and .hex)
BINDIR      :=  bin
# compiled object files
OBJDIR      :=  obj
# project documentation
DOCDIR		:=  doc
# libraries
LIBDIR      :=  lib
# .c sources files
SRCDIR      :=  src
# Project target and sources to be compiled
MAIN 		= 	main
# Define microcontroller settings
MCU 		?=	atmega328p
F_CPU		?=	16000000UL
# Optimization
OPT=s
# documentation (auto generated)
DOXYFILE_MK		=	Doxyfile

########### Project Settings ends here
################################################################################
################################################################################
################################################################################



# These will automatically be checked if they are set to YES
SPECIAL_DEFS +=

TARGET = $(lastword $(subst /, ,$(CURDIR)))

SRCS	=	$(shell find $(SRCDIR) -type f -name \*.c)
OBJS	=	$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.c=.o))

SILENT ?= @
CROSS ?= avr-
ifneq ($(CROSS), )
	CC = $(CROSS)gcc
	CXX = $(CROSS)g++
	OBJCOPY = $(CROSS)objcopy
	OBJDUMP = $(CROSS)objdump
	SIZE = $(CROSS)size
endif

ifneq ($(F_CPU),)
 	CFLAGS += -DF_CPU=$(F_CPU)
endif

## Special defines

define CHECK_ANSWER
	ifeq ($$($(1)), YES)
   		CFLAGS += -D$(1)
	endif
endef

$(foreach i,$(SPECIAL_DEFS),$(eval $(call CHECK_ANSWER,$(i))))

##


CFLAGS += \
	-O$(OPT) \
	-Wall \
	-std=gnu99 \
	-mmcu=$(MCU)

LDFLAGS = -Wl,-Map=$(OBJDIR)/$(TARGET).map
LDFLAGS += $(patsubst %,-L%,$(EXTRALIBDIRS))
LDFLAGS += $(PRINTF_LIB) $(SCANF_LIB) $(MATH_LIB)
#LDFLAGS += -static -Llib/DISPLAYS/SSD1306_AVR/ -lssd1306

## Intel Hex file production flags
HEX_FLASH_FLAGS = \
	-R .eeprom \
	-R .fuse \
	-R .lock \
	-R .signature
HEX_EEPROM_FLAGS = \
	-j .eeprom \
	--set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 --no-change-warnings

.PHONY: directories doc

# all
all: directories $(TARGET).elf size

# directories
directories:
	$(SILENT) $(MKDIR_P) $(BINDIR) $(OBJDIR) $(DOCDIR) $(LIBDIR) $(SRCDIR)

# size
size: $(TARGET).elf
	$(SILENT) $(SIZE) -C --mcu=$(MCU) $(BINDIR)/$<

# clean
ifneq ($(wildcard $(OBJS) $(TARGET).elf $(TARGET).hex $(TARGET).eep $(TARGET).map $(OBJS:%.o=%.d=%.map) $(OBJS:%.o=%.lst=%.map)), )
clean: rmdoc
	-rm $(wildcard $(OBJS) $(TARGET).elf $(TARGET).hex $(TARGET).eep $(TARGET).map $(OBJS:%.o=%.d=%.map) $(OBJS:%.o=%.lst=%.map))
else
clean:
	@echo "Nothing to clean."
endif

MKDIR_P := mkdir -p

.SECONDARY:

## Link
%.elf: $(OBJS)
	@echo "Linking:" $@...
	@echo ""
	$(SILENT) $(CC) $(CFLAGS) $(OBJS) -o $(BINDIR)/$@ $(LDFLAGS)

%.hex: $(TARGET)
	@echo "hex..:"
	@echo ""
	$(SILENT) $(OBJCPY) -O ihex $(HEX_FLASH_FLAGS)

## Compile
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "[$(TARGET)] Compiling:" $@...
	@echo ""
	$(SILENT) $(CC) $(CFLAGS) -MMD -MF $(@:%.o=%.d) -c $< -o $@

$(OBJDIR)/%.d: $(SRCDIR)/%.c
	@echo "[$(TARGET)] Generating dependency:" $@...
	@echo ""
	$(SILENT) $(CC) $(CFLAGS) -MM -MT $(addsuffix .o, $(basename $@)) -MF $@ $<

## Docs

# If makefile changes, maybe the list of sources has changed, so update doxygens list

doc: $(SRCS)
	@echo "Generating docs..."
	@echo ""
	$(SILENT) @mkdir -p $(DOCDIR)
	@echo $(cat $(DOXYFILE) ; echo INPUT = $(SRCDIR) ; echo PROJECT_NAME = $(shell basename $(PRJDIR))) | doxygen

rmdoc:
	@rm -rf doc
###############


# Check which .o files we already have and include their dependency files.
PRIOR_OBJS := $(wildcard $(OBJS))
include $(PRIOR_OBJS:%.o=%.d)
