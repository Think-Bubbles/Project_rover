#ifndef UNTITLED1_CARDPICK_H
#define UNTITLED1_CARDPICK_H

#endif //UNTITLED1_CARDPICK_H

#include "moves.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//------------- Variable definitions ------------
typedef struct Card_Node {
    t_move data; /// Stores card information.
    struct Card_Node* prev; /// Pointer to the previous node in the list.
    struct Card_Node* next; /// Pointer to the next node in the list.
} Card_Node;

typedef Card_Node** Card_deck; /// Defines a pointer to a pointer to a Card_Node (representing the deck).
typedef Card_Node** Card_hand; /// Defines a pointer to a pointer to a Card_Node (representing a hand of cards).

static int NUMBER_OF_MOVE = 5;
//-----------------------------------------------

//------- Functions to creates cards and Deck ------------

/**
 * @brief Creates a new card node, this structure contains the data, a pointer to a previous node, and a pointer to a next node
 *
 * @param data The card data to be stored in the node.
 * @return Pointer to the newly created Card_Node.
 */
Card_Node* create_node(t_move data);

/**
 * @brief Inserts a card node at the head of the deck (a standard linked list).
 *
 * @param deck Pointer to the deck (head of the list) where the node will be inserted.
 * @param data The card data to be inserted.
 */
void insert_at_head(Card_deck deck, t_move data);

/**
 * @brief Initializes a new card deck.
 *
 * @param newDeck Pointer to the new deck to be initialized.
 * @return Pointer to the initialized deck.
 */
Card_deck initializeDeck(Card_deck newDeck);

//----------------------------------------

//-------- Test Functions ---------

/**
 * @brief Converts card data to a string representation.
 *
 * @param m The card data to be converted.
 * @return String representation of the card.
 */
const char* getCardString(t_move m);

/**
 * @brief Prints the linked list from head to tail.
 *
 * @param head Pointer to the head of the list.
 */
void print_list_from_head(Card_Node* head);

//---------------------------------

/**
 * @brief Draws a card from the deck and updates the card data.
 *
 * @param deck Pointer to the deck from which the card is drawn.
 * @param card Pointer to the card data where the drawn card will be stored (standard array).
 */
void DrawCard(Card_deck, t_move*);

/**
 * @brief Removes a possibility from the list of possible moves.
 *
 * @param possibilities Array of possible moves.
 * @param len Length of the array of possible moves.
 * @param idx Index of the move to be removed.
 * @return Reduced array of possible moves without the removed move.
 */
t_move* remove_possibility(t_move* possibilities, int len, int idx);