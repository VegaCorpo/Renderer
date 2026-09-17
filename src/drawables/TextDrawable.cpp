#include "TextDrawable.hpp"
#include "GLRenderer.hpp"

void render::TextDrawable::draw(GLRenderer& renderer, const Transform& transform) const
{
    renderer.drawText(this->_text, {transform.position.x(), transform.position.y()}, this->_color);
}
