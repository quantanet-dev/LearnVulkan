#include "Engine.hpp"

namespace lv {

	Engine::~Engine()
	{
		delete m_Window;
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