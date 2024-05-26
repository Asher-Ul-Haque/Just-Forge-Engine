#include "vulkan_backend.h"
#include "vulkan_types.h"
#include "core/logger.h"


static vulkanContext context;

bool8 vulkanRendererBackendInitialize(rendererBackend* BACKEND, const char* APPLICATION, struct platformState* PLATFORM)
{
    //TODO: custom allocator
    context.allocator = 0;

    //Setup vulkan instance
    VkApplicationInfo appInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    appInfo.apiVersion = VK_API_VERSION_1_2; //Vulkan API version 1.2.0 seems popular
    appInfo.pApplicationName = APPLICATION; 
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0); //Version of the application
    appInfo.pEngineName = "Just Forge Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0); //Version of the game engine

    VkInstanceCreateInfo createInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = 0;
    createInfo.ppEnabledExtensionNames = 0;
    createInfo.ppEnabledLayerNames = 0;

    VkResult result = vkCreateInstance(&createInfo, context.allocator, &context.instance);
    if (result != VK_SUCCESS)
    {
        FORGE_LOG_ERROR("vkCreateInstance failed with result: %u", result);
        return FALSE;
    }
    FORGE_LOG_INFO("Vulkan Renderer Initialized");
    return TRUE;
}

void vulkanRendererBackendShutdown(rendererBackend* BACKEND)
{
}

void vulkanRendererBackendResized(rendererBackend* BACKEND, unsigned short WIDTH, unsigned short HEIGHT)
{
}

bool8 vulkanRendrerBackendBeginFrame(rendererBackend* BACKEND, float DELTA_TIME)
{
    return TRUE;
}

bool8 vulkanRendererBackendEndFrame(rendererBackend* BACKEND, float DELTA_TIME)
{
    return TRUE;
}
