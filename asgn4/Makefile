CC = clang
CFLAGS =  -Wall -Werror -Wpedantic -Wextra
LFLAGS = -lm

all: tsp
debug: tsp.c graph.c stack.c path.c
	gcc -g tsp.c graph.c stack.c path.c
tsp: tsp.o graph.o stack.o path.o
	$(CC) -o tsp tsp.o graph.o stack.o path.o $(LFLAGS)
graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c
path.o: path.c 
	$(CC) $(CFLAGS) -c path.c 
stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c
tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c
clean:
	rm tsp *.o
format:
	clang-format -i -style=file *.[ch]
