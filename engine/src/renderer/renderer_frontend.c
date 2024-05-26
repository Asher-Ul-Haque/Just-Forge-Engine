#include "renderer_frontend.h"
#include "renderer_backend.h"
#include "core/logger.h"
#include "core/memory.h"
#include "renderer_types.h"


// - - - | Renderer Frontend | - - -


// - - - Renderer Backend Instance
static rendererBackend* rendererBackendInstance = 0;


// - - - Renderer Frontend Class Methods - - -

bool8 rendererIntitialize(const char* APPLICATION, struct platformState *PLATFORM_STATE)
{
    rendererBackendInstance = forgeAllocateMemory(sizeof(rendererBackend), MEMORY_TAG_RENDERER);

    //TODO: make this configurable
    rendererBackendCreate(RENDERER_VULKAN, PLATFORM_STATE, rendererBackendInstance);
    rendererBackendInstance->frameNumber = 0;

    if (!rendererBackendInstance->initialize(rendererBackendInstance, APPLICATION, PLATFORM_STATE))
    {
        FORGE_LOG_FATAL("Renderer Backend Failed to Create!");
        return FALSE;
    }
    FORGE_LOG_INFO("Renderer Backend Initialized!");
    return TRUE;
}

void rendererShutdown()
{
    rendererBackendInstance->shutdown(rendererBackendInstance);
    forgeFreeMemory(rendererBackendInstance, sizeof(rendererBackend), MEMORY_TAG_RENDERER);
    FORGE_LOG_INFO("Renderer Backend Shutdown!");
}

bool8 rendererBeginFrame(float DELTA_TIME)
{
    return rendererBackendInstance->beginFrame(rendererBackendInstance, DELTA_TIME);
}

bool8 rendererEndFrame(float DELTA_TIME)
{
    rendererBackendInstance->frameNumber++;
    return rendererBackendInstance->endFrame(rendererBackendInstance, DELTA_TIME); 
}

bool8 rendererDrawFrame(rendererPacket *PACKET)
{
    if (rendererBeginFrame(PACKET->deltaTime))
    {
        if (!rendererEndFrame(PACKET->deltaTime))
        {
            FORGE_LOG_ERROR("Failed to finish frame: %llu", rendererBackendInstance->frameNumber);
            return FALSE;
        }
    }

    return TRUE;
}
