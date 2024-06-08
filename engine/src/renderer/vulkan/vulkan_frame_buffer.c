#include "vulkan_frame_buffer.h"
#include "core/memory.h"

void createFrameBuffer(vulkanContext* CONTEXT, vulkanRenderpass* RENDERPASS, unsigned int WIDTH, unsigned int HEIGHT, unsigned int ATTACHMENT_COUNT, VkImageView* ATTACHMENTS, vulkanFramebuffer* FRAMEBUFFER)
{
    // Make a copy of the attachments, renderpass and attachment count
    FRAMEBUFFER->attachments = forgeAllocateMemory(sizeof(VkImageView) * ATTACHMENT_COUNT, MEMORY_TAG_RENDERER);
    for (unsigned int i = 0; i < ATTACHMENT_COUNT; i++)
    {
        FRAMEBUFFER->attachments[i] = ATTACHMENTS[i];
    }
    FRAMEBUFFER->renderpass = RENDERPASS;
    FRAMEBUFFER->attachmentCount = ATTACHMENT_COUNT;

    // Create the framebuffer
    VkFramebufferCreateInfo framebufferInfo = {};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = RENDERPASS->handle;
    framebufferInfo.attachmentCount = ATTACHMENT_COUNT;
    framebufferInfo.pAttachments = ATTACHMENTS;
    framebufferInfo.width = WIDTH;
    framebufferInfo.height = HEIGHT;
    framebufferInfo.layers = 1;

    VK_CHECK(vkCreateFramebuffer(CONTEXT->device.logicalDevice, &framebufferInfo, CONTEXT->allocator, &FRAMEBUFFER->handle));
}

void destroyFrameBuffer(vulkanContext* CONTEXT, vulkanFramebuffer* FRAMEBUFFER)
{
    vkDestroyFramebuffer(CONTEXT->device.logicalDevice, FRAMEBUFFER->handle, CONTEXT->allocator);
    if (FRAMEBUFFER->attachments)
    {
        forgeFreeMemory(FRAMEBUFFER->attachments, sizeof(VkImageView) * FRAMEBUFFER->attachmentCount, MEMORY_TAG_RENDERER);
        FRAMEBUFFER->attachments = 0;
    }
    FRAMEBUFFER->attachmentCount = 0;
    FRAMEBUFFER->renderpass = 0;
    FRAMEBUFFER->handle = 0;
}
