cmake_minimum_required(VERSION 3.20)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/glm)

add_library(core
	"core/renderer/renderer.cpp"
	"core/renderer/renderer.h"
	"core/constants.h"
    "core/physics/physics_world.cpp"
	"core/physics/physics_world.h"
	"core/scene/scene.cpp"
	"core/scene/scene.h"
    "core/game_math/vector.cpp"
	"core/game_math/vector.h"
	"core/game_math/matrix.cpp"
	"core/game_math/matrix.h"
	"core/game_math/quaternion.cpp"
	"core/game_math/quaternion.h"
	"core/scene/mesh.cpp"
	"core/scene/mesh.h"
	"core/renderer/opengl/shader.h"
	"core/renderer/opengl/shader.cpp"
	"core/renderer/opengl/texture.cpp"
	"core/renderer/opengl/texture.h"
	"core/renderer/opengl/buffer.cpp"
	"core/renderer/opengl/buffer.h"
	"core/renderer/opengl/vertex_array.cpp"
	"core/renderer/opengl/vertex_array.h"
	"core/renderer/opengl/framebuffer.cpp"
	"core/renderer/opengl/framebuffer.h"
	"core/renderer/opengl/render_state.h"
	"core/renderer/passes/IRenderPass.h"
	"core/renderer/passes/ShadowPass.h"
	"core/renderer/passes/ShadowPass.cpp"
	"core/renderer/passes/GeometryPass.h"
	"core/renderer/passes/GeometryPass.cpp"
	"core/renderer/passes/SkyboxPass.h"
	"core/renderer/passes/SkyboxPass.cpp"
	"core/renderer/passes/PostProcessPass.h"
	"core/renderer/passes/PostProcessPass.cpp"
	"core/renderer/resources/ResourceManager.cpp"
	"core/renderer/resources/ResourceManager.h"
	"core/renderer/RenderContext.h"
	"core/scene/Entity.h"
	"core/scene/Transform.h";
	"core/scene/Camera.h"
	"core/scene/Material.h"
	"core/scene/Light.h"
)

find_package(OpenGL REQUIRED)
target_link_libraries(core PUBLIC OpenGL::GL)
target_link_libraries(core PUBLIC glfw) 
target_link_libraries(core PUBLIC glad) 
target_link_libraries(core PUBLIC glm) 

target_include_directories(core
	PUBLIC core external
)

add_executable( app
	app/main.cpp	
    "core/constants.h"
    "core/physics/physics_world.cpp" 
	"core/physics/physics_world.h"
	"core/scene/scene.cpp"
	"core/scene/scene.h"
	"core/app/app.cpp"
	"core/app/app.h"
	"core/game_math/vector.cpp"
	"core/game_math/vector.h"
	"core/game_math/matrix.cpp"
	"core/game_math/matrix.h"
	"core/game_math/quaternion.cpp"
	"core/game_math/quaternion.h"
	"core/scene/mesh.cpp"
	"core/scene/mesh.h"
	"core/app/window.cpp"
	"core/app/window.h"
	"core/renderer/opengl/shader.h"
	"core/renderer/opengl/shader.cpp"
	"core/renderer/opengl/texture.cpp"
	"core/renderer/opengl/texture.h"
 "core/renderer/opengl/buffer.cpp" "core/renderer/opengl/buffer.h" "core/renderer/opengl/vertex_array.cpp" "core/renderer/opengl/vertex_array.h" "core/renderer/opengl/framebuffer.cpp" "core/renderer/opengl/framebuffer.h" "core/renderer/opengl/render_state.h" "core/renderer/passes/IRenderPass.h" "core/renderer/passes/ShadowPass.h" "core/renderer/passes/ShadowPass.cpp" "core/renderer/passes/GeometryPass.h" "core/renderer/passes/GeometryPass.cpp" "core/renderer/passes/SkyboxPass.h" "core/renderer/passes/SkyboxPass.cpp" "core/renderer/passes/PostProcessPass.h" "core/renderer/passes/PostProcessPass.cpp" "core/renderer/resources/ResourceManager.cpp" "core/renderer/resources/ResourceManager.h" "core/renderer/RenderContext.h" "core/scene/Entity.h" "core/scene/Transform.h" "core/scene/Camera.h" "core/scene/Material.h" "core/scene/Light.h")

target_link_libraries(app PRIVATE core)
