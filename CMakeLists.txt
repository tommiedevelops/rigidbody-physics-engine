cmake_minimum_required(VERSION 3.20)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)

add_library(core
	core/renderer.cpp
	"core/renderer.h"
	"core/constants.h"
)

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
)

target_link_libraries(app PRIVATE core)
