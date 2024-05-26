#pragma once 
#include "defines.h"


// - - - | Renderer Structs | - - -


// - - - Types of Graphics API
typedef enum rendererBackendType
{
    RENDERER_OPENGL,
    RENDERER_DIRECTX,
    RENDERER_VULKAN,
    RENDERER_METAL,
    RENDERER_NULL
} rendererBackendType;


// - - - Renderer Backend Struct (Class) - - -

typedef struct rendererBackend 
{
    unsigned long long frameNumber;

    struct platformState* platform;

    bool8 (*initialize)(struct rendererBackend* BACKEND, const char* APPLICATION, struct platformState* PLATFORM_STATE);

    bool8 (*shutdown)(struct rendererBackend* BACKEND);

    void (*resized)(struct rendererBackend* BACKEND, unsigned short WIDTH, unsigned short HEIGHT);

    bool8 (*beginFrame)(struct rendererBackend* BACKEND, float DELTA_TIME);

    bool8 (*endFrame)(struct rendererBackend* BACKEND, float DELTA_TIME);
    
} rendererBackend;


// - - - Renderer Packet Struct 
typedef struct rendererPacket
{
    float deltaTime;
} rendererPacket;
