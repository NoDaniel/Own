///\file graphcommands.h
///\brief C library for implementation of Graph commands(check for adjacency, bfs sorting)
///

#ifndef GRAPHCOMMANDS_H_INCLUDED
#define GRAPHCOMMANDS_H_INCLUDED

struct a_list_node{
    ///\brief Struct that defines a list type

    ///\var info The value of the list element
    int info;

    ///\var *next of type struct a_list_next, that defines the conection between two of the list elements
    struct a_list_node *next;
};

int is_adjacent(struct a_graph *my_graph, int node1, int node2);
void push_begining_list(struct a_list_node *head, int new_element_value);
int pop_end_list(struct a_list_node *head);
void graph_bfs(struct a_graph *my_graph, int start_node, int *bfs_order_vector);


#endif // GRAPHCOMMANDS_H_INCLUDED
