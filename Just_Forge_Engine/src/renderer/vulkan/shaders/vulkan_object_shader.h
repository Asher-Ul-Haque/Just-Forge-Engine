#pragma once
#include "renderer/vulkan/vulkan_types.h"
#include "renderer/renderer_types.h"


bool8 createObjectShader(vulkanContext* CONTEXT, vulkanObjectShader* SHADER);
void destroyObjectShader(vulkanContext* CONTEXT, vulkanObjectShader* SHADER);

void useObjectShader(vulkanContext* CONTEXT, vulkanObjectShader* SHADER);


