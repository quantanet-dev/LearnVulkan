#pragma once

#include "vulkan/vulkan.hpp"
#include <optional>

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

    struct InstanceInfo;

    class VulkanDevice
    {
    public:
        VulkanDevice(const vk::Instance &instance, const InstanceInfo &instanceInfo);
        ~VulkanDevice();

        vk::PhysicalDevice GetPhysicalDevice() const { return m_PhysicalDevice; }

    private:
        vk::PhysicalDevice PickPhysicalDevice(std::vector<vk::PhysicalDevice> devices);
        bool FindQueueFamilies(vk::PhysicalDevice device);

    private:
        vk::PhysicalDevice m_PhysicalDevice;
        vk::Device m_LogicalDevice;
        QueueFamilyIndices m_QueueFamilyIndices;
        vk::Queue m_GraphicsQueue;
    };
}