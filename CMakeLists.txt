cmake_minimum_required(VERSION 3.14)

file(GLOB_RECURSE src "*.cpp")
file(GLOB_RECURSE common_src "${CMAKE_SOURCE_DIR}/common/src/*.cpp")

add_library(orbital_render SHARED ${src} ${common_src})

# target_link_libraries(orbital_render PRIVATE)

target_include_directories(orbital_render PRIVATE
    ${CMAKE_SOURCE_DIR}/common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

if(WIN32)
    target_compile_definitions(orbital_render PRIVATE NOGDI NOUSER WIN32_LEAN_AND_MEAN)

    set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
    set(BUILD_DIR ${CMAKE_BINARY_DIR})
    set(RENDER_DIR "${BUILD_DIR}/render/${CMAKE_BUILD_TYPE}")

    set(TARGET_DIR "${PROJECT_DIR}")
endif()
