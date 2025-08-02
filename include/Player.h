#pragma once
#include "PlayerDeck.h"
#include "DrawDeck.h"
#include "DiscardPile.h"
#include <memory>
class Player {

public:
Player();

PlayerDeck deck;
PlayableCards choices;
bool hasDrawn;

void drawCard(DrawDeck& HiddenCards);

void drawSevenCards(DrawDeck& HiddenCards);

std::unique_ptr<Card> removeCard(size_t idx);

void discardCard(size_t idx, DiscardPile& DiscardPile);

bool hasPlayableCards();

void refreshPlayableCards(DiscardPile& DiscardPile);

bool hasWon();

virtual bool ishuman() const;

};

class Human : public Player
{
private:


public:
void printPlayable();

void print();

bool ishuman() const override;
};

class CPU : public Player
{
private:
    PlayableCards filterForSpecial();

    int selectRandom(PlayableCards special);
    int selectRandom();
public: 
    int CPUAlgorithm(DiscardPile& DiscardPile, DrawDeck& HiddenCards); 

};