#pragma once
#include "defines.h"


// - - - Clock - - -

typedef struct clock 
{
    double startTime;
    double elapsedTime;
} clock;


// - - - Clock Functions - - -

void clockUpdate(clock* CLOCK);
void clockStart(clock* CLOCK);
void clockStop(clock* CLOCK);
