#include <string.h>
#include "vulkan_backend.h"
#include "vulkan_types.h"
#include "core/logger.h"
#include "dataStructures/list.h"
#include "vulkan_platform.h"


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
    
    const char** requiredExtensions = listCreate(const char*);
    listAppend(requiredExtensions, VK_KHR_SURFACE_EXTENSION_NAME); // Required for surface creation
    platformGetRequiredExtensions(&requiredExtensions); //TODO: make this function platformGetRequiredExtensions
    #if defined(_DEBUG)
        listAppend(requiredExtensions, VK_EXT_DEBUG_UTILS_EXTENSION_NAME); // Required for debug utils
        FORGE_LOG_DEBUG("Required extensions: ");
        for (unsigned long long i = 0; i < _listGetField(requiredExtensions, LIST_LENGTH); ++i)
        {
            FORGE_LOG_DEBUG("/t%s", requiredExtensions[i]);
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
        FORGE_LOG_INFO("All required validation layers found.");
    #endif


    createInfo.enabledLayerCount = requiredValidationLayerCount;
    createInfo.ppEnabledLayerNames = requiredValidationLayerNames;

    VK_CHECK(vkCreateInstance(&createInfo, context.allocator, &context.instance));
    FORGE_LOG_INFO("Vulkan Renderer Initialized");

    #if defined(_DEBUG)
        FORGE_LOG_DEBUG("Creating debug messenger...");
        unsigned int logSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
        debugCreateInfo.messageSeverity = logSeverity;
        debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
        debugCreateInfo.pfnUserCallback = vkDebugCallback;
        debugCreateInfo.pUserData = 0;
    #endif

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
