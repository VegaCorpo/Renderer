#pragma once

#include <memory>
#include <raylib.h>
#include "IRenderEngine.hpp"

namespace render {
    constexpr const char* DEFAULT_TITLE = "Orbital Engine Renderer";

    class RenderEngine : public IRenderEngine {
        public:
            RenderEngine();
            ~RenderEngine() override;

            void init() override;

            [[nodiscard]] bool isRunning() const override { return this->_running; }
            void update(float deltaTime) override;

            void render() override;

        private:
            bool _running = false;

            int _width;
            int _height;

            const int _fps;

            const char* _title;

            Camera _camera{};
    };
} // namespace render

extern "C++" {
    std::unique_ptr<render::IRenderEngine> get_render_engine();
}
