CC = clang
CFLAGS =  -Wall -Werror -Wpedantic -Wextra $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)


randstate: randstate.o
	$(CC) -o randstate randstate.o $(LFLAGS)
randstate.o: randstate.c
	$(CC) $(CFLAGS) -c randstate.c
clean:
	rm *.o
format:
	clang-format -i -style=file *.[ch]

