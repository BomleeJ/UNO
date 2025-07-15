#include "Playloop.h"
#include "Player.h"
#include <iostream>

PlayLoop::PlayLoop(int CPU_, DrawDeck& Deck)
{
    Human* Humanplayer = new Human();
    Humanplayer->drawSevenCards(Deck);
    HumanNode = new Node(Humanplayer);
    CurrTurn = HumanNode;
    Node* PrevNode = CurrTurn;

    while (CPU_ > 0)
    {
        CPU* CPUPlayer = new CPU();
        CPUPlayer->drawSevenCards(Deck);
        Node* CPUNode = new Node(CPUPlayer);

        CPUNode->prev = PrevNode;
        PrevNode->next = CPUNode;
        PrevNode = PrevNode->next;

        CPU_--;
    }

    Node* CurrTurn = HumanNode;
    //Fi
    if (HumanNode->next != nullptr)
    {
        HumanNode->prev = PrevNode;
        PrevNode->next = HumanNode;

    }
}

void PlayLoop::destroyCPUs()
{
Node* curr = HumanNode->next;

while(HumanNode->prev != nullptr)
{
    Node* next = curr->next;

    delete curr->player;
    curr->player = nullptr;

    delete curr;
    curr = nullptr;

    curr = next;
}

}

void PlayLoop::destroyHuman()
{
    delete HumanNode->player;
    HumanNode->player = nullptr;
    delete HumanNode;
    HumanNode = nullptr;
}

bool PlayLoop::CurrentPlayerEmpty()
{
    return CurrTurn->player->hasWon();
}

void PlayLoop::advance()
{
    CurrTurn = CurrTurn->next;
}

PlayLoop::Node* PlayLoop::GetHumanNode()
{
    return HumanNode;
}

Player* PlayLoop::CurrentPlayer()
{
    return CurrTurn->player;
}

PlayLoop::~PlayLoop()
{
destroyCPUs();
destroyHuman();
std::cerr << "Player Loop Destructor called";
}