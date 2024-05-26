#pragma once
#include "renderer/renderer_backend.h"

bool8 metalRendererBackendInitialize(rendererBackend* BACKEND, const char* APPLICATION, struct platformState* PLATFORM);

void metalRendererBackendShutdown(rendererBackend* BACKEND, unsigned short WIDTH, unsigned short HEIGHT);

bool8 metalRendrerBackendBeginFrame(rendererBackend* BACKEND, float DELTA_TIME);

bool8 metalRendererBackendEndFrame(rendererBackend* BACKEND, float DELTA_TIME);