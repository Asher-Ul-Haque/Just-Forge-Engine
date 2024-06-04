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

    VkFormat depthFormat;
} vulkanDevice;

// - - - Vulkan Image
typedef struct vulkanImage
{
    VkImage handle;
    VkDeviceMemory memory;
    VkImageView view;
    unsigned int width;
    unsigned int height;
} vulkanImage;

// - - - Vulkan Swapchain
typedef struct vulkanSwapchain 
{
    VkSurfaceFormatKHR imageFormat; // Vulkan requires us to know the format of the images in the swapchain
    unsigned char maxFramesInFlight; // Maximum number of images in the swapchain
    VkSwapchainKHR handle;
    VkImage* images;
    unsigned int imageCount;
    VkImageView* imageViews; // Image views are required to use the images in the swapchain. Image views describe how to access an image and which part of the image to access
    vulkanImage depthAttachment;
} vulkanSwapchain;

// - - - Vulkan Context
typedef struct vulkanContext
{
    unsigned int framebufferHeight;
    unsigned int framebufferWidth;
    VkInstance instance;
    VkAllocationCallbacks* allocator;
    VkSurfaceKHR surface;
    vulkanDevice device;
    vulkanSwapchain swapchain;
    unsigned int imageIndex;
    unsigned int currentFrame;
    bool8 recreateSwapchain;
    int (*findMemoryIndex)(unsigned int TYPE_FILTER, unsigned int PROPERTY_FLAGS);
    #if defined(_DEBUG)
        VkDebugUtilsMessengerEXT debugMessenger;
    #endif
} vulkanContext;
