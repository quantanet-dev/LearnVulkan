// Internal
#include "backend/Engine.hpp"

// Defines entrypoint for the application

int main()
{
	lv::Engine& engine = lv::Engine::GetInstance();
	engine.Initialize(1280, 720, "LearnVulkan");
	engine.Run();

	return EXIT_SUCCESS;
}
