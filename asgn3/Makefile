CC = clang
CFLAGS = -Wall -Werror -Wpedantic -Wextra
LFLAGS = -lm
all: sorting
sorting: sorting.o stats.o insert.o
	$(CC) -o sorting sorting.o stats.o insert.o $(LFLAGS)
sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c
stats.o: stats.c
	$(CC) $(CFLAGS) -c stats.c
insert.o: insert.c
	$(CC) $(CFLAGS) -c insert.c
clean:
	rm sorting *.o
format:
	clang-format -i -style=file *.[ch]
