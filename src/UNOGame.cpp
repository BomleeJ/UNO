
#include "UNOGame.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <thread>   
#include <chrono>   

UNOGame::UNOGame(int cpu):
played { }, 
numCPU { cpu },
todraw { },
Players(cpu, todraw),
winner { false }
{ }

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

void UNOGame::printRules()
{
    
    std::cout << R"(
    =======================================
                   U N O
    =======================================
    
    - Each player starts with 7 cards.
    - Match cards by color or number.
    - Use special cards to skip, reverse, or make others draw cards.
    - First player to get rid of all their cards wins.
    - If you can't play a card, you must draw from the pile.)" << std::endl;

}

void UNOGame::StartMenuLoop()
{
    printStartMenu();
    int response = 0;

    while (response != 1 && response != 3)
    {
        std::cin >> response;

        switch (response)
        {
        case 1:
            std::cout << "Starting game....";
            break;
        case 2:
            printRules();
            break;
        case 3: 
            std::exit(0);
        default:
            std::cout << "Invalid input, try again: \n";
        }
    }
    
}

void UNOGame::firstDraw()
{
    std::unique_ptr<Card> card = todraw.draw();
    played.add(std::move(card));
}

void UNOGame::HumanPlayCardSequence(Human* CurrentPlayer)
{
    std::cout << "Please select a card to play based on the index: \n";
    int cardIDX = -1;

    while (true)
    {
        std::cin >> cardIDX;
        if (CurrentPlayer->choices.count(cardIDX) == 0)
        {
            std::cout << "Invalid input, try again: \n";
        }
        else 
        {
            break;
        }
    }
    CurrentPlayer->discardCard(cardIDX, played);
    std::cout << "Turn Complete! \n";
}

void UNOGame::HumanDrawCardSequence(Human* CurrentPlayer)
{
    std::cout << "You have no playable cards, you must draw a card.\n You drew: \n";
    todraw.top().printFancy();
    CurrentPlayer->drawCard(todraw);
}

void UNOGame::HumanTurnSequence()
{
    std::cout << "The Most Recent Card is: \n";
    played.top().printFancy();

    Human* CurrentPlayer = dynamic_cast<Human*>(Players.CurrentPlayer());

    std::cout << "You have " << CurrentPlayer->deck.size() << " cards left.\n";

    std::cout << "These are the cards in your hand: \n";
    CurrentPlayer->print();

    CurrentPlayer->refreshPlayableCards(played);
    if (CurrentPlayer->hasPlayableCards())
    {
        std::cout << "Here are your playable cards: \n";
        CurrentPlayer->printPlayable();
        HumanPlayCardSequence(CurrentPlayer);
    }
    else
    {
        HumanDrawCardSequence(CurrentPlayer);
    }
    
}

void UNOGame::CPUTurnSequence()
{
    CPU* CurrentPlayer = dynamic_cast<CPU*>(Players.CurrentPlayer());
    int cardIDX = CurrentPlayer->CPUAlgorithm(played, todraw); 
    std::cout << "Player " << Players.CurrentPlayerIndex();

    if (cardIDX == -1)
    {
        std::cout << " has drawn a card\n";
        return;
    }
    else
    {
        CurrentPlayer->discardCard(cardIDX, played);
        std::cout << " has decided to play\n";
        played.top().printFancy();
    }
    
}

void UNOGame::HumanWildCardSequence()
{
    int response = -1;
    Color newColor;

    while (response < 0 || response > 3)
    {
        std::cout << "Which Color which you like to switch to?\n0. Red \n1. Green \n2. Blue \n3. Yellow\n";
        std::cin >> response;
        
        switch (response)
        {
            case 0:
                newColor = Color::RED;
                break;
            case 1:
                newColor = Color::GREEN;
                break;
            case 2:
                newColor = Color::BLUE;
                break;
            case 3:
                newColor = Color::YELLOW;
                break;
            default:
                std::cout << "Invalid Input. segmentation fault. (Just Kidding) try again.\n";
                break;
        }
    }

    WildCardColorChange(newColor);

}

void UNOGame::CPUWildCardSequence()
{
    Color newColor = Players.CurrentPlayer()->MostCommonColorinDeck();
    std::string color;

    switch (newColor)
    {
        case Color::RED:
            color = "Red";
            break;
        case Color::GREEN:
            color = "Green";
            break;
        case Color::BLUE:
            color = "Blue";
            break;
        case Color::YELLOW:
            color = "Yellow";
            break;
        default:
            color = "Invalid Color";
            break;
    }
    

    std::cout << "A wild Card was placed on the deck, the new color is " << color << '\n';
    WildCardColorChange(newColor);
}

void UNOGame::WildCardColorChange(Color newColor)
{
    Label HiddenWild = Label::WildTemp; //This WildCard is a hidden card that essentially changes the deck to be "Red"
    std::unique_ptr<Card> newCard =std::make_unique<Card>(newColor, HiddenWild);
    played.add(std::move(newCard));

}

void UNOGame::ApplyCardEffects()
{
    Label label = played.top().getLabel();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    switch (label)
    {
        case Label::Skip:
            Players.AdvanceTurn();
            if (Players.CurrentPlayer()->ishuman())
            {
                std::cout << "You have been skipped.\n";
            }
            else
            {
                std::cout << "CPU Player" << Players.CurrentPlayerIndex() << " has been skipped.\n";
            }
            break;

        case Label::Reverse:
            Players.ReverseDirection();
            std::cout << "The order has been reversed.\n";
            break;

        case Label::DrawTwo:
            Players.AddTwotoNextPlayer(todraw);
            if (Players.NextPlayer()->ishuman())
            {
                std::cout << "Two cards have been added to your deck.\n";
            }
            else
            {
                std::cout << "CPU Player" << Players.NextPlayerIndex() << " has drawn two cards.\n";
            }
            break;

        case Label::WildDrawFour:
            Players.AddFourtoNextPlayer(todraw);
            if (Players.NextPlayer()->ishuman())
            {
                std::cout << "Four cards have been added to your deck.\n";
            }
            else
            {
                std::cout << "CPU Player " << Players.NextPlayerIndex() << " has drawn four cards.\n";
            }
            // Fallthrough to trigger color selection logic
            [[fallthrough]];

        case Label::Wild:
            if (Players.CurrentPlayer()->ishuman())
            {
                HumanWildCardSequence();
            }
            else
            {
                CPUWildCardSequence();
            }
            break;

        default:
            // No special action needed for numeric cards
            break;
            
    }
}

void UNOGame::GameLoop()
{
    firstDraw();
    while (!winner)
    {
        Player* CurrentPlayer = Players.CurrentPlayer();

        if (CurrentPlayer->ishuman())
        {
            HumanTurnSequence();
        }
        else
        {
            CPUTurnSequence();
        }
        
        if (played.top().isspecial())
        {
            ApplyCardEffects();
        }

        if (CurrentPlayer->hasWon())
        {
            winner = true;
            break;
        }

        Players.AdvanceTurn();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void UNOGame::EndScreen()
{
    if (Players.CurrentPlayer()->hasWon())
    {
        if (Players.CurrentPlayer()->ishuman())
        {
            std::cout << "\nCongratulations! You’ve won the game of UNO.\n";
            std::cout << "You played skillfully and outwitted your CPU opponents.\n";
        }
        else
        {
            std::cout << "\nThe CPU Player " << Players.CurrentPlayerIndex() << " has won the game.\n";
            std::cout << "You put up a good fight, but the machine reigns this time.\n";
            std::cout << "Better luck next round.\n";
        }
    }
    else
    {
        std::cout << "\nThe game has ended, but no clear winner was found.\n";
        std::cout << "That’s odd. Did something go wrong?\n";
    }

    std::cout << "\nThanks for playing UNO Terminal Edition.\n";
}

void UNOGame::RunGame()
{
    StartMenuLoop();
    GameLoop();
    EndScreen();
}