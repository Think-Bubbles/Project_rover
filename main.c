#include <stdio.h>
#include "map.h"
#include "CardPicker.h"

int main() {
    t_map map;

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#elif defined(__APPLE__) || defined(__MACH__)
    map = createMapFromFile("../maps/example1.map");
#else
    printf("Système d'exploitation non reconnu.\n");
#endif




    srand(time(NULL)); // Initialise a random number generator

    int edge = rand() % 4; // Generate a number between 1 and 4 to decide which side the rover is on
    t_localisation rover;

    switch (edge) // Filter through each case
    {
        case 0: // Top edge
            rover = loc_init(rand() % map.x_max, 0, rand() % 4);
            break;
        case 1: // Right edge
            rover = loc_init(map.x_max - 1, rand() % map.y_max, rand() % 4);
            break;
        case 2: // Bottom edge
            rover = loc_init(rand() % map.x_max, map.y_max - 1, rand() % 4);
            break;
        default: // Left edge
            rover = loc_init(0, rand() % map.y_max, rand() % 4);
            break;
    } while (map.soils[rover.pos.y][rover.pos.x] == CREVASSE); // In case the rover starts in a crevasse, we regenerate the position


    printf("Here is a %d x %d map : \n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            if (i == rover.pos.y && j == rover.pos.x) printf("R "); // print R for rover's position
            else printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }


    printf("\nNow here is the map represented through costs : \n");
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            if (i == rover.pos.y && j == rover.pos.x) printf("(R%-2d) ", map.costs[i][j]);  // print 'R' along with cost at the rover's position
             else printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);

    //---- Part to test card picker ----
    Card_deck test = initializeDeck();
    print_list_from_head(*test);

    t_move testHand[9];
    DrawCard(test,testHand);

    printf("\n");
    //print hand
    for (int i = 0; i < 9; i++) {
        printf("%s ", getCardString(testHand[i]));
    }
    //----------------------------------

    return 0;
}
