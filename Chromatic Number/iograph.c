///\file iograph.c
///\brief C library for implementation of Input/Output of graphs
///

#include <stdio.h>
#include "iograph.h"

void non_trivial_graph_generator(struct a_graph *my_graph){
    ///\fn void non_trivial_graph_generator(struct graph *my_graph)
    ///\brief Generator for a random adjecency matrix

    ///\var i iterator
    int i;
    ///\var j iterator
    int j;
    ///\var aux iterator
    int aux;

    srand(time(NULL));

    aux=rand()%1000;

    my_graph->number_of_nodes=aux;
    ///We set the is_initialized to 1 so that we know the graph is now initialized
    my_graph->is_initialized = 1;
    ///Allocating memory to the adjacent matrix of our graph
    my_graph->adjacent_matrix = calloc(my_graph->number_of_nodes*my_graph->number_of_nodes, sizeof(*my_graph));
    ///Initialize number of vertices as 0
    my_graph->number_of_vertices = 0;

    for(i=1; i<=my_graph->number_of_nodes; i++){
        for(j=i+1; j<=my_graph->number_of_nodes; j++){
            aux=rand()%2;
            *(my_graph->adjacent_matrix + i*my_graph->number_of_nodes + j)=aux;
            *(my_graph->adjacent_matrix + j*my_graph->number_of_nodes + i)=aux;
        }
    }
}

void print_graph(struct a_graph *my_graph){

    ///\fn void print_graph(struct a_graph *my_graph)
    ///\brief Prints a graph
    ///
    ///\param *my_graph Pointer to our graph
    ///

    ///\var iterator_rows An iterator for counting rows in the adjacent matrix
    int iterator_rows;
    ///\var iterator_columns An iterator for counting columns in the adjacent matrix
    int iterator_columns;
    ///

    ///Printing a message so the user know what's printing on the console
    printf("\nAdjacent matrix of our graph :\n");

    ///We take 2 for loops, one for rows and one for columns
    ///By using pointer arithmetics, a vector in the memory becomes a "matrix" for a easier understanding and operating
    printf("\n");
    for(iterator_rows=1; iterator_rows<=my_graph->number_of_nodes; iterator_rows++){
        printf("           ");
        for(iterator_columns=1; iterator_columns<=my_graph->number_of_nodes; iterator_columns++){
            ///We print every element of our adjacent matrix, formated as a matrix in the console
            printf("%d ", *(my_graph->adjacent_matrix + iterator_rows*my_graph->number_of_nodes + iterator_columns));
        }
        printf("\n");
    }
}

void read_graph(struct a_graph *my_graph){

    ///\fn void print_graph(struct a_graph *my_graph)
    ///\brief Prints a graph
    ///
    ///\param *my_graph Pointer to our graph
    ///

    ///\var iterator_rows An iterator for counting rows in the adjacent matrix
    int iterator_rows;
    ///\var iterator_columns An iterator for counting columns in the adjacent matrix
    int iterator_columns;
    ///\var input_option Variable to let the user decide which nodes are adjacent (Y = Yes/ N=No)
    char input_option;
    ///

    ///Printing a message so the user knows what's printing on the console, and a space for visual aspect
    printf("\nNumber of nodes ");
    printf("\n");
    ///Read the number of nodes from the keyboard
    scanf("%d", &my_graph->number_of_nodes);
    ///We set the is_initialized to 1 so that we know the graph is now initialized
    my_graph->is_initialized = 1;
    ///Allocating memory to the adjacent matrix of our graph
    my_graph->adjacent_matrix = calloc(my_graph->number_of_nodes*my_graph->number_of_nodes, sizeof(*my_graph));
    ///Initialize number of vertices as 0
    my_graph->number_of_vertices = 0;

    for(iterator_rows = 1; iterator_rows <= my_graph->number_of_nodes; iterator_rows++){
        for(iterator_columns = iterator_rows + 1; iterator_columns <= my_graph->number_of_nodes; iterator_columns++){
            ///Ask the user if the two nodes display are adjacent or not
            printf("Node %d is adjacent with node %d ? (Y/N) ", iterator_rows , iterator_columns  );
            scanf(" %c", &input_option);
            ///And check how they answered
            if(input_option == 'y' || input_option == 'Y'){
                ///If the input was Y=Yes - so true - we input in the adjacent matrix that the two nodes are adjacent
                *(my_graph->adjacent_matrix + iterator_rows*my_graph->number_of_nodes + iterator_columns)=1;
                *(my_graph->adjacent_matrix + iterator_columns*my_graph->number_of_nodes + iterator_rows)=1;
                ///Count the number of vertices (the vertice from X to Y it's the same as the one from Y to X)
                my_graph->number_of_vertices=my_graph->number_of_vertices + 1;
            }
        }
    }
}

void read_graph_file(struct a_graph *my_graph){

    ///\fn void print_graph(struct a_graph *my_graph)
    ///\brief Prints a graph
    ///
    ///\param *my_graph Pointer to our graph
    ///

    ///\var iterator_rows An iterator for counting rows in the adjacent matrix
    int iterator_rows;
    ///\var iterator_columns An iterator for counting columns in the adjacent matrix
    int iterator_columns;
    ///\var input_placeholder Variable to store the input from file before passing it to the matrix
    int input_placeholder;
    ///\var file Variable of type file, used to read from a file
    FILE *test_file;
    ///

    ///Open file and read number of nodes
    test_file=fopen("greedy_test.in", "r+");
    fscanf(test_file, "%d", &my_graph->number_of_nodes);

    ///We set the is_initialized to 1 so that we know the graph is now initialized
    my_graph->is_initialized = 1;
    ///Allocating memory to the adjacent matrix of our graph
    my_graph->adjacent_matrix = calloc(my_graph->number_of_nodes*my_graph->number_of_nodes, sizeof(*my_graph));
    ///Initialize number of vertices as 0
    my_graph->number_of_vertices = 0;

    for(iterator_rows = 1; iterator_rows <= my_graph->number_of_nodes; iterator_rows++){
        for(iterator_columns = 1; iterator_columns <= my_graph->number_of_nodes; iterator_columns++){
                ///Read the value into a placeholder and then input it into the matrix
                fscanf(test_file, "%d", &input_placeholder);
                *(my_graph->adjacent_matrix + iterator_rows*my_graph->number_of_nodes + iterator_columns)=input_placeholder;
                ///Count the vertices
                if(input_placeholder==1){
                    my_graph->number_of_vertices=my_graph->number_of_vertices + 1;
                }
        }
    }

    ///Divide vertices by 2, becouse the vertice from X to Y it's the same as the one from Y to X
    my_graph->number_of_vertices=my_graph->number_of_vertices/2;
    ///Close file
    fclose(test_file);
}
