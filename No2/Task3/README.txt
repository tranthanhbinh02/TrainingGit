Write two Kernel modules A and B, in which module A exports an int variable x, 
and module B declare extern x. Find ways to load module
B into the kernel with Automatic Loading without Tool

How to run:
Build:
  1- make
  2- cp task1.ko and task2.ko in the path
  3- sudo depmod -a in the path
  4- sudo modprobe task2
  3- sudo dmesg
