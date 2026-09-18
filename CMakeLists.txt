cmake_minimum_required(VERSION 3.14)

project(orbital_render)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_CXX_STANDARD 23 CACHE STRING "C++ standard")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CPM_USE_LOCAL_PACKAGES ON)

include(cmake/CPM.cmake)
CPMUsePackageLock(package-lock.cmake)

CPMGetPackage("Common")
CPMGetPackage("Eigen")
CPMGetPackage("EnTT")
CPMGetPackage("glfw")
CPMGetPackage("glad")
CPMGetPackage("stb")

set(glfw3_FOUND TRUE)

# glad2 doesn't provide an out-of-the-box library: its own CMakeLists exposes glad_add_library,
# which generates the loader for the requested API/profile.
add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
glad_add_library(glad_gl_core_41 STATIC REPRODUCIBLE API gl:core=4.1)

set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /Od")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -O0")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g3 -O0")
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Asan")
    if(MSVC)
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

    # Drawables
    src/drawables/MeshDrawable.cpp
    src/drawables/LineDrawable.cpp
    src/drawables/TextDrawable.cpp

    # Renderer
    src/graphics/GLRenderer.cpp
    src/graphics/GLContext.cpp
    src/graphics/GLMesh.cpp
    src/graphics/GLTexture.cpp
    src/graphics/models/ModelLoader.cpp
    src/graphics/models/OBJLoader.cpp
    src/graphics/shaders/Shader.cpp

    # Scene
    src/scene/Scene.cpp
    src/scene/RenderCamera.cpp

    src/scene/celestial/CelestialManager.cpp
    src/scene/celestial/CelestialBody.cpp

    src/scene/celestial/scaleMode/VisualScaleMode.cpp
    src/scene/celestial/scaleMode/RealisticScaleMode.cpp

    src/scene/celestial/resources/ResourceManager.cpp
)

find_package(OpenGL REQUIRED)

target_link_libraries(orbital_render PRIVATE
    Common
    Eigen3::Eigen
    EnTT::EnTT
    glfw
    OpenGL::GL
    glad_gl_core_41
)

target_include_directories(orbital_render PUBLIC
    ${Common_SOURCE_DIR}

    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/inputs #! to change
    ${CMAKE_CURRENT_SOURCE_DIR}/src/window

    # Scene
    ${CMAKE_CURRENT_SOURCE_DIR}/src/scene
    ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/celestial
    ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/celestial/scaleMode
    ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/celestial/resources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/celestial/features

    # Math
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math

    # Drawables
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drawables

    # Renderer (OpenGL)
    ${stb_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/models
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/shaders
)

if(WIN32)
    target_compile_definitions(orbital_render PRIVATE NOGDI NOUSER WIN32_LEAN_AND_MEAN)

    set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
    set(BUILD_DIR ${CMAKE_BINARY_DIR})
    set(RENDER_DIR "${BUILD_DIR}/render/${CMAKE_BUILD_TYPE}")

    set(TARGET_DIR "${PROJECT_DIR}")
endif()
