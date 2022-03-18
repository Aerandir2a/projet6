cmake_minimum_required(VERSION 3.23)

project(moteur)

add_executable(moteur main.cpp gc_3d_defs.hpp 
shader/shader.hpp shader/loadShader.cpp 
shader/TranformVertexShader.vertexshader.txt shader/SimpleFragmentShader.fragmentshader.txt 
stb_image.h stb.c stb.h
images/UwU3.gif images/UwU2.jpg images/rickroll_roll.gif)

add_subdirectory(SDL dep/SDL)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)


include(CMake/glew.cmake)

set(IMGUI_USE_OGL3 true)
include(CMake/imgui.cmake)

target_include_directories(moteur PRIVATE 
	${SDL_INCLUDE_DIR} 
	${GLM_INCLUDE_DIR}
	${IMGUI_INCLUDE_DIR}
)
target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32 glew imgui)