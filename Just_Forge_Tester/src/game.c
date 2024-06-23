#include "game.h"
#include <core/logger.h>
#include <core/input.h>
#include <core/event.h>
#include <core/memory.h>

bool8 gameInit(game* GAME)
{
    FORGE_LOG_INFO("Game initialised");
    return true;
}

bool8 gameUpdate(game* GAME, float DELTA_TIME)
{
//    FORGE_LOG_TRACE("Game updated");
    unsigned long long allocCount = forgeGetMemoryAllocCount();
    if (inputIsKeyUp(KEY_M) & inputWasKeyDown(KEY_M))
    {
        FORGE_LOG_INFO("Memory allocations: %llu", forgeGetMemoryAllocCount() - allocCount);
        allocCount = forgeGetMemoryAllocCount();
    }
    return true;
}

bool8 gameRender(game* GAME, float DELTA_TIME)
{
//    FORGE_LOG_TRACE("Game rendered");
    return true;
}

void gameOnResize(game* GAME, unsigned int WIDTH, unsigned int HEIGHT)
{
    FORGE_LOG_DEBUG("Game resized");
}
