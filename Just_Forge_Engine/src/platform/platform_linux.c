#include "platform.h"
#if FORGE_PLATFORM_LINUX

#include "core/logger.h"
#include "core/input.h"
#include "core/event.h"

#include <dataStructures/list.h>

#include <X11/X.h>
#include <xcb/xproto.h>
#include <xcb/xcb.h>
#include <X11/XKBlib.h> //sudo apt-get install libx11-xcb-dev
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h> //sudo apt-get install libxkbcommon-x11-dev
#include <X11/keysym.h>
#include <sys/time.h>

// - - - Distribution dependent time
#if _POSIX_C_SOURCE >= 199309L // This means that the system is POSIX compliant
// What this means is that the system has a clock that can be used to measure time as compared to non-POSIX systems which do not have a clock but a timer
#include <time.h>
#else 
#include <unistd.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define VK_USE_PLATFORM_XCB_KHR
#include <vulkan/vulkan.h>
#include "renderer/vulkan/vulkan_types.h"

// - - - Key Transaltion
keys translateKeycode(unsigned int X_KEYCODE);

// - - - Platform state 
typedef struct internalState
{
    Display* display;
    xcb_connection_t* connection;
    xcb_screen_t* screen;
    xcb_window_t window;
    xcb_atom_t windowProtocols;
    xcb_atom_t windowDelete;
    VkSurfaceKHR surface;
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

    XAutoRepeatOn(state->display);
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

        switch (event->response_type & ~0x80) //Documentation says so, do not question this number
        {
            case XCB_KEY_PRESS:

            case XCB_KEY_RELEASE:
            {
                xcb_key_press_event_t* keyEvent = (xcb_key_press_event_t *) event;
                bool8 pressed = event->response_type == XCB_KEY_PRESS;
                xcb_keycode_t code = keyEvent->detail;
                KeySym keySym = XkbKeycodeToKeysym(state->display, (KeyCode) code, 0, code & ShiftMask ? 1 : 0);
                keys key = translateKeycode(keySym);
                inputProcessKey(key, pressed);
            } 
            break;

            case XCB_BUTTON_PRESS:

            case XCB_BUTTON_RELEASE:
            {
                xcb_button_press_event_t* mouseEvent = (xcb_button_press_event_t *) event;
                bool8 pressed = event->response_type == XCB_BUTTON_PRESS;
                buttons mouseButton = BUTTON_MAX_BUTTONS;
                switch (mouseEvent->detail)
                {
                    case XCB_BUTTON_INDEX_1:
                        mouseButton = BUTTON_LEFT;
                        break;

                    case XCB_BUTTON_INDEX_2:
                        mouseButton = BUTTON_MIDDLE;
                        break;

                    case XCB_MAP_INDEX_3:
                        mouseButton = BUTTON_RIGHT;
                        break;
                }

                if (mouseButton != BUTTON_MAX_BUTTONS)
                {
                    inputProcessButton(mouseButton, pressed);
                }
            }
            break;

            case XCB_MOTION_NOTIFY:
                {
                    xcb_motion_notify_event_t* moveEvent = (xcb_motion_notify_event_t *) event;
                    inputProcessMouseMovement(moveEvent->event_x, moveEvent->event_y);
                }
                break;

            case XCB_CONFIGURE_NOTIFY:
                //Note that this also happens in window moving
                {
                    xcb_configure_notify_event_t* configureEvent = (xcb_configure_notify_event_t*) event;

                    //Fire the event. The application layer should pick this up but not handle it to let it be visible to the game
                    eventContext context;
                    context.data.u16[0] = configureEvent->width;
                    context.data.u16[1] = configureEvent->height;
                    eventTrigger(EVENT_CODE_RESIZE, 0, context);
                }
                break;
                
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


// - - - Key Translation
keys translateKeycode(unsigned int X_KEYCODE)
{
    switch (X_KEYCODE)
    {
        case XK_BackSpace:
            return KEY_BACKSPACE;

        case XK_Return:
            return KEY_ENTER;

        case XK_Tab:
            return KEY_TAB;
            //case XK_Shift: return KEY_SHIFT;
            //case XK_Control: return KEY_CONTROL;

        case XK_Pause:
            return KEY_PAUSE;

        case XK_Caps_Lock:
            return KEY_CAPITAL;

        case XK_Escape:
            return KEY_ESCAPE;

            // Not supported
            // case : return KEY_CONVERT;
            // case : return KEY_NONCONVERT;
            // case : return KEY_ACCEPT;

        case XK_Mode_switch:
            return KEY_MODECHANGE;

        case XK_space:
            return KEY_SPACE;

        case XK_Prior:
            return KEY_PRIOR;

        case XK_Next:
            return KEY_NEXT;

        case XK_End:
            return KEY_END;

        case XK_Home:
            return KEY_HOME;

        case XK_Left:
            return KEY_LEFT;

        case XK_Up:
            return KEY_UP;

        case XK_Right:
            return KEY_RIGHT;

        case XK_Down:
            return KEY_DOWN;

        case XK_Select:
            return KEY_SELECT;

        case XK_Print:
            return KEY_PRINT;

        case XK_Execute:
            return KEY_EXECUTE;

        // case XK_snapshot: return KEY_SNAPSHOT; // not supported
        case XK_Insert:
            return KEY_INSERT;

        case XK_Delete:
            return KEY_DELETE;

        case XK_Help:
            return KEY_HELP;

        case XK_Super_L:
            return KEY_LWIN;

        case XK_Super_R:
            return KEY_RWIN;

        case XK_KP_0:
            return KEY_NUMPAD0;

        case XK_KP_1:
            return KEY_NUMPAD1;

        case XK_KP_2:
            return KEY_NUMPAD2;

        case XK_KP_3:
            return KEY_NUMPAD3;

        case XK_KP_4:
            return KEY_NUMPAD4;

        case XK_KP_5:
            return KEY_NUMPAD5;

        case XK_KP_6:
            return KEY_NUMPAD6;

        case XK_KP_7:
            return KEY_NUMPAD7;

        case XK_KP_8:
            return KEY_NUMPAD8;

        case XK_KP_9:
            return KEY_NUMPAD9;

        case XK_multiply:
            return KEY_MULTIPLY;

        case XK_KP_Add:
            return KEY_ADD;

        case XK_KP_Separator:
            return KEY_SEPARATOR;

        case XK_KP_Subtract:
            return KEY_SUBTRACT;

        case XK_KP_Decimal:
            return KEY_DECIMAL;

        case XK_KP_Divide:
            return KEY_DIVIDE;

        case XK_F1:
            return KEY_F1;

        case XK_F2:
            return KEY_F2;

        case XK_F3:
            return KEY_F3;

        case XK_F4:
            return KEY_F4;

        case XK_F5:
            return KEY_F5;

        case XK_F6:
            return KEY_F6;

        case XK_F7:
            return KEY_F7;

        case XK_F8:
            return KEY_F8;

        case XK_F9:
            return KEY_F9;

        case XK_F10:
            return KEY_F10;

        case XK_F11:
            return KEY_F11;

        case XK_F12:
            return KEY_F12;

        case XK_F13:
            return KEY_F13;

        case XK_F14:
            return KEY_F14;

        case XK_F15:
            return KEY_F15;

        case XK_F16:
            return KEY_F16;

        case XK_F17:
            return KEY_F17;

        case XK_F18:
            return KEY_F18;

        case XK_F19:
            return KEY_F19;

        case XK_F20:
            return KEY_F20;

        case XK_F21:
            return KEY_F21;

        case XK_F22:
            return KEY_F22;

        case XK_F23:
            return KEY_F23;

        case XK_F24:
            return KEY_F24;

        case XK_Num_Lock:
            return KEY_NUMLOCK;

        case XK_Scroll_Lock:
            return KEY_SCROLL;

        case XK_KP_Equal:
            return KEY_NUMPAD_EQUAL;

        case XK_Shift_L:
            return KEY_LSHIFT;

        case XK_Shift_R:
            return KEY_RSHIFT;

        case XK_Control_L:
            return KEY_LCONTROL;

        case XK_Control_R:
            return KEY_RCONTROL;

        // case XK_Menu: return KEY_LMENU;
        case XK_Menu:
            return KEY_RMENU;

        case XK_semicolon:
            return KEY_SEMICOLON;

        case XK_plus:
            return KEY_PLUS;

        case XK_comma:
            return KEY_COMMA;

        case XK_minus:
            return KEY_MINUS;

        case XK_period:
            return KEY_PERIOD;

        case XK_slash:
            return KEY_SLASH;

        case XK_grave:
            return KEY_GRAVE;

        case XK_a:
        case XK_A:
            return KEY_A;

        case XK_b:
        case XK_B:
            return KEY_B;

        case XK_c:
        case XK_C:
            return KEY_C;

        case XK_d:
        case XK_D:
            return KEY_D;

        case XK_e:
        case XK_E:
            return KEY_E;

        case XK_f:
        case XK_F:
            return KEY_F;

        case XK_g:
        case XK_G:
            return KEY_G;

        case XK_h:
        case XK_H:
            return KEY_H;

        case XK_i:
        case XK_I:
            return KEY_I;

        case XK_j:
        case XK_J:
            return KEY_J;

        case XK_k:
        case XK_K:
            return KEY_K;

        case XK_l:
        case XK_L:
            return KEY_L;

        case XK_m:
        case XK_M:
            return KEY_M;

        case XK_n:
        case XK_N:
            return KEY_N;

        case XK_o:
        case XK_O:
            return KEY_O;

        case XK_p:
        case XK_P:
            return KEY_P;

        case XK_q:
        case XK_Q:
            return KEY_Q;

        case XK_r:
        case XK_R:
            return KEY_R;

        case XK_s:
        case XK_S:
            return KEY_S;

        case XK_t:
        case XK_T:
            return KEY_T;

        case XK_u:
        case XK_U:
            return KEY_U;

        case XK_v:
        case XK_V:
            return KEY_V;

        case XK_w:
        case XK_W:
            return KEY_W;

        case XK_x:
        case XK_X:
            return KEY_X;

        case XK_y:
        case XK_Y:
            return KEY_Y;

        case XK_z:
        case XK_Z:
            return KEY_Z;

        default:
            return 0; 
    }
}

// - - - Vulkan Functions - - -

void platformGetRequiredExtensions(const char*** EXTENSIONS)
{
    listAppend(*EXTENSIONS, &"VK_KHR_xcb_surface");
}

bool8 platformCreateSurface(platformState* STATE, vulkanContext* CONTEXT)
{
    internalState* state = (internalState*)STATE->internalState;

    VkXcbSurfaceCreateInfoKHR createInfo = {VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR};
    createInfo.connection = state->connection;
    createInfo.window = state->window;
    
    VkResult result = vkCreateXcbSurfaceKHR(CONTEXT->instance, &createInfo, CONTEXT->allocator, &state->surface);
    if (result != VK_SUCCESS)
    {
        FORGE_LOG_FATAL("Failed to create the surface: %d\n", result);
        return FALSE;
    }
    CONTEXT->surface = state->surface;
    return TRUE;
}

#endif
