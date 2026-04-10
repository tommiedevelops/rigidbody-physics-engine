cmake_minimum_required(VERSION 3.20)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/glm)
add_subdirectory(external/entt)
add_subdirectory(external/assimp)

add_library(core
	Core/Application/App.cpp
	
	Core/Layers/LayerStack.cpp
	Core/Layers/SceneLayer.cpp
	Core/Layers/UILayer.cpp

	Core/AssetManager/AssetManager.cpp
	Core/AssetManager/Shader.cpp
	Core/AssetManager/Texture.cpp
	Core/AssetManager/Mesh.cpp
	Core/AssetManager/Material.h
	Core/AssetManager/Material.cpp

	Core/Scene/Entity.cpp
	Core/Scene/Scene.cpp

	Core/Platform/Window.cpp
	Core/Platform/GameTime.cpp
)

find_package(OpenGL REQUIRED)
target_link_libraries(core PUBLIC OpenGL::GL)
target_link_libraries(core PUBLIC glfw) 
target_link_libraries(core PUBLIC glad) 
target_link_libraries(core PUBLIC glm) 
target_link_libraries(core PUBLIC EnTT::EnTT)
target_link_libraries(core PUBLIC assimp)

target_include_directories(core
	PUBLIC
		Core/Includes
		Core/Application
		Core/Physics
		Core/Renderer
		Core/Scene
		Core/AssetManager
		Core/Platform
		Core/Scripting
		Core/Layers
		Core/Events
		Core
		External
)

add_executable(app App/Main.cpp)

target_link_libraries(app PRIVATE core)




