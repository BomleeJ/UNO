#include "DrawDeck.h"
#include <algorithm>
#include <random>

DrawDeck::DrawDeck()
{
    // for each regular color 
    // create two of each card
    for (int i = static_cast<int>(Color::RED); i <= static_cast<int>(Color::YELLOW); i++ )
    {   
        Color color = static_cast<Color>(i);
        for (int j = static_cast<int>(Label::Zero); j <= static_cast<int>(Label::DrawTwo); j++ )
        {   
            Label label = static_cast<Label>(j);
            Card* card1 = new Card(color, label);
            Card* card2 = new Card(color, label);
            
            deck.push_back(card1);
            deck.push_back(card2);
        }

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

Card* DrawDeck::draw()
{
    Card* back = deck.back();
    deck.pop_back();
    return back; 

}

Card* DrawDeck::top()
{
    return deck.back();
}

size_t DrawDeck::size()
{
    return deck.size();
}

DrawDeck::~DrawDeck()
{   
    size_t size = deck.size();
    for(size_t i = 0; i < size; i++)
    {
        delete deck[i];
        deck[i] = nullptr;
    }
    
}