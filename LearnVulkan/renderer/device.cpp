#include "device.hpp"
#include "instance.hpp"
#include <iostream>
#include <map>

namespace lv
{

    int rateDeviceSuitability(vk::PhysicalDevice device)
    {
        int score = 0;
        vk::PhysicalDeviceProperties deviceProperties = device.getProperties();

        if (deviceProperties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
        {
            score += 1000;
        }
        else if (deviceProperties.deviceType == vk::PhysicalDeviceType::eIntegratedGpu)
        {
            score += 500;
        }

        return score;
    }

    bool VulkanDevice::FindQueueFamilies(vk::PhysicalDevice device)
    {
        std::vector<vk::QueueFamilyProperties> queueFamilies = device.getQueueFamilyProperties();

        uint32_t i = 0;
        for (const auto &queueFamily : queueFamilies)
        {
            if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
            {
                m_QueueFamilyIndices.graphicsFamily = i;
            }
            if (queueFamily.queueFlags & vk::QueueFlagBits::eProtected)
            {
                m_QueueFamilyIndices.graphicsFamily = i;
            }

            std::cout << vk::to_string(queueFamily.queueFlags) << std::endl;

            i++;
        }

        return m_QueueFamilyIndices.isComplete();
    };

    vk::PhysicalDevice VulkanDevice::PickPhysicalDevice(std::vector<vk::PhysicalDevice> devices)
    {
        std::multimap<int, vk::PhysicalDevice> candidates;
        vk::PhysicalDevice chosenDevice{nullptr};
        for (const auto &device : devices)
        {
            int score = rateDeviceSuitability(device);
            candidates.insert(std::make_pair(score, device));
        }

        if (candidates.rbegin()->first > 0)
        {
            chosenDevice = candidates.rbegin()->second;
        }
        else
        {
            throw std::runtime_error("failed to find a suitable GPU!");
        }

        if (FindQueueFamilies(chosenDevice))
        {
            return chosenDevice;
        }
        else
        {
            throw std::runtime_error("unable to locate required device queue indices!");
        }

        return chosenDevice;
    }

    VulkanDevice::VulkanDevice(const vk::Instance &instance, const InstanceInfo &instanceInfo)
    {
        std::vector<vk::PhysicalDevice> devices = instance.enumeratePhysicalDevices();
        m_PhysicalDevice = PickPhysicalDevice(devices);
        std::cout << "Selected device: \n";
        std::cout << "\tDeviceName: " << m_PhysicalDevice.getProperties().deviceName << "\n";
        std::cout << "\tDeviceType: " << vk::to_string(m_PhysicalDevice.getProperties().deviceType) << "\n";
        std::cout << "\tDriverVersion: " << m_PhysicalDevice.getProperties().driverVersion << "\n";
        std::cout << "\tAPIVersion: " << m_PhysicalDevice.getProperties().apiVersion << "\n";

        float queuePriority = 1.0f;

        vk::DeviceQueueCreateInfo queueCreateInfo = vk::DeviceQueueCreateInfo(
            vk::DeviceQueueCreateFlags(),
            m_QueueFamilyIndices.graphicsFamily.value(),
            1,
            &queuePriority);

        vk::PhysicalDeviceFeatures deviceFeatures{};

        vk::DeviceCreateInfo deviceCreateInfo = vk::DeviceCreateInfo(
            vk::DeviceCreateFlags(),
            1,
            &queueCreateInfo,
            0,
            nullptr,
            0,
            nullptr);

        if (enableValidationLayers)
        {
            deviceCreateInfo.enabledLayerCount = instanceInfo.validationLayerCount;
            deviceCreateInfo.ppEnabledLayerNames = instanceInfo.validationLayers.data();
        }

#ifdef MacOS
        const char *macOSextension = "VK_KHR_portability_subset";
        deviceCreateInfo.enabledExtensionCount = 1;
        deviceCreateInfo.ppEnabledExtensionNames = &macOSextension;
#endif

        m_LogicalDevice = m_PhysicalDevice.createDevice(deviceCreateInfo);
    }

    VulkanDevice::~VulkanDevice()
    {
        m_LogicalDevice.destroy();
    }
}