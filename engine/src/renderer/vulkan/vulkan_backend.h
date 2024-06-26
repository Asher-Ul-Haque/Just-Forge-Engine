#pragma once
#include "renderer/renderer_backend.h"


// - - - | Vulkan as a Renderer Backend | - - -


// - - - Start and Shutdown - - -

bool8 vulkanRendererBackendInitialize(rendererBackend* BACKEND, const char* APPLICATION, struct platformState* PLATFORM);
void vulkanRendererBackendShutdown(rendererBackend* BACKEND);

// - - - Utils - - -
void vulkanRendererBackendResized(rendererBackend* BACKEND, unsigned short WIDTH, unsigned short HEIGHT);

// - - - Frame - - -
bool8 vulkanRendrerBackendBeginFrame(rendererBackend* BACKEND, float DELTA_TIME);
bool8 vulkanRendererBackendEndFrame(rendererBackend* BACKEND, float DELTA_TIME);
