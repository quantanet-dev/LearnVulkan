#include "device.hpp"

#include <iostream>
#include <map>

namespace lv
{

    bool FindQueueFamilies(vk::PhysicalDevice device)
    {
        QueueFamilyIndices indices;
        std::vector<vk::QueueFamilyProperties> queueFamilies = device.getQueueFamilyProperties();

        uint32_t i = 0;
        for (const auto &queueFamily : queueFamilies)
        {
            if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
            {
                indices.graphicsFamily = i;
            }

            i++;
        }

        return indices.isComplete();
    };

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

    vk::PhysicalDevice PickPhysicalDevice(std::vector<vk::PhysicalDevice> devices)
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

    VulkanDevice::VulkanDevice(const vk::Instance &instance)
    {
        std::vector<vk::PhysicalDevice> devices = instance.enumeratePhysicalDevices();
        m_PhysicalDevice = PickPhysicalDevice(devices);
        std::cout << "Selected device: \n";
        std::cout << "\tDeviceName: " << m_PhysicalDevice.getProperties().deviceName << "\n";
        std::cout << "\tDeviceType: " << vk::to_string(m_PhysicalDevice.getProperties().deviceType) << "\n";
        std::cout << "\tDriverVersion: " << m_PhysicalDevice.getProperties().driverVersion << "\n";
        std::cout << "\tAPIVersion: " << m_PhysicalDevice.getProperties().apiVersion << "\n";
    }

    VulkanDevice::~VulkanDevice()
    {
    }
}