CC = clang
CFLAGS =  -Wall -Werror -Wpedantic -Wextra
LFLAGS = -lm

huffman: node.o
	$(CC) $(CFLAGS) -o huffman node.o

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

clean:
	rm huffman *.o
format:
	clang-format -i -style=file *.[ch]

