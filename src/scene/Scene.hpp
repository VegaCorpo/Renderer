#pragma once

#include <types/World.hpp>
#include <functional>
#include <unordered_map>
#include <memory>
#include <types/types.hpp>
#include "CelestialManager.hpp"
#include "GLRenderer.hpp"
#include "RenderCamera.hpp"

namespace render {
    class Scene {
        public:
            Scene();
            ~Scene() = default;

            void init(std::shared_ptr<GLRenderer>& renderer, const common::SpecificDataRender& data);

            void handleAction(const common::InputAction& action);

            void syncIn(const common::WorldState& world);
            void update();

            void render();

        private:
            using ActionHandler = std::function<void(Scene&, const common::InputAction&)>;

            std::shared_ptr<GLRenderer> _renderer;

            std::unique_ptr<render::RenderCamera> _camera;

            std::unique_ptr<CelestialManager> _celestialManager;

            const std::unordered_map<common::Action, ActionHandler> dispatchTable = {
                {common::Action::MOVE_CAMERA_FORWARD, [](Scene& s, auto&) { s._camera->addMovement({0, 0, 1}); }},
                {common::Action::MOVE_CAMERA_BACKWARD, [](Scene& s, auto&) { s._camera->addMovement({0, 0, -1}); }},
                {common::Action::MOVE_CAMERA_UP, [](Scene& s, auto&) { s._camera->addMovement({0, 1, 0}); }},
                {common::Action::MOVE_CAMERA_DOWN, [](Scene& s, auto&) { s._camera->addMovement({0, -1, 0}); }},
                {common::Action::MOVE_CAMERA_LEFT, [](Scene& s, auto&) { s._camera->addMovement({-1, 0, 0}); }},
                {common::Action::MOVE_CAMERA_RIGHT, [](Scene& s, auto&) { s._camera->addMovement({1, 0, 0}); }},
                {common::Action::ROTATE_CAMERA_UP, [](Scene& s, auto&) { s._camera->addRotation({0, -1, 0}); }},
                {common::Action::ROTATE_CAMERA_DOWN, [](Scene& s, auto&) { s._camera->addRotation({0, 1, 0}); }},
                {common::Action::ROTATE_CAMERA_LEFT, [](Scene& s, auto&) { s._camera->addRotation({-1, 0, 0}); }},
                {common::Action::ROTATE_CAMERA_RIGHT, [](Scene& s, auto&) { s._camera->addRotation({1, 0, 0}); }},
                {common::Action::ROTATE_CAMERA_MOUSE, [](Scene& s, auto& a) { s._camera->addMouseRotation(a.x, a.y); }},
                {common::Action::CHANGE_RESCALE_MODE, [](Scene& s, auto&) { s._celestialManager->changeScaleMode(); }}};
    };
} // namespace render
