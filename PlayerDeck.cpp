#include "PlayerDeck.h"
#include <iostream>




PlayerDeck::PlayerDeck()
{

}

void PlayerDeck::initial_fill(DrawDeck& Drawdeck)
{
    int start_cards = 7;
    for(int i = 0; i < start_cards; i++)
    {
        Card* card = Drawdeck.draw();
        deck.push_back(card); 
    }
}

void PlayerDeck::add(Card* card)
{
    deck.push_back(card);
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

PlayableCards PlayerDeck::filter_playable(DiscardPile& pile)
{
    Card* other = pile.top();
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

void PlayerDeck::printPlayable(PlayableCards playable)
{
    for (const auto [key, value] : playable)
    {
        std::cout << "INDEX: " << key << " CARD: ";
        value->print();
        std::cout << std::endl;
    }
}

bool PlayerDeck::empty()
{
    return deck.empty();
}

PlayerDeck::~PlayerDeck()
{
    for (auto card : deck)
    {
        delete card;
        card = nullptr;
    }
}
