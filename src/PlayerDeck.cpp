#include "PlayerDeck.h"
#include <iostream>
#include <iterator>




PlayerDeck::PlayerDeck()
{

}

void PlayerDeck::initial_fill(DrawDeck& Drawdeck)
{
    int start_cards = 7;
    for(int i = 0; i < start_cards; i++)
    {
        std::unique_ptr<Card> card = Drawdeck.draw();
        deck.push_back(std::move(card)); 
    }
}

void PlayerDeck::add(std::unique_ptr<Card> card)
{
    deck.push_back(std::move(card));
}

void PlayerDeck::print()
{
    for (const auto& card : deck)
    {
        card->print();
    }
}

size_t PlayerDeck::size()
{
    return deck.size();
}

std::unique_ptr<Card> PlayerDeck::remove(size_t idx)
{   
    if (idx >= deck.size())
    {
        throw std::out_of_range("Index out of range");
    }
    auto it = deck.begin();
    std::advance(it, idx);
    std::unique_ptr<Card> card = std::move(*it);
    deck.erase(it);
    return card;   
}

PlayableCards PlayerDeck::filter_playable(DiscardPile& pile)
{
    const Card& other = pile.top();
    PlayableCards playable;
    int idx = 0;
    for (const auto& card : deck)
    {
        if(card->isvalid(other))
        {
            playable[idx] = card.get();
        }
        idx++;
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

