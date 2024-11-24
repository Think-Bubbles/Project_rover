#ifndef PROJECT_ROVER_CARDPICKER_H
#define PROJECT_ROVER_CARDPICKER_H

#include "moves.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//------------- Variable definitions ------------

typedef struct Card_Node {
    t_move data;
    struct Card_Node* prev;
    struct Card_Node* next;
} Card_Node;

typedef Card_Node** Card_deck; // A list containing pointers to card_nodes
typedef Card_Node** Card_hand; // A list containing pointers to card_nodes

//-----------------------------------------------

//------- Functions to creates cards and Deck ------------

/**
* @brief Creates a new Card_Node structure
* @param t_move : The type of move the card represents
* @return A pointer to the created node
*/
Card_Node* create_node(t_move);

/**
* @brief Inserts a new card node at the start of the deck
* @param Card_deck : The card deck where the new card node will be placed
* @param t_move : The type of move the card inserted to the deck represents
*/
void insert_at_head(Card_deck, t_move);

/**
* @brief Initialize a new card deck with a certain distribution of card types
* @return The initialized card deck
*/
Card_deck initializeDeck();

//----------------------------------------

//-------- Test Functions ---------

/**
* @brief Gets the string representation of a Card move
* @param t_move : The Card move to represent as a string
* @return A pointer to the string representation of the Card move
*/
const char* getCardString(t_move);

/**
* @brief Prints all the cards present from the head of the deck
* @param Card_Node* : The starting node from which cards will be printed
*/
void print_list_from_head(Card_Node*);

//---------------------------------

/**
* @brief Draw 9 cards from the Card deck and update the player's hand
* @param Card_deck : The Card deck from which the cards will be drawn
* @param t_move* : A pointer to the player's hand which will be updated with the drawn cards
*/
void DrawCard(Card_deck, t_move*);

#endif //PROJECT_ROVER_CARDPICKER_H
