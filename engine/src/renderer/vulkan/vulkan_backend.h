#pragma once
#include "renderer/renderer_backend.h"

bool8 vulkanRendererBackendInitialize(rendererBackend* BACKEND, const char* APPLICATION, struct platformState* PLATFORM);

void vulkanRendererBackendShutdown(rendererBackend* BACKEND);

void vulkanRendererBackendResized(rendererBackend* BACKEND, unsigned short WIDTH, unsigned short HEIGHT);

bool8 vulkanRendrerBackendBeginFrame(rendererBackend* BACKEND, float DELTA_TIME);

bool8 vulkanRendererBackendEndFrame(rendererBackend* BACKEND, float DELTA_TIME);
