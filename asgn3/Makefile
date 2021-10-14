CC = clang
CFLAGS = -Wall -Werror -Wpedantic -Wextra
all: sorting
mathlib-test: sorting.o insert.o stats.o shell.o heap.o quick.o
	$(CC) -o sorting.o sorting.o insert.o stats.o shell.o heap.o quick.o 
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
bbp.o: bbp.c
	$(CC) $(CFLAGS) -c bbp.c
viete.o: viete.c
	$(CC) $(CFLAGS) -c viete.c
clean:
	rm mathlib-test *.o
format:
	clang-format -i -style=file *.[ch]
