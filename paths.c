#include "paths.h"

p_node findMinimalNode(p_node node, int* min_cost, p_node currentMin) {

    if (!node) return currentMin;


    if (node->terrain_cost < *min_cost || //le coût est infereur au coût minimal actuel
        (node->terrain_cost == *min_cost && // ou le coût est égal au coût minimal actuel
         (currentMin == NULL || node->depth < currentMin->depth))) { // et la profondeur est inférieure à la profondeur minimale actuelle (si les coût sont égaux)
        *min_cost = node->terrain_cost; //on met à jour le coût minimal
        currentMin = node;
    }

    for (int i = 0; i < node->nb_sons; i++) { //parcourt tous les fils du noeud
        currentMin = findMinimalNode(node->sons[i], min_cost, currentMin);
    }

    return currentMin;
}


p_node findBestNode(t_tree *tree) {
    if (tree == NULL || tree->root == NULL) return NULL; //est-ce que l'arbre existe

    int min_cost = COST_UNDEF;  // Coût initial très élevé comme ca ca prends un nouveau minimum
    return findMinimalNode(tree->root, &min_cost, NULL);
}

t_stack extractPath(p_node node, p_tree tree)
{
    t_stack path = createStack(6); //6 psk max_depth = 5 et on prend la racine dont la depth = 0

    p_node current = node;
    while (current != tree->root)
    {
        push(&path, current->move); //on ajoute le mouvement dans le stack
        current = current->parent; //on remonte dans l'arbre
    }

    t_stack final_path = createStack(6);

    while (path.nbElts > 0) //on inverse le chemin psk on veut de la racine au noeud
    {
        t_move move = pop(&path);
        push(&final_path, pop(&path)); //on inverse le stack
    }
    return final_path;
}

t_stack findBestPath(t_tree *tree)
{
    p_node bestNode = findBestNode(tree);
    return extractPath(bestNode, tree);
}

void printBestPath(t_stack path) {
    printf("Chemin optimal (racine → nœud) :\n");
    while (path.nbElts > 0) {
        // Dépiler un élément de la pile
        t_move move = pop(&path);
        // Afficher le mouvement sous forme de chaîne
        printf("%s -> ", getMoveAsString(move));
    }
    printf("FIN\n");
}


