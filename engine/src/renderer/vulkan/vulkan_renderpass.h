#pragma once
#include "vulkan_types.h"

void createRenderpass(vulkanContext* CONTEXT, vulkanRenderpass* RENDERPASS, float X, float Y, float WIDTH, float HEIGHT, float CLEAR_COLOR[4], float DEPTH, unsigned int PENCIL);

void destroyRenderpass(vulkanContext* CONTEXT, vulkanRenderpass* RENDERPASS);

void beginRenderpass(vulkanCommandBuffer* COMMAND_BUFFER, vulkanRenderpass* RENDERPASS, VkFramebuffer FRAMEBUFFER);

void endRenderpass(vulkanCommandBuffer* COMMAND_BUFFER, vulkanRenderpass* RENDERPASS);
