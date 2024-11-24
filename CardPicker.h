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

Card_Node* create_node(t_move data); // Function to create a new card node
void insert_at_head(Card_deck deck, t_move data); // Function to insert the Card Node at the head of the Card Deck
Card_deck initializeDeck(); // Function to initialize a new Card Deck

//----------------------------------------

//-------- Test Functions ---------

const char* getCardString(t_move m); // Function to get the string representation of card move
void print_list_from_head(Card_Node* head); // Function to print the list of cards in the deck from the head of list

//---------------------------------

void DrawCard(Card_deck, t_move*); // function reads nine cards from the deck, removing them from the deck and adding them to the hand. It prints out every drawn card

#endif //PROJECT_ROVER_CARDPICKER_H
