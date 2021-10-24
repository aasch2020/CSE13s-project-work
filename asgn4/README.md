# Assignment 4 - The Perambulations of Denver Long
The program finds the shortest Hamiltonian path given a graph as an input file or as user input. It uses three structs, a graph, a stack, and a path to achieve this. A Hamiltonian path is the path that includes all vertices in a graph. The graph is inputted as first a number a vertices, then names of vertices, and then as triples i,j,k, which is an edge from i to j of weight k.
##Run the following to build the program:
```
$ make tsp
```

## Running
```
./tsp -args
```
  -u             Use undirected graph.
  -v             Enable verbose printing.
  -h             Program usage and help.
  -i infile      Input containing graph (default: stdin)
  -o outfile     Output of computed path (default: stdout)

