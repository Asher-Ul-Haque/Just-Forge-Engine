#include <core/logger.h>
#include <core/asserts.h>

int main(void) 
{
    FORGE_LOG_FATAL("A test messgae: %f", 3.14);
    FORGE_LOG_ERROR("A test messgae: %f", 3.14);
    FORGE_LOG_WARNING("A test messgae: %f", 3.14);
    FORGE_LOG_INFO("A test messgae: %f", 3.14);
    FORGE_LOG_DEBUG("A test messgae: %f", 3.14);
    FORGE_LOG_TRACE("A test messgae: %f", 3.14);

    FORGE_ASSERT(1 == 1);
    FORGE_ASSERT_MESSAGE(1 == 0, "This is a test message");
    return 0;
}
