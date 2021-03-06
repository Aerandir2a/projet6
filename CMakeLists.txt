cmake_minimum_required(VERSION 3.23)

project(moteur)

add_executable(moteur
main.cpp
gc_3d_defs.hpp
shader/shader.hpp
shader/loadShader.cpp
shader/TranformVertexShader.vertexshader.txt
shader/SimpleFragmentShader.fragmentshader.txt
shader/SimpleFragmentShader.fragmentshaderGif.txt
shader/1.model_loading.fs
shader/1.model_loading.vs
header/stb_image.h
glad/glad.h
src/directorySnippet.cpp
header/buffer.hpp
header/camera.hpp
header/controls.hpp
header/directorySnippet.hpp
header/table.hpp
header/mesh.h
header/model.h
header/shader_.h
src/buffer.cpp
src/camera.cpp
src/controls.cpp
src/table.cpp
Texture.hpp 
Texture.cpp
stb.c
stb.h
)

add_subdirectory(SDL dep/SDL)

add_custom_target(copy_shader COMMAND ${CMAKE_COMMAND}
-E copy_directory ${CMAKE_SOURCE_DIR}/shader $<TARGET_FILE_DIR:moteur>/shader)

add_dependencies(moteur copy_shader)

add_custom_target(copy_objets3D COMMAND ${CMAKE_COMMAND}
-E copy_directory ${CMAKE_SOURCE_DIR}/objets3D $<TARGET_FILE_DIR:moteur>/objets3D)

add_dependencies(moteur copy_objets3D)

add_custom_target(copy_images COMMAND ${CMAKE_COMMAND}
-E copy_directory ${CMAKE_SOURCE_DIR}/images $<TARGET_FILE_DIR:moteur>/images)

add_dependencies(moteur copy_images)

set_property(TARGET moteur PROPERTY CXX_STANDARD 17)


set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)
set(ASSIMP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/assimp)
set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/imgui)


include(CMake/glew.cmake)

set(IMGUI_USE_OGL3 true)
include(CMake/imgui.cmake)

include(CMake/assimp.cmake)



target_include_directories(moteur PRIVATE 
	${SDL_INCLUDE_DIR} 
	${GLM_INCLUDE_DIR}
	${IMGUI_INCLUDE_DIR}
)

target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32 glew imgui assimp)