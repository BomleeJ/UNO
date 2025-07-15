#include "Player.h"

Player::Player() { }

void Player::drawCard(DrawDeck& HiddenCards)
{
    Card* card = HiddenCards.draw();
    deck.add(card);
}

void Player::drawSevenCards(DrawDeck& HiddenCards)
{
    for (int i = 0; i < 7; i++)
        drawCard(HiddenCards);
}

Card* Player::removeCard(size_t idx)
{
    return deck.remove(idx);
}

void Player::discardCard(size_t idx, DiscardPile& DiscardPile)
{
    Card* card = removeCard(idx);
    DiscardPile.add(card);

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
    return deck.empty();
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
Card* card = pile.top();
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

