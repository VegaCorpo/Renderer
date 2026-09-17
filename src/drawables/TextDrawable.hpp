#pragma once

#include <string>
#include "IDrawable.hpp"
#include "RenderTypes.hpp"

namespace render {
    // Draws a screen-space label, e.g. a celestial body's name/icon.
    // `transform.position` is expected to already be a screen-space position
    // (x, y in pixels) computed by the caller via a world-to-screen projection.
    class TextDrawable : public IDrawable {
        public:
            TextDrawable(std::string text, Color color) : _text(std::move(text)), _color(color) {}

            void setText(std::string text) { _text = std::move(text); }
            void setColor(Color color) { this->_color = color; }

            void draw(GLRenderer& renderer, const Transform& transform) const override;

        private:
            std::string _text;
            Color _color;
    };
} // namespace render
