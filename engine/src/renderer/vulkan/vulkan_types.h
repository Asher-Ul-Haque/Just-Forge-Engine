#pragma once
#include "defines.h"
#include "core/asserts.h"
#include <vulkan/vulkan.h>

#define VK_CHECK(EXPRESSION) \
    { \
        FORGE_ASSERT(EXPRESSION == VK_SUCCESS); \
    }

typedef struct vulkanContext
{
    VkInstance instance;
    VkAllocationCallbacks* allocator;
    #if defined(_DEBUG)
        VkDebugUtilsMessengerEXT debugMessenger;
    #endif
} vulkanContext;
