#include "paths.h"

p_node findMinimalNode(p_node node, int* min_cost, p_node currentMin) {

    if (!node) return currentMin;


    if (node->terrain_cost < *min_cost || /// The cost is inferior to what we currently consider to be the minimal cost
        (node->terrain_cost == *min_cost && /// Or the cost is equal to what we already have
         (currentMin == NULL || node->depth < currentMin->depth))) { /// (If they both are equal) Check which one has the lowest depth
        *min_cost = node->terrain_cost; /// Update the current minimal cost
        currentMin = node;
    }

    for (int i = 0; i < node->nb_sons; i++) { /// Search through all of the nodes sons
        currentMin = findMinimalNode(node->sons[i], min_cost, currentMin);
    }

    return currentMin;
}


p_node findBestNode(t_tree *tree) {
    if (tree == NULL || tree->root == NULL) return NULL; /// Does the tree exist?

    int min_cost = COST_UNDEF;  /// Set the initial cost very high so that we take a new minimum
    return findMinimalNode(tree->root, &min_cost, NULL);
}

t_stack extractPath(p_node node, p_tree tree, t_map map,int* stoppedAtReg) {
    t_stack path = createStack(tree->max_depth+1); /// Since the height goes from 0 to 5 add 1

    p_node current = node;
    while (current != tree->root)
    {
        push(&path, current->move); /// Add the move to the stack
        if (map.soils[current->localisation.pos.y][current->localisation.pos.x] == REG)
            *stoppedAtReg = 1; /// If the path has encountered a reg
        current = current->parent; /// Go back up the tree
    }

    return path;
}

t_stack findBestPath(t_tree *tree, t_map map, int* stoppedAtReg) {
    p_node bestNode = findBestNode(tree);
    return extractPath(bestNode, tree, map, stoppedAtReg);
}

void printBestPath(t_stack path) {
    printf("Optimal path (root -> node) :\n");
    while (path.nbElts > 0) {
        /// Unstack an element from the stack
        t_move move = pop(&path);
        /// Display the move as a string
        printf("%s -> ", getMoveAsString(move));
    }
    printf("FIN\n");
}


