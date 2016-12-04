obj-m += test.o #oder testdriver.o
KERNELDIR = /usr/src/linux-headers-`uname -r`
all:
	make -C $(KERNELDIR) SUBDIRS=$(PWD) modules
clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order
