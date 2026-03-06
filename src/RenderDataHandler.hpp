#pragma once

#include <memory>
#include <Mesh.hpp>
#include "types/RenderDataBuffer.hpp"

namespace render {
    class RenderDataHandler {
        public:
            RenderDataHandler() = default;
            ~RenderDataHandler() = default;

            void update(common::RenderDataBuffer& renderDataBuffer);

            void render();

        private:
            std::unique_ptr<raylib::Mesh> _mesh;
    };
} // namespace render
