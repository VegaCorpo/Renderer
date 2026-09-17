#include "MeshDrawable.hpp"
#include "GLRenderer.hpp"

void render::MeshDrawable::draw(GLRenderer& renderer, const Transform& transform) const
{
    renderer.drawMesh(this->_mesh, this->_texture, transform.position, transform.scale);
}
