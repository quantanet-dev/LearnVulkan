#pragma once

// deps
#include "vulkan/vulkan.hpp"
#include "device.hpp"

namespace lv
{

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