#include "test_manager.h"
#include "memory/pile_allocator_tests.h"
#include <core/logger.h>

int main()
{
    initializeTestManager();

    // TODO: Register tests here
    pileAllocatorRegisterTests();
    
    FORGE_LOG_DEBUG("Running tests...");

    testManagerRunTests();

    return 0;
}
