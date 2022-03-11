#glew cannot be easily built from sources
#so we are going to do download a pre-built binary version

include (FetchContent)
FetchContent_Declare(
  glew_archive
  URL https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip/download
  URL_HASH MD5=32A72E6B43367DB8DBEA6010CD095355
)

FetchContent_MakeAvailable(glew_archive)

set(GLEW_DIR ${glew_archive_SOURCE_DIR})

add_library(glew STATIC IMPORTED)
set_property(TARGET glew PROPERTY
             IMPORTED_LOCATION ${GLEW_DIR}/lib/Release/x64/glew32s.lib)

#Setup include path and libraries
set(GLEW_INCLUDE_DIR ${GLEW_DIR}/include)
target_include_directories(glew INTERFACE ${GLEW_INCLUDE_DIR})
#using the static version of glew, so add the corresponding compile definitions to public defs
target_compile_definitions(glew INTERFACE -DGLEW_STATIC)



