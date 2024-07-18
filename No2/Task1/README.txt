Write two Kernel modules A and B, in which module A exports an int variable x, 
and module B declare extern x. Find ways to load module
B into the kernel with Manual loading

How to run?
Build:
  1- make
  2- sudo insmod task1.ko
  3- sudo insmod task2.ko
  4- sudo dmesg
