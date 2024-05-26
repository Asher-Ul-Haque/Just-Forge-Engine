#include "logger.h"
#include "asserts.h"
#include "platform/platform.h"


// - - - | Log Functions | - - -


// - - - System Controls - - -

// TODO: temporary
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

bool8 initializeLogger()
{
    // TODO: create log file
    FORGE_LOG_INFO("Logger Initialized");
    return TRUE;
}

void shutdownLogger()
{
    FORGE_LOG_INFO("Logger Shutdown");
    // TODO: cleanup and write all queued entries
}


// - - - API Controls - - -

void logOutput(LogLevel LEVEL, const char* MESSAGE, ...)
{
    const char* levelStrings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
    bool8 isError = LEVEL < LOG_LEVEL_WARNING;
    const int messageLength = 32000;
    char outputMessage[messageLength];
    memset(outputMessage, 0, sizeof(outputMessage));

    // Add the rest of the arguments
    __builtin_va_list argumentPointer;
    va_start(argumentPointer, MESSAGE);
    vsnprintf(outputMessage, sizeof(outputMessage), MESSAGE, argumentPointer);
    va_end(argumentPointer);

    //Prepend with level header
    char finalMessage[32000];
    sprintf(finalMessage, "%s%s\n", levelStrings[LEVEL], outputMessage);

    //write to the console
    if (isError)
    {
        platformWriteConsoleError(finalMessage, LEVEL);
    }
    else 
    {
        platformWriteConsole(finalMessage, LEVEL);    
    }
}


// - - - | Assert Functions | - - -


void reportAssertionFailure(const char* EXPRESSION, const char* MESSAGE, const char* FILE, int LINE)
{
    logOutput(LOG_LEVEL_FATAL, "Assertion Failed: %s, message: %s in file: %s at line: %d", EXPRESSION, MESSAGE, FILE, LINE);
}
