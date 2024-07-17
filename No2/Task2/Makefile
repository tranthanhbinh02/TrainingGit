obj-m += task1.o task2.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	sudo insmod task1.ko
	sudo insmod task2.ko
	sudo dmesg | tail -20   # Adjust tail command as needed to show relevant output

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	sudo rmmod task2.ko
	sudo rmmod task1.ko




	
