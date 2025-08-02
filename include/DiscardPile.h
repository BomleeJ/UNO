#pragma once
#include <vector>
#include "Card.h"
#include <memory>

class DiscardPile {

std::vector<std::unique_ptr<Card>> deck;

public:

    void add(std::unique_ptr<Card> card);

    const Card& top();

    size_t size();

};