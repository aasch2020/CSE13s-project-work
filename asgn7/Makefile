CC = clang
CFLAGS =  -Wall -Werror -Wpedantic -Wextra


all: banhammer
banhammer: bv.o node.o banhammer.o
	$(CC) $(CFLAGS) -o banhammer bv.o node.o banhammer.o
bvtest: bv.o
	$(CC) $(CFLAGS) -o bitvec bv.o
bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c 
node.o: node.c
	$(CC) $(CFLAGS) -c node.c 
banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c
clean:
	rm banhammer *.o
