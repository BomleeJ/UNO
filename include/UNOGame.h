#include "Player.h"
#include "DiscardPile.h"
#include "DrawDeck.h" 
#include "Playloop.h"


class UNOGame
{
private:
    DiscardPile played;
    DrawDeck todraw;
    int numCPU;
    PlayLoop Players;

    void printPlayerChoices();

    int safeInputInt(int min, int max);

    void printRecentlyPlayed();

    void printPlayable();

    void printUnPlayable();

    void printStartMenu();

    void PlayerAddCard();

    int printRulesAndConfirm();


public:

UNOGame(int CPU); //creates neccesary game objects

void GameLoop();

void StartGame(); //Create Decks, Create Players

int StartMenu();

void playerSequence();

void CPUSequence();
};

