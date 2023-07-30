# Message encryption simple minimal app just to test the needs of makefile :) 

To compile :
	$ gcc encrypt.c  message_hider.c -o message_hider
	$ ./message_hider

All this can be minimilized in a simple makefile with the forme of :
Target(message_hider.o): dependecies(encrypt.c )
	reciepe(gcc -o message_hider.c)


This is the purpose of makefile and the mechanism of make, that when a project has multiple files and the compilation time is so much because it recompile all the files whenever a change is made.
So make will know exactly what file has changed by its timestamp and just recompile it and relink it with the binary output.
