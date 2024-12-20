// Internal
#include "Engine.hpp"

namespace lv {

	Engine::~Engine()
	{
		delete m_Window;
		delete m_VulkanInstance;
	}

	void Engine::Initialize(int width, int height, std::string windowTitle)
	{
		CreateWindow(width, height, windowTitle);
		CreateVulkanInstance();
	}

	void Engine::CreateVulkanInstance()
	{
		m_VulkanInstance = new VulkanInstance(m_applicationName, m_EngineName);
	}

	void Engine::CreateWindow(int width, int height, std::string windowTitle)
	{
		m_Window = new Window(width, height, windowTitle);
	}

	void Engine::Run()
	{
		m_ShouldQuit = false;

		while (!m_ShouldQuit){
			m_Window->PollEvents();
		}
	}

	void Engine::Shutdown()
	{
		m_ShouldQuit = true;
	}

}