#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "loc.h"
#include "map.h"
#include "moves.h"
#include "CardPicker.h"

//------- Basic functions for tree -------
p_node createNode(t_localisation loc, t_move move, int cost, int depth, int num_sons, t_node *parent)
{
    p_node node = malloc(sizeof(t_node));

    node->terrain_cost = cost;
    node->depth = depth;
    node->nb_sons = num_sons;
    node->localisation = loc;
    node->move = move;
    node->parent = parent;
    node->sons = malloc(num_sons*sizeof(p_node));
    for (int i= 0; i < num_sons; i++) node->sons[i]= NULL;
    return node;
}

p_tree createTree(t_localisation root_loc, t_map map, t_move* moveList)
{
    p_tree tree = malloc(sizeof (t_tree));
    t_move no_move = -1;
    tree->max_depth = NB_UTILIZED_MOVES;
    tree->root = buildTreeRec(NULL, map, tree, root_loc, 0, no_move, moveList);
    //createNode(root_loc, no_move, COST_UNDEF, 0, num_sons, NULL);

    return tree;
}

void deleteNode(p_node node)
{
    for (int i = 0; i < node->nb_sons; i++)
    {
        if (node->sons[i])
        {
            deleteNode(node->sons[i]);
        }

    }
    free(node->sons);
    node->sons = NULL;
    node->parent = NULL;
    free(node);
}

void deleteTree(p_tree tree)
{
    deleteNode(tree->root);
    free(tree);
}
//----------------------------------------

//------- Functions to build the tree -------

p_node buildTreeRec(p_node parent, t_map map, p_tree tree, t_localisation loc, int depth, t_move move_to_node,t_move* remainingMoves)
{
    if (depth == tree->max_depth+1)
    {
        return NULL;
    }

    int x = loc.pos.x;
    int y = loc.pos.y;

    int cost = 0;
    int num_sons = NUMBER_OF_MOVE-depth;

    if (x < 0 || y < 0 || x >= map.x_max || y >= map.y_max) {
        cost = 10000;
        num_sons = 0;
    }
    else if (map.soils[y][x] == BASE_STATION) {
        cost = 0;
        num_sons = 0;
    }
    else if (map.soils[y][x] == CREVASSE){
        cost = 10000;
        num_sons = 0;
    }
    else
        cost = map.costs[y][x];

    p_node node = createNode(loc, move_to_node, cost, depth, num_sons, parent);

    if (num_sons == 0) {
        return node;
    }

    node->sons = malloc(num_sons*sizeof(p_node));

    for (int i = 0; i < num_sons; i++) {
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