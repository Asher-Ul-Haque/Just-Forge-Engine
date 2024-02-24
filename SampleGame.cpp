//
// Created by conta on 19-02-2024.
//
#include "Engine/TheMachine/GameEngine.h"
#include <iostream>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    //Create a game engine
    GameEngine game(R"(..\\Assets\\ConfigurationFiles\\AssetFile)");
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