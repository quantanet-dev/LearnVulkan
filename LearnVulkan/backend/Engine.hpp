#pragma once

// Internal
#include "Window.hpp"

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

		void CreateWindow(int width, int height, std::string windowTitle);
		void Run();
		void Shutdown();

	private:
		bool m_ShouldQuit{ true };
		Window* m_Window{ nullptr };

	private:
		Engine() = default;
		~Engine();

	};

}