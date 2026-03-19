cmake_minimum_required(VERSION 3.20)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)

add_library(core
	"core/renderer/renderer.cpp"
	"core/renderer/renderer.h"
	"core/constants.h"
    "core/physics/physics_world.cpp"
	"core/physics/physics_world.h"
	"core/scene/scene.cpp"
	"core/scene/scene.h"
	"core/app.cpp"
	"core/app.h"
 "core/game_math/vector.cpp" "core/game_math/vector.h" "core/game_math/matrix.cpp" "core/game_math/matrix.h" "core/game_math/quaternion.cpp" "core/game_math/quaternion.h" "core/resource_manager/mesh.cpp" "core/resource_manager/mesh.h")

find_package(OpenGL REQUIRED)
target_link_libraries(core PUBLIC OpenGL::GL)
target_link_libraries(core PUBLIC glfw) 
target_link_libraries(core PUBLIC glad) 

target_include_directories(core
	PUBLIC core
)

add_executable(app
	app/main.cpp	
    "core/constants.h"
 "core/physics/physics_world.cpp" "core/physics/physics_world.h" "core/scene/scene.cpp" "core/scene/scene.h" "core/app.cpp" "core/app.h" "core/game_math/vector.cpp" "core/game_math/vector.h" "core/game_math/matrix.cpp" "core/game_math/matrix.h" "core/game_math/quaternion.cpp" "core/game_math/quaternion.h" "core/resource_manager/mesh.cpp" "core/resource_manager/mesh.h")

target_link_libraries(app PRIVATE core)
