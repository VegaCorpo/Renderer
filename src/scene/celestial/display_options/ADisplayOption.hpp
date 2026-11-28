#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>
#include "IDisplayOption.hpp"

namespace render {
    class ADisplayOption : public IDisplayOption {
        public:
            enum class Layer { SCENE_3D, SCREEN_2D };

            static constexpr bool DEFAULT_ENABLED = true;

            ADisplayOption(std::string_view name, std::string_view description, Layer layer);
            ~ADisplayOption() override = default;

            ADisplayOption(const ADisplayOption&) = delete;
            ADisplayOption& operator=(const ADisplayOption&) = delete;
            ADisplayOption(ADisplayOption&&) = delete;
            ADisplayOption& operator=(ADisplayOption&&) = delete;

            [[nodiscard]] bool is2D() const final;

            [[nodiscard]] bool isEnabled() const final;
            void setEnabled(bool enabled) final;

            [[nodiscard]] std::vector<common::DisplayOptionParam> params() const final;
            void setParams(const std::vector<common::DisplayOptionParam>& params) final;

            [[nodiscard]] common::DisplayOption toDisplayOption(common::DisplayOptionId id) const final;

        protected:
            using ParamValue = decltype(common::DisplayOptionParam::value);

            /**
             * @brief Expose a member of the option as a tunable parameter
             *
             * @param target the member read by params() and written by setParams()
             * @param sanitize optional correction applied to the value sent by the UI (e.g. a lower bound)
             */
            template <typename T>
            void _addParam(const std::string_view name, const std::string_view description, T& target,
                           std::function<T(T)> sanitize = nullptr)
            {
                this->_params.push_back({
                    .name = std::string(name),
                    .description = std::string(description),
                    .get = [&target]() { return ParamValue{target}; },
                    .set =
                        [&target, sanitize = std::move(sanitize)](const ParamValue& value)
                    {
                        const T* const newValue = std::get_if<T>(&value);

                        if (!newValue) {
                            return;
                        }
                        target = sanitize ? sanitize(*newValue) : *newValue;
                    },
                });
            }

        private:
            struct BoundParam {
                    std::string name;
                    std::string description;
                    std::function<ParamValue()> get;
                    std::function<void(const ParamValue&)> set;
            };

            std::string _name;
            std::string _description;
            Layer _layer;
            bool _enabled;

            std::vector<BoundParam> _params;
    };
} // namespace render
