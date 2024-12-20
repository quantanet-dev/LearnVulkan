#pragma once

// Internal
#include "Window.hpp"
#include "renderer/instance.hpp"

//stdlib
#include <string>


namespace lv {

	class Engine {
	public:
		static inline Engine& GetInstance() {
			static Engine* instance = nullptr;
			if (!instance) {
				instance = new Engine;
			}
				return *instance;
		}

		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

		void Initialize(int width, int height, std::string windowTitle);
		void Run();
		void Shutdown();

	private:
		bool m_ShouldQuit{ true };
		Window* m_Window{ nullptr };
		VulkanInstance* m_VulkanInstance{ nullptr };
		std::string m_applicationName{ "LearnVulkan" }, m_EngineName{ "LearnVulkan" };

	private:
		Engine() = default;
		~Engine();

		void CreateWindow(int width, int height, std::string windowTitle);
		void CreateVulkanInstance();
	};

}