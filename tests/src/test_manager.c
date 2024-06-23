#include "test_manager.h"
#include <dataStructures/list.h>
#include <core/logger.h>
#include <core/clock.h>

typedef struct TestEntry
{
    testFunction func;
    char* description;
} TestEntry;

static TestEntry* tests;

void initializeTestManager()
{
    tests = listCreate(TestEntry);
}

void testManagerRegisterTest(unsigned char (*testFunction)(), char *DESCRIPTION)
{
    TestEntry entry;
    entry.func = testFunction;
    entry.description = DESCRIPTION;
    listAppend(tests, entry);
}

void testManagerRunTests()
{
    unsigned int passed = 0;
    unsigned int failed = 0;
    unsigned int bypassed = 0;

    unsigned int count = listLength(tests);
    clock totalTime;
    clockStart(&totalTime);

    for (unsigned int i = 0; i < count; ++i)
    {
        clock testTime;
        clockStart(&testTime);
        unsigned char result = tests[i].func();
        clockUpdate(&testTime);

        if (result == true)
        {
            ++passed;
        }
        else if (result == BYPASS)
        {
            FORGE_LOG_WARNING("Test bypassed: %s", tests[i].description);
            ++failed;
        }
        else
        {
            FORGE_LOG_ERROR("Test Failed: %s", tests[i].description);
            ++failed;
        }

        clockUpdate(&totalTime);
        FORGE_LOG_INFO("Executed %d of %d, (%.6f sec / %.6f sec total)", i + 1, count, testTime.elapsedTime, totalTime.elapsedTime);
    }

    clockStop(&totalTime);
    FORGE_LOG_INFO("Results: %d passed, %d failed, %d bypassed", passed, failed, bypassed);
}
