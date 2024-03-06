#include "Engine/TheMachine/GameEngine.h"
#include <cstdlib>
#include <iostream>

int main()
{
    //Create a game engine
    std::cout << " _ _ _ _ _   NAH-RIO MESSAGE _ _ _ _ _" << std::endl;
    std::cout << " Creating game engine" << std::endl << " - - - - - - - - - - - - - " << std::endl << std::endl;
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