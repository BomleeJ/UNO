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
    bool winner;

    //START MENU
    void printStartMenu();
    void printRules();
    int StartMenuResponse();

    //GAME LOOP
    void firstDraw();
    void CPUTurnSequence();
    void HumanTurnSequence();
    void HumanPlayCardSequence(Human* CurrentPlayer);
    void HumanDrawCardSequence(Human* CurrentPlayer);
    void ApplyCardEffects();
    void CheckForWin();

    void HumanWildCardSequence();
    void CPUWildCardSequence();
    void WildCardColorChange(Color newColor);

    void StartMenuLoop();
    void GameLoop();
    void EndScreen();

public:

UNOGame(int CPU); //creates neccesary game objects

void RunGame();


};
