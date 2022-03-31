#Add to your project in <root>/cmake/imgui.cmake
#Assumes that 'git submodule add https://github.com/ocornut/imgui dep/imgui' was ran

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/imgui)

set(IMGUI_INCLUDE_DIR ${IMGUI_DIR} ${IMGUI_DIR}/backends)

set(IMGUI_SRCS

${IMGUI_DIR}/imgui.cpp
${IMGUI_DIR}/imgui_draw.cpp
${IMGUI_DIR}/imgui_tables.cpp
${IMGUI_DIR}/imgui_widgets.cpp
${IMGUI_DIR}/backends/imgui_impl_sdl.cpp
)

# swap implementation between OGL3 and OGL2
if(${IMGUI_USE_OGL3})
  # supposes that GLEW is available
  add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLEW)
  set(IMGUI_SRCS ${IMGUI_SRCS} ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)
else()
  set(IMGUI_SRCS ${IMGUI_SRCS} ${IMGUI_DIR}/backends/imgui_impl_opengl2.cpp)
endif()

add_library(imgui STATIC ${IMGUI_SRCS})
target_include_directories(imgui PRIVATE 
  ${IMGUI_DIR}
  ${SDL_INCLUDE_DIR}
)

if(${IMGUI_USE_OGL3})
target_link_libraries(imgui glew)
endif()