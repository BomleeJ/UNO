#include "DiscardPile.h"


void DiscardPile::add(Card* card)
{
    deck.push_back(card);
}

Card* DiscardPile::top()
{
    return deck.back();
}

size_t DiscardPile::size() 
{
    return deck.size();
}

DiscardPile::~DiscardPile()
{   
    size_t size = deck.size();
    for(size_t i = 0; i < size; i++)
    {
        delete deck[i];
        deck[i] = nullptr;
    }
    
}