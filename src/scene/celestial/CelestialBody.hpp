#pragma once

#include <memory>
#include <Model.hpp>
#include <string>

namespace render {
    class CelestialBody {
        public:
            CelestialBody();
            ~CelestialBody() = default;

            /**
             * @brief Has the celestial body been modified since last checked?
             * This determine when to compute the new render scale and when a new render scale is needed
             * Reset the boolean when used
             *
             * @return true
             * @return false
             */
            [[nodiscard]] bool hasBeenModified();

            void setName(const std::string& name) { this->_name = name; }
            [[nodiscard]] const std::string& getName() const { return this->_name; }

            void setRealPositionKm(const Vector3& position);
            [[nodiscard]] const Vector3& getRealPositionKm() const { return this->_realPositionKm; }
            void setScenePosition(const Vector3& position) { this->_scenePosition = position; }
            [[nodiscard]] const Vector3& getScenePosition() const { return this->_scenePosition; }

            void setRealRadiusKm(float radius);
            [[nodiscard]] float getRealRadiusKm() const { return this->_realRadiusKm; }
            void setRenderScale(float scale) { this->_renderScale = scale; }
            [[nodiscard]] float getRenderScale() const { return this->_renderScale; }

            void setModel(std::shared_ptr<raylib::Model>& model) { this->_model = model; }
            [[nodiscard]] const std::shared_ptr<raylib::Model>& getModel() const { return this->_model; }

            void setColor(const Color& color) { this->_color = color; }
            [[nodiscard]] const Color& getColor() const { return this->_color; }

            void computePositionAndScale(float scaleFactor);
            void computeScenePosition(float scaleFactor);
            void computeRenderScale(float sizeScaleFactor);

            void render() const;

        protected:
            void _modified() { this->_hasBeenModified = true; }

            std::string _name;

            Vector3 _realPositionKm;
            Vector3 _scenePosition;

            float _realRadiusKm;
            float _renderScale;

            std::shared_ptr<raylib::Model> _model;
            Color _color;

            bool _hasBeenModified;
    };
} // namespace render
