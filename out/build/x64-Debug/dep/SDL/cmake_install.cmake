# Install script for directory: D:/Users/ppiglioni/projet6/SDL

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/Users/ppiglioni/projet6/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/SDL2d.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/SDL2d.dll")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/SDL2maind.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/SDL2-staticd.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake"
         "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/CMakeFiles/Export/cmake/SDL2Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/CMakeFiles/Export/cmake/SDL2Targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/CMakeFiles/Export/cmake/SDL2Targets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2mainTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2mainTargets.cmake"
         "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/CMakeFiles/Export/cmake/SDL2mainTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2mainTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2mainTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/CMakeFiles/Export/cmake/SDL2mainTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/CMakeFiles/Export/cmake/SDL2mainTargets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2staticTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2staticTargets.cmake"
         "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/CMakeFiles/Export/cmake/SDL2staticTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2staticTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2staticTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/CMakeFiles/Export/cmake/SDL2staticTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/CMakeFiles/Export/cmake/SDL2staticTargets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES
    "D:/Users/ppiglioni/projet6/SDL/SDL2Config.cmake"
    "D:/Users/ppiglioni/projet6/out/build/x64-Debug/SDL2ConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "D:/Users/ppiglioni/projet6/SDL/include/SDL.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_assert.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_atomic.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_audio.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_bits.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_blendmode.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_clipboard.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_config_android.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_config_emscripten.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_config_iphoneos.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_config_macosx.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_config_minimal.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_config_os2.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_config_pandora.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_config_windows.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_config_winrt.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_copying.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_cpuinfo.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_egl.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_endian.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_error.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_events.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_filesystem.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_gamecontroller.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_gesture.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_haptic.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_hidapi.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_hints.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_joystick.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_keyboard.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_keycode.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_loadso.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_locale.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_log.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_main.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_messagebox.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_metal.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_misc.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_mouse.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_mutex.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_name.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_opengl.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_opengl_glext.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_opengles.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_opengles2.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_opengles2_gl2.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_opengles2_gl2ext.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_opengles2_gl2platform.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_opengles2_khrplatform.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_pixels.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_platform.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_power.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_quit.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_rect.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_render.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_rwops.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_scancode.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_sensor.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_shape.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_stdinc.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_surface.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_system.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_syswm.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_test.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_test_assert.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_test_common.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_test_compare.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_test_crc32.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_test_font.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_test_fuzzer.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_test_harness.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_test_images.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_test_log.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_test_md5.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_test_memory.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_test_random.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_thread.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_timer.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_touch.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_types.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_version.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_video.h"
    "D:/Users/ppiglioni/projet6/SDL/include/SDL_vulkan.h"
    "D:/Users/ppiglioni/projet6/SDL/include/begin_code.h"
    "D:/Users/ppiglioni/projet6/SDL/include/close_code.h"
    "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/include/SDL_config.h"
    "D:/Users/ppiglioni/projet6/out/build/x64-Debug/dep/SDL/include/SDL_revision.h"
    )
endif()

