#include "CardPicker.h"

//------- Functions to creates cards and Deck ------------

Card_Node* create_node(t_move data) {
    Card_Node* new_node = malloc(sizeof(Card_Node)); // Allocate memory for a new Card Node
    new_node->data = data; // Assign the data value to the new node
    new_node->prev = NULL; // Initialize the node's previous pointer to NULL
    new_node->next = NULL; // Initialize the node's next pointer to NULL
    return new_node;
}

void insert_at_head(Card_deck deck, t_move data) {
    Card_Node* new_node = create_node(data); // Create a new node with the provided data
    if (*deck != NULL) { // If the deck already contains nodes
        (*deck)->prev = new_node; // update the previous pointer of the current head of the deck to point to the new node
    }
    new_node->next = *deck; // The deck is empty so simply set the current head to the new node
    *deck = new_node;
}

//----------------------------------------

Card_deck initializeDeck() {
    Card_deck newDeck;
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

void DrawCard(Card_deck deck, t_move* hand)
{

    int CardNumber = 100;
    srand(time(0)^ getpid());

    for (int i = 0; i < 9; ++i) {

        int temp = rand() % (CardNumber + 1); // generate a random number between 0 and cardnumber+1
        Card_Node *n = *deck; // Set a node to the head of the deck
        for (int j = 0; j < temp-1; ++j) {
            n = n->next;
        }
        printf("Card drawn: %s\n", getCardString(n->data));
        hand[i] = n->data;

        // Remove the card from the deck
        if (n->prev != NULL) { // If the drawn card is not the first one in the deck,
            n->prev->next = n->next;  // link the previous card with the next card to remove the drawn card from the deck
        }
        else { // If the drawn card is the first one,
            *deck = n->next; // set the next card to be the head of the deck
        }

        for (int skip = 0; skip < 3; skip++) rand();
        // Generate numbers to move the rand() internal pointer to increase randomness

        CardNumber--; // Decrease the total number of cards after drawing
    }
}