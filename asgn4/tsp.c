#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"
// The above header files are provided in the resources repository by Professor Long. (2021 Professor Long)
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "huvi:o:"

//The function dsp takes two pointers to path structs, a vertex v, a pointer to a graph G,
//A boolean value of verbose, a file to write to of outfile, an array of strings citite[]
//and a pointer to an integer to track the number of recursions.
//
//This function contains the implemenation of depth first search by recursion, inspired by
//the pseudocode provided in the resources repository by Professor Long.
void dfs(Path *current, Path *shortest, uint32_t v, Graph *G, bool verbose, FILE *outfile,
    char *cities[], uint32_t *recursions) {
    //To begin, the code adds one to the recursive count to track the number.
    //It then marks the given vertex as visited and adds it to the path.
    *recursions += 1;
    graph_mark_visited(G, v);
    path_push_vertex(current, v, G);
    uint32_t total_vertices = graph_vertices(G);
    bool dead_end = true;
    //The below statements first check if the current path is not longer that the shortest path,
    //in which case, it will stop testing this path.
    //
    //It then loops through all vertices, and checks if there are unvisited vertices from the current vertex.
    //For each of those vertices, it will call itself recursively to continue the path.
    if (!((path_length(shortest) > 0) && (path_length(current) >= (path_length(shortest))))) {
        for (uint32_t i = 0; i < total_vertices; i++) {
            if ((!(graph_visited(G, i)) && (graph_has_edge(G, v, i)))) {
                dead_end = false;
                dfs(current, shortest, i, G, verbose, outfile, cities, recursions);
            }
        }
        //This statement uses the dead_end tracking boolean, this boolean being true indicated that
        //there are no unvisited vertices from the current vertex.
        //It then checks if the number of the vertices in the path is the same as the number of total vertices,
        //and if the graph has an edge from the current vertex to the origin.
        //If the above conditions are met, we have found a Hamiltonian path.
        //This code then checks if this path is the shortest, and if it is, copies it into the shortest path.
        //It also prints all found paths if verbose is specified.
        if (dead_end) {
            if ((path_vertices(current) == total_vertices) && (graph_has_edge(G, v, 0))) {
                path_push_vertex(current, 0, G);
                if (verbose) {
                    path_print(current, outfile, cities);
                }
                if ((path_length(current) < path_length(shortest))
                    || (path_length(shortest) == 0)) {
                    path_copy(shortest, current);
                }
                uint32_t ye = 0;
                path_pop_vertex(current, &ye, G);
            }
        }
    }
    //This unvisits the current vertex, and pops it from the path, allowing for the function to backtrack.
    graph_mark_unvisited(G, v);
    uint32_t popped = 0;
    path_pop_vertex(current, &popped, G);
    return;
}

//The main function takes command line arguements, and returns an int.
//
//This function parses command line arguements, and parses user input.
//Ater taking the input, it runs the dfs function
//It also allocates and frees the neccessary memory.
int main(int argc, char **argv) {
    // The below code parses command line arguments,
    // It sets the verbose and undirected booleans to true if given.
    // It also sets the input and output files if they are given, and errors if the infile is invalid.
    int opt = 0;
    bool verbose = false;
    bool undirected = false;
    FILE *input = stdin;
    FILE *output = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("help msh\n");
            return 0;
            break;
        case 'v': verbose = true; break;
        case 'u': undirected = true; break;
        case 'i':
            if (!(input = fopen(optarg, "r"))) {
                printf("Error: failed to open infile.\n");
                return 1;
            };
            break;
        case 'o': output = fopen(optarg, "w"); break;
        }
    }

    //This code parses user input. It takes the number of vertices from either stdin or the specified input file
    //This code's usage of fgets and sscanf inspired by the code provided in section by Eugene Chou. (2021 Eugene Chou)
    uint32_t number_vertices = 0;

    char buffer[1025];
    fgets(buffer, 1024, input);
    if (1 != sscanf(buffer, "%" SCNu32, &number_vertices)) {
        printf("Error: malformed number of vertices.\n");
        return 1;
    }
    if (number_vertices == 1) {
        printf("There's nowhere to go\n");
    }

    //The below code allocates an array of strings of length number_vertices, to be used to store city names.
    //It the parses through the next number_vertices lines of input, and after taking the \n off the end,
    //stores the value in the array of strings using strdup.
    //The code's usage of fgets is inspired by, the code provided in section by Eugene Chou. (2021 Eugene Chou)
    char **city = (char **) calloc(number_vertices, sizeof(char *));
    for (uint32_t i = 0; i < number_vertices; i++) {
        fgets(buffer, 1024, input);
        buffer[strlen(buffer) - 1] = '\0';
        city[i] = strdup(buffer);
    }

    //The below code takes unsigned integers inputted by the user, and continues to loop until the end of file.
    //It adds the values to the graph as a vertex, for every triple inputted, regardless of newlines, adds them as vertices to the graph.
    //If the vertex is malformed, the code prints an error, frees memory, and returns.
    //The belwo usage of fgets and sscanf inspired by the code provided in section by Eugene Chou. (2021 Eugene Chou)
    uint32_t i_vertex;
    uint32_t j_vertex;
    uint32_t weight;
    struct Graph *graph = graph_create(number_vertices, undirected);
    uint32_t input_counter = 0;
    int sscanfout = 0;
    uint32_t field_1 = 0;
    uint32_t field_2 = 0;
    uint32_t field_3 = 0;
    while (fgets(buffer, 1024, input)) {

        sscanfout = sscanf(buffer, "%" SCNu32 "%" SCNu32 "%" SCNu32, &field_1, &field_2, &field_3);
        if (sscanfout == 3) {
            switch (input_counter) {
            case 0: graph_add_edge(graph, field_1, field_2, field_3); break;
            case 1:
                j_vertex = field_1;
                weight = field_2;
                graph_add_edge(graph, i_vertex, j_vertex, weight);
                i_vertex = field_3;
                input_counter = 1;
                break;
            case 2:
                weight = field_1;
                graph_add_edge(graph, i_vertex, j_vertex, weight);
                input_counter = 2;
                i_vertex = field_2;
                j_vertex = field_3;
                break;
            default: break;
            }

        } else if (sscanfout == 2) {
            switch (input_counter) {
            case 0:
                i_vertex = field_1;
                j_vertex = field_2;
                input_counter += 2;
                break;
            case 1:
                j_vertex = field_1;
                weight = field_2;
                graph_add_edge(graph, i_vertex, j_vertex, weight);
                input_counter = 0;
                break;
            case 2:
                weight = field_1;
                graph_add_edge(graph, i_vertex, j_vertex, weight);
                input_counter = 1;
                i_vertex = field_2;
                break;
            default: break;
            }
        } else if (sscanfout == 1) {
            switch (input_counter) {
            case 0:
                i_vertex = field_1;
                input_counter += 1;
                break;
            case 1:
                j_vertex = field_1;
                input_counter = 2;
                break;
            case 2:
                weight = field_1;
                graph_add_edge(graph, i_vertex, j_vertex, weight);
                input_counter = 0;
                break;
            default: break;
            }
        } else if (sscanfout == EOF) {
            break;
        } else {
            printf("Error: malformed edge.\n");
            graph_delete(&graph);
            for (uint32_t i = 0; i < number_vertices; i++) {
                free(city[i]);
            }
            free(city);

            return 1;
            break;
        }
    }

    //the below code allocates memory and initializes variables to be used in dfs, and then calls dfs
    //It then prints the result of the shortest Hamiltonian path and frees allocated memory.
    struct Path *current = path_create();
    struct Path *shortest = path_create();
    uint32_t num_rcr = 0;
    dfs(current, shortest, 0, graph, verbose, output, city, &num_rcr);
    if (path_vertices(shortest) == 0) {
        fprintf(output, "There's no Hamiltonian path found\n");
    } else {
        path_print(shortest, output, city);
    }
    graph_delete(&graph);
    fprintf(output, "Total recursive calls: %d\n", num_rcr);
    for (uint32_t i = 0; i < number_vertices; i++) {
        free(city[i]);
    }
    free(city);
    path_delete(&current);
    path_delete(&shortest);
}
