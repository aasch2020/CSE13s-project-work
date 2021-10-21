CC = clang
CFLAGS =  -Wall -Werror -Wpedantic -Wextra
LFLAGS = -lm

all: tsp
sorting: tsp.o graph.o path.o stack.o
	$(CC) -o tsp tsp.o graph.o path.o stack.o $(LFLAGS)
graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c
path.o: path.c
	$(CC) $(CFLAGS) -c path.c 
stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c
sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c
clean:
	rm sorting *.o
format:
	clang-format -i -style=file *.[ch]
