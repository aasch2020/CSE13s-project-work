CC = clang
CFLAGS =  -Wall -Werror -Wpedantic -Wextra $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)

numtheoryinc: numtheoryinc.o
	$(CC) -o numtheoryinc numtheoryinc.o $(LFLAGS)
numtheoryinc.o: numtheoryinc.c
	$(CC) $(CFLAGS) -c numtheoryinc.c

randstate: randstate.o
	$(CC) -o randstate randstate.o $(LFLAGS)
randstate.o: randstate.c
	$(CC) $(CFLAGS) -c randstate.c
clean:
	rm *.o
format:
	clang-format -i -style=file *.[ch]

