/*
This is the Deck that Players and CPUs can Draw from
*/
#pragma once
#include <vector>
#include "Card.h"

class DrawDeck {

std::vector<Card*> deck;

void shuffle();

public:
    DrawDeck();

    Card* draw();

    Card* top();

    size_t size();

    ~DrawDeck();

};