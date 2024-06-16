#include "core/input.h"
#include "core/memory.h"
#include "core/logger.h"
#include "core/event.h"
#include "event.h"
#include "input.h"


// - - - | Input Tracking | - - -


// - - - Keyboard
typedef struct keyBoardState
{
    bool8 keys[256];
} keyBoardState;

// - - - Mouse
typedef struct mouseState
{
    unsigned char buttons[BUTTON_MAX_BUTTONS];
    short x, y;
} mouseState;

// - - - Input State 
typedef struct inputState
{
    keyBoardState keyBoardCurrent;
    keyBoardState keyBoardPrevious;
    mouseState mouseCurrent;
    mouseState mousePrevious;
} inputState;

// - - - Input State
static bool8 isInitialized =  FALSE;
static inputState state;


// - - - | Input Functions | - - -


// - - - System Functions - - -

void inputInitialize()
{
    forgeZeroMemory(&state, sizeof(inputState));
    isInitialized = TRUE;
    FORGE_LOG_INFO("Input system initialized");
}

void inputShutdown()
{
    //TODO: Shutdown routines
    isInitialized = FALSE;
    FORGE_LOG_INFO("Input system shutdown");
}

void inputUpdate(double DELTA_TIME)
{
    if (!isInitialized)
    {
        return;
    }
    
    //Copy current state to previous state 
    forgeCopyMemory(&state.keyBoardPrevious, &state.keyBoardCurrent, sizeof(keyBoardState));
    forgeCopyMemory(&state.mousePrevious, &state.mouseCurrent, sizeof(mouseState));
}


// - - - Keyboard Functions - - -

// - - - Key Functions
bool8 inputIsKeyDown(keys KEY)
{
    if (!isInitialized)
    {
        return FALSE;
    }
    return state.keyBoardCurrent.keys[KEY] == TRUE;
}

bool8 inputIsKeyUp(keys KEY)
{
    if (!isInitialized)
    {
        return TRUE;
    }
    return state.keyBoardCurrent.keys[KEY] == FALSE;
}

bool8 inputWasKeyDown(keys KEY)
{
    if (!isInitialized)
    {
        return FALSE;
    }
    return state.keyBoardPrevious.keys[KEY] == TRUE;
}

bool8 inputWasKeyUp(keys KEY)
{
    if (!isInitialized)
    {
        return TRUE;
    }
    return state.keyBoardPrevious.keys[KEY] == FALSE;
}

// - - - Input Processing Functions
void inputProcessKey(keys KEY, bool8 IS_DOWN)
{
    if (state.keyBoardCurrent.keys[KEY] != IS_DOWN)
    {
        state.keyBoardCurrent.keys[KEY] = IS_DOWN;

        eventContext context;
        context.data.u16[0] = KEY;
        eventTrigger(IS_DOWN ? EVENT_CODE_KEY_PRESS : EVENT_CODE_KEY_RELEASE, 0, context);
    }
}


// - - - Mouse Functions - - -

// - - - Button Functions
bool8 inputIsButtonDown(buttons BUTTON)
{
    if (!isInitialized)
    {
        return FALSE;
    }
    return state.mouseCurrent.buttons[BUTTON] == TRUE;
}

bool8 inputIsButtonUp(buttons BUTTON)
{
    if (!isInitialized)
    {
        return TRUE;
    }
    return state.mouseCurrent.buttons[BUTTON] == FALSE;
}

bool8 inputWasButtonDown(buttons BUTTON)
{
    if (!isInitialized)
    {
        return FALSE;
    }
    return state.mousePrevious.buttons[BUTTON] == TRUE;
}

bool8 inputWasButtonUp(buttons BUTTON)
{
    if (!isInitialized)
    {
        return TRUE;
    }
    return state.mousePrevious.buttons[BUTTON] == FALSE;
}

void inputGetMousePosition(int *X, int *Y)
{
    if (!isInitialized)
    {
        *X = 0;
        *Y = 0;
        return;
    }
    *X = state.mouseCurrent.x;
    *Y = state.mouseCurrent.y;
}

void inputGetPreviousMousePosition(int *X, int *Y)
{
    if (!isInitialized)
    {
        *X = 0;
        *Y = 0;
        return;
    }
    *X = state.mousePrevious.x;
    *Y = state.mousePrevious.y;
}

// - - - Input Processing Functions
void inputProcessButton(buttons BUTTON, bool8 IS_DOWN)
{
    if (state.mouseCurrent.buttons[BUTTON] != IS_DOWN)
    {
        state.mouseCurrent.buttons[BUTTON] = IS_DOWN;

        eventContext context;
        context.data.u16[0] = BUTTON;
        eventTrigger(IS_DOWN ? EVENT_CODE_BUTTON_PRESS : EVENT_CODE_BUTTON_RELEASE, 0, context);
    }
}

void inputProcessMouseMovement(short X, short Y)
{
    if (state.mouseCurrent.x != X || state.mouseCurrent.y != Y)
    {
        FORGE_LOG_TRACE("Mouse Position: %i, %i", X, Y);

        state.mouseCurrent.x = X;
        state.mouseCurrent.y = Y;

        eventContext context;
        context.data.u16[0] = X;
        context.data.u16[1] = Y;
        eventTrigger(EVENT_CODE_MOUSE_MOVE, 0 , context);
    }
}

void inputProcessMouseWheel(char WHEEL_DELTA)
{
    // NOTE: no internal state to update
    eventContext context;
    context.data.u8[0] = WHEEL_DELTA;
    eventTrigger(EVENT_CODE_MOUSE_WHEEL, 0, context);
}
