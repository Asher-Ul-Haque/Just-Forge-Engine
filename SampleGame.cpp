#include "Engine/TheMachine/GameEngine.h"
#include <cstdlib>
#include <iostream>

int main()
{
    //Create a game engine

    GameEngine game(R"(..\\Assets)");
    //Run the game
    try
    {
        game.run();
        return 0;
    }
    catch (std::exception e){
        return -1;
    }
}