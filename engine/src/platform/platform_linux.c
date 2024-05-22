#include "platform.h"
#if FORGE_PLATFORM_LINUX
#include "core/logger.h"
#include <xcb/xcb.h>
#include <X11/XKBlib.h> //sudo apt-get install libx11-xcb-dev
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h> //sudo apt-get install libxkbcommon-x11-dev
#include <X11/keysym.h>
#include <sys/time.h>

// - - - Distribution dependent time
#if _POSIX_C_SOURCE >= 199309L // This means that the system is POSIX compliant
#include <time.h>
#else 
#include <unistd.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// - - - Platform state 
typedef struct internalState
{
    Display* display;
    xcb_connection_t* connection;
    xcb_screen_t* screen;
    xcb_window_t window;
    xcb_atom_t windowProtocols;
    xcb_atom_t windowDelete;
} internalState;


// - - - | Platform Functions | - - -


// - - - State Functions - - -

bool8 platformInit(platformState* STATE, const char* APPLICATION, int X, int Y, int WIDTH, int HEIGHT)
{
    STATE->internalState = malloc(sizeof(internalState));
    internalState* state = (internalState*)STATE->internalState;
    
    //Connect to X
    state->display = XOpenDisplay(NULL);
    
    //Turn off key repeats
    XAutoRepeatOff(state->display); //This happens OS wide, remember to turn it back on
    
    //Get the connection
    state->connection = XGetXCBConnection(state->display);

    if (xcb_connection_has_error(state->connection))
    {
        FORGE_LOG_FATAL("Failed to get the XCB connection\n");
        return FALSE;
    }

    //Get data from X server
    const struct xcb_setup_t* setup = xcb_get_setup(state->connection);

    //Loop through the screens using iterator
    xcb_screen_iterator_t iterator = xcb_setup_roots_iterator(setup);
    int screenPointer = 0;
    for (int i = screenPointer; i > 0; --i)
    {
        xcb_screen_next(&iterator);
    }
    state->screen = iterator.data;

    //Allocate a XID for the window to be created
    state->window = xcb_generate_id(state->connection);

    // Register for events
    // XCB_CW_BACK_PIXEL - The background color of the window
    // XCB_CW_EVENT_MASK - The events that the window will receive
    unsigned int eventMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;

    unsigned int eventValues =  XCB_EVENT_MASK_BUTTON_PRESS |
                                XCB_EVENT_MASK_BUTTON_RELEASE |
                                XCB_EVENT_MASK_EXPOSURE |
                                XCB_EVENT_MASK_KEY_PRESS |
                                XCB_EVENT_MASK_KEY_RELEASE |
                                XCB_EVENT_MASK_POINTER_MOTION |
                                XCB_EVENT_MASK_STRUCTURE_NOTIFY;

    //Values to send to XCB (bg color and event mask)
    unsigned int valueList[] = {state->screen->black_pixel, eventValues};

    //Create the window
    xcb_void_cookie_t cookie = xcb_create_window(
        state->connection,
        XCB_COPY_FROM_PARENT,   //Depth of the window
        state->window,          
        state->screen->root,    //Parent window
        X, Y,                   //X and Y position
        WIDTH, HEIGHT,          //Width and Height
        0,                      //Border width
        XCB_WINDOW_CLASS_INPUT_OUTPUT, //Window class (input/output)
        state->screen->root_visual,
        eventMask,
        valueList);

    //Change the title
    xcb_change_property(
        state->connection,
        XCB_PROP_MODE_REPLACE,
        state->window,
        XCB_ATOM_WM_NAME,
        XCB_ATOM_STRING,
        8, //8 bits per byte, Title is viewed a byte at a time, because title is an array of chars and a char is one byte
        strlen(APPLICATION),
        APPLICATION);

    //Yo server, tell the window manager that when you want to close this window
    xcb_intern_atom_cookie_t deleteCookie = xcb_intern_atom(
        state->connection,
        0,
        strlen("WM_DELETE_WINDOW"),
        "WM_DELETE_WINDOW");

    xcb_intern_atom_cookie_t protocolsCookie = xcb_intern_atom(
        state->connection, 
        0, 
        strlen("WM_PROTOCOLS"),
        "WM_PROTOCOLS");

    xcb_intern_atom_reply_t* deleteReply = xcb_intern_atom_reply(
        state->connection, 
        deleteCookie, 
        NULL);

    xcb_intern_atom_reply_t* protocolsReply = xcb_intern_atom_reply(
        state->connection, 
        protocolsCookie, 
        NULL);

    state->windowDelete = deleteReply->atom;
    state->windowProtocols = protocolsReply->atom;

    xcb_change_property(
        state->connection,
        XCB_PROP_MODE_REPLACE,
        state->window,
        protocolsReply->atom,
        4,
        32,
        1,
        &deleteReply->atom);

    //Map the window
    xcb_map_window(state->connection, state->window);

    //Flush the request
    int streamResult = xcb_flush(state->connection);
    if (streamResult <= 0)
    {
        FORGE_LOG_FATAL("Failed to flush the request: %d\n", streamResult);
        return FALSE;
    }

    return TRUE;
}

void platformShutdown(platformState* STATE)
{
    internalState* state = (internalState*)STATE->internalState;

    XAutoRepeatOn(state->display);

    xcb_destroy_window(state->connection, state->window);
}

bool8 platformGiveMessages(platformState* STATE)
{
    internalState* state = (internalState*)STATE->internalState;
    xcb_generic_event_t* event;
    xcb_client_message_event_t* clientMessage;
    bool8 quitFlag = FALSE;
    
    while ((event = xcb_poll_for_event(state->connection)))
    {
        if (event == 0)
        {
            break;
        }

        switch (event->response_type & -0x80) //Documentation says so, do not question this number
        {
            case XCB_KEY_PRESS:

            case XCB_KEY_RELEASE:
                // TODO: Input from keyboard
                break;

            case XCB_BUTTON_PRESS:

            case XCB_BUTTON_RELEASE:
                // TODO: Input from mouse
                break;

            case XCB_MOTION_NOTIFY:
                // TODO: Mouse movement
                break;

            case XCB_CONFIGURE_NOTIFY:
                // TODO: resizing

            case XCB_CLIENT_MESSAGE:
                clientMessage = (xcb_client_message_event_t*)event;

                //Check if the window is being closed
                if (clientMessage->data.data32[0] == state->windowDelete)
                {
                    quitFlag = TRUE;
                }
                break;

            default:
                break;
        }
        free(event);
    }
    return !quitFlag;
}


// - - - Memory Functions - - -

void* platformAllocateMemory(unsigned long long SIZE, bool8 ALIGNED)
{
    return malloc(SIZE);
}

void platformFreeMemory(void* MEMORY, bool8 ALIGNED)
{
    free(MEMORY);
}

void* platformZeroMemory(void* MEMORY, unsigned long long SIZE)
{
    return memset(MEMORY, 0, SIZE);
}

void* platformCopyMemory(void* DESTINATION, const void* SOURCE, unsigned long long SIZE)
{
    return memcpy(DESTINATION, SOURCE, SIZE);
}

void* platformSetMemory(void* DESTINATION, int VALUE, unsigned long long SIZE)
{
    return memset(DESTINATION, VALUE, SIZE);
}


// - - - Writing Functions - - - 

void platformWriteConsole(const char* MESSAGE, unsigned char COLOR)
{
    //FATAL, ERROR, WARN, INFO, DEBUG, TRACE : damn color codes work on nvim
    const char* colorStrings[] = { "0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    printf("\033[%sm%s\033[0m", colorStrings[COLOR], MESSAGE); //This looks scary
    //Here is how it works:
    //\033[ - This is the escape character
    //%s - This is the color code
    //m - This is the end of the color code
    //%s - This is the message
    //\033[0m - This is the end of the color
    //This is how you print colored text in the terminal
}

void platformWriteConsoleError(const char* MESSAGE, unsigned char COLOR)
{
    //Why change code if you can just copy it
    //FATAL, ERROR, WARN, INFO, DEBUG, TRACE : damn color codes work on nvim
    const char* colorStrings[] = { "1;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    printf("\033[%sm%s\033[0m", colorStrings[COLOR], MESSAGE); //This looks scary
    //Here is how it works:
    //\033[ - This is the escape character
    //%s - This is the color code
    //m - This is the end of the color code
    //%s - This is the message
    //\033[0m - This is the end of the color
    //This is how you print colored text in the terminal
}


// - - - Time and Sleep Functions - - -

void platformSleep(unsigned long long MILLISECONDS)
{
#if _POSIX_C_SOURCE >= 199309L
    struct timespec sleepTime;
    sleepTime.tv_sec = MILLISECONDS / 1000;
    sleepTime.tv_nsec = (MILLISECONDS % 1000) * 1000 * 1000;
    nanosleep(&sleepTime, NULL);
#else
    if (MILLISECONDS >= 1000)
    {
        sleep(MILLISECONDS / 1000);
    }
    usleep((MILLISECONDS % 1000) * 1000);
#endif
}

double platformGetTime()
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec + now.tv_nsec * 0.000000001; //Seconds in double
}

#endif
