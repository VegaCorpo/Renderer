#raylib
CPMDeclarePackage(Raylib
    GIT_TAG 5.5
    GITHUB_REPOSITORY raysan5/raylib
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)

#raylib-cpp
CPMDeclarePackage(raylib_cpp
    GIT_TAG v5.5.0
    GITHUB_REPOSITORY robloach/raylib-cpp
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)

# Common
CPMDeclarePackage(Common
    GIT_TAG main
    GITHUB_REPOSITORY VegaCorpo/Common
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
    DOWNLOAD_ONLY YES
)
