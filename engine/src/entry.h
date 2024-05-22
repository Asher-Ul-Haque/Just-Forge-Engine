#pragma once
#include "core/application.h"
#include "core/logger.h"
#include "game_types.h"


// - - - | Game Application | - - -


// - - - External Function
extern bool8 createGame(game* OUPUT_GAME);

// - - - Main Function
int main(void)
{
    game gameInstance;
    if (!createGame(&gameInstance))
    {
        FORGE_LOG_FATAL("Failed to create game instance");
        return -1;
    }

    //Ensure the function pointers are not null
    if (!gameInstance.init || !gameInstance.update || !gameInstance.render || !gameInstance.onResize)
    {
        FORGE_LOG_FATAL("Game instance function pointers are null");
        return -2;
    }

    //Initialise the game
    if (!createApplication(&gameInstance))
    {
        FORGE_LOG_INFO("Failed to create application");
        return 1;
    }
    
    //Begin the game loop
    if (!runApplication())
    {
        FORGE_LOG_INFO("Failed to shutdown gracefully");
        return 2;
    }
    
    return 0;
}
