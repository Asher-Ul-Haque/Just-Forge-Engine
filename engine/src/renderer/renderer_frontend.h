#pragma once
#include "renderer_types.h"


// - - - | Renderer Frontend | - - -


// - - - Forward Declarations
struct staticMeshData; 
struct platformState;


// - - - Renderer Frontend Struct (Class) - - -

bool8 rendererIntitialize(const char* APPLICATION, struct platformState* PLATFORM_STATE);

void rendererShutdown();

void rendererResized(unsigned short WIDTH, unsigned short HEIGHT);

bool8 rendererDrawFrame(rendererPacket* PACKET);
