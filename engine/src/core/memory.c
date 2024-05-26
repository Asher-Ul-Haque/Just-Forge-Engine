#include "memory.h"
#include "core/logger.h"
#include "logger.h"
#include "platform/platform.h"
#include "string.h"
#include "stdio.h"


// - - - Memory Stats - - -

struct memoryStats
{
    unsigned long long totalAllocated;
    unsigned long long taggedAllocated[MEMORY_TAG_MAX];
};

static struct memoryStats stats;

// - - - String representation of tags
static const char* memoryTagAsStrings[MEMORY_TAG_MAX] = {
    "NONE           ",
    "ARRAY          ",
    "LIST           ",
    "DICTIONARY     ",
    "CIRCULAR_QUEUE ",
    "BST            ",
    "STRING         ",
    "APPLICATION    ",
    "TASK           ",
    "TEXTURE        ",
    "MATERIAL       ",
    "RENDERER       ",
    "GAME           ",
    "TRANSFORM      ",
    "ENTITY         ",
    "ENTITY_NODE    ",
    "SCENE          "};


// - - - | Memory Functions | - - -


// - - - Engine Memory Functions - - -

void initializeMemory()
{
    FORGE_LOG_INFO("Memory Initialized");
    platformZeroMemory(&stats, sizeof(stats));
}

void shutdownMemory()
{
    FORGE_LOG_INFO("Memory Shutdown");
    //TODO: cleanup of memory applications
}


// - - - Game Developer Memory Functions - - -

void* forgeAllocateMemory(unsigned long long SIZE, memoryTag TAG)
{
    if (TAG == MEMORY_TAG_NONE)
    {
        FORGE_LOG_WARNING("forgeAllocateMemory called using MEMORY_TAG_NONE. Recommended to use only tagged allocations");
    }

    stats.totalAllocated += SIZE;
    stats.taggedAllocated[TAG] += SIZE;

    // TODO: memory allignment
    void* memoryBlock = platformAllocateMemory(SIZE, FALSE);
    platformZeroMemory(memoryBlock, SIZE);

    return memoryBlock;
}

void forgeFreeMemory(void* MEMORY, unsigned long long SIZE, memoryTag TAG)
{
    if (TAG == MEMORY_TAG_NONE)
    {
        FORGE_LOG_WARNING("forgeAllocateMemory called using MEMORY_TAG_NONE. Recommended to use only tagged allocations");
    }

    stats.totalAllocated -= SIZE;
    stats.taggedAllocated[TAG] -= SIZE;

    // TODO: memory allignment
    platformFreeMemory(MEMORY, FALSE);
}

void forgeZeroMemory(void* MEMORY, unsigned long long SIZE)
{
    platformZeroMemory(MEMORY, SIZE);
}

void forgeCopyMemory(void* DESTINATION, const void* SOURCE, unsigned long long SIZE)
{
    platformCopyMemory(DESTINATION, SOURCE, SIZE);
}

void forgeSetMemory(void* MEMORY, int VALUE, unsigned long long SIZE)
{
    platformSetMemory(MEMORY, VALUE, SIZE);
}

// - - - Debug Function
char* forgeGetMemoryStats()
{
    const unsigned long long kb = 1024; //Cant allocated less than a byte
    const unsigned long long mb = kb * 1024;
    const unsigned long long gb = mb * 1024;

    char buffer[8000] = "System memory use (tagged):\n";
    unsigned long long offset = strlen(buffer);
    float amount = 1.0f;
    char unit[3] = "XB";
    for (int i = 0; i < MEMORY_TAG_MAX; ++i)
    {
        if (stats.taggedAllocated[i] >= gb)
        {
            unit[0] = 'G';
            amount = stats.taggedAllocated[i] / (float) gb;
        }
        else if (stats.taggedAllocated[i] >= mb)
        {
            unit[0] = 'M';
            amount = stats.taggedAllocated[i] / (float) mb;
        }
        else if (stats.taggedAllocated[i] >= kb)
        {
            unit[0] = 'K';
            amount = stats.taggedAllocated[i] / (float) kb;
        }
        else
        {
            unit[0] = 'B';
            unit[1] = 0; //Terminate string
            amount = stats.taggedAllocated[i];
        }

        int length = snprintf(buffer + offset, 8000, "  %s: %.2f %s\n", memoryTagAsStrings[i], amount, unit);
        offset += length;

        //Add a total memory allocation
    }
    unsigned long long total = stats.totalAllocated;
    if (total >= gb)
    {
        unit[0] = 'G';
        amount = total / (float) gb;
    }
    else if (total >= mb)
    {
        unit[0] = 'M';
        amount = total / (float) mb;
    }
    else if (total >= kb)
    {
        unit[0] = 'K';
        amount = total / (float) kb;
    }
    else
    {
        unit[0] = 'B';
        unit[1] = 0; //Terminate string
        amount = total;
    }
    snprintf(buffer + offset, 8000, "  Total: %.2f %s\n", amount, unit);

    char* outputString = stringDuplicate(buffer);
    return outputString;
}
