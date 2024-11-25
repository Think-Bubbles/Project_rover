#include <stdio.h>
#include "stack.h"
#include "paths.h"
#include "map.h"
#include "CardPicker.h"
#include "moves.h"
#include "tree.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>  // For usleep function


t_localisation initialiseRoverStart(t_map map);

void DisplayCostMap(t_map map, t_localisation rover);

void printWithDelay(const char* text, int delayMilliSeconds) {
    while (*text) {
        printf("%c", *text++);
        fflush(stdout);
        usleep(delayMilliSeconds);
    }
}

void printIntro() {

    printWithDelay("Starting Mars Rover Simulation...\n", 100);  // Print letter by letter

    usleep(500);

    const char* intro_lines[] = {
            " __  __                  ____                     \n",
            "|  \\/  | __ _ _ __ ___  |  _ \\ _____   _____ _ __ \n",
            "| |\\/| |/ _` | '__/ __| | |_) / _ \\ \\ / / _ \\ '__|\n",
            "| |  | | (_| | |  \\__ \\ |  _ < (_) \\ V /  __/ |   \n",
            "|_|  |_|\\__,_|_|  |___/ |_| \\_\\___/ \\_/ \\___|_|   \n"
    };

    for (int i = 0; i < sizeof(intro_lines) / sizeof(intro_lines[0]); i++) {
        printWithDelay(intro_lines[i], 30);  // Speeding up this part further
    }

    //usleep(500); // A final pause before continuing
}

t_localisation initialiseRoverStart(t_map map) {
    int edge;
    t_localisation rover;

    do {
        edge = rand() % 4; // Generate a number between 0 and 4 to decide which side the rover is on

        switch (edge) {
            case 0: { // Top edge
                int x = rand() % map.x_max;
                int direction = rand() % 3 + 1; // 1 (EAST), 2 (SOUTH), or 3 (WEST)
                if (x == 0) { // Top left corner
                    direction = (rand() % 2) + 1; // Must face EAST (1) or SOUTH (2)
                } else if (x == map.x_max - 1) { // Top right corner
                    direction = (rand() % 2) + 2; // Must face SOUTH (2) or WEST (3)
                }
                rover = loc_init(x, 0, (t_orientation)direction);
                break;
            }
            case 1: { // Right edge
                int y = rand() % map.y_max;
                int direction = rand() % 4; // Set a default invalid direction
                while (direction == EAST) {
                    direction = rand() % 4; // 0 (NORTH), 2 (SOUTH), or 3 (WEST)
                }
                if (y == 0) { // Top right corner
                    direction = (rand() % 2) + 2; // Must face SOUTH (2) or WEST (3)
                } else if (y == map.y_max - 1) { // Bottom right corner
                    direction = rand() % 2 + 0; // Must face NORTH (0) or WEST (3)
                    if (direction == 1) direction = 3; // Adjust if random choice was invalid
                }
                rover = loc_init(map.x_max - 1, y, (t_orientation)direction);
                break;
            }
            case 2: { // Bottom edge
                int x = rand() % map.x_max;
                int direction = rand() % 4; // Set a default invalid direction
                while (direction == SOUTH) {
                    direction = rand() % 4; // 0 (NORTH), 1 (EAST), or 3 (WEST)
                }
                if (x == 0) { // Bottom left corner
                    direction = rand() % 2 + 1; // Must face EAST (1) or NORTH (0)
                    if (direction == 2) direction = 0; // Adjust if random choice was invalid
                } else if (x == map.x_max - 1) { // Bottom right corner
                    direction = rand() % 2; // Must face NORTH (0) or WEST (3)
                }
                rover = loc_init(x, map.y_max - 1, (t_orientation)direction);
                break;
            }
            default: { // Left edge
                int y = rand() % map.y_max;
                int direction = rand() % 4; // Set a default invalid direction
                while (direction == WEST) {
                    direction = rand() % 4; // 0 (NORTH), 1 (EAST), or 2 (SOUTH)
                }
                if (y == 0) { // Top left corner
                    direction = (rand() % 2) + 1; // Must face EAST (1) or SOUTH (2)
                } else if (y == map.y_max - 1) { // Bottom left corner
                    direction = rand() % 2 + 1; // Must face EAST (1) or NORTH (0)
                    if (direction == 2) direction = 0; // Adjust if random choice was invalid
                }
                rover = loc_init(0, y, (t_orientation)direction);
                break;
            }
        }
    } while (map.soils[rover.pos.y][rover.pos.x] == CREVASSE); // In case the rover starts in a crevasse, regenerate the position
    return rover;
}

void DisplayCostMap(t_map map, t_localisation rover) {
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            if (i == rover.pos.y && j == rover.pos.x) {
                char orientation;
                switch (rover.ori) {
                    case 0:
                        orientation = '^'; // North
                        break;
                    case 1:
                        orientation = '>'; // East
                        break;
                    case 2:
                        orientation = 'v'; // South
                        break;
                    case 3:
                        orientation = '<'; // West
                        break;
                    default:
                        orientation = 'R'; // Default to 'R' if something goes wrong
                }
                printf("(%-2dR%c) ", map.costs[i][j], orientation); // print 'R', then the cost along with the rover orientation at the rover's position

            } else {
                printf("%-6d ", map.costs[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {

    printIntro();
    srand(time(0)); // Initialise a random number generator
    unsigned int map_choice;

    printf("\nWhich map would you like to choose : (Choose a number between 0 and 3) \n");
    scanf("%u", &map_choice);

    // Assuming 'map' is selected based on map_choice
    t_map map;
    switch (map_choice) {
        case 0:
            map = createMapFromFile("..\\maps\\example1.map");
            break;
        case 1:
            map = createMapFromFile("..\\maps\\example2.map");
            break;
        case 2:
            map = createMapFromFile("..\\maps\\example3.map");
            break;
        case 3:
            map = createMapFromFile("..\\maps\\training.map");
            break;
        default:
            printf("Invalid choice");
            return 1;
    }

    //------ Choose the starting location of the rover ------
    unsigned int location_choice;
    printf("\nDo you want a random starting location (press 1) or the test location for the map (press 0) :  \n");
    scanf("%u", &location_choice);
    t_localisation rover; // The rover's starting location and orientation
    if(location_choice == 1) {
        rover = initialiseRoverStart(map); // Random starting location
    }
    else {
        switch (map_choice) {
            case 0:
                rover = loc_init(4,6,NORTH);
                break;
            case 1:
                rover = loc_init(8,0,SOUTH);
                break;
            case 2:
                rover = loc_init(12,0,SOUTH);
                break;
            case 3:
                rover = loc_init(0,10,NORTH);
                break;
            default:
                printf("Invalid choice");
                return 1;
        }
    }

    //-------- Display the map with the rover's position and orientation --------
    printf("Here is a %d x %d map : \n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            if (i == rover.pos.y && j == rover.pos.x) {
                char orientation;
                switch (rover.ori) {
                    case 0:
                        orientation = '^'; // North
                        break;
                    case 1:
                        orientation = '>'; // East
                        break;
                    case 2:
                        orientation = 'v'; // South
                        break;
                    case 3:
                        orientation = '<'; // West
                        break;
                    default:
                        orientation = 'R'; // Default to 'R' if something goes wrong
                }
                printf("%c ", orientation); // print arrow for rover's position
            } else {
                printf("%d ", map.soils[i][j]);
            }
        }
        printf("\n");
    }

    printf("\nNow here is the map represented through costs : \n");
    DisplayCostMap(map, rover);

    printf("\n");
    // displayMap(map);

// ---- Initialisation of variables before the loop ----
    printf("\n \n");
    t_move* testHand;
    p_tree testTree;
    p_node BestNode = NULL;
    int phase = 1;
    int stoppedAtReg = 0; // Flag to check if the rover stopped at a reg
    t_localisation phaseStartLocation = rover;
//------------------------------------------------------------

//----- Main loop of the simulation -----
    do {
        printf("Phase %d: \n", phase);

//----- Draw cards -----
        testHand = getRandomMoves(NUMBER_OF_MOVE);

        printf("Drawn cards: | ");
        //print hand
        for (int i = 0; i < NUMBER_OF_MOVE; i++) {
            printf("%s | ", getCardString(testHand[i]));
        }
        printf("\n");

//----- Create tree and calculate the best path -----
        testTree = createTree(phaseStartLocation,map,testHand,stoppedAtReg);
        stoppedAtReg = 0; // Reset the flag
        t_stack stack = findBestPath(testTree, map, &stoppedAtReg);
        printBestPath(stack);

//----- Prepare for next phase -----
        BestNode = findBestNode(testTree);
        phaseStartLocation = BestNode->localisation;
        phase++;

//----- Display the map -----
        printf("\n---------- Map ----------\n");
        DisplayCostMap(map, phaseStartLocation);
        printf("----------------------\n");
        printf("\n");

//----- Free memory -----
        free(testHand);
        deleteNode(testTree->root);
        free(testTree);

    } while(BestNode->terrain_cost != 0); // Continue until the rover reaches the base station


    return 0;
}


