#pragma once

#include <Eigen/Dense>
#include <memory>
#include <string>
#include "IDrawable.hpp"
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

            void setRealPositionKm(const Eigen::Vector3f& position);
            [[nodiscard]] const Eigen::Vector3f& getRealPositionKm() const { return this->_realPositionKm; }
            void setScenePosition(const Eigen::Vector3f& position) { this->_scenePosition = position; }
            [[nodiscard]] const Eigen::Vector3f& getScenePosition() const { return this->_scenePosition; }

            void setRealRadiusKm(float radius);
            [[nodiscard]] float getRealRadiusKm() const { return this->_realRadiusKm; }
            void setRenderScale(float scale) { this->_renderScale = scale; }
            [[nodiscard]] float getRenderScale() const { return this->_renderScale; }

            void setModelInfo(std::shared_ptr<ModelInfo> modelInfo) { this->_modelInfo = std::move(modelInfo); }
            [[nodiscard]] const std::shared_ptr<ModelInfo>& getModelInfo() const { return this->_modelInfo; }

            // Owned by CelestialManager: it knows about meshes/textures, this class doesn't.
            void setDrawable(std::shared_ptr<IDrawable> drawable) { this->_drawable = std::move(drawable); }

            void computePositionAndScale(float scaleFactor);
            void computeScenePosition(float scaleFactor);
            void computeRenderScale(float sizeScaleFactor);

            // Only forwards to the drawable — never touches GLRenderer directly.
            void draw(GLRenderer& renderer) const;

        protected:
            bool _hasBeenInitialized;
            bool _hasBeenModified;

            std::string _name;

            Eigen::Vector3f _realPositionKm;
            Eigen::Vector3f _scenePosition;

            float _realRadiusKm;
            float _renderScale;

            std::shared_ptr<render::ModelInfo> _modelInfo;
            std::shared_ptr<IDrawable> _drawable;
    };
} // namespace render
