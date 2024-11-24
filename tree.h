#ifndef PROJECT_ROVER_TREE_H
#define PROJECT_ROVER_TREE_H

#include "moves.h"
#include "map.h"

typedef struct s_node
{
    t_localisation localisation;
    t_move move;
    int terrain_cost;
    int nb_sons;
    int depth;
    struct s_node **sons;
    struct s_node *parent;
}t_node, *p_node;

typedef struct s_tree
{
    t_node *root;
    int max_depth;
}t_tree, *p_tree;

static int NB_UTILIZED_MOVES = 3;

p_node createNode(t_localisation loc, t_move move, int cost, int depth, int num_sons, t_node *parent);

p_tree createTree(t_localisation root_loc, t_map map, t_move* moveList);

void printTree(p_node node, int depth);

void deleteNode(p_node node);

void deleteTree(p_tree tree);

t_localisation ergMove(t_localisation loc, t_move mvt); /// A REVOIRRR

p_node buildTreeRec(p_node parent, t_map map, p_tree tree, t_localisation loc, int depth, t_move move_to_node,t_move* remainingMoves);

p_tree buildTree(t_map map, int maxDepth, t_localisation iniLoc);

#endif //PROJECT_ROVER_TREE_H


