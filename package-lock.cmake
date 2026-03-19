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
    GIT_TAG 5.5
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
    OPTIONS
        "USE_EXTERNAL_GLFW OFF"
        "BUILD_EXAMPLES OFF"
        "BUILD_GAMES OFF"
)

#raylib-cpp
CPMDeclarePackage(raylib_cpp
    GITHUB_REPOSITORY robloach/raylib-cpp
    GIT_TAG v5.5.0
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)

# Dear Imgui
CPMDeclarePackage(ImGui
    GIT_TAG v1.92.6
    GITHUB_REPOSITORY ocornut/imgui
    DOWNLOAD_ONLY YES
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)
