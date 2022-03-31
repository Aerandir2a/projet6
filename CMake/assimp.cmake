#Assumes that the following command was ran : git submodule add https://github.com/assimp/assimp.git dep/assimp

set(ASSIMP_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/dep/assimp)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(${ASSIMP_ROOT} dep/assimp)

set(ASSIMP_INCLUDE_DIR ${ASSIMP_ROOT}/include)
