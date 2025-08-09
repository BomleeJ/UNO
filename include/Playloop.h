#pragma once
#include "Player.h"

class PlayLoop
{
private:
    std::vector<std::unique_ptr<Player>> players;
    size_t numPlayers;
    size_t currentPlayer;
    size_t direction;

public:

    PlayLoop(size_t CPU, DrawDeck& Deck);
    Player* CurrentPlayer();
    void SkipTurn();
    void AdvanceTurn();
    void ReverseDirection();
    void AddFourtoNextPlayer(DrawDeck& Deck);
    void AddTwotoNextPlayer(DrawDeck& Deck);
    size_t CurrentPlayerIndex();
    size_t NextPlayerIndex();
    Player* NextPlayer();

};