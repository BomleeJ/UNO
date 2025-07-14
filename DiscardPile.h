#pragma once
#include <vector>
#include "Card.h"

class DiscardPile {

std::vector<Card*> deck;

public:

    void add(Card* card);

    Card* top();

    size_t size();

    ~DiscardPile();
};