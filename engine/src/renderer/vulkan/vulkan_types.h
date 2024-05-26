#pragma once
#include "defines.h"
#include <vulkan/vulkan.h>


typedef struct vulkanContext
{
    VkInstance instance;
    VkAllocationCallbacks* allocator;
} vulkanContext;
