#This is a generic makefile that you can pass the programe name as an argument to make command like :
#	$ make PG_N=hello
#It will compile the " hello.c" and give you an executable file named "hello"

#Defining variables
CC = gcc
CFLAGS = -Wall

#Detect all .c files and assign them to SRCS variable and then replace the .c file with the .o files and  put them into OBJS
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

#Define the program name variable
PG_N ?= program

#define the targets all and clean
.PHONY: all clean


all: $(PG_N)

$(PG_N): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PG_N) $(OBJS)
