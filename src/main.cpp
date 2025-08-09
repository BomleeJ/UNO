#include "UNOGame.h"
#include <iostream>

int main() 
{ 
    std::cout << "Please enter the number of Computer Players: ";
    int numCPU;
    std::cin >> numCPU;

    std::cout << "\n";


    UNOGame game = UNOGame(numCPU);
    game.RunGame();
    return 0;
}