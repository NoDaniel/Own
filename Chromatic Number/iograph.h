///\file iograph.h
///\brief C library for Input/Output of graphs
///

#ifndef IOGRAPH_H_INCLUDED
#define IOGRAPH_H_INCLUDED

struct a_graph{
    ///\brief Struct that defines a graph type

    ///\var number_of_nodes
    ///Stores number of nodes in our graph
    int number_of_nodes;

    ///\var is_initialized Boolean value
        ///TRUE (1) =is initialized
        ///FALSE (0) =is not initialized
    int is_initialized;

    ///\var *adjacent_matrix Pointer to the adjacent matrix
    ///Used to store the edges, connection between the nodes
    int *adjacent_matrix;

    ///\var *node_value Pointer to the vector storing the value of the node
    int *node_value;

    ///\var *number_of_vertices Number of vertices in our graph
    int number_of_vertices;
};

void non_trivial_graph_generator(struct a_graph *my_graph);
void print_graph(struct a_graph *my_graph);
void read_graph(struct a_graph *my_graph);
void read_graph_file(struct a_graph *my_graph);


#endif // IOGRAPH_H_INCLUDED
