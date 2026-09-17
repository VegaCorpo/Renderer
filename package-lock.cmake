# Common
CPMDeclarePackage(Common
    GITHUB_REPOSITORY VegaCorpo/Common
    GIT_TAG main
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)

# Eigen
CPMDeclarePackage(Eigen
        GIT_TAG 5.0.1
        GITLAB_REPOSITORY libeigen/eigen
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

# glfw
CPMDeclarePackage(glfw
    GITHUB_REPOSITORY glfw/glfw
    GIT_TAG 3.4
    OPTIONS
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_DOCS OFF"
        "BUILD_SHARED_LIBS ON"
        "GLFW_BUILD_X11 ON"
        "GLFW_BUILD_WAYLAND OFF"
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)

# glad
CPMDeclarePackage(glad
    GITHUB_REPOSITORY Dav1dde/glad
    GIT_TAG glad2
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)

# stb (stb_image.h, header-only)
CPMDeclarePackage(stb
    GITHUB_REPOSITORY nothings/stb
    GIT_TAG master
    DOWNLOAD_ONLY YES
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)
