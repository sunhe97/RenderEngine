cmake_minimum_required(VERSION 3.8)
project(ImGui)

set(CMAKE_CXX_STANDARD 17)

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

# ImGui library
set(IMGUI_SRC
    imconfig.h
    imgui.h
    imgui.cpp
    imgui_draw.cpp
    imgui_internal.h
    imgui_tables.cpp
    imgui_widgets.cpp
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    imgui_demo.cpp
)



add_library(ImGui STATIC ${IMGUI_SRC})
target_compile_features(ImGui PUBLIC cxx_std_17)

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

# 设置静态运行时库
#if(WIN32)
#    target_compile_options(ImGui PRIVATE /MD)
#endif()

# 配置系统相关选项
#if(UNIX)
#    set_target_properties(ImGui PROPERTIES POSITION_INDEPENDENT_CODE ON)
#endif()

# 设置输出目录
set_target_properties(ImGui PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}"
        )