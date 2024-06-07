#include "vulkan_types.h"


// - - - | Command buffer functions | - - -


// - - - Allocation - - -

void commandBufferAllocate(vulkanContext* CONTEXT, VkCommandPool COMMAND_POOL, bool8 IS_PRIMARY, vulkanCommandBuffer* COMMAND_BUFFER);

void commandBufferFree(vulkanContext* CONTEXT, VkCommandPool COMMAND_POOL, vulkanCommandBuffer* COMMAND_BUFFER);


// - - - Recording - - -

void commandBufferBegin(vulkanCommandBuffer* COMMAND_BUFFER, bool8 IS_SINGLE_USE, bool8 IS_SIMULTANEOUS_USE, bool8 IS_RENDERPASS_CONTINUE);

void vulkanCommandBufferEnd(vulkanCommandBuffer* COMMAND_BUFFER);

void commandBufferUpdateSubmits(vulkanCommandBuffer* COMMAND_BUFFER);

void commandBufferReset(vulkanCommandBuffer* COMMAND_BUFFER);


// - - - Single use - - -

void commandBufferBeginSingleUse(vulkanContext* CONTEXT, VkCommandPool POOL, vulkanCommandBuffer* COMMAND_BUFFER);

void commandBufferEndSingleUse(vulkanContext* CONTEXT, VkCommandPool POOL, vulkanCommandBuffer* COMMAND_BUFFER, VkQueue QUEUE);
