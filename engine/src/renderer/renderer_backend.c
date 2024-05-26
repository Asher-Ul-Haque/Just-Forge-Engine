#include "renderer_backend.h"
#include "rendererTypes.h"


// - - - Renderer Backend Functions - - -

bool8 rendererBackendCreate(rendererBackendType TYPE, struct platformState* PLATFORM_STATE, rendererBackend* BACKEND)
{
    BACKEND->platform = PLATFORM_STATE;

    switch (TYPE)
    {
        case RENDERER_NULL:
            return TRUE; // If You dont want a renderer, you could just say so

        case RENDERER_OPENGL:
            //TODO: make an openGL renderer
            return TRUE;

        case RENDERER_DIRECTX:
            //TODO: make a DirectX renderer
            return TRUE;

        case RENDERER_VULKAN:
            //TODO: make a Vulkan renderer
            return TRUE;

        case RENDERER_METAL:
            //TODO: make a Metal renderer
            return TRUE;
    }
    return FALSE;
}

void rendererBackendDestroy(rendererBackend* BACKEND)
{
    BACKEND->initialize = 0;
    BACKEND->shutdown = 0;
    BACKEND->resized = 0;
    BACKEND->beginFrame = 0;
    BACKEND->endFrame = 0;
    BACKEND->shutdown(BACKEND);
}
