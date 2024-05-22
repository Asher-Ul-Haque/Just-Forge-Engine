#include "game.h"
#include <core/logger.h>


bool8 gameInit(game* GAME)
{
    FORGE_LOG_DEBUG("Game initialised");
    return TRUE;
}

bool8 gameUpdate(game* GAME, float DELTA_TIME)
{
//    FORGE_LOG_DEBUG("Game updated");
    return TRUE;
}

bool8 gameRender(game* GAME, float DELTA_TIME)
{
//    FORGE_LOG_DEBUG("Game rendered");
    return TRUE;
}

void gameOnResize(game* GAME, unsigned int WIDTH, unsigned int HEIGHT)
{
    FORGE_LOG_DEBUG("Game resized");
}
