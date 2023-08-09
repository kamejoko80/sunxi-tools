# Copyright (C) 2012       Alejandro Mery <amery@geeks.cl>
# Copyright (C) 2012,2013  Henrik Nordstrom <henrik@henriknordstrom.net>
# Copyright (C) 2013       Patrick Wood <patrickhwood@gmail.com>
# Copyright (C) 2013       Pat Wood <Pat.Wood@efi.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Windows predefines OS in the environment (to "Windows_NT"), otherwise use uname
OS ?= $(shell uname)

CC ?= gcc
AR ?= ar
DEFAULT_CFLAGS := -std=c99
DEFAULT_CFLAGS += -Wall -Wextra -Wno-unused-result

DEFAULT_CFLAGS += -D_POSIX_C_SOURCE=200112L
# Define _BSD_SOURCE, necessary to expose all endian conversions properly.
# See http://linux.die.net/man/3/endian
DEFAULT_CFLAGS += -D_BSD_SOURCE
# glibc 2.20+ also requires _DEFAULT_SOURCE
DEFAULT_CFLAGS += -D_DEFAULT_SOURCE
ifeq ($(OS),NetBSD)
# add explicit _NETBSD_SOURCE, see https://github.com/linux-sunxi/sunxi-tools/pull/22
DEFAULT_CFLAGS += -D_NETBSD_SOURCE
endif

DEFAULT_CFLAGS += -Iinclude/

PKG_CONFIG ?= pkg-config

# Tools useful on host and target
TOOLS = sunxi-fexc sunxi-bootinfo sunxi-fel sunxi-nand-part sunxi-pio

# Symlinks to sunxi-fexc
FEXC_LINKS = bin2fex fex2bin

# Tools which are only useful on the target
TARGET_TOOLS = sunxi-meminfo

# Misc tools (of more "exotic" nature) not part of our default build / install
MISC_TOOLS = phoenix_info sunxi-nand-image-builder

# ARM binaries and images
# Note: To use this target, set/adjust CROSS_COMPILE and MKSUNXIBOOT if needed
BINFILES = jtag-loop.sunxi fel-sdboot.sunxi uart0-helloworld-sdboot.sunxi

MKSUNXIBOOT ?= mksunxiboot
PATH_DIRS := $(shell echo $$PATH | sed -e 's/:/ /g')
# Try to guess a suitable default ARM cross toolchain
CROSS_DEFAULT := arm_toolchains/xpack-arm-none-eabi-gcc-12.2.1-1.2/bin/arm-none-eabi-
CROSS_COMPILE ?= $(or $(shell ./find-arm-gcc.sh),$(CROSS_DEFAULT))
CROSS_CC := $(CROSS_COMPILE)gcc
CROSS_OBJCOPY := $(CROSS_COMPILE)objcopy

DESTDIR ?=
PREFIX  ?= /usr/local
BINDIR  ?= $(PREFIX)/bin
MANDIR  ?= $(PREFIX)/share/man/man1

# Create libfdt src
LIBFDT_SRCS = \
libfdt/fdt.c \
libfdt/fdt_ro.c \
libfdt/fdt_wip.c \
libfdt/fdt_sw.c \
libfdt/fdt_rw.c \
libfdt/fdt_strerror.c \
libfdt/fdt_empty_tree.c \
libfdt/fdt_addresses.c \
libfdt/fdt_overlay.c \
libfdt/fdt_check.c

# Define the output directory
LIBFDT_OBJDIR = libfdt_obj

# Create a list of object files from source files
LIBFDT_OBJS = $(patsubst libfdt/%.c,$(LIBFDT_OBJDIR)/%.o,$(LIBFDT_SRCS))

# Define the library name
LIBFDT_NAME = libfdt.a

# Define the library cflags
LIBFDT_CFLAGS = -Wall -Wextra -Ilibfdt

.PHONY: all clean tools target-tools install install-tools install-target-tools
.PHONY: check

tools: $(TOOLS) $(FEXC_LINKS)
target-tools: $(TARGET_TOOLS)

all: tools target-tools

misc: $(MISC_TOOLS)

binfiles: $(BINFILES)

install: install-tools
install-all: install-tools install-target-tools

install-tools: $(TOOLS)
	install -d $(DESTDIR)$(BINDIR)
	@set -ex ; for t in $^ ; do \
		install -m0755 $$t $(DESTDIR)$(BINDIR)/$$t ; \
	done
	@set -ex ; for l in $(FEXC_LINKS) ; do \
		ln -nfs sunxi-fexc $(DESTDIR)$(BINDIR)/$$l ; \
	done
	install -D -m0644 -t $(DESTDIR)$(MANDIR) sunxi-fel.1

install-target-tools: $(TARGET_TOOLS)
	install -d $(DESTDIR)$(BINDIR)
	@set -ex ; for t in $^ ; do \
		install -m0755 $$t $(DESTDIR)$(BINDIR)/$$t ; \
	done

install-misc: $(MISC_TOOLS)
	install -d $(DESTDIR)$(BINDIR)
	@set -ex ; for t in $^ ; do \
		install -m0755 $$t $(DESTDIR)$(BINDIR)/$$t ; \
	done

clean:
	make -C tests/ clean
	@rm -rf $(LIBFDT_OBJDIR)
	@rm -vf $(TOOLS) $(FEXC_LINKS) $(TARGET_TOOLS) $(MISC_TOOLS)
	@rm -vf version.h *.o *.elf *.sunxi *.bin *.nm *.orig

$(TOOLS) $(TARGET_TOOLS) $(MISC_TOOLS): Makefile common.h version.h

fex2bin bin2fex: sunxi-fexc
	ln -nsf $< $@

sunxi-fexc: fexc.h script.h script.c \
	script_uboot.h script_uboot.c \
	script_bin.h script_bin.c \
	script_fex.h script_fex.c

# pacman -S mingw-w64-x86_64-libusb
LIBUSB = libusb-1.0
LIBUSB_CFLAGS = -I/mingw64/include/libusb-1.0
LIBUSB_LIBS = -L/mingw64/lib -lusb-1.0

# Or link libusb locally
#LIBUSB = libusb-1.0
#LIBUSB_CFLAGS = -Ilibusb-MinGW-x64/include/libusb-1.0
#LIBUSB_LIBS = -Llibusb-MinGW-x64/lib -lusb-1.0

# pacman -S mingw-w64-x86_64-zlib
ZLIB = zlib
ZLIB_CFLAGS = -I/mingw64/include
ZLIB_LIBS = -L/mingw64/lib -lz

ifeq ($(OS),Windows_NT)
	# Windows lacks mman.h / mmap()
	DEFAULT_CFLAGS += -DNO_MMAP
	# portable_endian.h relies on winsock2
	LIBS += -lws2_32
endif

HOST_CFLAGS = $(DEFAULT_CFLAGS) $(CFLAGS)

PROGRESS := progress.c progress.h
SOC_INFO := soc_info.c soc_info.h
FEL_LIB  := fel_lib.c fel_lib.h
SPI_FLASH:= fel-spiflash.c fel-spiflash.h fel-remotefunc-spi-data-transfer.h

sunxi-fel: $(LIBFDT_OBJDIR) $(LIBFDT_NAME) fel.c fit_image.c thunks/fel-to-spl-thunk.h $(PROGRESS) $(SOC_INFO) $(FEL_LIB) $(SPI_FLASH)
	$(CC) $(HOST_CFLAGS) $(LIBUSB_CFLAGS) $(ZLIB_CFLAGS) $(LDFLAGS) -o $@ \
		$(filter %.c,$^) $(LIBS) $(LIBUSB_LIBS) $(ZLIB_LIBS) -Ilibfdt -L$(LIBFDT_OBJDIR) -lfdt

# Create output directory
$(LIBFDT_OBJDIR):
	@mkdir -p $(LIBFDT_OBJDIR)

# Build library
$(LIBFDT_NAME): $(LIBFDT_OBJS)
	$(AR) rcs $(LIBFDT_OBJDIR)/$(LIBFDT_NAME) $(LIBFDT_OBJS)

# Compile source files to object files
$(LIBFDT_OBJDIR)/%.o: libfdt/%.c
	$(CC) $(LIBFDT_CFLAGS) -c $< -o $@

sunxi-nand-part: nand-part-main.c nand-part.c nand-part-a10.h nand-part-a20.h
	$(CC) $(HOST_CFLAGS) -c -o nand-part-main.o nand-part-main.c
	$(CC) $(HOST_CFLAGS) -c -o nand-part-a10.o nand-part.c -D A10
	$(CC) $(HOST_CFLAGS) -c -o nand-part-a20.o nand-part.c -D A20
	$(CC) $(LDFLAGS) -o $@ nand-part-main.o nand-part-a10.o nand-part-a20.o $(LIBS)

sunxi-%: %.c
	$(CC) $(HOST_CFLAGS) $(LDFLAGS) -o $@ $(filter %.c,$^) $(LIBS)
phoenix_info: phoenix_info.c
	$(CC) $(HOST_CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

%.bin: %.elf
	$(CROSS_COMPILE)objcopy -O binary $< $@

%.sunxi: %.bin
	$(MKSUNXIBOOT) $< $@

ARM_ELF_FLAGS = -Os -marm -fpic -Wall
ARM_ELF_FLAGS += -fno-common -fno-builtin -ffreestanding -nostdinc -fno-strict-aliasing
ARM_ELF_FLAGS += -mno-thumb-interwork -fno-stack-protector -fno-toplevel-reorder
ARM_ELF_FLAGS += -Wstrict-prototypes -Wno-format-nonliteral -Wno-format-security

jtag-loop.bin: jtag-loop.elf jtag-loop.c jtag-loop.lds
	$(CROSS_OBJCOPY) -O binary jtag-loop.elf jtag-loop.bin

jtag-loop.elf: jtag-loop.c jtag-loop.lds
	$(CROSS_CC) $(ARM_ELF_FLAGS) $< -nostdlib -o $@ -T jtag-loop.lds -Wl,-Map=jtag-loop.map

fel-sdboot.elf: fel-sdboot.S fel-sdboot.lds
	$(CROSS_CC) -march=armv5te -g $(ARM_ELF_FLAGS) $< -nostdlib -o $@ -T fel-sdboot.lds -Wl,-N

uart0-helloworld-sdboot.elf: uart0-helloworld-sdboot.c uart0-helloworld-sdboot.lds
	$(CROSS_CC) -march=armv5te -g $(ARM_ELF_FLAGS) $< -nostdlib -o $@ -T uart0-helloworld-sdboot.lds -Wl,-N

boot_head_sun3i.elf: boot_head.S boot_head.lds
	$(CROSS_CC) -g $(ARM_ELF_FLAGS) $< -nostdlib -o $@ -T boot_head.lds -Wl,-N -DMACHID=0x1094

boot_head_sun4i.elf: boot_head.S boot_head.lds
	$(CROSS_CC) -g $(ARM_ELF_FLAGS) $< -nostdlib -o $@ -T boot_head.lds -Wl,-N -DMACHID=0x1008

boot_head_sun5i.elf: boot_head.S boot_head.lds
	$(CROSS_CC) -g $(ARM_ELF_FLAGS) $< -nostdlib -o $@ -T boot_head.lds -Wl,-N -DMACHID=0x102A

sunxi-bootinfo: bootinfo.c

# "preprocessed" .h files for inclusion of ARM thunk code
headers:
	make -C thunks/ CROSS_COMPILE=$(CROSS_COMPILE)


# target tools
TARGET_CFLAGS = $(DEFAULT_CFLAGS) -static $(CFLAGS)
sunxi-meminfo: meminfo.c
	$(CROSS_CC) $(TARGET_CFLAGS) -o $@ $<
sunxi-script_extractor: script_extractor.c
	$(CROSS_CC) $(TARGET_CFLAGS) -o $@ $<

version.h:
	@./autoversion.sh > $@

.gitignore: Makefile
	@for x in $(TOOLS) $(FEXC_LINKS) $(TARGET_TOOLS) version.h '*.o' '*.swp'; do \
		echo "$$x"; \
	done | sort -V > $@

check: $(FEXC_LINKS)
	make -C tests/
