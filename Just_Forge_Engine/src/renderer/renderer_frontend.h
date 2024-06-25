#pragma once
#include "renderer_types.h"


// - - - | Renderer Frontend | - - -


// - - - Renderer Frontend Struct (Class) - - -

bool8 renderingSystemIntitialize(unsigned long long* MEMORY_REQUIREMENT, void* STATE, const char* APPLICATION);

void rendererSystemShutdown(void* STATE);

void rendererResized(unsigned short WIDTH, unsigned short HEIGHT);

bool8 rendererDrawFrame(rendererPacket* PACKET);
