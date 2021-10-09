CC = clang
CFLAGS = -Wall -Werror -Wpedantic -Wextra
LFLAGS = -lm
all: pig
mathlib-test: mathlib-test.o e.o newton.o madhava.o euler.o
	$(CC) -o mathlib-test mathlib-test.o e.o newton.o madhava.o euler.o $(LFLAGS)
mathlib-test.o: mathlib-test.c
	$(CC) $(CFLAGS) -c mathlib-test.c
e.o: e.c
	$(CC) $(CFLAGS) -c e.c
newton.o: newton.c
	$(CC) $(CFLAGS) -c newton.c
madhava.o: madhava.c
	$(CC) $(CFLAGS) -c madhava.c
euler.o: euler.c
	$(CC) $(CFLAGS) -c euler.c
clean:
	rm mathlib-test *.o
format:
	clang-format -i -style=file *.[ch]
