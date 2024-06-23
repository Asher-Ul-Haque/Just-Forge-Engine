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

static bool8 isInitialized = false;
static eventSystemState state;


// - - - | Event System functions | - - -


// - - - Game engine functions - - -

bool8 eventInitialize()
{
    if (isInitialized == true)
    {
        return false;
    }
    isInitialized = true;
    forgeZeroMemory(&state, sizeof(state));
    FORGE_LOG_INFO("Event System Initialized");
    return true;
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
    isInitialized = false;
    FORGE_LOG_INFO("Event System Shutdown");
}


// - - - Game developer functions - - -

bool8 eventRegister(unsigned short CODE,  void* LISTENER, eventCallback CALLBACK)
{
    if (isInitialized == false)
    {
        return false;
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
            FORGE_LOG_WARNING("Listener already registered for event code %i", CODE);
            return false;
        }
    }

    //Safe to register
    registeredEvent event;
    event.listener = LISTENER;
    event.callback = CALLBACK;
    listAppend(state.registry[CODE].events, event);

    return true;
}

bool8 eventUnregister(unsigned short CODE, void* LISTENER, eventCallback CALLBACK)
{
    if (isInitialized == false)
    {
        return false;
    }

    if (state.registry[CODE].events == 0)
    {
        FORGE_LOG_WARNING("No listeners registered for event code %i", CODE);
        return false;
    }

    unsigned long long registeredCount = listLength(state.registry[CODE].events);

    for (unsigned long long i = 0; i < registeredCount; ++i)
    {
        registeredEvent event = state.registry[CODE].events[i];
        if (event.listener == LISTENER && event.callback == CALLBACK)
        {
            registeredEvent poppedEvent;
            listRemove(state.registry[CODE].events, i, &poppedEvent);
            return true;
        }
    }

    //Not found
    return false;
}

bool8 eventTrigger(unsigned short CODE, void* SENDER, eventContext CONTEXT)
{
    if (isInitialized == false)
    {
        return false;
    }

    if (state.registry[CODE].events == 0)
    {
        return false;
    }

    unsigned long long registeredCount = listLength(state.registry[CODE].events);
    for (unsigned long long i = 0; i < registeredCount; ++i)
    {
        registeredEvent event = state.registry[CODE].events[i];
        if (event.callback(CODE, SENDER, event.listener, CONTEXT))
        {
            //Message has been handled, no need to send for other listeners
            return true;
        }
    }
    
    //Not found
    return false;
}
