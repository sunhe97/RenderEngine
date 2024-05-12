cmake_minimum_required(VERSION 3.8)
project(GLFW)

# Variables for build configurations
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_CONFIG "debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(BUILD_CONFIG "release")
else()
    set(BUILD_CONFIG ${CMAKE_BUILD_TYPE})
endif()

# 获取系统名称
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(SYSTEM_NAME "windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(SYSTEM_NAME "linux")
else()
    set(SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
endif()

# 获取处理器架构
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(ARCHITECTURE "x64")
else()
    set(ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
endif()

# 设置outputdir
set(OUTPUT_DIR "${BUILD_CONFIG}-${SYSTEM_NAME}-${ARCHITECTURE}")
# GLFW library
set(GLFW_SRC
    include/GLFW/glfw3.h
    include/GLFW/glfw3native.h
 #   src/glfw_config.h
    src/context.c
    src/init.c
    src/input.c
    src/monitor.c
    src/null_init.c
    src/null_joystick.c
    src/null_monitor.c
    src/null_window.c
    src/platform.c
    src/vulkan.c
    src/window.c
)

if(WIN32)
    list(APPEND GLFW_SRC
        src/win32_init.c
        src/win32_joystick.c
        src/win32_module.c
        src/win32_monitor.c
        src/win32_time.c
        src/win32_thread.c
        src/win32_window.c
        src/wgl_context.c
        src/egl_context.c
        src/osmesa_context.c
    )
    add_definitions(-D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS)
    link_libraries(Dwmapi.lib)
elseif(UNIX AND NOT APPLE)
    list(APPEND GLFW_SRC
        src/x11_init.c
        src/x11_monitor.c
        src/x11_window.c
        src/xkb_unicode.c
        src/posix_time.c
        src/posix_thread.c
        src/glx_context.c
        src/egl_context.c
        src/osmesa_context.c
        src/linux_joystick.c
    )
    add_definitions(-D_GLFW_X11)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

add_library(GLFW STATIC ${GLFW_SRC})

target_include_directories(GLFW PUBLIC
    include
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DHZ_DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O1")
endif()


if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DHZ_RELEASE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
endif()

# Configuration specific options
#if(WIN32)
#    target_compile_options(GLFW PRIVATE
#        $<$<CONFIG:Release>:/MD>
#    )
#endif()

# Configuration specific definitions
#target_compile_definitions(GLFW PRIVATE
#    $<$<CONFIG:Debug>:DEBUG>
#    $<$<CONFIG:Release>:NDEBUG>
#)

# Configuration specific features
set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/${OUTPUT_DIR}/${PROJECT_NAME}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/${OUTPUT_DIR}/${PROJECT_NAME}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/${OUTPUT_DIR}/${PROJECT_NAME}"
        )