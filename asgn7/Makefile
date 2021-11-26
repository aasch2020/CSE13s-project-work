CC = clang
CFLAGS =  -Wall -Werror -Wpedantic -Wextra


all: banhammer

bvtest: bv.o
	$(CC) $(CFLAGS) -o bitvec bv.o
bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c 

