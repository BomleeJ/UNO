#include "PlayerDeck.h"
#include <iostream>




PlayerDeck::PlayerDeck(DrawDeck& Drawdeck)
{
    int start_cards = 7;
    for(int i = 0; i < start_cards; i++)
    {
        Card* card = Drawdeck.draw();
        deck.push_back(card); 
    }
}

void PlayerDeck::print()
{
    for (Card* card : deck)
    {
        card->print();
    }
}

Card* PlayerDeck::remove(size_t idx)
{   
    size_t curr = 0;
    for (Card* card : deck )
    {
        if(curr == idx)
        {
            return card;
        }
        curr++;
    }
    return nullptr;
}

PlayableCards PlayerDeck::filter_playable(Card* other)
{
    PlayableCards playable;
    int idx = 0;
    for (Card* card : deck)
    {
        if(card->isvalid(other));
        {
            playable[idx] = card;
        }

    }
    return playable;
}

void PlayerDeck::print(PlayableCards playable)
{
    for (const auto [key, value] : playable)
    {
        std::cout << "INDEX: " << key << " CARD: ";
        value->print();
        std::cout << std::endl;
    }
}

PlayerDeck::~PlayerDeck()
{
    for (auto card : deck)
    {
        delete card;
        card = nullptr;
    }
}