#pragma once
#include "defines.h"
#include "core/asserts.h"
#include <vulkan/vulkan.h>


// - - - Assert on Vulkan check
#define VK_CHECK(EXPRESSION) \
    { \
        FORGE_ASSERT(EXPRESSION == VK_SUCCESS); \
    }


// - - - | Structs | - - -


// - - - Vulkan Swapchain Support Info
typedef struct vulkanSwapchainSupportInfo
{
    VkSurfaceCapabilitiesKHR capabilities;
    unsigned int formatCount;
    VkSurfaceFormatKHR* formats;
    unsigned int presentModeCount;
    VkPresentModeKHR* presentModes;
} vulkanSwapchainSupportInfo; 

// - - - Vulkan Device
typedef struct vulkanDevice
{
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;
    vulkanSwapchainSupportInfo swapchainSupport;

    int graphicsQueueIndex;
    int presentQueueIndex;
    int computeQueueIndex;
    int transferQueueIndex;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkQueue computeQueue;
    VkQueue transferQueue;

    VkPhysicalDeviceProperties properties;
    VkPhysicalDeviceFeatures features;
    VkPhysicalDeviceMemoryProperties memory;
} vulkanDevice;

// - - - Vulkan Context
typedef struct vulkanContext
{
    VkInstance instance;
    VkAllocationCallbacks* allocator;
    VkSurfaceKHR surface;
    vulkanDevice device;
    #if defined(_DEBUG)
        VkDebugUtilsMessengerEXT debugMessenger;
    #endif
} vulkanContext;
