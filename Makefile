obj-m += akoya-fixup.o
KDIR := /lib/modules/`uname -r`/build
PWD := $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
