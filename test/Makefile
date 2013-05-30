
CC =	g++
CFLAGS =  -W -Wall -Werror -g
CPP =	g++ -E
LINK =	$(CC) -lgtest


INCS = -I ../src

DEPS = ../src/xor_list.h

test: xor_list.o xor_list_test.o test.o bk_tree.o bk_tree_test.o
	$(LINK) xor_list.o xor_list_test.o \
		bk_tree.o bk_tree_test.o \
		test.o -o test

xor_list.o: ../src/xor_list.h ../src/xor_list.c
	$(CC) -c $(CFLAGS) $(INCS) -o xor_list.o ../src/xor_list.c

xor_list_test.o: ../src/xor_list.h xor_list_test.cc
	$(CC) -c $(CFLAGS) $(INCS) -o xor_list_test.o xor_list_test.cc

bk_tree.o: ../src/bk_tree.h ../src/bk_tree.c
	$(CC) -c $(CFLAGS) $(INCS) -o bk_tree.o ../src/bk_tree.c

bk_tree_test.o: ../src/bk_tree.h bk_tree_test.cc
	$(CC) -c $(CFLAGS) $(INCS) -o bk_tree_test.o bk_tree_test.cc
test.o: test.cc
	$(CC) -c $(CFLAGS) $(INCS) -o test.o test.cc
