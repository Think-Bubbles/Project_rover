//
// Created by batur on 11.11.2024.
//

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
    t_move data;
    struct Card_Node* prev;
    struct Card_Node* next;
} Card_Node;

typedef Card_Node** Card_deck;
typedef Card_Node** Card_hand;

static int NUMBER_OF_MOVE = 5;
//-----------------------------------------------

//------- Functions to creates cards and Deck ------------
Card_Node* create_node(t_move data);
void insert_at_head(Card_deck deck, t_move data);
Card_deck initializeDeck(Card_deck newDeck);
//----------------------------------------

//-------- Test Functions ---------
const char* getCardString(t_move m);
void print_list_from_head(Card_Node* head);
//---------------------------------

void DrawCard(Card_deck, t_move*);
t_move* remove_possibility(t_move* possibilities, int len, int idx);