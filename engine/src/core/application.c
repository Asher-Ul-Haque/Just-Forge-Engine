#include "application.h"
#include "logger.h"
#include "platform/platform.h"
#include "game_types.h"


// - - - | Application State | - - -


typedef struct applicationState
{
    game* gameInstance;
    bool8 isRunning;
    bool8 isSuspended;
    platformState* platform;
    short width;
    short height;
    double lastTime;
} applicationState;

static bool8 initialized = FALSE;
static applicationState appState;


// - - - | Application Functions | - - -


// - - - Create Application
bool8 createApplication(game* GAME)
{
    if (initialized)
    {
        FORGE_LOG_ERROR("Application cannot be created more than once");
        return FALSE;
    }

    appState.gameInstance = GAME;

    //Initialise logging system
    initializeLogger();
    FORGE_LOG_FATAL("A test messgae: %f", 3.14);
    FORGE_LOG_ERROR("A test messgae: %f", 3.14);
    FORGE_LOG_WARNING("A test messgae: %f", 3.14);
    FORGE_LOG_INFO("A test messgae: %f", 3.14);
    FORGE_LOG_DEBUG("A test messgae: %f", 3.14);
    FORGE_LOG_TRACE("A test messgae: %f", 3.14);

    appState.isRunning = TRUE;
    appState.isSuspended = FALSE;

    if(!platformInit(&appState.platform, GAME->config.name, GAME->config.startPositionX, GAME->config.startPositionY, GAME->config.startWidth, GAME->config.startHeight)) 
    {
        return FALSE;
    }
    
    //Initialise the game
    if (!appState.gameInstance->init(appState.gameInstance))
    {
        FORGE_LOG_FATAL("Failed to initialise game");
        return FALSE;
    }

    appState.gameInstance->onResize(appState.gameInstance, appState.width, appState.height);

    initialized = TRUE;
    return TRUE;
}

// - - - Run Application
bool8 runApplication()
{
    while (appState.isRunning) 
    {
        if (!platformGiveMessages(&appState.platform))
        {
            appState.isRunning = FALSE;
        }

        if (!appState.isSuspended)
        {
            if (!appState.gameInstance->update(appState.gameInstance, 0.0f))
            {
                FORGE_LOG_FATAL("Failed to update game");
                appState.isRunning = FALSE;
                break;
            }

            if (!appState.gameInstance->render(appState.gameInstance, 0.0f))
            {
                FORGE_LOG_FATAL("Failed to render game");
                appState.isRunning = FALSE;
                break;
            }
        }
    }

    appState.isRunning = FALSE;
    platformShutdown(&appState.platform);
    return TRUE;
}
