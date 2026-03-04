# GODOT GDE CPP
CPMDeclarePackage(
    godot_cpp
    GITHUB_REPOSITORY godotengine/godot-cpp
    GIT_TAG           godot-4.3-stable
    SYSTEM            YES
    EXCLUDE_FROM_ALL  YES
    OPTIONS
        "GODOT_CPP_SYSTEM_HEADERS ON"
        "BUILD_TESTING OFF"
)