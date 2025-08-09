#include "PlayerDeck.h"
#include <iostream>
#include <iterator>
#include <map>
#include <algorithm>



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

    std::map<Color, std::vector<std::string>> colorGroups;

    colorGroups[Color::RED] = {};
    colorGroups[Color::BLUE] = {};
    colorGroups[Color::GREEN] = {};
    colorGroups[Color::YELLOW] = {};
    colorGroups[Color::NONE] = {}; 
    
    
    for (const auto& card : deck) {
        Color color = card->getColor();
        std::string label = card->LabeltoString();
        
        
        if (label.length() > 7) {
            label = label.substr(0, 6) + ".";
        }
        
        colorGroups[color].push_back(label);
    }
    
    size_t maxCards = 0;
    for (const auto& [color, cards] : colorGroups) {
        maxCards = std::max(maxCards, cards.size());
    }
    

    
    // Print header
    std::cout << std::format("{:^10} {:^10} {:^10} {:^10} {:^10}", 
                            "RED", "GREEN", "BLUE", "YELLOW", "SPECIAL") << std::endl;
    
    // Print divider
    std::cout << std::string(50, '-') << std::endl;
    
    // Print cards row by row
    for (size_t row = 0; row < maxCards; ++row) {
        // Top border row
        std::cout << "| ";
        for (const auto& [color, cards] : colorGroups) {
            if (row < cards.size()) {
                std::cout << std::format("┌───────┐ ");
            } else {
                std::cout << std::format("{:^9} ", "");
            }
        }
        std::cout << "|" << std::endl;
        
        // Label row
        std::cout << "| ";
        for (const auto& [color, cards] : colorGroups) {
            if (row < cards.size()) {
                std::cout << std::format("|{:^7}| ", cards[row]);
            } else {
                std::cout << std::format("{:^9} ", "");
            }
        }
        std::cout << "|" << std::endl;
        
        // Bottom border row
        std::cout << "| ";
        for (const auto& [color, cards] : colorGroups) {
            if (row < cards.size()) {
                std::cout << std::format("└───────┘ ");
            } else {
                std::cout << std::format("{:^9} ", "");
            }
        }
        std::cout << "|" << std::endl;
        
        // Add spacing between card rows (except for last row)
        if (row < maxCards - 1) {
            std::cout << "| ";
            for (size_t i = 0; i < 5; ++i) {
                std::cout << std::format("{:^9} ", "");
            }
            std::cout << "|" << std::endl;
        }
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

Color PlayerDeck::MostCommonColorinDeck()
{
    std::map<Color, int> colorfreq = {
        {Color::RED, 0},
        {Color::GREEN, 0},
        {Color::BLUE, 0},
        {Color::YELLOW, 0},
    };

    for (const auto& card : deck)
    {
        Color color = card->getColor();
        if (color != Color::NONE)
            colorfreq[color]++;
    }
    

    auto it = std::max_element(
        colorfreq.begin(), 
        colorfreq.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; }
    );

    return it->first;
}