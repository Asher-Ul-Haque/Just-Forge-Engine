#include "application.h"
#include "event.h"
#include "input.h"
#include "logger.h"
#include "memory.h"
#include "platform/platform.h"
#include "game_types.h"
#include "core/memory.h"
#include "core/event.h"
#include "core/input.h"
#include "core/clock.h"
#include "renderer/renderer_frontend.h"


// - - - | Application State | - - -


typedef struct applicationState
{
    game* gameInstance;
    bool8 isRunning;
    bool8 isSuspended;
    platformState platform;
    short width;
    short height;
    double lastTime;
    clock clock;
} applicationState;

static bool8 initialized = FALSE;
static applicationState appState;


// - - - | Application Functions | - - -


// - - - Event Handlers - - -

bool8 applicationOnEvent(unsigned short CODE, void* SENDER, void* LISTENER, eventContext context);

bool8 applicationOnKey(unsigned short CODE, void* SENDER, void* LISTENER, eventContext context);

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

    //Intialise input system
    inputInitialize();

    appState.isRunning = TRUE;
    appState.isSuspended = FALSE;

    //Initialise the event system
    if (!eventInitialize())
    {
        FORGE_LOG_FATAL("Event system failed initialisation");
        return FALSE;
    }
    
    //Register event listeners
    eventRegister(EVENT_CODE_APPLICATION_QUIT, 0, applicationOnEvent);
    eventRegister(EVENT_CODE_KEY_PRESS, 0, applicationOnKey);
    eventRegister(EVENT_CODE_KEY_RELEASE, 0, applicationOnKey);

    //Intitialise the platform
    if(!platformInit(&appState.platform, GAME->config.name, GAME->config.startPositionX, GAME->config.startPositionY, GAME->config.startWidth, GAME->config.startHeight)) 
    {
        return FALSE;
    }
    
    //Initialise the renderer
    if (!rendererIntitialize(GAME->config.name, &appState.platform))
    {
        FORGE_LOG_FATAL("Failed to initialize the renderer");
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
    clockStart(&appState.clock);
    clockUpdate(&appState.clock);
    appState.lastTime = appState.clock.elapsedTime;
    double runningTime = 0.0;
    unsigned char frameCount = 0;
    double targetFrameTime = 1.0f / 60.0; // 60 fps

    FORGE_LOG_INFO(forgeGetMemoryStats());

    while (appState.isRunning) 
    {
        if (!platformGiveMessages(&appState.platform))
        {
            appState.isRunning = FALSE;
        }

        // TODO: take care of delta time.
        if (!appState.isSuspended)
        {
            clockUpdate(&appState.clock);
            double currentTime = appState.clock.elapsedTime;
            double deltaTime = currentTime - appState.lastTime;
            double frameStartTime = platformGetTime();

            if (!appState.gameInstance->update(appState.gameInstance, deltaTime))
            {
                FORGE_LOG_FATAL("Failed to update game");
                appState.isRunning = FALSE;
                break;
            }

            if (!appState.gameInstance->render(appState.gameInstance, deltaTime))
            {
                FORGE_LOG_FATAL("Failed to render game");
                appState.isRunning = FALSE;
                break;
            }

            rendererPacket packet;
            packet.deltaTime = deltaTime;
            rendererDrawFrame(&packet);  

            double frameEndTime = platformGetTime();
            double frameElapsedTime = frameEndTime - frameStartTime;
            runningTime += frameElapsedTime;
            double remainingSeconds = targetFrameTime - frameElapsedTime;

            if (remainingSeconds > 0)
            {
                unsigned long long remainingMiliseconds = (remainingSeconds * 1000);
                bool8 limitFrames = FALSE; //give time back to os
                if (remainingMiliseconds > 0 && limitFrames)
                {
                    platformSleep(remainingMiliseconds - 1);
                }
                ++frameCount;
            }

            //NOTE: input state should be handled after input recorded or before this line
            inputUpdate(deltaTime);
            
            appState.lastTime = currentTime;
        }
    }

    appState.isRunning = FALSE;

    //Unregister event listeners
    eventUnregister(EVENT_CODE_APPLICATION_QUIT, 0, applicationOnEvent);
    eventUnregister(EVENT_CODE_KEY_PRESS, 0, applicationOnKey);
    eventUnregister(EVENT_CODE_KEY_RELEASE, 0, applicationOnKey);
    eventShutdown();
    inputShutdown();
    rendererShutdown();
    platformShutdown(&appState.platform);
    return TRUE;
}


// - - - Event Handlers - - -

bool8 applicationOnEvent(unsigned short CODE, void* SENDER, void* LISTENER, eventContext context)
{
    switch (CODE)
    {
        case EVENT_CODE_APPLICATION_QUIT:
            FORGE_LOG_INFO("EVENT_CODE_APPLICATION_QUIT recieved, shutting down.\n");
            appState.isRunning = FALSE;
            return TRUE;
    }

    return FALSE;
}

bool8 applicationOnKey(unsigned short CODE, void* SENDER, void* LISTENER, eventContext CONTEXT)
{
    unsigned short keyCode;
    eventContext context = {};
    switch (CODE)
    {
        case EVENT_CODE_KEY_PRESS:
            keyCode = CONTEXT.data.u16[0];
            switch (keyCode)
            {
                case KEY_ESCAPE:
                    eventTrigger(EVENT_CODE_APPLICATION_QUIT, 0, context);
                    return TRUE;

                case KEY_F1:
                    appState.isSuspended = !appState.isSuspended;
                    return TRUE;

                case KEY_A:
                    FORGE_LOG_DEBUG("Key A pressed");
                    return TRUE;

                default:
                    FORGE_LOG_DEBUG("Key %i pressed", keyCode);
                    return FALSE;
            }
            break;

        case EVENT_CODE_KEY_RELEASE:
            keyCode = CONTEXT.data.u16[0];
            switch (keyCode)
            {
                case KEY_B:
                    FORGE_LOG_DEBUG("Key A released");
                    return TRUE;

                default:
                    FORGE_LOG_DEBUG("Key %i released", keyCode);
                    return FALSE;
            }
            break;
    }
    return FALSE;
}
