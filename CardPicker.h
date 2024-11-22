//
// Created by batur on 22.11.2024.
//

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

typedef Card_Node** Card_deck;
typedef Card_Node** Card_hand;
//-----------------------------------------------

//------- Functions to creates cards and Deck ------------
Card_Node* create_node(t_move data);
void insert_at_head(Card_deck deck, t_move data);
Card_deck initializeDeck();
//----------------------------------------

//-------- Test Functions ---------
const char* getCardString(t_move m);
void print_list_from_head(Card_Node* head);
//---------------------------------

void DrawCard(Card_deck, t_move*);

#endif //PROJECT_ROVER_CARDPICKER_H
