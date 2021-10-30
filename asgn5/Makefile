CC = clang
CFLAGS =  -Wall -Werror -Wpedantic -Wextra
LFLAGS = -lm

all: encode decode

encode: pq.o node.o encode.o code.o
	$(CC) $(CFLAGS) -o encode pq.o node.o encode.o code.o

decode: pq.o node.o decode.o code.o
	$(CC) $(CFLAGS) -o decode pq.o node.o encode.o code.o

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c
decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c
code.o: code.c
	$(CC) $(CFLAGS) -c code.c
pqdb: pq.o node.o
	$(CC) $(CFLAGS) -o pq pq.o node.o
nodedb: node.o
	$(CC) $(CFLAGS) -o node node.o
pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c
node.o: node.c
	$(CC) $(CFLAGS) -c node.c

clean:
	rm encode decode *.o
format:
	clang-format -i -style=file *.[ch]

