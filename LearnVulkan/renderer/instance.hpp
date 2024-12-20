#pragma once

#ifdef LV_HOST_OS
#if LV_HOST_OS == Darwin
#define MacOS
#endif
#endif

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif // !NDEBUG

// deps
#include "vulkan/vulkan.hpp"
#include "device.hpp"

namespace lv
{

	struct InstanceInfo
	{
		std::vector<const char *> validationLayers;
		uint32_t validationLayerCount;
		std::vector<const char *> extensions;
		uint32_t extensionCount;
	};

	class VulkanInstance
	{
	public:
		VulkanInstance(std::string applicationName, std::string engineName);
		~VulkanInstance();

	private:
		vk::Instance m_Instance{nullptr};
		uint32_t m_Version{0};
		VulkanDevice *m_Device{nullptr};

	private:
		std::vector<vk::ExtensionProperties> CheckExtensionSupport();
		bool CheckValidationLayerSupport();
	};
}