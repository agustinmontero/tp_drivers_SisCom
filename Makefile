#
# Makefile for compiling a congestion control module. This has been
# tested with Linux version 2.6.26.
#

# obj-m    := chardev_ioctl.o
# chardev_ioctl-objs := chardev.o ioctl.o
obj-m    := interrupt.o

KDIR    := /lib/modules/$(shell uname -r)/build
PWD    := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -f interrupt.mod.c interrupt.mod.o interrupt.ko int.o
	rm -f modules.order Module.symvers
	rm -f .??*cmd
	rm -rf .tmp_versions
