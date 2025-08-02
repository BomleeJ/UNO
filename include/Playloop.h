#pragma once
#include "Player.h"

class PlayLoop
{

    struct Node
    {
        Player* player;
        Node* prev;
        Node* next;

        Node(Player* p): 
            player { p }, 
            prev { nullptr }, 
            next { nullptr }
        { }
    };
    Node* HumanNode;
    Node* CurrTurn;
    void destroyCPUs();
    void destroyHuman();

public:

    PlayLoop(int CPU, DrawDeck& Deck);
    PlayLoop(PlayLoop& other);
    void advance(); // Advances to the next one
    Player* CurrentPlayer();
    Node* GetHumanNode();
    bool CurrentPlayerEmpty();

    ~PlayLoop();

};