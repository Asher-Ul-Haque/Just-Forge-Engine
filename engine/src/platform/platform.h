#pragma once
#include "../defines.h"

// - - - Platform State
typedef struct platformState
{
    void* internalState;
} platformState;


// - - - | Platform Functions | - - -


// - - - State Functions - - -

FORGE_API bool8 platformInit(platformState* STATE, const char* APPLICATION, int X, int Y, int WIDTH, int HEIGHT);

FORGE_API void platformShutdown(platformState* STATE);

FORGE_API bool8 platformGiveMessages(platformState* STATE);


// - - - Memory Functions - - -

void* platformAllocateMemory(unsigned long long SIZE, bool8 ALIGNED);

void platformFreeMemory(void* MEMORY, bool8 ALIGNED);

void* platformZeroMemory(void* MEMORY, unsigned long long SIZE);

void* platformCopyMemory(void* DESTINATION, const void* SOURCE, unsigned long long SIZE);

void* platformSetMemory(void* DESTINATION, int VALUE, unsigned long long SIZE);


// - - - Writing Functions - - - 

void platformWriteConsole(const char* MESSAGE, unsigned char COLOR);

void platformWriteConsoleError(const char* MESSAGE, unsigned char COLOR);


// - - - Time and Sleep Functions - - -

void platformSleep(unsigned long long MILLISECONDS);

double platformGetTime();
