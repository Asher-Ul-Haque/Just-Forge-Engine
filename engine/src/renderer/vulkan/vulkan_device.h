#pragma once
#include "vulkan_types.h"


// - - - | Vulkan Device Functions | - - -

bool8 createVulkanDevice(vulkanContext* CONTEXT);

void destroyVulkanDevice(vulkanContext* CONTEXT);

bool8 vulkanDeviceQuerySwapchainSupport(VkPhysicalDevice GPU, VkSurfaceKHR SURFACE, vulkanSwapchainSupportInfo* INFO);

bool8 vulkanDeviceDetectDepthFormat(vulkanDevice* DEVICE);
