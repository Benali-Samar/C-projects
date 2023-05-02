obj-m += vmalloc.o

kdir=/lib/modules/$(shell uname -r)/build
all:
	make -C $(kdir) M=$(PWD) modules

install:
	make -C $(KERNEL_SRC) M=$(PWD) modules_install


clean:
	 make -C $(KERNEL_SRC) M=$(PWD) clean
