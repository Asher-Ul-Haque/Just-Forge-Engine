#include <core/logger.h>
#include <core/asserts.h>
#include <platform/platform.h>

int main(void) 
{
    FORGE_LOG_FATAL("A test messgae: %f", 3.14);
    FORGE_LOG_ERROR("A test messgae: %f", 3.14);
    FORGE_LOG_WARNING("A test messgae: %f", 3.14);
    FORGE_LOG_INFO("A test messgae: %f", 3.14);
    FORGE_LOG_DEBUG("A test messgae: %f", 3.14);
    FORGE_LOG_TRACE("A test messgae: %f", 3.14);

    platformState state;
    if(platformInit(&state, "Just Forge Tester", 100, 100, 1280, 720)) {
        while(TRUE) {
            platformGiveMessages(&state);
        }
    }
    platformShutdown(&state);
    return 0;
}
