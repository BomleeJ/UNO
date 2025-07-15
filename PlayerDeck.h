#pragma once
#include "Card.h"
#include "DrawDeck.h"
#include "DiscardPile.h"
#include <list>
#include <map>

using PlayableCards = std::map<int, Card*>;

class PlayerDeck 
{
private:
    std::list<Card*> deck; 

public:
    PlayerDeck();

    //filters card in the player deck 
    PlayableCards filter_playable(DiscardPile& pile);

    void initial_fill(DrawDeck& deck);

    void add(Card* card);

    Card* remove(size_t idx);

    bool empty();

    void print();

    void printPlayable(PlayableCards playable);

    ~PlayerDeck();
    

};