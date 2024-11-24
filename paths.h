#ifndef PROJECT_ROVER_PATHS_H
#define PROJECT_ROVER_PATHS_H
#include "tree.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

p_node findMinimalNode(p_node node, int* min_cost, p_node currentMin);

p_node findBestNode(t_tree *tree);

t_stack extractPath(p_node node, p_tree tree);

t_stack findBestPath(t_tree *tree);

void printBestPath(t_stack path);

#endif //PROJECT_ROVER_PATHS_H
