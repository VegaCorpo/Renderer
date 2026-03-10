#pragma once

#include <entt/entt.hpp>
#include <memory>
#include <Model.hpp>
#include <types/types.hpp>
#include <unordered_map>
#include "RenderCamera.hpp"

namespace render {
    class Scene {
        public:
            Scene();
            ~Scene() = default;

            void init();

            raylib::Camera getCamera() { return this->_camera->getCamera(); }

            void handleAction(common::Action action);

            void update(entt::registry& registry);

            void render();

        private:
            std::unique_ptr<render::RenderCamera> _camera;

            std::unique_ptr<raylib::Model> _sphereModel;
            std::unordered_map<entt::entity, Vector3> _positions;

            Vector3 _earth = {};
            Vector3 _moon = {};
            Vector3 _sun = {};

            static const std::unordered_map<common::Action, std::function<void(Scene&)>> dispatchTable;
    };
} // namespace render
