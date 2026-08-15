#pragma once

#include <entt/entt.hpp>
#include <memory>
#include <types/types.hpp>
#include "CelestialManager.hpp"
#include "RenderCamera.hpp"
#include "renderer/ARenderer.hpp"

namespace render {
    class Scene {
        public:
            Scene();
            ~Scene() = default;

            void init(std::shared_ptr<ARenderer> &renderer);

            void handleAction(common::Action action);

            void syncIn(entt::registry& registry);
            void update();

            void render();

        private:
            std::shared_ptr<ARenderer> _renderer;

            std::unique_ptr<render::RenderCamera> _camera;

            std::unique_ptr<CelestialManager> _celestialManager;

            const std::unordered_map<common::Action, std::function<void(Scene&)>> dispatchTable = {
                {common::Action::MOVE_CAMERA_FORWARD, [](Scene& s) { s._camera->addMovement({0, 0, 1}); }},
                {common::Action::MOVE_CAMERA_BACKWARD, [](Scene& s) { s._camera->addMovement({0, 0, -1}); }},
                {common::Action::MOVE_CAMERA_UP, [](Scene& s) { s._camera->addMovement({0, 1, 0}); }},
                {common::Action::MOVE_CAMERA_DOWN, [](Scene& s) { s._camera->addMovement({0, -1, 0}); }},
                {common::Action::MOVE_CAMERA_LEFT, [](Scene& s) { s._camera->addMovement({-1, 0, 0}); }},
                {common::Action::MOVE_CAMERA_RIGHT, [](Scene& s) { s._camera->addMovement({1, 0, 0}); }},
                {common::Action::ROTATE_CAMERA_UP, [](Scene& s) { s._camera->addRotation({0, -1, 0}); }},
                {common::Action::ROTATE_CAMERA_DOWN, [](Scene& s) { s._camera->addRotation({0, 1, 0}); }},
                {common::Action::ROTATE_CAMERA_LEFT, [](Scene& s) { s._camera->addRotation({-1, 0, 0}); }},
                {common::Action::ROTATE_CAMERA_RIGHT, [](Scene& s) { s._camera->addRotation({1, 0, 0}); }},
                {common::Action::CHANGE_RESCALE_MODE, [](Scene& s) { s._celestialManager->changeScaleMode(); }}
            };
    };
} // namespace render
