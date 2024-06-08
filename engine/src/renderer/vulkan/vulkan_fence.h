#pragma once
#include "vulkan_types.h"

void createFence(vulkanContext* CONTEXT, bool8 createSignal, vulkanFence* FENCE);

void destroyFence(vulkanContext* CONTEXT, vulkanFence* FENCE);

bool8 waitForFence(vulkanContext* CONTEXT, vulkanFence* FENCE, unsigned long long TIMEOUT);

void resetFence(vulkanContext* CONTEXT, vulkanFence* FENCE);
