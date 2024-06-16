#pragma once
#include "renderer_types.h"


// - - - | Renderer Backend | - - -


// - - - Forward Declaration
struct platformState;


// - - - Renderer Backend Functions - - - 

bool8 rendererBackendCreate(rendererBackendType TYPE, struct platformState* PLATFORM_STATE, rendererBackend* BACKEND);

void rendererBackendDestroy(rendererBackend* BACKEND);
