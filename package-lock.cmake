# Common
CPMDeclarePackage(Common
    GITHUB_REPOSITORY VegaCorpo/Common
    GIT_TAG main
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)

#entt
CPMDeclarePackage(EnTT
    GITHUB_REPOSITORY skypjack/entt
    GIT_TAG v3.16.0
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)

#raylib
CPMDeclarePackage(raylib
    GITHUB_REPOSITORY raysan5/raylib
    GIT_TAG 6.0
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
    OPTIONS
        "BUILD_SHARED_LIBS ON"
        "CUSTOMIZE_BUILD ON"
        "BUILD_EXAMPLES OFF"
        "BUILD_GAMES OFF"
)

#raylib-cpp
CPMDeclarePackage(raylib_cpp
    GITHUB_REPOSITORY robloach/raylib-cpp
    GIT_TAG v6.0.2
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)

#glfw
CPMDeclarePackage(glfw
    GITHUB_REPOSITORY glfw/glfw
    GIT_TAG 3.4
    OPTIONS
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_DOCS OFF"
        "GLFW_BUILD_WAYLAND OFF"
        "BUILD_SHARED_LIBS ON"
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)
