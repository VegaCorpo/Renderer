#pragma once

#include <memory>
#include "ARenderer.hpp"
#include "IRenderFeature.hpp"

namespace render {
    class ARenderFeature : public IRenderFeature {
        public:
            explicit ARenderFeature(std::shared_ptr<ARenderer>& renderer) : _renderer(renderer) {}
            ~ARenderFeature() override = default;

        protected:
            std::shared_ptr<ARenderer> _renderer;
    };
} // namespace render
