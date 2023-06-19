#			---------- Compile and Debug tools ----------

This repo is just for the response of these questions:

	- "How to compile this ?" 

	- "Wait what the !!??"

	- "Okay how to debug this shit ?" 

Just don't worry, those steps are a must :) 

#	Compile, how ?

For C language we have the celebrity GLIBC "Gnu Lib C", the C standart library that gave us the compilation tool "GCC".
Glibc is the collections of files containing functions that are wrappers for the real system call functions.

Functions like "fopen", "fclose","fgets" and "printf" .. these are the wrappers for "open","close",
"read" and "write" system calls.

The main reason of this is simple: a system call must be performed quickly, very quickly. 
As a system call must be quick, it must be small. The standard library takes responsibility 
to perform system calls with the correct parameters and makes different checks before 
it will call the given system call.

So we just have to do magic with the "gcc" tool ;)

	$ gcc file.c -o file

This compile the file.c code and turns it to an object file that can be executed with:

	$ ./file

And thats it ! But there are different steps our file.c is passing by;

1-Preprocessing:

The first step of compilation is getting the missing chiffred part of the code, the preprocessor will fetch all the macros, headers and directives and replace them with needed source code.

	$ gcc -E file.c -o file.i

2- Compilation:

The compiler takes the preprocessed file "file.i" and translates it into assembly code "file.s" with:

	$ gcc -S file.i -o file.s

3- Assembly:

The assembler "as" takes the assembly code "file.s" and produces an ovject file "file.o" containing machine code specific to the target architecture.

	$ gcc -c file.s -o file.o

4- Linking:

The linker "ld" combines the object file "file.o" with other necessary object files and librairies to create an executable binary file.

	$ gcc file.o -o file

Here are some resources about linkers because it is so huge domaine:
	
	* https://sourceware.org/binutils/docs/ld/Scripts.html#Scripts
	* https://www.wh0rd.org/books/linkers-and-loaders/linkers_and_loaders.pdf

Here is a diagram illustrating the compilation process with gcc:

	        +--------------+
	        |   file.c     |
	        +--------------+
        	       |
        	       v
	        +--------------+
	        | Preprocessing|
	        |   file.i     |		
	        +--------------+
	               |
	               v
	        +--------------+
	        | Compilation  |
	        |   file.s     |
	        +--------------+
	               |
	               v
	        +--------------+
	        |   Assembly   |
	        |    file.o    |
	        +--------------+
	               |
	               v
	        +--------------+
	        |   Linking    |
	        +--------------+
	               |
	               v
	        +--------------+
	        |  Executable  |
	        |     file     |
	        +--------------+


#	Debug, how ?

Congrats! you've compiled a program and all went good :) 

But sometimes we be faced to problems, bugs that we need to debug and see the trace of the code while compiling ...
Also to see where is the problem exaxtly and what part of the compilation steps is missing.

Here you be in the phase "What the !!??" , don't panic u just need to debug it and find a solution,
most errors are so simple to fix ;)

There are different tools for debuging like GDB  "GnuDeBugger" ... (TO DO!)

Also there is "strace" ans "ltrace", those two can help examin the compiled code.


"ltrace" focuses on tracing library calls (the wrappers), It intercepts and records the dynamic library calls made by 
a process, showing you the function names, arguments, and return values.
While strace focuses on tracing system calls (the functions). 
They provide complementary information and can be used together to get a comprehensive 
understanding of program behavior.

Specify the problem and start looking for solution, you face another problem just do the thing again in loop untill it will work.



#	Example:

As an example we have a simple hello world C code "syscall.c" that opens a file "test.txt" and reads 
what's inside then prints it to the stdout and finally close that file.

The wrappers used in the program are actually the functions of the system calls like "fopen" is the "open" syscall.

Compiling the code and later examining it with "ltrace" gives something like that:

	$ gcc syscall.c -o syscall
	$ ltrace ./syscall

output:


	__libc_start_main([ "./test" ] <unfinished ...>
	fopen("test.txt", "r")                                             = 0x602010
	fgets("Hello World!\n", 255, 0x602010)                             = 0x7ffd2745e700
	puts("Hello World!\n"Hello World!
	
	)                                                                  = 14
	fclose(0x602010)                                                   = 0
	+++ exited (status 0) +++

It displays a set of userspace calls of a program, . The fopen function opens the given text file, the fgets function reads file content to the buf buffer, the puts function prints the buffer to stdout, and the fclose function closes the file given by the file descriptor.


#	GDB
The gnu debugger is the standard  GNU project for debbugging, it is mostly present in all unix like systems.
It is used generally with C/C++ programs, but to display debugging informations you should compile withe the "-g" option!
So you just need to :
	$ gdb ./file

For running the program with gdb you can type "run" or "start" to excute one line and keep typing "next" for continueing or "continue" or "step", also you can use "nexti" for assembly code.

You can also put a break point with "break".
You can display the source code by "list" command, or by "lay" command.
GDB helps define and find bugs in c codes, for example we have this simple C code that is obviously buggy:

	#include <stdio.h>
	int main(){
	int d=2;
	printf("Give a number\n");
	scanf("%d", d);
	printf("You gave: %d\n",d);
	return 0;
	}

This code if it runs it will give "SEGMENTATION FAULT" error because it does not know the d or its address in the scanf statement.
With gdb at that line while we typed "8" we've got this:

	8

	Program received signal SIGSEGV, Segmentation fault.
	0x00007ffff7c671c9 in __vfscanf_internal (s=<optimized out>, format=<optimized out>, argptr=argptr@entry=0x7fffffffdb10, mode_flags=mode_flags@entry=2) at ./stdio-common/vfscanf-internal.c:1896

It says that is a "SIGSEGV" as we said earlier it is a segmentation fault.
so when we want to see the assembly at that line : 
	(gdb) x/i $pc
	=> 0x7ffff7c671c9 <__vfscanf_internal+18281>:	mov    %edx,(%rax)
It says that the content of the register rax is moved to the register edx, but when we type "info registers" to see those two registers we got that the "rax" register has 2 in it but the "edx" register has 8, so this is the error, the move instruction didn't executed because it has not the address of "d". 

So to fixe that we should just change the scanf line with 
	scanf("%d", &d);

And that's all :) .

