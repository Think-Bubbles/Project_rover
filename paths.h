#ifndef PROJECT_ROVER_PATHS_H
#define PROJECT_ROVER_PATHS_H
#include "tree.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Finds the node with the minimal cost in the given tree node's subtree.
 * Parameters:
 *  - node: The current node to evaluate.
 *  - min_cost: A pointer to the minimum cost found so far.
 *  - currentMin: The current node with the minimal cost.
 * Returns: The node with the minimal cost found in the subtree.
 */
p_node findMinimalNode(p_node node, int* min_cost, p_node currentMin);

/**
 * Determines the best node in the tree based on some criteria (e.g., minimal cost).
 * Parameters:
 *  - tree: The tree to search.
 * Returns: The best node found in the tree.
 */
p_node findBestNode(t_tree *tree);

/**
 * Extracts the path from the root node to the given node.
 * Parameters:
 *  - node: The target node.
 *  - tree: The tree containing the nodes.
 *  - map: A map providing additional context or data.
 *  - stoppedAtReg: A pointer to an integer indicating the point at which the path stopped.
 * Returns: A stack containing the path from the root to the target node.
 */
t_stack extractPath(p_node node, p_tree tree, t_map map,int* stoppedAtReg);

/**
 * Finds the best path in the tree based on some criteria (e.g., minimal cost).
 * Parameters:
 *  - tree: The tree to search.
 *  - map: A map providing additional context or data.
 *  - stoppedAtReg: A pointer to an integer indicating the point at which the path stopped.
 * Returns: The best path found in the tree.
 */
t_stack findBestPath(t_tree *tree, t_map map,int* stoppedAtReg);

/**
 * Prints the best path found.
 * Parameters:
 *  - path: The stack containing the best path.
 */
void printBestPath(t_stack path);

#endif //PROJECT_ROVER_PATHS_H
