CC = clang
CFLAGS =  -Wall -Werror -Wpedantic -Wextra
LFLAGS = -lm
all: huffman

pqdb: pq.o node.o
	$(CC) $(CFLAGS) -o pq pq.o node.o
nodedb: node.o
	$(CC) $(CFLAGS) -o node node.o

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c
node.o: node.c
	$(CC) $(CFLAGS) -c node.c

clean:
	rm huffman *.o
format:
	clang-format -i -style=file *.[ch]

