# Kernel version
KDIR := /lib/modules/$(shell uname -r)/build

# Module name
obj-m := pid.o

# Default target
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# Clean target
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
