#pragma once

namespace render::shaders {
    inline constexpr const char* MeshVertex = R"glsl(
        #version 460 core
        layout(location = 0) in vec3 aPosition;
        layout(location = 1) in vec3 aNormal;
        layout(location = 2) in vec2 aUV;
        layout(location = 3) in mat4 aModel;

        layout(std140) uniform Camera {
            mat4 uView;
            mat4 uProjection;
        };

        out vec2 vUV;
        out vec3 vWorldPosition;
        out vec3 vNormal;

        void main()
        {
            vec4 worldPosition = aModel * vec4(aPosition, 1.0);

            vUV = aUV;
            vWorldPosition = worldPosition.xyz;
            // Model matrices only hold rotation + uniform scale, so no inverse-transpose needed
            vNormal = mat3(aModel) * aNormal;
            gl_Position = uProjection * uView * worldPosition;
        }
    )glsl";

    inline constexpr const char* MeshFragment = R"glsl(
        #version 460 core
        in vec2 vUV;
        in vec3 vWorldPosition;
        in vec3 vNormal;
        out vec4 FragColor;

        uniform sampler2D uTexture;
        uniform vec3 uLightPosition;
        uniform int uLit;

        const float AMBIENT = 0.15;

        void main()
        {
            vec4 color = texture(uTexture, vUV);

            if (uLit == 0) {
                FragColor = color;
                return;
            }

            vec3 normal = normalize(vNormal);
            vec3 toLight = normalize(uLightPosition - vWorldPosition);
            float diffuse = max(dot(normal, toLight), 0.0);

            FragColor = vec4(color.rgb * (AMBIENT + (1.0 - AMBIENT) * diffuse), color.a);
        }
    )glsl";

    inline constexpr const char* LineVertex = R"glsl(
        #version 460 core
        layout(location = 0) in vec3 aPosition;

        layout(std140) uniform Camera {
            mat4 uView;
            mat4 uProjection;
        };

        void main()
        {
            gl_Position = uProjection * uView * vec4(aPosition, 1.0);
        }
    )glsl";

    inline constexpr const char* LineFragment = R"glsl(
        #version 460 core
        out vec4 FragColor;

        uniform vec3 uColor;

        void main()
        {
            FragColor = vec4(uColor, 1.0);
        }
    )glsl";
} // namespace render::shaders
