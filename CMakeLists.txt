cmake_minimum_required(VERSION 3.20)
project(PhysicsEngine)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)

add_library(core
	core/renderer.cpp
)

find_package(OpenGL REQUIRED)
target_link_libraries(core PUBLIC OpenGL::GL)
target_link_libraries(core PUBLIC glfw) 
target_link_libraries(core PUBLIC glad) 

target_include_directories(core
	PUBLIC core/include
)

add_executable(app
	app/main.cpp	
)

target_link_libraries(app PRIVATE core)
