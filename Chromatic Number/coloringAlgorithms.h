///\file coloringAlgorithms.h
///\brief C library for implementation of diferent algorithms of Graph Coloring
///

#ifndef COLORINGALGORITHMS_H_INCLUDED
#define COLORINGALGORITHMS_H_INCLUDED

void find_color_greedy_alg_basic(struct a_graph *my_graph);
void find_color_greedy_alg_with_bfs(struct a_graph *my_graph, int *bfs_order_vector);
void print_solution(int *colors, struct a_graph *my_graph, int *bfs_order_vector);
int is_safe(int node, struct a_graph *my_graph, int *colors, int c, int *bfs_order_vector);
int graph_coloring_tool(struct a_graph *my_graph, int m, int *colors, int node, int *bfs_order_vector);
int graph_coloring_backtracking(struct a_graph *my_graph, int m, int *bfs_order_vector);

#endif // COLORINGALGORITHMS_H_INCLUDED
