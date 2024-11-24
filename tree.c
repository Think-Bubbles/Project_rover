#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "loc.h"
#include "map.h"
#include "moves.h"
#include "CardPicker.h"

//------- Basic functions for tree -------

p_node createNode(t_localisation loc, t_move move, int cost, int depth, int num_sons, t_node *parent) {
    p_node node = malloc(sizeof(t_node));

    node->move = move;               /// Assign the given move to the node
    node->depth = depth;             /// Assign the depth level to the node
    node->parent = parent;           /// Set the parent node
    node->nb_sons = num_sons;        /// Set the number of child nodes
    node->localisation = loc;        /// Set the location information for the node
    node->terrain_cost = cost;       /// Set the terrain cost

    node->sons = malloc(num_sons*sizeof(p_node));
    for (int i= 0; i < num_sons; i++) node->sons[i]= NULL; /// Allocate memory for the child nodes and initialize them to NULL

    return node;
}

p_tree createTree(t_localisation root_loc, t_map map, t_move* moveList) {
    p_tree tree = malloc(sizeof (t_tree));

    t_move no_move = -1; /// No moves were made to get to this beginning position so we set it to -1, think of it as Undefined
    tree->max_depth = NB_UTILIZED_MOVES; /// Cap the maximum allowed height (or depth) of the tree
    tree->root = buildTreeRec(NULL, map, tree, root_loc, 0, no_move, moveList); /// Create the rest of the tree based off of the root.
    /// Since it is the root we consider the parent to be NULL; we take the standard map;
    // createNode(root_loc, no_move, COST_UNDEF, 0, num_sons, NULL);

    return tree;
}

void deleteNode(p_node node) {
    for (int i = 0; i < node->nb_sons; i++) { /// Recursive loop to start deleting from the bottom up
        if (node->sons[i])
            deleteNode(node->sons[i]);
    }
    free(node->sons);
    node->sons = NULL;
    node->parent = NULL;
    free(node);
}

void deleteTree(p_tree tree) {
    deleteNode(tree->root);
    free(tree);
}
//----------------------------------------

//------- Functions to build the tree -------

p_node buildTreeRec(p_node parent, t_map map, p_tree tree, t_localisation loc, int depth, t_move move_to_node,t_move* remainingMoves) {
    if (depth == tree->max_depth+1) /// If the current depth is at the maximum tree height, we stop building the tree.
    {
        return NULL;
    }

    int x = loc.pos.x; /// Initialise both x and y
    int y = loc.pos.y;

    int cost = 0;
    int num_sons = NUMBER_OF_MOVE-depth; /// any given node can have Number_of_moves sons MINUS its current depth (=height)

    if (x < 0 || y < 0 || x >= map.x_max || y >= map.y_max) { /// If the rover out of the map, we stop
        cost = 10000;
        num_sons = 0;
    }
    else if (map.soils[y][x] == BASE_STATION) { /// if the rover is on the base_station, we just stop
        cost = 0;
        num_sons = 0;
    }
    else if (map.soils[y][x] == CREVASSE){
        cost = 10000;
        num_sons = 0;
    }
    else
        cost = map.costs[y][x]; /// Otherwise just get the cost from map.costs

    p_node node = createNode(loc, move_to_node, cost, depth, num_sons, parent);

    if (num_sons == 0) { /// If we are on any of the "end" cases, we just return the node without having any sons
        return node;
    }

    node->sons = malloc(num_sons*sizeof(p_node));

    for (int i = 0; i < num_sons; i++) { /// In any other cases, the node will have a or multiple sons
        t_localisation new_loc = move(loc, remainingMoves[i]);
        t_move* newRemainingMoves = remove_possibility(remainingMoves, num_sons, i);
        node->sons[i] = buildTreeRec(node, map, tree, new_loc, depth+1, remainingMoves[i], newRemainingMoves);
    }
    return node;
}

void printTree(p_node node, int depth) {
    if (node == NULL) return;
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("Node at (%d, %d) with cost %d\n", node->localisation.pos.x, node->localisation.pos.y, node->terrain_cost);
    for (int i = 0; i < node->nb_sons; i++) {
        printTree(node->sons[i], depth+1);
    }
}