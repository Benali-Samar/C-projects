S#This is a generic makefile that you can pass the programe name as an argument to make command like :
#	$ make PG_N=hello
#It will compile the " hello.c" and give you an executable file named "hello"

#Defining variables
CC = gcc
CFLAGS = -Wall

#Define the target variable
all: $(PG_N: .c=)

#Compile the specified file
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

#Clean the .o and excutables generated
#clean:
#	rm -f $(PG_N:.c=)
