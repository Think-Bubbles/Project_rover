#include "CardPicker.h"

//------- Functions to creates cards and Deck ------------
Card_Node* create_node(t_move data) {
    Card_Node* new_node = (Card_Node*)malloc(sizeof(Card_Node));
    new_node->data = data; /// set the given Data
    new_node->prev = NULL; /// set the previous to Null
    new_node->next = NULL; /// set the next to Null
    return new_node;
}

void insert_at_head(Card_deck deck, t_move data) {
    Card_Node* new_node = create_node(data); /// Make a new node
    if (*deck != NULL) { /// If our deck isn't empty
        (*deck)->prev = new_node; /// Take the current head of the deck, set its previous equal to our new node
    }
    new_node->next = *deck; /// Then in both cases set the next of our new node equal to the head of the deck.
    *deck = new_node;
}
//----------------------------------------


Card_deck initializeDeck(Card_deck newDeck) {
    for (int i = 0; i < 22; i++) {
        insert_at_head(newDeck,F_10);
    }
    for (int i = 0; i < 15; i++) {
        insert_at_head(newDeck,F_20);
    }
    for (int i = 0; i < 7; i++) {
        insert_at_head(newDeck,F_30);
    }
    for (int i = 0; i < 7; i++) {
        insert_at_head(newDeck,B_10);
    }
    for (int i = 0; i < 21; i++) {
        insert_at_head(newDeck,T_LEFT);
    }
    for (int i = 0; i < 21; i++) {
        insert_at_head(newDeck,T_RIGHT);
    }
    for (int i = 0; i < 7; i++) {
        insert_at_head(newDeck,U_TURN);
    }
    return newDeck;
}

//-------- Test Functions ---------

void print_list_from_head(Card_Node* head) {
    Card_Node* temp = head;
    printf("Liste : ");
    while (temp != NULL) {
        printf("%s ", getCardString(temp->data));
        temp = temp->next;
    }
    printf("\n");
}

const char* getCardString(t_move m) {
    switch(m) {
        case F_10: return "F_10";
        case F_20: return "F_20";
        case F_30: return "F_30";
        case B_10: return "B_10";
        case T_LEFT: return "T_LEFT";
        case T_RIGHT: return "T_RIGHT";
        case U_TURN: return "U_TURN";
        default: return "Unknown";
    }
}
//----------------------------------------

void DrawCard(Card_deck deck, t_move* hand) {

    int CardNumber = 100;
    srand(time(0)^ getpid());

    for (int i = 0; i < NUMBER_OF_MOVE; ++i) {

        int temp = rand() % (CardNumber + 1);
        Card_Node *n = *deck;
        for (int j = 0; j < temp-1; ++j) {
            n = n->next;
        }
        hand[i] = n->data;

        // Remove the card from the deck
        if (n->prev != NULL) {
            n->prev->next = n->next;
        }
        else {
            *deck = n->next;
        }

        for (int skip = 0; skip < 3; skip++) rand();

        CardNumber--;
    }
}

t_move* remove_possibility(t_move* possibilities, int len, int idx) {
    t_move* new_possibilities = (t_move*) malloc((len-1) * sizeof(t_move));
    int j = 0;
    for (int i = 0; i < len-1; i++){
        if (i == idx) j++;
        new_possibilities[i] = possibilities[j++];
    }
    return new_possibilities;
}