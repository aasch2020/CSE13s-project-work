CC = clang
CFLAGS =  -Wall -Werror -Wpedantic -Wextra
LFLAGS = -lm

all: encode decode

encode: pq.o node.o encode.o code.o io.o stack.o huffman.o
	$(CC) $(CFLAGS) -o encode pq.o node.o encode.o code.o io.o stack.o huffman.o

decode: pq.o node.o decode.o code.o io.o stack.o huffman.o
	$(CC) $(CFLAGS) -o decode pq.o node.o encode.o code.o io.o stack.o huffman.o

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c
decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c
huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c
code.o: code.c
	$(CC) $(CFLAGS) -c code.c
io.o: io.c
	$(CC) $(CFLAGS) -c io.c
stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c
pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c
node.o: node.c
	$(CC) $(CFLAGS) -c node.c

clean:
	rm encode decode *.o
format:
	clang-format -i -style=file *.[ch]

