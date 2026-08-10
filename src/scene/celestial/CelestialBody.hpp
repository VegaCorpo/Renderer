#pragma once

#include <memory>
#include <Model.hpp>
#include <raylib.h>
#include <string>
#include "ResourceManager.hpp"

namespace render {
    class CelestialBody {
        public:
            CelestialBody();
            ~CelestialBody() = default;

            [[nodiscard]] bool hasBeenInitialized() const { return this->_hasBeenInitialized; }
            void init() { this->_hasBeenInitialized = true; }

            /**
             * @brief Has the celestial body been modified since last checked?
             * This determine when to compute the new render scale and when a new render scale is needed
             * Reset the boolean when used
             *
             * @return true
             * @return false
             */
            [[nodiscard]] bool hasBeenModified();
            void modified() { this->_hasBeenModified = true; }

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

            void setModelInfo(std::shared_ptr<ModelInfo> modelInfo) { this->_modelInfo = std::move(modelInfo); }
            [[nodiscard]] const std::shared_ptr<ModelInfo>& getModelInfo() const { return this->_modelInfo; }

            void computePositionAndScale(float scaleFactor);
            void computeScenePosition(float scaleFactor);
            void computeRenderScale(float sizeScaleFactor);

            void draw(const raylib::Model &model) const;

        protected:
            bool _hasBeenInitialized;
            bool _hasBeenModified;

            std::string _name;

            Vector3 _realPositionKm;
            Vector3 _scenePosition;

            float _realRadiusKm;
            float _renderScale;

            std::shared_ptr<render::ModelInfo> _modelInfo;
    };
} // namespace render
