#pragma once

// Stdlib
#include <string>

// Deps
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace lv {

	class Window {
	public:
		Window(int width, int height, std::string windowTitle);
		~Window();

		void PollEvents();

		inline GLFWwindow& GetGlfwWindow() const { return *m_Window; }

	private:
		GLFWwindow* m_Window{ nullptr };
		int m_Width{ 640 }, m_Height{ 480 };
		std::string m_WindowTitle{ "Untitled" };
	};

}