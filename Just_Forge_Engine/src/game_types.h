#pragma once
#include "core/application.h"


// - - - Game Structure - - -

typedef struct game 
{
    applicationConfig config;
    bool8 (* init)(struct game* GAME);
    bool8 (* update)(struct game* GAME, float DELTA_TIME);
    bool8 (* render)(struct game* GAME, float DELTA_TIME);
    void (* onResize)(struct game* GAME, unsigned int WIDTH, unsigned int HEIGHT);
    void* state; //created and managed by the game
    void* applicationState;
} game;
