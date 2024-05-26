#include "core/event.h"
#include "core/memory.h"
#include "core/logger.h"
#include "event.h"
#include "dataStructures/list.h"

typedef struct registeredEvent
{
    void* listener;
    eventCallback callback;
} registeredEvent;

typedef struct eventCodeEntry
{
    registeredEvent* events;
} eventCodeEntry;

// This should be enough number of codes
#define MAX_MESSAGE_CODES 16384

//State structure
typedef struct eventSystemState
{
    eventCodeEntry registry[MAX_MESSAGE_CODES];
} eventSystemState;

static bool8 isInitialized = FALSE;
static eventSystemState state;


// - - - | Event System functions | - - -


// - - - Game engine functions - - -

bool8 eventInitialize()
{
    if (isInitialized == TRUE)
    {
        return FALSE;
    }
    isInitialized = TRUE;
    forgeZeroMemory(&state, sizeof(state));
    FORGE_LOG_INFO("Event System Initialized");
    return TRUE;
}

void eventShutdown()
{
    for (unsigned short i = 0; i < MAX_MESSAGE_CODES; ++i)
    {
        if (state.registry[i].events != 0)
        {
            listDestroy(state.registry[i].events);
            state.registry[i].events = 0;
        }
    }
    isInitialized = FALSE;
    FORGE_LOG_INFO("Event System Shutdown");
}


// - - - Game developer functions - - -

bool8 eventRegister(unsigned short CODE,  void* LISTENER, eventCallback CALLBACK)
{
    if (isInitialized == FALSE)
    {
        return FALSE;
    }

    if (state.registry[CODE].events == 0)
    {
        state.registry[CODE].events = listCreate(registeredEvent);
    }

    unsigned long long registeredCount = listLength(state.registry[CODE].events);
    for (unsigned long long i = 0; i < registeredCount; ++i)
    {
        if (state.registry[CODE].events[i].listener == LISTENER)
        {
            // TODO: warn
            return FALSE;
        }
    }

    //Safe to register
    registeredEvent event;
    event.listener = LISTENER;
    event.callback = CALLBACK;
    listAppend(state.registry[CODE].events, event);

    return TRUE;
}

bool8 eventUnregister(unsigned short CODE, void* LISTENER, eventCallback CALLBACK)
{
    if (isInitialized == FALSE)
    {
        return FALSE;
    }

    if (state.registry[CODE].events == 0)
    {
        // TODO: warn
        return FALSE;
    }

    unsigned long long registeredCount = listLength(state.registry[CODE].events);

    for (unsigned long long i = 0; i < registeredCount; ++i)
    {
        registeredEvent event = state.registry[CODE].events[i];
        if (event.listener == LISTENER && event.callback == CALLBACK)
        {
            registeredEvent poppedEvent;
            listRemove(state.registry[CODE].events, i, &poppedEvent);
            return TRUE;
        }
    }

    //Not found
    return FALSE;
}

bool8 eventTrigger(unsigned short CODE, void* SENDER, eventContext CONTEXT)
{
    if (isInitialized == FALSE)
    {
        return FALSE;
    }

    if (state.registry[CODE].events == 0)
    {
        return FALSE;
    }

    unsigned long long registeredCount = listLength(state.registry[CODE].events);
    for (unsigned long long i = 0; i < registeredCount; ++i)
    {
        registeredEvent event = state.registry[CODE].events[i];
        if (event.callback(CODE, SENDER, event.listener, CONTEXT))
        {
            //Message has been handled, no need to send for other listeners
            return TRUE;
        }
    }
    
    //Not found
    return FALSE;
}
