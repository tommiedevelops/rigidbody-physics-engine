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
	"core/renderer/Model.h"
	"core/renderer/renderer.cpp"
	"core/renderer/renderer.h"
	"core/constants.h"
    "core/physics/physics_world.cpp"
	"core/physics/physics_world.h"
	"core/scene/Entity.cpp"
	"core/scene/Entity.h"
	"core/scene/scene.cpp"
	"core/scene/scene.h"
	"core/renderer/shader.h"
	"core/renderer/shader.cpp"
	"core/renderer/texture.cpp"
	"core/renderer/texture.h"
)

find_package(OpenGL REQUIRED)
target_link_libraries(core PUBLIC OpenGL::GL)
target_link_libraries(core PUBLIC glfw) 
target_link_libraries(core PUBLIC glad) 
target_link_libraries(core PUBLIC glm) 
target_link_libraries(core PUBLIC EnTT::EnTT)
target_link_libraries(core PUBLIC assimp)

target_include_directories(core
	PUBLIC core external
)

add_executable(app
	"app/Main.cpp"
	"core/app/app.cpp"
	"core/app/app.h"
	"core/app/window.cpp"
	"core/app/window.h"
	"core/renderer/renderer.cpp"
	"core/renderer/renderer.h"
	"core/constants.h"
    "core/physics/physics_world.cpp"
	"core/physics/physics_world.h"
	"core/scene/Entity.cpp"
	"core/scene/Entity.h"
	"core/scene/scene.cpp"
	"core/scene/scene.h"
	"core/renderer/shader.h"
	"core/renderer/shader.cpp"
	"core/renderer/texture.cpp"
	"core/renderer/texture.h"
	"core/renderer/Mesh.h"
)

target_link_libraries(app PRIVATE core)
