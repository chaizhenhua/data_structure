
CC =	g++
CFLAGS =  -W -Wall -Werror
CPP =	g++ -E
LINK =	$(CC) -lgtest


INCS = -I ../src

DEPS = ../src/xor_list.h

test: xor_list.o xor_list_test.o test.o
	$(LINK) xor_list.o xor_list_test.o \
		test.o -o test

xor_list.o: ../src/xor_list.h ../src/xor_list.c
	$(CC) -c $(CFLAGS) $(INCS) -o xor_list.o ../src/xor_list.c

xor_list_test.o: ../src/xor_list.h xor_list_test.cc
	$(CC) -c $(CFLAGS) $(INCS) -o xor_list_test.o xor_list_test.cc

test.o: test.cc
	$(CC) -c $(CFLAGS) $(INCS) -o test.o test.cc
