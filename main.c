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

void printWithDelay(const char* text, int delayMilliSeconds) {
    while (*text) {
        printf("%c", *text++);
        fflush(stdout);
        usleep(delayMilliSeconds);
    }
}

void printIntro() {

    printWithDelay("Starting Mars Rover Simulation...\n", 50);  // Print letter by letter

    usleep(400);

    const char* intro_lines[] = {
            " __  __                  ____                     \n",
            "|  \\/  | __ _ _ __ ___  |  _ \\ _____   _____ _ __ \n",
            "| |\\/| |/ _` | '__/ __| | |_) / _ \\ \\ / / _ \\ '__|\n",
            "| |  | | (_| | |  \\__ \\ |  _ < (_) \\ V /  __/ |   \n",
            "|_|  |_|\\__,_|_|  |___/ |_| \\_\\___/ \\_/ \\___|_|   \n"
    };

    for (int i = 0; i < sizeof(intro_lines) / sizeof(intro_lines[0]); i++) {
        printWithDelay(intro_lines[i], 10);  // Speeding up this part further
    }

    usleep(500); // A final pause before continuing
}

t_localisation initialiseRoverStart(t_map map) {
    int edge = rand() % 4; // Generate a number between 1 and 4 to decide which side the rover is on
    t_localisation rover;

    switch (edge) // Filter through each case
    {
        case 0: // Top edge
            rover = loc_init(rand() % map.x_max, 0, rand() % 3 + 1); // can't face up (0)
            break;
        case 1: // Right edge
            rover = loc_init(map.x_max - 1, rand() % map.y_max, (rand() % 3 + 1) % 4); // can't face right (1)
            break;
        case 2: // Bottom edge
            rover = loc_init(rand() % map.x_max, map.y_max - 1, (rand() % 3 + 2) % 4); // can't face down (2)
            break;
        default: // Left edge
            rover = loc_init(0, rand() % map.y_max, (rand() % 3 + 3) % 4); // can't face left (3)
            break;
    }
    while (map.soils[rover.pos.y][rover.pos.x] == CREVASSE); // In case the rover starts in a crevasse, regenerate the position
    return rover;
}

int main() {

    printIntro();

    t_map first_map = createMapFromFile("..\\maps\\example1.map");
    t_map second_map = createMapFromFile("..\\maps\\example2.map");
    t_map training_map = createMapFromFile("..\\maps\\training.map");

    unsigned int map_choice;

    printf("\nWhich map would you like to choose : (Choose a number between 0 and 2) \n");
    scanf("%u", &map_choice);

    // Assuming 'map' is selected based on map_choice
    t_map map;
    switch (map_choice) {
        case 0:
            map = first_map;
            break;
        case 1:
            map = second_map;
            break;
        case 2:
            map = training_map;
            break;
        default:
            printf("Invalid choice");
            return 1;
    }

    srand(time(NULL)); // Initialise a random number generator

    t_localisation rover = initialiseRoverStart(map);

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
                printf("(R%-2d %c) ", map.costs[i][j], orientation); // print 'R', then the cost along with the rover orientation at the rover's position
            } else {
                printf("%-5d ", map.costs[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
    displayMap(map);

    //---- Part to test card picker ----
    t_move* testHand;
    testHand = getRandomMoves(NUMBER_OF_MOVE);

    printf("\n");
    //print hand
    for (int i = 0; i < NUMBER_OF_MOVE; i++) {
        printf("%s ", getCardString(testHand[i]));
    }
    printf("\n");
    //----------------------------------
    p_tree testTree = createTree(loc_init(4,6,NORTH),map,testHand);
    printf("\n \n");
    printTree(testTree->root,0);
    t_stack stack = findBestPath(testTree);
    printBestPath(stack);
    return 0;
}
