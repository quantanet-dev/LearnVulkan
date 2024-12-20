// Internal
#include "instance.hpp"
#include "version.hpp"

// Deps
#include "GLFW/glfw3.h"

// stdlib
#include <iostream>
#include <string>

#ifdef LV_HOST_OS
#if LV_HOST_OS == Darwin
#define MacOS
#endif
#endif

// TODO: Add VkDebugUtilsMessengerEXT

namespace lv
{
	static InstanceInfo p_InstanceInfo;

	lv::VulkanInstance::VulkanInstance(std::string applicationName, std::string engineName)
	{
		p_InstanceInfo.validationLayers = {"VK_LAYER_KHRONOS_validation"};
		p_InstanceInfo.validationLayerCount = p_InstanceInfo.validationLayers.size();

		m_Version = vk::enumerateInstanceVersion();

		std::vector<vk::ExtensionProperties> availableExtensions = CheckExtensionSupport();

#ifdef MacOS
		p_InstanceInfo.extensions.emplace_back(vk::KHRPortabilityEnumerationExtensionName);
#endif

		for (const auto &extension : availableExtensions)
		{
			p_InstanceInfo.extensions.emplace_back(extension.extensionName);
		}

		p_InstanceInfo.extensionCount = p_InstanceInfo.extensions.size();

		if (enableValidationLayers && !CheckValidationLayerSupport())
		{
			throw std::runtime_error("validation layers requested, but not available!");
		}

		vk::ApplicationInfo appInfo = vk::ApplicationInfo(
			applicationName.c_str(),
			VK_MAKE_VERSION(
				applicationVersion.Major,
				applicationVersion.Minor,
				applicationVersion.Patch),
			engineName.c_str(),
			VK_MAKE_VERSION(
				applicationVersion.Major,
				applicationVersion.Minor,
				applicationVersion.Patch),
			m_Version);

		vk::InstanceCreateInfo createInfo{};
		if (enableValidationLayers)
		{
			createInfo = vk::InstanceCreateInfo(
				vk::InstanceCreateFlags(),
				&appInfo,
				p_InstanceInfo.validationLayerCount,
				p_InstanceInfo.validationLayers.data(),
				p_InstanceInfo.extensionCount,
				p_InstanceInfo.extensions.data());
		}
		else
		{
			createInfo = vk::InstanceCreateInfo(
				vk::InstanceCreateFlags(),
				&appInfo,
				0,
				nullptr,
				p_InstanceInfo.extensionCount,
				p_InstanceInfo.extensions.data());
		}

#ifdef MacOS
		createInfo.flags = vk::InstanceCreateFlags(VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR);
#endif

		m_Instance = vk::createInstance(createInfo);
		if (!m_Instance)
		{
			throw std::runtime_error("unable to create vulkan instance!");
		}

		m_Device = new VulkanDevice(m_Instance, p_InstanceInfo);
	}

	lv::VulkanInstance::~VulkanInstance()
	{
		delete m_Device;
		m_Instance.destroy();
	}

	std::vector<vk::ExtensionProperties> VulkanInstance::CheckExtensionSupport()
	{
		uint32_t glfwExtensionCount = 0;

		const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		if (!glfwExtensions)
		{
			throw std::runtime_error("cannot get glfw extensions!");
		}

		std::vector<const char *> glfwExtensionsStrings;

		std::cout << "Required extensions: \n";
		for (uint32_t i = 0; i < glfwExtensionCount; i++)
		{
			std::cout << "\t" << glfwExtensions[i] << "\n";
			glfwExtensionsStrings.emplace_back(glfwExtensions[i]);
		}

		std::vector<vk::ExtensionProperties> availableExtensions = vk::enumerateInstanceExtensionProperties();
		std::vector<const char *> enabledExtensions;

		std::cout << "Available Extensions: \n";
		for (const auto &extension : availableExtensions)
		{
			enabledExtensions.emplace_back(extension.extensionName);
			std::cout << "\t" << extension.extensionName.data() << "\n";
		}

		bool found = false;
		for (uint32_t i = 0; i < glfwExtensionCount; i++)
		{
			found = std::find(enabledExtensions.begin(), enabledExtensions.end() - 1, glfwExtensionsStrings[i]) != enabledExtensions.end();
		};

		if (!found)
		{
			throw std::runtime_error("Required extensions are not supported!");
		}

		return availableExtensions;
	}

	bool VulkanInstance::CheckValidationLayerSupport()
	{
		std::vector<vk::LayerProperties> layers = vk::enumerateInstanceLayerProperties();

		std::cout << "Available Layers: \n";
		for (uint32_t i = 0; i < layers.size(); i++)
		{
			std::cout << "\t" << layers[i].layerName << std::endl;
		}

		bool layerFound = false;
		for (const char *layerName : p_InstanceInfo.validationLayers)
		{
			for (const auto &layerProperties : layers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					std::cout << "Found Requested Layer: " << layerProperties.layerName << std::endl;
					break;
				}
			}
		}

		return layerFound;
	}

}