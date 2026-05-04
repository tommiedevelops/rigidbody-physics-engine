cmake_minimum_required(VERSION 3.20)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(external/glad)
add_subdirectory(external/glm)
add_subdirectory(external/entt)
add_subdirectory(external/imgui)

add_library(core
	Core/Application/App.cpp
	
	Core/Layers/LayerStack.cpp
	Core/Layers/SceneLayer.cpp
	Core/Layers/GlobalOverlayLayer.cpp

	Core/AssetManager/AssetManager.cpp
	Core/AssetManager/Shader.cpp
	Core/AssetManager/Texture.cpp
	Core/AssetManager/Mesh.cpp
	Core/AssetManager/Material.h
	

	Core/Physics/Rigidbody.cpp
	Core/Physics/RigidbodyForceRegistry.cpp
	Core/Physics/GravityForceGenerator.cpp

	Core/Collisions/ContactGenerator.cpp
	Core/Collisions/ContactResolver.cpp

	Core/Scene/Entity.cpp
	Core/Scene/Scene.cpp
	

	Core/Platform/Window.cpp
	Core/Platform/GameTime.cpp
	Core/Scene/ScriptableEntity.cpp
)

find_package(OpenGL REQUIRED)
target_link_libraries(core PUBLIC OpenGL::GL)
target_link_libraries(core PUBLIC glad) 
target_link_libraries(core PUBLIC glm) 
target_link_libraries(core PUBLIC EnTT::EnTT)
target_link_libraries(core PUBLIC imgui)

if (EMSCRIPTEN)
	target_link_options(core PRIVATE -sUSE_GLFW=3)
else()
	add_subdirectory(external/glfw)
	target_link_libraries(core PUBLIC glfw)
endif()

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
		Core/Collisions
		Core
		External
)

add_executable(app App/Main.cpp App/PlayerMoveScript.cpp) 

if (EMSCRIPTEN)
	target_link_options(app PRIVATE
        -sUSE_GLFW=3
        -sMIN_WEBGL_VERSION=2
        -sMAX_WEBGL_VERSION=2
        -sALLOW_MEMORY_GROWTH=1
        --preload-file ${CMAKE_SOURCE_DIR}/Assets@/Assets
    )
    set_target_properties(app PROPERTIES SUFFIX ".html")
endif()

target_link_libraries(app PRIVATE core)




