#include "DrawDeck.h"
#include <algorithm>
#include <random>

DrawDeck::DrawDeck()
{
    // for each regular color create two of each card
    for (int i = static_cast<int>(Color::RED); i <= static_cast<int>(Color::YELLOW); i++ )
    {   
        Color color = static_cast<Color>(i);
        for (int j = static_cast<int>(Label::Zero); j <= static_cast<int>(Label::DrawTwo); j++ )
        {   
            Label label = static_cast<Label>(j);
            deck.push_back(std::make_unique<Card>(color, label));
            deck.push_back(std::make_unique<Card>(color, label));
        }
    }

    for (size_t idx = 0; idx < 4; idx++)    
    {
        deck.push_back(std::make_unique<Card>(Color::NONE, Label::Wild));
        deck.push_back(std::make_unique<Card>(Color::NONE, Label::WildDrawFour));
    }

    shuffle();

}

void DrawDeck::shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());

    for (size_t i = deck.size() - 1; i > 0; i--)
    {
        std::uniform_int_distribution<> dist(0, i);
        size_t j = dist(g);
        std::swap(deck[i], deck[j]);        // swap current card with random earlier card
    }
}

void DrawDeck::replenish()
{
    DrawDeck newDeck;
    deck = std::move(newDeck.deck);
}

std::unique_ptr<Card> DrawDeck::draw()
{
    if (deck.empty())
    {
        replenish();
    }

    std::unique_ptr<Card> back = std::move(deck.back());
    deck.pop_back();
    return back; 

}

const Card& DrawDeck::top() const
{
    return *deck.back();
}

size_t DrawDeck::size() const
{
    return deck.size();
}

