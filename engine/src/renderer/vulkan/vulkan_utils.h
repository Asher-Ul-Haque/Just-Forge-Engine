#pragma once
#include "vulkan_types.h"

const char* vulkanResultToString(VkResult RESULT, bool8 GET_MORE);

bool8 resultSuccess(VkResult RESULT);
