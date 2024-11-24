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

static int NB_UTILIZED_MOVES = 5;

/**
 * @brief Creates a new node in the tree with specified parameters.
 *
 * @param loc The localisation information for the node (x y coordinates and orientation).
 * @param move The move associated with the node.
 * @param cost The cost associated with the node's terrain.
 * @param depth The depth level of the node in the tree.
 * @param num_sons The number of child nodes this node can have.
 * @param parent Pointer to the parent node.
 * @return Pointer to the newly created node.
 */
p_node createNode(t_localisation loc, t_move move, int cost, int depth, int num_sons, t_node *parent);

/**
 * @brief Creates a tree with an initial root location, a map, and a list of moves.
 *
 * @param root_loc The location of the root node.
 * @param map The map data used for building the tree.
 * @param moveList A list of moves that can be used to build the tree.
 * @return Pointer to the newly created tree.
 */
p_tree createTree(t_localisation root_loc, t_map map, t_move* moveList, int stoppedAtReg);

/**
 * @brief Prints the tree from the specified node and depth level.
 *
 * @param node The starting node for printing the tree.
 * @param depth The current depth level of the node.
 */
void printTree(p_node node, int depth);

/**
 * @brief Deletes the specified node and its child nodes.
 *
 * @param node The node to be deleted.
 */
void deleteNode(p_node node);

/**
 * @brief Deletes the specified tree and all its nodes.
 *
 * @param tree The tree to be deleted.
 */
void deleteTree(p_tree tree);

/**
 * @brief Calculates the resulting location after making a specified move.
 *
 * @param loc The initial location.
 * @param mvt The move to be made.
 * @return The new location after the move.
 */
t_localisation Movement_on_erg(t_localisation loc, t_move mvt);

/**
 * @brief Recursively builds a tree from the specified parent node and parameters.
 *
 * @param parent The parent node.
 * @param map The map data used for building the tree.
 * @param tree The tree being constructed.
 * @param loc The current location in the tree.
 * @param depth The current depth level.
 * @param move_to_node The move that led to this node.
 * @param remainingMoves The list of remaining moves.
 * @return Pointer to the newly built node.
 */
p_node buildTreeRec(p_node parent, t_map map, p_tree tree, t_localisation loc, int depth, t_move move_to_node,t_move* remainingMoves);

/**
 * @brief Builds a tree from the initial location and map up to a specified maximum depth.
 *
 * @param map The map data used for building the tree.
 * @param maxDepth The maximum depth for the tree.
 * @param iniLoc The initial location for the root of the tree.
 * @return Pointer to the newly created tree.
 */
p_tree buildTree(t_map map, int maxDepth, t_localisation iniLoc);

#endif //PROJECT_ROVER_TREE_H


