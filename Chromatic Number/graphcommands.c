///\file graphcommands.c
///\brief C library for Graph commands(check for adjacency, bfs sorting)
///

#include <stdio.h>
#include "iograph.h"
#include "graphcommands.h"

int is_adjacent(struct a_graph *my_graph, int node1, int node2){

    ///\fn int is_adjacent(struct a_graph *my_graph, int node1, int node2)
    ///\brief Check if two nodes are adjacent
    ///
    ///\param *my_graph Pointer to our graph
    ///\param node1 First node
    ///\param node2 Second node
    ///

    ///We check in the adjacent matrix if the two nodes provided as parameters are adjacent
    if(*(my_graph->adjacent_matrix + node1*my_graph->number_of_nodes + node2)==1){
        ///Return 1 if nodes are adjacent
        return 1;
    }else{
        ///Return 0 if nodes are adjacent
        return 0;
    }
}

void push_begining_list(struct a_list_node *head, int new_element_value){
    ///\fn void push_begining_list(struct a_list_node *head, int new_element_value)
    ///\brief Push element at the begining of the list
    ///
    ///\param *head The head of the list
    ///\param new_element_value New element value
    ///

    ///\var *next_element Next element in the list
    struct a_list_node *next_element;
    ///\var *new_element The new element put in the list
    struct a_list_node *new_element;

    ///We store where the head points in the variable next_element
    next_element = head->next;
    ///Allocating memory for the new element
    new_element = malloc(sizeof(struct a_list_node));
    ///We put the value given as parameter in the info of our new element
    new_element->info = new_element_value;
    ///The "next" of the new element it's given the "next" of the curent head
    new_element->next = head->next;
    ///And the "next" of the head it's given the position of the new element
    head->next = new_element;
}

int pop_end_list(struct a_list_node *head) {
    ///\fn int pop_end_list(struct a_list_node *head)
    ///\brief Pop element from the end of the list
    ///
    ///\param *head The head of the list
    ///

    ///\var *deleted_element
    struct a_list_node *deleted_element;
    ///\var *iterator Iterator to go through the list
    struct a_list_node *iterator;
    ///\var aux An auxiliar, an empty box to store something
    int aux;

    ///If the list it's not empty(The next element from the head it's not NULL)
    ///If the list it's empty, print that it's empty and return -1
    if (head->next != NULL) {
        ///Iterate through the list until the second next element it's NULL
        for (iterator = head; iterator->next->next != NULL; iterator = iterator->next);
        ///We store the next element from the iterator, which it's gonna be deleted
        deleted_element = iterator->next;
        ///Store it's info
        aux = deleted_element->info;
        ///We give the iterator(Which now it's the last element) the next of the delete element(Which it's NULL)
        iterator->next = deleted_element->next;
        ///Free the part in the memory which stored the now deleted element
        free(deleted_element);
        ///Return the value of the deleted element
        return aux;
    } else {
        printf("\n The list is empty");
        return -1;
    }
}

void graph_bfs(struct a_graph *my_graph, int start_node, int *bfs_order_vector){
    ///\fn void graph_bfs(struct a_graph *my_graph, int start_node, int *bfs_order_vector)
    ///\brief Order the graph nodes in a Breadth-first manner
    ///
    ///\param *my_graph The graph
    ///\param start_node The node that we consider as a "head"
    ///\param *bfs_order_vector A vector that's gonna store the order in which bfs crosses the graph
    ///

    ///\var *head_queue Declaration of a adjacency list
    struct a_list_node *head_queue;
    ///\var *visited Stores which nodes were already visited
    int *visited;
    ///\var column_index Iterator of the column
    int column_index;
    ///\var aux Auxiliar, stores something, like an empty box
    int aux;
    ///\var current_node The node to which we are at a given moment of time
    int current_node;
    ///\var i Iterator for the bfs_order_vector
    int i=1;

    ///Allocating memory for the head element of the queue
    head_queue = calloc(1, sizeof(struct a_list_node));
    head_queue->next = NULL;
    head_queue->info = 0;

    ///Allocating memory for the visited vector, 1 more the the number of nodes
    ///We start the graph from 1 instead of 0 for simplicity
    visited = calloc((my_graph->number_of_nodes + 1), sizeof(int));
    push_begining_list(head_queue, start_node);
    visited[start_node] = 1;
    ///Go through the queue until there is nothing left(So while there is at least 1 element)
    while (head_queue->next != NULL){
        current_node = pop_end_list(head_queue);
        ///Print the current node
        ///Store which node it was
        *(bfs_order_vector + i)=current_node;
        ///And increment the iterator for it
        i++;
        ///Go through the nodes, check if they are adjacent and not visitated
        for(column_index = 1; column_index <= my_graph->number_of_nodes; column_index++){
            aux = *(my_graph->adjacent_matrix + current_node * my_graph->number_of_nodes + column_index);
            if ( (aux != 0) && ( (visited[column_index]) == 0 )){
                push_begining_list(head_queue, column_index);
                visited[column_index] = 1;
            }
        }
    }

    free(head_queue);
    free(visited);
}
