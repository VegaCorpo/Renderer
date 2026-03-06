cmake_minimum_required(VERSION 3.14)

project(orbital_render)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CPM_USE_LOCAL_PACKAGES ON)

include(cmake/CPM.cmake)
CPMUsePackageLock(package-lock.cmake)
CPMGetPackage("Common")
CPMGetPackage("EnTT")
CPMGetPackage("Raylib")
CPMGetPackage("raylib_cpp")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /Od")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -O0")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g3 -O0")
    endif()
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Asan")
    if (MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /Od")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -O0 -fsanitize=address")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g3 -O0 -fsanitize=address")
    endif()
endif()

add_library(orbital_render SHARED
    src/RendererExtern.cpp
    src/RenderEngine.cpp
    src/RenderDataHandler.cpp
)

target_link_libraries(orbital_render PRIVATE
    Common
    EnTT::EnTT
    raylib
    raylib_cpp
)

target_include_directories(orbital_render PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Common_SOURCE_DIR}/include
)

if(WIN32)
    target_compile_definitions(orbital_render PRIVATE NOGDI NOUSER WIN32_LEAN_AND_MEAN)

    set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
    set(BUILD_DIR ${CMAKE_BINARY_DIR})
    set(RENDER_DIR "${BUILD_DIR}/render/${CMAKE_BUILD_TYPE}")

    set(TARGET_DIR "${PROJECT_DIR}")
endif()

#! =============================================
#! Temporary executable for testing RenderEngine
#! =============================================

if(ENABLE_RENDER_TEST)

add_executable(test_render src/testmain.cpp)

# Include the RenderEngine headers
target_include_directories(test_render PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Common_SOURCE_DIR}/include
)

# Link the RenderEngine shared library
target_link_libraries(test_render PRIVATE
    orbital_render
    Common
    EnTT::EnTT
    raylib
    raylib_cpp
)

# Set runtime library search path so it finds liborbital_render.so
set_target_properties(test_render PROPERTIES BUILD_RPATH "${CMAKE_BINARY_DIR}")

endif()
