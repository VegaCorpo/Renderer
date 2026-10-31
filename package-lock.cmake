# Common
CPMDeclarePackage(Common
    GITHUB_REPOSITORY VegaCorpo/Common
    GIT_TAG v0.4.1
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

# stb (stb_image.h, header-only)
CPMDeclarePackage(stb
    GITHUB_REPOSITORY nothings/stb
    GIT_TAG a7d4c2175630e1ea5b6f8dd00ab96fed0b97b96d
    DOWNLOAD_ONLY YES
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)
