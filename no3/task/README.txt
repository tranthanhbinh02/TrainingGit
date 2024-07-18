write a program like cp, when used to copy a regular file that 
contains holes(sequences of null bytes), also creates 
corresponding holes in the target file.

run:
  gcc -o task task.c

  ./task input.txt output.txt

  vi output.txt
