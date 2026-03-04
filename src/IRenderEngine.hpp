#pragma once

namespace render {
    class IRenderEngine {
        public:
            virtual ~IRenderEngine() = default;

            virtual void init() = 0;

            [[nodiscard]] virtual bool isRunning() const = 0;

            virtual void setUIBuffer(/* std::vector<UIElement*> uiElements */) = 0;

            virtual void update(float deltaTime /*, scene details*/) = 0;
    };
} // namespace render
