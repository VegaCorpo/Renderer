#pragma once

#include <Mesh.hpp>
#include "types/RenderDataBuffer.hpp"

namespace render {
    class RenderDataHandler {
        public:
            RenderDataHandler() = default;
            ~RenderDataHandler() = default;

            void setVertexBuffer(common::RenderDataBuffer& renderDataBuffer);

            void render();

        private:
            raylib::Mesh _mesh;
    };
} // namespace render
