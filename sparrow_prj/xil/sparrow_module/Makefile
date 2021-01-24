#################################################
# Makefile for sepia defectoscope drv
# 2019 (C) Velog
# Author : Vladimir Golev <vagolev@velog.ru>
#################################################
ARCH:=arm
###CROSS_COMPILE:=arm-xilinx-linux-gnueabi-
CROSS_COMPILE:=arm-linux-gnueabihf-
###KDIR_DI := /media/vovag/07f0e685-575b-4e47-895d-2490c005fd982/proj/octopuz_prj/xil/linux-xlnx-4.4
###KDIR_DI := ../../linux-xlnx-4.19
KDIR_DI := ../linux-xlnx-4.19
### TOPDIR     := /home/vovag/proj/octopuz_prj/xil/linux-xlnx-xilinx-v2015.1
PWD			:= $(shell pwd)

CFLAGS_MODULE += -DLINUX
CFLAGS_MODULE += -DDIVX_ENABLE
###EXTRA_CFLAGS += -Wno-error=date-time
CFLAGS_MODULE += -Wno-error=date-time

obj-m		:= sparrow.o 

sparrow-y := sparrow_read.o sparrow_drv.o \
				sparrow_write.o sparrow_ioctl.o 
				 
				
all:
#here:
###	(cd $(KERNEL_DIR); make SUBDIRS=$(PWD) modules)
	make -C $(KDIR_DI) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf .*.cmd
	rm -rf *.o
	rm -rf Module.*
