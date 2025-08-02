/*
This is the Deck that Players and CPUs can Draw from
*/
#pragma once
#include <vector>
#include "Card.h"
#include <memory>

class DrawDeck {

std::vector<std::unique_ptr<Card>> deck;

void shuffle();

public:
    DrawDeck();

    std::unique_ptr<Card> draw();

    void replenish();

    const Card& top() const;

    size_t size() const;

};