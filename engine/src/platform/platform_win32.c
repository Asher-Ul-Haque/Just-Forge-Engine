#include "platform.h"
#ifdef FORGE_PLATFORM_WINDOWS
#include <windows.h>
#include <windowsx.h> //This is for the GET_X_LPARAM and GET_Y_LPARAM macros

// - - - Platform state 
typedef struct internalState
{
    HINSTANCE hInstance;
    HWND hwnd;
} internalState;


// - - - | Platform Functions | - - -


// - - - State Functions - - -

bool8 platformInit(platformState* STATE, const char* APPLICATION, int X, int Y, int WIDTH, int HEIGHT)
{
    STATE->internalState = malloc(sizeof(internalState));
    internalState* state = (internalState*) STATE->internalState;

    state->hInstance = GetModuleHandle(0); //Get the handle to the application running this code
}

#endif
