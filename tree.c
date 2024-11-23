//
// Created by HIM on 23/11/2024.
//

//
// Created by HIM on 12/11/2024.
//

#include "tree.h"

p_node createNode(t_localisation loc, t_move move, int cost, int depth, int num_sons, t_node *parent)
{
    p_node node = (p_node)malloc(sizeof(t_node));

    node->cost = cost;
    node->depth = depth;
    node->num_sons = num_sons;
    node->loc = loc;
    node->move = move;
    node->parent = parent;
    node->sons = (p_node*)malloc(num_sons*sizeof(p_node));
    for (int i= 0; i < num_sons; i++)
    {
        node->sons[i]= NULL;
    }
    return node;
}

p_tree createTree(t_localisation root_loc)
{
    p_tree tree = malloc(sizeof (t_tree));
    t_move no_move = -1;
    int num_sons = 9;
    tree->root = createNode(root_loc, no_move, COST_UNDEF, 0, num_sons, NULL);
    tree->max_depth = 5;
    return tree;
}

void deleteNode(p_node node)
{
    for (int i = 0; i < node->num_sons; i++)
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

t_localisation ergMove(t_localisation loc, t_move mvt) {
    t_move *ptr = &mvt;
    switch (mvt) {
        case F_10:
        case B_10:
        case T_LEFT:
        case T_RIGHT:
            ptr = NULL;
            break;
        case F_20:
            *ptr = F_10;
            break;
        case F_30:
            *ptr = F_20;
            break;
        case U_TURN:
            if (rand() % 2 == 1)
                *ptr = T_RIGHT;
            else
                *ptr = T_LEFT;
            break;
    }

    if (ptr != NULL)
        loc = move(loc, *ptr);

    return loc;

}

t_localisation adjustAndApplyMove(t_localisation loc, t_move mvt) {
    t_move adjustedMove = mvt;

    if (mvt == F_30) {
        adjustedMove = F_20;
    } else if (mvt == F_20) {
        adjustedMove = F_10;
    } else if (mvt == U_TURN) {

        static int toggle = 0;
        adjustedMove = (toggle++ % 2 == 0) ? T_LEFT : T_RIGHT;
    }
    return move(loc, adjustedMove);
}


int alreadyVisited(int x, int y, int **visited, int map_x_max, int map_y_max) {
    return (x >= 0 && y >= 0 && x < map_x_max && y < map_y_max && visited[y][x] == 1);
}

void markVisited(int x, int y, int **visited) {
    visited[y][x] = 1;
}

p_node buildTreeRec(p_node parent, t_map map, p_tree tree, t_localisation loc, int depth, int **visited) {
    if (depth > tree->max_depth) {
        return NULL;
    }

    int x = loc.pos.x;
    int y = loc.pos.y;

    // Si la position a déjà été visitée, ne pas poursuivre la récursion
    if (alreadyVisited(x, y, visited, map.x_max, map.y_max)) {
        return NULL;
    }

    // Marquer la position actuelle comme visitée
    markVisited(x, y, visited);

    int cost = 0;
    int num_sons = (U_TURN - F_10 + 1);

    if (x < 0 || y < 0 || x >= map.x_max || y >= map.y_max) {
        cost = COST_DIE;
        num_sons = 0;
    } else {
        cost = map.costs[y][x];

        switch (map.soils[y][x]) {
            case BASE_STATION:
                cost = 0;
                num_sons = 0;
                break;
            case CREVASSE:
                cost = COST_DIE;
                num_sons = 0;
                break;
            case ERG:
                num_sons = (F_30 - F_10 + 1);
                break;
            default:
                break;
        }
    }

    p_node node = createNode(loc, COST_UNDEF, cost, depth, num_sons, parent);

    if (num_sons == 0) {
        return node;
    }

    node->sons = calloc(num_sons, sizeof(p_node));

    int index = 0;
    for (t_move movement = F_10; movement <= U_TURN; movement++) {
        t_localisation newLoc;

        if (map.soils[y][x] == ERG) {
            newLoc = ergMove(loc, movement);
        } else {
            newLoc = move(loc, movement);
        }

        if (
                newLoc.pos.x >= 0 && newLoc.pos.y >= 0 &&
                newLoc.pos.x < map.x_max && newLoc.pos.y < map.y_max
                ) {
            node->sons[index++] = buildTreeRec(node, map, tree, newLoc, depth + 1, visited);
        } else {
            node->sons[index++] = NULL;
        }
    }

    return node;
}

p_tree buildTree(t_map map, int maxDepth, t_localisation iniLoc) {
    p_tree tree = createTree(iniLoc);
    tree->max_depth = maxDepth;

    // Allocation de la mémoire pour un tableau de suivi des positions visitées
    int **visited = calloc(map.y_max, sizeof(int *));
    for (int i = 0; i < map.y_max; i++) {
        visited[i] = calloc(map.x_max, sizeof(int));
    }

    // Construire l'arbre à partir de la position initiale
    tree->root->num_sons = (U_TURN - F_10 + 1);
    tree->root->sons = calloc(tree->root->num_sons, sizeof(p_node));

    for (t_move movement = F_10; movement <= U_TURN; movement++) {
        t_localisation newLoc = move(iniLoc, movement);

        if (
                newLoc.pos.x >= 0 && newLoc.pos.y >= 0 &&
                newLoc.pos.x < map.x_max && newLoc.pos.y < map.y_max
                ) {
            tree->root->sons[movement] = buildTreeRec(tree->root, map, tree, newLoc, 1, visited);
        } else {
            tree->root->sons[movement] = NULL;
        }
    }

    // Libérer la mémoire du tableau visited
    for (int i = 0; i < map.y_max; i++) {
        free(visited[i]);
    }
    free(visited);

    return tree;
}
void printTree(p_node node, int depth) {
    if (node->depth == 5) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("Node at (%d, %d) with cost %d\n", node->loc.pos.x, node->loc.pos.y, node->cost);

    for (int i = 0; i < node->num_sons; i++) {
        printTree(node->sons[i], depth + 1);
    }
}