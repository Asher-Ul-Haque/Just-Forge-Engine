#pragma once
#include "renderer/renderer_backend.h"

bool8 openGLRendererBackendInitialize(rendererBackend* BACKEND, const char* APPLICATION, struct platformState* PLATFORM);

void openGLRendererBackendShutdown(rendererBackend* BACKEND, unsigned short WIDTH, unsigned short HEIGHT);

bool8 openGLRendrerBackendBeginFrame(rendererBackend* BACKEND, float DELTA_TIME);

bool8 openGLRendererBackendEndFrame(rendererBackend* BACKEND, float DELTA_TIME);