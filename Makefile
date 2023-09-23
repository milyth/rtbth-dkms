#include config.mk

CONFIG_RTBTH = m
MOD_NAME = rtbth
MDIR = kernel/drivers/bluetooth
obj-$(CONFIG_RTBTH) := $(MOD_NAME).o
$(MOD_NAME)-objs := rtbth_core_main.o \
					rtbth_core_init.o \
					rtbth_core_pci.o \
					rtbth_core_bluez.o \
					rtbth_core_us.o \
					rtbth_hlpr_hw.o \
					rtbth_hlpr_dbg.o \
					rtbth_hlpr_linux.o \

ccflags-y := -I$(src)/include
ccflags-y += -DDBG -DRT3298 -DRTBT_IFACE_PCI -DLINUX

MAKE = make
LINUX_SRC ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(LINUX_SRC) M=$(PWD) modules

clean:
	$(MAKE) -C $(LINUX_SRC) M=$(PWD) clean

modules_install:
	$(MAKE) INSTALL_MOD_PATH=$(DESTDIR) INSTALL_MOD_DIR=$(MDIR) \
			-C $(LINUX_SRC) M=$(PWD) modules_install

install:
	install -m 0755 -o root -g root tools/rtbt -D $(DESTDIR)/opt/ralink/rtbt # Firmware loader
	install -m 0755 -o root -g root tools/rtbth -D $(DESTDIR)/opt/ralink/rtbth  # Helper script
	install -m 0644 -o root -g root systemd/rtbth.service -D $(DESTDIR)/usr/local/lib/systemd/system/rtbth.service  # Systemd service
