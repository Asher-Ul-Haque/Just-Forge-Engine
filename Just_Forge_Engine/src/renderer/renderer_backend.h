#pragma once
#include "renderer_types.h"


// - - - | Renderer Backend | - - -


// - - - Renderer Backend Functions - - - 

bool8 rendererBackendCreate(rendererBackendType TYPE, rendererBackend* BACKEND);

void rendererBackendDestroy(rendererBackend* BACKEND);
