CC = clang
CFLAGS =  -Wall -Werror -Wpedantic -Wextra $(shell pkg-config --cflags gmp)

LFLAGS = $(shell pkg-config --libs gmp)
all: encrypt decrypt keygen

encrypt: encrypt.o numtheory.o randstate.o rsa.o
	$(CC) -o encrypt encrypt.o numtheory.o randstate.o rsa.o $(LFLAGS)

keygen: numtheory.o randstate.o keygen.o rsa.o
	$(CC) -o keygen keygen.o numtheory.o randstate.o rsa.o $(LFLAGS)

decrypt: numtheory.o randstate.o decrypt.o rsa.o
	$(CC) -o decrypt decrypt.o numtheory.o randstate.o rsa.o $(LFLAGS)

encrypt.o: encrypt.c
	$(CC) $(CFLAGS) -c encrypt.c

rsa.o: rsa.c
	$(CC) $(CFLAGS) -c rsa.c

keygen.o: keygen.c
	$(CC) $(CFLAGS) -c keygen.c

decrypt.o: decrypt.c
	$(CC) $(CFLAGS) -c decrypt.c


numtheory.o: numtheory.c
	$(CC) $(CFLAGS) -c numtheory.c

randstate.o: randstate.c
	$(CC) $(CFLAGS) -c randstate.c
clean:
	rm encrypt decrypt keygen *.o
format:
	clang-format -i -style=file *.[ch]

