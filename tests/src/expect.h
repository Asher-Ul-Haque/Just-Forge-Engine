#include <core/logger.h>
#include <math/forge_math.h>


#define expectShouldBe(EXPECTED, ACTUAL) \
    if (EXPECTED != ACTUAL) \
    { \
        FORGE_LOG_ERROR("Expected: %d, Actual: %s.%d", EXPECTED, ACTUAL, __FILE__, __LINE__); \
        return false; \
    }

#define expectShouldNotBe(EXPECTED, ACTUAL) \
    if (EXPECTED == ACTUAL) \
    { \
        FORGE_LOG_ERROR("Not Expected: %d, Actual: %s.%d", EXPECTED, ACTUAL, __FILE__, __LINE__); \
        return false; \
    }

#define expectFloatShouldBe(EXPECTED, ACTUAL) \
    if (EXPECTED - ACTUAL > 0.001f) \
    { \
        FORGE_LOG_ERROR("Expected: %f, Actual: %f.%d", EXPECTED, ACTUAL, __FILE__, __LINE__); \
        return false; \
    }

#define expectFloatShouldNotBe(EXPECTED, ACTUAL) \
    if (EXPECTED - ACTUAL < 0.001f) \
    { \
        FORGE_LOG_ERROR("Not Expected: %f, Actual: %f.%d", EXPECTED, ACTUAL, __FILE__, __LINE__); \
        return false; \
    }

#define expectToBeTrue(ACTUAL) \
    if (ACTUAL != true) \
    { \
        FORGE_LOG_ERROR("Expected %s to be true, got false instead. File: %s.%d.", ACTUAL, __FILE__, __LINE__); \
        return false; \
    }

#define expectToBeFalse(ACTUAL) \
    if (ACTUAL != false) \
    { \
        FORGE_LOG_ERROR("Expected %s to be false, got true instead. File: %s.%d.", ACTUAL, __FILE__, __LINE__); \
        return false; \
    }
