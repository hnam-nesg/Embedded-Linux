CC=gcc
CFLAG=-Wall -fPIC
LIB_NAME=strutils

all: static shared

static: lib$(LIB_NAME).a main.c 
	$(CC) main.c -L. -l$(LIB_NAME) -o main_static
shared: lib$(LIB_NAME).so main.c 
	$(CC) main.c -L. -l$(LIB_NAME) -o main_shared

lib$(LIB_NAME).a: strutils.o
	ar rcs $@ $^
lib$(LIB_NAME).so: strutils.o
	$(CC) $(CFLAG) -shared -o $@ $^

strutils.o: bstrutils.c strutils.h
	$(CC) -c bstrutils.c -o $@

clean:
	rm -rf *.o *.a *.so main_static main_shared
