///\file main.c
///\brief Chromatic Number Problem.
///
/// The minimum number of colors needed to colors each node in an undirected graph
///


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "iograph.h"
#include "graphcommands.h"
#include "coloringAlgorithms.h"


void clrscr(){
    ///\fn void clrscr();
    ///\brief Clear the screen function
    system("@cls||clear");
}

int main(){
    ///\fn int main()
    ///\brief Main function.
    /// Function calls of sum and sub imported from arithmetic.h

    ///\var *my_graph A graph of type a_graph
    struct a_graph *my_graph;
    ///\var *bfs_order_vector Vector where we are gonna store the way our graph is sorted with bfs
    int *bfs_order_vector;
    ///\var input_option Used for chosing what method we are going to use
    int input_option;
    ///

    ///Allocate memory dynamically to the graph
    my_graph=calloc(1, sizeof(struct a_graph));
    ///Allocate memory dynamically to the vector that memorizes the node value
    ///In our case it stores the color "number"
    my_graph->node_value = calloc(my_graph->number_of_nodes, sizeof(*my_graph));

    ///Read graph either from file or keyboard(user choice)
    printf("\n");
    printf("     Way of input    \n");
    printf("1.Input from keyboard\n");
    printf("2.Input from file\n");
    printf("3.Random graph");
    scanf("%d", &input_option);
    if(input_option==1){
        clrscr();
        read_graph(my_graph);
    }else if(input_option==2){
        clrscr();
        read_graph_file(my_graph);
    }else if(input_option==3){
        non_trivial_graph_generator(my_graph);
    }
    clrscr();

    ///Allocate memory dynamically to the bfs order vector
    bfs_order_vector=(int*)calloc((my_graph->number_of_nodes+1), sizeof(*bfs_order_vector));

    ///BFS ordering, that gets stored in our vector
    graph_bfs(my_graph, 1, bfs_order_vector);

    ///Print graph
    //print_graph(my_graph);

    ///Solve the graph with one of the implemented methods(user choice)
    printf("\n");
    printf("Which method do you want to use?\n");
    printf("1.Simple Greedy Algorithm\n");
    printf("2.Greedy Algorithm with prior bfs\n");
    printf("3.Backtracking with prior bfs\n");
    scanf("%d", &input_option);
    clrscr();
    if(input_option == 1){
        ///"Color" the graph and output the minimum number of colors with simple greedy algorithm
        find_color_greedy_alg_basic(my_graph);
    }else if(input_option == 2){
        ///"Color" the graph and output the minimum number of colors with greedy algorithm aplied on the bfs graph
        find_color_greedy_alg_with_bfs(my_graph, bfs_order_vector);
    }else if(input_option == 3){
         ///"Color" the graph and output the minimum number of colors with simple backtracking algorithm
        graph_coloring_backtracking(my_graph, my_graph->number_of_nodes, bfs_order_vector);
    }

    ///Free memory for adjacent matrix, node value and in the end, graph, bfs order vector
    free(my_graph->adjacent_matrix);
    free(my_graph->node_value);
    free(my_graph);
    free(bfs_order_vector);

    return 0;
}
