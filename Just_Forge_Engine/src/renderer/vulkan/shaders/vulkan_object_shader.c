#include "vulkan_object_shader.h"
#include "core/logger.h"
#include "renderer/vulkan/vulkan_shader_utils.h"

#define BUILTIN_SHADER_NAME_OBJECT "Builtin.ObjectShader"

bool8 createObjectShader(vulkanContext* CONTEXT, vulkanObjectShader* SHADER)
{
    char stageTypeStrings[OBJECT_SHADER_STAGE_COUNT][5] = {"vert", "frag"};
    VkShaderStageFlagBits stageTypes[OBJECT_SHADER_STAGE_COUNT] = {VK_SHADER_STAGE_VERTEX_BIT, VK_SHADER_STAGE_FRAGMENT_BIT};

    for (unsigned int i = 0; i < OBJECT_SHADER_STAGE_COUNT; ++i)
    {
        if (!createShaderModule(CONTEXT, BUILTIN_SHADER_NAME_OBJECT, stageTypeStrings[i], stageTypes[i], i, SHADER->stages)) 
        {
            FORGE_LOG_ERROR("Unable to create %s shader module for '%s'", stageTypeStrings[i], BUILTIN_SHADER_NAME_OBJECT);
            return false;
        }
    }

    //TODO: Descriptors
    return true;
}

void destroyObjectShader(vulkanContext* CONTEXT, vulkanObjectShader* SHADER)
{
}

void useObjectShader(vulkanContext* CONTEXT, vulkanObjectShader* SHADER)
{
}
