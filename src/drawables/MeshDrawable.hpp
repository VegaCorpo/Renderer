#pragma once

#include "IDrawable.hpp"
#include "RenderTypes.hpp"

namespace render {
    // Draws a single textured mesh, e.g. a planet's sphere.
    class MeshDrawable : public IDrawable {
        public:
            MeshDrawable(MeshHandle mesh, TextureHandle texture) : _mesh(mesh), _texture(texture) {}

            void setMesh(MeshHandle mesh) { this->_mesh = mesh; }
            void setTexture(TextureHandle texture) { this->_texture = texture; }

            void draw(GLRenderer& renderer, const Transform& transform) const override;

        private:
            MeshHandle _mesh;
            TextureHandle _texture;
    };
} // namespace render
