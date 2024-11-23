//
// Created by HIM on 23/11/2024.
//

#ifndef PROJECT_ROVER_TREE_H
#define PROJECT_ROVER_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include "loc.h"
#include "moves.h"
#include "map.h"
#include "queue.h"
#include "stack.h"
#include "moves.h"

typedef struct s_node
{
    t_localisation loc;
    t_move move;
    int cost;
    struct s_node **sons;
    int num_sons;
    int depth;
    struct s_node *parent;
}t_node, *p_node;

typedef struct s_tree
{
    t_node *root;
    int max_depth;
}t_tree, *p_tree;

p_node createNode(t_localisation loc, t_move move, int cost, int depth, int num_sons, t_node *parent);

p_tree createTree(t_localisation root_loc);

void printTree(p_node node, int depth);

void deleteNode(p_node node);

void deleteTree(p_tree tree);

t_localisation ergMove(t_localisation loc, t_move mvt); /// A REVOIRRR

p_node buildTreeRec(p_node parent, t_map map, p_tree tree, t_localisation loc, int depth, int **visited);

p_tree buildTree(t_map map, int maxDepth, t_localisation iniLoc);

int alreadyVisited(int x, int y, int **visited, int map_x_max, int map_y_max);

void markVisited(int x, int y, int **visited);

#endif //PROJECT_ROVER_TREE_H


