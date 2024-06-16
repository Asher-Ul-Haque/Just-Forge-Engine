#pragma once
#include "renderer/renderer_backend.h"

bool8 directXRendererBackendInitialize(rendererBackend* BACKEND, const char* APPLICATION, struct platformState* PLATFORM);

void directXRendererBackendShutdown(rendererBackend* BACKEND, unsigned short WIDTH, unsigned short HEIGHT);

bool8 directXRendrerBackendBeginFrame(rendererBackend* BACKEND, float DELTA_TIME);

bool8 directXRendererBackendEndFrame(rendererBackend* BACKEND, float DELTA_TIME);