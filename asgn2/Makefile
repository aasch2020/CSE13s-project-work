CC = clang
CFLAGS = -Wall -Werror -Wpedantic -Wextra
LFLAGS = -lm

mathlib-test: mathlib-test.o e.o newton.o
	$(CC) -o mathlib-test mathlib-test.o e.o newton.o $(LFLAGS)
mathlib-test.o: mathlib-test.c
	$(CC) $(CFLAGS) -c mathlib-test.c
e.o: e.c
	$(CC) $(CFLAGS) -c e.c
newton.o: newton.c
	$(CC) $(CFLAGS) -c newton.c
clean:
	rm mathlib-test *.o
