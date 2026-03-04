#pragma once

namespace render {
    class IRenderEngine {
        public:
            virtual ~IRenderEngine() = default;

            /**
             * @brief Initialize the rendering engine
             */
            virtual void init() = 0;

            /**
             * @brief Is the rendering engine still running
             *
             * @return true if running false otherwise
             */
            [[nodiscard]] virtual bool isRunning() const = 0;

            /**
             * @brief update the UI buffer
             *
             * @param uiElements the elements to be drawn
             */
            virtual void setUIBuffer(/* std::vector<UIElement*> uiElements */) = 0;

            /**
             * @brief update the rendering engine
             *
             * also render the actual frame
             */
            virtual void update() = 0;
    };
} // namespace render
