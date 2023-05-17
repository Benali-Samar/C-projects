#mmap() function test

mmap, munmap ==> mapping/unmapping for device files.

mmap() : creates a new mapping in the virtual address space of the calling process.
The specified arguments are described in the comments in the mmap.c 

#How to ?

Just compile the code by gcc mmap.c -o mmap

Excute it and pass the arguments by : ./mmap read.txt 0 10

The first argument is the file to be mapped for reading.
The second is the starting offset where to start mapping.
And the last one is the length of the mapped region for reading.


! more explanations are in the source code file.

Have fun :) 
