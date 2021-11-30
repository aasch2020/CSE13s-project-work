CC = clang
CFLAGS =  -Wall -Werror -Wpedantic -Wextra


all: banhammer
banhammer: bv.o node.o banhammer.o bf.o speck.o bst.o ht.o
	$(CC) $(CFLAGS) -o banhammer bv.o node.o banhammer.o bf.o speck.o bst.o ht.o
bvtest: bv.o
	$(CC) $(CFLAGS) -o bitvec bv.o
bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c 
node.o: node.c
	$(CC) $(CFLAGS) -c node.c 
banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c
bst.o: bst.c
	$(CC) $(CFLAGS) -c bst.c
ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c
clean:
	rm banhammer *.o
format:
	clang-format -i -style=file *.[ch]

