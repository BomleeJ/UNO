#include "UNOGame.h"
#include <iostream>
#include <limits>

UNOGame::UNOGame(int cpu):
played { }, 
numCPU { cpu },
todraw { },
Players(cpu, todraw)
{ }

int UNOGame::safeInputInt(int min, int max) {
    int value;

    while (true) {
        if (std::cin >> value) { //  Valid integer?
            if (value >= min && value <= max) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Flush extras
                return value;
            } else {
                std::cout << "Please enter a number between " << min << " and " << max << ".\n";
            }
        } else {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Flush bad input
        }
    }
}


void UNOGame::printStartMenu()
{
    
        std::cout << R"(
    
     _    _  _   _   ___   
    | |  | || \ | | / _ \ 
    | |  | ||  \| || | | |
    | |__| || |\  || |_| |
     \____/ |_| \_| \____/  
    
      C++  U N O   E D I T I O N
    ------------------------------------
      1. Start Game
      2. Rules
      3. Quit
    ------------------------------------
    Select an option: 
    )" << std::endl;

}

int UNOGame::StartMenu()
{
    printStartMenu();

    int response = safeInputInt(1, 3);
    
    return response;
    
}

void UNOGame::PlayerAddCard()
{
    Player* CurrentPlayer = Players.CurrentPlayer();
    std::cout << "Which Card which you like to remove? ";
    while (true) 
    {
        int play;
        std::cin >> play;
        if (CurrentPlayer->choices.count(play))
        {
            CurrentPlayer->discardCard(play, played);
            break;
        } 
        else
        {
            std::cout << "Invalid Input, Try Again";
        }
       
    }
}

void UNOGame::printPlayable()
{
    Human* CurrentPlayer = dynamic_cast<Human*>(Players.CurrentPlayer());
    CurrentPlayer->printPlayable();
}

void UNOGame::playerSequence()
{   
    std::cout << "MOST RECENT CARD: ";
    played.top()->printFancy();

    printPlayable();

    Human* CurrentPlayer = dynamic_cast<Human*>(Players.CurrentPlayer());

    std::cout << R"(
        1. Draw
        2. Play
        3. Show all Cards
        )";

    while (true)
    {


        int response = safeInputInt(1, 3);

        switch (response)
        {
        case 1:
            CurrentPlayer->drawCard(todraw);
            break;
        case 2:
            PlayerAddCard();
            break;
        case 3:
            CurrentPlayer->print();
            playerSequence();
            break;
        }
        break;
    }

}


void UNOGame::CPUSequence()
{
   
    CPU* CurrentPlayer = dynamic_cast<CPU*>(Players.CurrentPlayer());

    int cardIDX = CurrentPlayer->CPUAlgorithm(played, todraw);

    if (cardIDX >= 0)
    {
        CurrentPlayer->discardCard(cardIDX, played);
    }

    std::cout << "CPU PLAYED";
    
}

void UNOGame::GameLoop()
{
    while(true)
    {
        if(Players.CurrentPlayerEmpty())
        {
            std::cout << "Game Over";
            break;
        }

        if(Players.CurrentPlayer()->ishuman()) 
        { 
            playerSequence(); 
        }
        else
        {
            CPUSequence();
        }
        
        Players.advance();
    }
}

#include <iostream>

int UNOGame::printRulesAndConfirm() {
    std::cout << R"(
=======================================
               U N O
=======================================

- Each player starts with 7 cards.
- Match cards by color or number.
- Use special cards to skip, reverse, or make others draw cards.
- First player to get rid of all their cards wins.
- If you can't play a card, you must draw from the pile.

Do you still want to play?
Press Y to play, or any other key to quit: 
)";

    char response;
    std::cin >> response;

    if (response == 'Y' || response == 'y') {
        return 1; // Play
    } else {
        return 3; // Quit
    }
}

void UNOGame::StartGame()
{
    int menu_response = StartMenu();
    while(true)
    {
        if(menu_response == 2)
        {
            menu_response = printRulesAndConfirm();
        }
        
        switch (menu_response)
        {
        case 1: 
            break;
        case 3:
            return;
        }
        break;
    }

    GameLoop();
}