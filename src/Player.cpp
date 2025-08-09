#include "../include/Player.h"

Player::Player(): hasDrawn(false) { }

void Player::drawCard(DrawDeck& HiddenCards)
{
    deck.add(HiddenCards.draw());
    hasDrawn = true;
}

void Player::drawSevenCards(DrawDeck& HiddenCards)
{
    for (int i = 0; i < 7; i++)
        drawCard(HiddenCards);
}

std::unique_ptr<Card> Player::removeCard(size_t idx)
{
    return std::move(deck.remove(idx));
}

void Player::discardCard(size_t idx, DiscardPile& DiscardPile)
{
    DiscardPile.add(removeCard(idx));
}

void Player::refreshPlayableCards(DiscardPile& pile)
{
   choices = deck.filter_playable(pile);
}

bool Player::hasPlayableCards()
{
    return !choices.empty();
}

bool Player::hasWon() 
{ 
    return hasDrawn && deck.empty();
}

bool Player::ishuman() const
{
    return false;
}

bool Human::ishuman() const
{
    return true;
}

void Human::printPlayable()
{
    deck.printPlayable(choices);
}

void Human::print()
{
    deck.print();
}



PlayableCards CPU::filterForSpecial()
{
    PlayableCards specialCards;
    for (const auto [key, val] : choices)
    {
        if (val->isspecial())
        {
            specialCards[key] = val;
        }
    }
    return specialCards;
}

int CPU::selectRandom(PlayableCards special)
{
    std::vector<int> cards;

    for (const auto [key, val] : special)
    {
        cards.push_back(key);
    }

    int randomIndex = std::rand() % cards.size();
    return cards[randomIndex];

}

int CPU::selectRandom()
{
    std::vector<int> cards;

    for (const auto [key, val] : choices)
    {
        cards.push_back(key);
    }

    int randomIndex = std::rand() % cards.size();
    return cards[randomIndex];
}



int CPU::CPUAlgorithm(DiscardPile& pile, DrawDeck& HiddenCards) 
{
refreshPlayableCards(pile);

if (!hasPlayableCards()) 
{ 
    drawCard(HiddenCards); 
    refreshPlayableCards(pile);
    if(!hasPlayableCards()) { return -1; }
    
}


PlayableCards specialCards = filterForSpecial();
int index;
if (!specialCards.empty())
{
    index = selectRandom(specialCards);  
} 
else 
{ 
    index = selectRandom(); 
}

return index;

}

Color Player::MostCommonColorinDeck()
{
    return deck.MostCommonColorinDeck();
}