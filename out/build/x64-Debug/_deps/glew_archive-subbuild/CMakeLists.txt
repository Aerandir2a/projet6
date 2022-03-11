# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.20.21032501-MSVC_2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(glew_archive-populate NONE)



include(ExternalProject)
ExternalProject_Add(glew_archive-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip/download" "URL_HASH" "MD5=32A72E6B43367DB8DBEA6010CD095355"
                    SOURCE_DIR          "D:/Users/ppiglioni/projet6/out/build/x64-Debug/_deps/glew_archive-src"
                    BINARY_DIR          "D:/Users/ppiglioni/projet6/out/build/x64-Debug/_deps/glew_archive-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


