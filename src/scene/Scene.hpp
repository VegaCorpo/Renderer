#pragma once

#include <entt/entt.hpp>
#include <memory>
#include <Model.hpp>
#include <types/types.hpp>
#include "CelestialManager.hpp"
#include "RenderCamera.hpp"

namespace render {
    class Scene {
        public:
            Scene();
            ~Scene() = default;

            void init();

            raylib::Camera getCamera() { return this->_camera->getCamera(); }
            render::RenderCamera& getRenderCamera() { return *_camera; }

            void handleAction(common::Action action);

            void update(entt::registry& registry);

            void render();

        private:
            std::unique_ptr<render::RenderCamera> _camera;

            std::unique_ptr<CelestialManager> _celestialManager;

            const std::unordered_map<common::Action, std::function<void(Scene&)>> dispatchTable = {
                {common::Action::MOVE_CAMERA_FORWARD, [](Scene& s) { s._camera->addMovement({0, 0, 1}); }},
                {common::Action::MOVE_CAMERA_BACKWARD, [](Scene& s) { s._camera->addMovement({0, 0, -1}); }},
                {common::Action::MOVE_CAMERA_UP, [](Scene& s) { s._camera->addMovement({0, 1, 0}); }},
                {common::Action::MOVE_CAMERA_DOWN, [](Scene& s) { s._camera->addMovement({0, -1, 0}); }},
                {common::Action::MOVE_CAMERA_LEFT, [](Scene& s) { s._camera->addMovement({-1, 0, 0}); }},
                {common::Action::MOVE_CAMERA_RIGHT, [](Scene& s) { s._camera->addMovement({1, 0, 0}); }},
                {common::Action::ROTATE_CAMERA_UP, [](Scene& s) { s._camera->addRotation({0, -1}); }},
                {common::Action::ROTATE_CAMERA_DOWN, [](Scene& s) { s._camera->addRotation({0, 1}); }},
                {common::Action::ROTATE_CAMERA_LEFT, [](Scene& s) { s._camera->addRotation({-1, 0}); }},
                {common::Action::ROTATE_CAMERA_RIGHT, [](Scene& s) { s._camera->addRotation({1, 0}); }},
            };
    };
} // namespace render
