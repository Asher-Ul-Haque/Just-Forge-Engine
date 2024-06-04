#include "vulkan_backend.h"
#include "vulkan_types.h"
#include "vulkan_platform.h"
#include "vulkan_device.h"
#include "vulkan_swapchain.h"
#include "core/logger.h"
#include "core/asserts.h"
#include "dataStructures/list.h"
#include "platform/platform.h" //TODO: remove this
#include <string.h>


// - - - | Vulkan Setup | - - -


// - - - Vulkan Context
static vulkanContext context;

// - - - Debug Callback
VKAPI_ATTR VkBool32 VKAPI_CALL vkDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT MESSAGE_SEVERITY, VkDebugUtilsMessageTypeFlagsEXT MESSAGE_TYPES, const VkDebugUtilsMessengerCallbackDataEXT* CALLBACK_DATA, void* USER_DATA);

// - - - FindMemoryIndex
int findMemoryIndex(unsigned int TYPE_FILTER, VkMemoryPropertyFlags PROPERTIES_FLAGS);


// - - - | Vulkan as a Renderer Backend | - - -


bool8 vulkanRendererBackendInitialize(rendererBackend* BACKEND, const char* APPLICATION, struct platformState* PLATFORM)
{
    //Function pointers
    context.findMemoryIndex = findMemoryIndex;

    //TODO: custom allocator
    context.allocator = 0;


    //Setup vulkan instance
    VkApplicationInfo appInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    appInfo.apiVersion = VK_API_VERSION_1_2; //Vulkan API version 1.2.0 seems popular
    appInfo.pApplicationName = APPLICATION; 
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0); //Version of the application
    appInfo.pEngineName = "Just Forge Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0); //Version of the game engine

    VkInstanceCreateInfo createInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    createInfo.pApplicationInfo = &appInfo;
    
    const char** requiredExtensions = listCreate(const char*);
    listAppend(requiredExtensions, &VK_KHR_SURFACE_EXTENSION_NAME); // Required for surface creation
    platformGetRequiredExtensions(&requiredExtensions);
    #if defined(_DEBUG)
        listAppend(requiredExtensions, &VK_EXT_DEBUG_UTILS_EXTENSION_NAME); // Required for debug utils
        FORGE_LOG_DEBUG("Required extensions: ");
        for (unsigned long long i = 0; i < listLength(requiredExtensions); ++i)
        {
            FORGE_LOG_DEBUG("    %s", requiredExtensions[i]);
        }
    #endif

    createInfo.enabledExtensionCount = listLength(requiredExtensions);
    createInfo.ppEnabledExtensionNames = requiredExtensions;


    //Validation layers
    const char** requiredValidationLayerNames = 0;
    unsigned int requiredValidationLayerCount = 0;

    #if defined(_DEBUG)
        FORGE_LOG_DEBUG("Validation layers enabled, Counting...");

        //The list of required validation layers
        requiredValidationLayerNames = listCreate(const char*);
        listAppend(requiredValidationLayerNames, &"VK_LAYER_KHRONOS_validation");
        requiredValidationLayerCount = listLength(requiredValidationLayerNames);

        //Get the available validation layers
        unsigned int availableLayerCount = 0;
        VK_CHECK(vkEnumerateInstanceLayerProperties(&availableLayerCount, 0));
        VkLayerProperties* availableLayers = listReserve(VkLayerProperties, availableLayerCount);
        VK_CHECK(vkEnumerateInstanceLayerProperties(&availableLayerCount, availableLayers));

        //Verify that the required validation layers are available
        for (unsigned int i = 0; i < requiredValidationLayerCount; ++i)
        {
            FORGE_LOG_DEBUG("Checking for validation layer: %s", requiredValidationLayerNames[i]);
            bool8 layerFound = FALSE;
            for (unsigned int j = 0; j < availableLayerCount; ++j)
            {
                if (strcmp(requiredValidationLayerNames[i], availableLayers[j].layerName) == 0)
                {
                    layerFound = TRUE;
                    FORGE_LOG_DEBUG("Validation layer found: %s", requiredValidationLayerNames[i]);
                    break;
                }
            }

            if (!layerFound)
            {
                FORGE_LOG_FATAL("Validation layer not found: %s", requiredValidationLayerNames[i]);
                return FALSE;
            }
        }
        FORGE_LOG_DEBUG("All required validation layers found.");
    #endif

    createInfo.enabledLayerCount = requiredValidationLayerCount;
    createInfo.ppEnabledLayerNames = requiredValidationLayerNames;

    VK_CHECK(vkCreateInstance(&createInfo, context.allocator, &context.instance));
    FORGE_LOG_DEBUG("Vulkan instance created");


    //Setup debug messenger
    #if defined(_DEBUG)
        FORGE_LOG_DEBUG("Creating debug messenger...");
        unsigned int logSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
        debugCreateInfo.messageSeverity = logSeverity;
        debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugCreateInfo.pfnUserCallback = vkDebugCallback;
        debugCreateInfo.pUserData = 0;

        PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(context.instance, "vkCreateDebugUtilsMessengerEXT");
        FORGE_ASSERT_MESSAGE(func, "Failed to create debug messenger!");
        VK_CHECK(func(context.instance, &debugCreateInfo, context.allocator, &context.debugMessenger));
        FORGE_LOG_DEBUG("Vulkan debugger created.");
    #endif
    
    //Setup vulkan surface
    FORGE_LOG_DEBUG("Creating vulkan surface...");
    if (!platformCreateSurface(PLATFORM, &context))
    {
        FORGE_LOG_ERROR("Failed to create vulkan surface");
        return FALSE;
    }

    //Setup vulkan device
    if (!createVulkanDevice(&context))
    {
        FORGE_LOG_ERROR("Failed to create vulkan device");
        return FALSE;
    }

    // Swapchain
    createVulkanSwapchain(&context, context.framebufferWidth, context.framebufferHeight, &context.swapchain);
    
    FORGE_LOG_DEBUG("Vulkan Renderer Initialized");
    return TRUE;
}

void vulkanRendererBackendShutdown(rendererBackend* BACKEND)
{
    //Destroy in the opposite order of creation

    FORGE_LOG_DEBUG("Destroying vulkan swapchain...");
    destroyVulkanSwapchain(&context, &context.swapchain);

    FORGE_LOG_DEBUG("Destroying vulkan device...");
    destroyVulkanDevice(&context);

    FORGE_LOG_DEBUG("Destroying vulkan surface...");
    if (context.surface)
    {
        vkDestroySurfaceKHR(context.instance, context.surface, context.allocator);
        context.surface = 0;
    }
        
    FORGE_LOG_DEBUG("Destroying vulkan debugger...");
    if (context.debugMessenger)
    {
        PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(context.instance, "vkDestroyDebugUtilsMessengerEXT");
        func(context.instance, context.debugMessenger, context.allocator);
    }

    FORGE_LOG_DEBUG("Destroying Vulkan Instance...");
    vkDestroyInstance(context.instance, context.allocator);
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

VKAPI_ATTR VkBool32 VKAPI_CALL vkDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT MESSAGE_SEVERITY, VkDebugUtilsMessageTypeFlagsEXT MESSAGE_TYPES, const VkDebugUtilsMessengerCallbackDataEXT* CALLBACK_DATA, void* USER_DATA)
{
    switch (MESSAGE_SEVERITY)
    {
        default:

        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            FORGE_LOG_ERROR(CALLBACK_DATA->pMessage);
            break;

        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            FORGE_LOG_WARNING(CALLBACK_DATA->pMessage);
            break;

        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            FORGE_LOG_INFO(CALLBACK_DATA->pMessage);
            break;

        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            FORGE_LOG_TRACE(CALLBACK_DATA->pMessage);
            break;
    }
    return VK_FALSE;
}

int findMemoryIndex(unsigned int TYPE_FILTER, unsigned int PROPERTY_FLAGS)
{
    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(context.device.physicalDevice, &memoryProperties);

    for (unsigned int i = 0; i < memoryProperties.memoryTypeCount; ++i)
    {
        if ((TYPE_FILTER & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & PROPERTY_FLAGS) == PROPERTY_FLAGS)
        {
            return i;
        }
    }

    FORGE_LOG_WARNING("Failed to find suitable memory type");
    return -1;
}
