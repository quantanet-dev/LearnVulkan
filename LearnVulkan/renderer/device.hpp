#pragma once

#include "vulkan/vulkan.hpp"

namespace lv
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;

        bool isComplete()
        {
            return graphicsFamily.has_value();
        }
    };

    class VulkanDevice
    {
    public:
        VulkanDevice(const vk::Instance &instance);
        ~VulkanDevice();

        vk::PhysicalDevice GetPhysicalDevice() const { return m_PhysicalDevice; }

    private:
        vk::PhysicalDevice m_PhysicalDevice{nullptr};
    };
}