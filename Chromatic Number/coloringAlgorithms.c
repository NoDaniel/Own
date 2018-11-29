///\file coloringAlgorithms.c
///\brief C library for diferent algorithms of Graph Coloring
///

#include <stdio.h>
#include "iograph.h"
#include "graphcommands.h"
#include "coloringAlgorithms.h"

void find_color_greedy_alg_basic(struct a_graph *my_graph){

    ///\fn void find_color_greedy_alg(struct a_graph *my_graph)
    ///\brief Colors the graph and prints the colors, using the greedy algorithm
    /// A greedy algorithm is an algorithmic paradigm that follows the problem solving heuristic of making the locally optimal choice at each stage with the hope of finding a global optimum
    ///
    ///\param *my_graph Pointer to our graph
    ///

    ///\var i Counter
    int i;
    ///\var j Counter
    int j;
    ///\var *colors Vector for storing the colors needed
    int *colors;
    ///\var maximum_number_of_colors Maximum number of colors needed to color
    ///Initialized as 1, becouse we need at least 1 color for every graph posible
    int maximum_number_of_colors=1;
    ///

    ///Allocate memory dynamically to colors vector
    colors=calloc(my_graph->number_of_nodes, sizeof(*colors));

    ///We cycle through our nodes, using the counter i, which starts from the node 1
    for(i=1;i<=my_graph->number_of_nodes;i++){
        ///Initially every node will have the color noted as 1
        *(colors + i)=1;
        ///We cycle through all the nodes before the "i" node
        for(j=1;j<=i;j++){
            ///Check if the node "i" and node "j" are adjacent. and if the colors of those 2 are the same
            if(is_adjacent(my_graph, i, j)==1 && *(colors + i)==*(colors + j)){
                ///If so, we add 1 to the color, changing the color to the next one
                ///We will do so until we found the first node color that it's not already owned by an adjecent node to the node "i"
                *(colors + i)=*(colors + j)+1;
                 maximum_number_of_colors=*(colors + j)+1;
            }
        }
    }

    ///Printing the nodes and the color the have
    printf("\n");
    for(i=1;i<=my_graph->number_of_nodes;i++){
        printf("Node[%d] is colored with color %d \n",i , *(colors + i));
    }

    ///Printing the number of colors we used
    printf("\n");
    printf("Colors needed : %d\n", maximum_number_of_colors);
}

void find_color_greedy_alg_with_bfs(struct a_graph *my_graph, int *bfs_order_vector){

    ///\fn void find_color_greedy_alg(struct a_graph *my_graph)
    ///\brief Colors the graph and prints the colors, using the greedy algorithm
    /// A greedy algorithm is an algorithmic paradigm that follows the problem solving heuristic of making the locally optimal choice at each stage with the hope of finding a global optimum
    ///
    ///\param *my_graph Pointer to our graph
    ///\param *bfs_order_vector BFS order of our graph
    ///

    ///\var i Counter
    int i;
    ///\var j Counter
    int j;
    ///\var *colors Vector for storing the colors needed
    int *colors;
    ///\var maximum_number_of_colors Maximum number of colors needed to color
    ///Initialized as 1, becouse we need at least 1 color for every graph posible
    int maximum_number_of_colors=1;
    ///

    ///Allocate memory dynamically to colors vector
    colors=calloc(my_graph->number_of_nodes, sizeof(*colors));

    ///We cycle through our nodes, using the counter i, which starts from the node 1
    for(i=1;i<=my_graph->number_of_nodes;i++){
        ///Initially every node will have the color noted as 1
        *(colors + i)=1;
        ///We cycle through all the nodes before the "i" node
        for(j=1;j<=i;j++){
            ///Check if the node "i"(after the bfs sort) and node "j"(after the bfs sort) are adjacent
            ///And if the colors of those 2 are the same
            if(is_adjacent(my_graph, *(bfs_order_vector + i) , *(bfs_order_vector + j ))==1 && *(colors + i)==*(colors + j)){
                ///If so, we add 1 to the color, changing the color to the next one
                ///We will do so until we found the first node color that it's not already owned by an adjecent node to the node "i"
                *(colors + i)=*(colors + j)+1;
                ///And if if that colors its bigger then all the ones before, we store it as the maximum color
                if((*(colors + j)+1) > maximum_number_of_colors){
                    maximum_number_of_colors=*(colors + j)+1;
                }
            }
        }
    }

    ///Printing the nodes and the color the have
    printf("\n");
    printf("Using the greedy algorithm we have as following :");
    printf("\n");
    for(i=1;i<=my_graph->number_of_nodes;i++){
        printf("Node[%d] is colored with color %d \n",*(bfs_order_vector + i) , *(colors + i));
    }

    ///Printing the number of colors we used
    printf("\n");
    printf("Colors needed : %d\n", maximum_number_of_colors);
}

void print_solution(int *colors, struct a_graph *my_graph, int *bfs_order_vector){

    ///\fn print_solution(int *colors, struct a_graph *my_graph, int *bfs_order_vector)
    ///\brief Print solution
    ///
    ///\param *colors Vector to store the colors
    ///\param *my_graph Pointer to our graph
    ///\param bfs_order_vector BFS order of our graph
    ///

    ///\var i Iterator
    int i;
    ///\var maximum_number_of_colors The maximum
    int maximum_number_of_colors;

    maximum_number_of_colors=0;

    ///Printing the nodes and the color the have
    printf("\n");
    printf("Using the backtracking algorithm we have as following :");
    printf("\n");
    for(i=1;i<=my_graph->number_of_nodes;i++){
        printf("Node[%d] is colored with color %d \n",*(bfs_order_vector + i) , *(colors + i));
        if(*(colors + i)> maximum_number_of_colors){
             maximum_number_of_colors=*(colors + i);
        }
    }



    ///Printing the number of colors we used
    printf("\n");
    printf("Colors needed : %d\n", maximum_number_of_colors);
}

int is_safe(int node, struct a_graph *my_graph, int *colors, int c, int *bfs_order_vector){

    ///\fn int is_safe(int node, struct a_graph *my_graph, int *colors, int c, int *bfs_order_vector
    ///\brief Check if the current color is safe for the node 'node'
    ///
    ///\param node Current node
    ///\param *my_graph Pointer to our graph
    ///\param *colors Vector to store the colors
    ///\param c Current color
    ///\param bfs_order_vector BFS order of our graph
    ///

    ///\var i Counter
    int i;
    ///

    ///Cycle throught all the nodes, and check adjacency and if the colors it's the same
    for (i = 1; i <= my_graph->number_of_nodes; i++){
        if(is_adjacent(my_graph, *(bfs_order_vector + node) , *(bfs_order_vector + i))==1 && c == *(colors + i))
        ///If so, return false, it's not safe
        return 0;
    }
    ///Else, return true, it is
    return 1;
}

int graph_coloring_tool(struct a_graph *my_graph, int m, int *colors, int node, int *bfs_order_vector){

    ///\fn int graph_coloring_tool(struct a_graph *my_graph, int m, int *colors, int node, int *bfs_order_vector)
    ///\brief Solving the
    ///
    ///\param *my_graph Pointer to our graph
    ///\param m The number of colors we try to color our graph with
    ///\param *colors Vector to store the colors
    ///\param node Current node
    ///\param bfs_order_vector BFS order of our graph
    ///

    ///\var c Iterator for the colors
    int c;

    ///If we get to the last node, it means all of them are asigned so we stop and return true
    if (node == my_graph->number_of_nodes + 1){
        return 1;
    }

    ///Cycle through colors
    for (c = 1; c <= m; c++){
        ///Check if the assignment is safe
        if (is_safe(node, my_graph, colors, c, bfs_order_vector)){
           *(colors + node) = c;
            ///The recursion in our program, assigning colors to rest of the nodes
            if (graph_coloring_tool(my_graph, m, colors, node+1, bfs_order_vector) == 1){
                return 1;
            }
            ///If the color c can't lead to a solution, remove it
           *(colors + node) = 0;
        }
    }

    return 0;
}

int graph_coloring_backtracking(struct a_graph *my_graph, int m, int *bfs_order_vector){

    ///\fn int graph_coloring_backtracking(struct a_graph *my_graph, int m, int *bfs_order_vector)
    ///\brief This functions solves the coloring problem using backtracking, mainly by using the tool created before
    ///\brief If the problem can be solved with 'm' or less colors, then it returns true and prints the solution, if not, it returns false
    ///
    ///\param *my_graph Pointer to our graph
    ///\param m The number of colors we try to color our graph with
    ///\param bfs_order_vector BFS order of our graph
    ///

    ///\var *colors Vector to store the colors
    int *colors;

    ///Allocate memory to the colors vector
    colors=calloc(my_graph->number_of_nodes+1, sizeof(colors));

    /// Call graph tool for node 0
    if (graph_coloring_tool(my_graph, m, colors, 0, bfs_order_vector) == 0){
      printf("Solution does not exist");
      return 0;
    }

    /// Print the solution
    print_solution(colors, my_graph, bfs_order_vector);

    return 1;
}

