#include "logger.h"
#include "asserts.h"


// - - - | Log Functions | - - -


// - - - System Controls - - -

// TODO: temporary
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

bool8 initializeLogger()
{
    // TODO: create log file
    return TRUE;
}

void shutdownLogger()
{
    // TODO: cleanup and write all queued entries
}


// - - - API Controls - - -

void logOutput(LogLevel LEVEL, const char* MESSAGE, ...)
{
    const char* levelStrings[6] = {"[FATAL]:\t", "[ERROR]:\t", "[WARN]:\t\t", "[INFO]:\t\t", "[DEBUG]:\t", "[TRACE]:\t"};
    bool8 isError = LEVEL < 2;
    char outputMessage[32000];
    for (int i = 0; i < sizeof(outputMessage); ++i)
    {
        outputMessage[i] = 0;
    }

    // Add the rest of the arguments
    __builtin_va_list argumentPointer;
    va_start(argumentPointer, MESSAGE);
    vsnprintf(outputMessage, sizeof(outputMessage), MESSAGE, argumentPointer);
    va_end(argumentPointer);

    //Prepend with level header
    char finalMessage[32000];
    sprintf(finalMessage, "%s%s\n", levelStrings[LEVEL], outputMessage);

    // TODO: platform specific output
    //write to the console
    printf("%s", finalMessage);
}


// - - - | Assert Functions | - - -


void reportAssertionFailure(const char* EXPRESSION, const char* MESSAGE, const char* FILE, int LINE)
{
    logOutput(LOG_LEVEL_FATAL, "Assertion Failed: %s: %s\tin file: %s at line: %d", EXPRESSION, MESSAGE, FILE, LINE);
}
