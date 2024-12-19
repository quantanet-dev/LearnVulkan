// Internal
#include "Engine.hpp"
#include "Window.hpp"


namespace lv {

	Window::Window(int width, int height, std::string windowTitle) :
		m_Width(width), m_Height(height), m_WindowTitle(windowTitle)
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowTitle.c_str(), nullptr, nullptr);
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			Engine& engine = Engine::GetInstance();
			engine.Shutdown();
		});
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::PollEvents()
	{
		if (!glfwWindowShouldClose(m_Window)) {
			glfwPollEvents();
		}
	}

}