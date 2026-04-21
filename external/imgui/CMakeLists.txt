cmake_minimum_required(VERSION 3.20)
project(ImGUI)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/External/imgui)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui
    ${IMGUI_SOURCES}
)

target_link_libraries(imgui PUBLIC glfw)

target_sources(imgui PRIVATE ${IMGUI_SOURCES})

target_include_directories(imgui
    PUBLIC
        ${IMGUI_DIR} 
        ${IMGUI_DIR}/backends
)
