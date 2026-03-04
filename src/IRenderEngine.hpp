#pragma once

namespace render {
    class IRenderEngine {
        public:
            virtual ~IRenderEngine() = default;

            virtual void init() = 0;

            [[nodiscard]] virtual bool isRunning() const = 0;
            virtual void update(float delta /*, UIType userInterface*/) = 0;

            virtual void render() = 0;
    };
} // namespace render
