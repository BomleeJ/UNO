#include "Playloop.h"
#include "Player.h"
#include "DrawDeck.h"
#include <iostream>
#include <memory>

PlayLoop::PlayLoop(size_t CPUnum, DrawDeck& Deck):
numPlayers(CPUnum + 1),
currentPlayer(0),
direction(1)
{
    players.push_back(std::make_unique<Human>());
    for (size_t i = 1; i < numPlayers; ++i) {
        players.push_back(std::make_unique<CPU>());
    }

    for (auto& player : players) {
        player->drawSevenCards(Deck);
    }
}

Player* PlayLoop::CurrentPlayer() {
    return players[currentPlayer].get();
}

Player* PlayLoop::NextPlayer()
{
    return players[(numPlayers + currentPlayer + direction) % numPlayers].get();
}

size_t PlayLoop::CurrentPlayerIndex()
{
    return currentPlayer;
}

size_t PlayLoop::NextPlayerIndex()
{
    return (numPlayers + currentPlayer + direction) % numPlayers;
}

void PlayLoop::SkipTurn() {
    AdvanceTurn();
    AdvanceTurn();
}

void PlayLoop::AdvanceTurn() {
    currentPlayer = (numPlayers + currentPlayer + direction) % numPlayers;
}

void PlayLoop::ReverseDirection() {
    direction = -direction;
}

void PlayLoop::AddFourtoNextPlayer(DrawDeck& Deck) {
    NextPlayer()->drawCard(Deck);
    NextPlayer()->drawCard(Deck);
    NextPlayer()->drawCard(Deck);
    NextPlayer()->drawCard(Deck);
}

void PlayLoop::AddTwotoNextPlayer(DrawDeck& Deck) {
    NextPlayer()->drawCard(Deck);
    NextPlayer()->drawCard(Deck);
}