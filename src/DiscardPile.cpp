#include "DiscardPile.h"


void DiscardPile::add(std::unique_ptr<Card> card)
{
    deck.push_back(std::move(card));
}

const Card& DiscardPile::top()
{
    return *deck.back();
}

size_t DiscardPile::size() 
{
    return deck.size();
}