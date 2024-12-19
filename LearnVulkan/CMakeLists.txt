# CMakeList.txt : CMake project for LearnVulkan, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (LearnVulkan "main.cpp"  "backend/Window.hpp" "backend/Window.cpp" "backend/Engine.cpp")

find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED )

target_link_libraries(LearnVulkan PRIVATE glfw Vulkan::Vulkan )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LearnVulkan PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
