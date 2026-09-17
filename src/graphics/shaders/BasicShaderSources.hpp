#pragma once

namespace render::shaders {
    inline constexpr const char* MeshVertex = R"glsl(
        #version 410 core
        layout(location = 0) in vec3 aPosition;
        layout(location = 1) in vec3 aNormal;
        layout(location = 2) in vec2 aUV;

        uniform mat4 uModel;
        uniform mat4 uView;
        uniform mat4 uProjection;

        out vec2 vUV;

        void main()
        {
            vUV = aUV;
            gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
        }
    )glsl";

    inline constexpr const char* MeshFragment = R"glsl(
        #version 410 core
        in vec2 vUV;
        out vec4 FragColor;

        uniform sampler2D uTexture;

        void main()
        {
            FragColor = texture(uTexture, vUV);
        }
    )glsl";

    inline constexpr const char* LineVertex = R"glsl(
        #version 410 core
        layout(location = 0) in vec3 aPosition;

        uniform mat4 uView;
        uniform mat4 uProjection;

        void main()
        {
            gl_Position = uProjection * uView * vec4(aPosition, 1.0);
        }
    )glsl";

    inline constexpr const char* LineFragment = R"glsl(
        #version 410 core
        out vec4 FragColor;

        uniform vec3 uColor;

        void main()
        {
            FragColor = vec4(uColor, 1.0);
        }
    )glsl";
} // namespace render::shaders
