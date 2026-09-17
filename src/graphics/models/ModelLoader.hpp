#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "IModelLoader.hpp"

namespace render {

    // Owns one instance of every known IModelLoader and dispatches by file
    // extension.
    class ModelLoader {
        public:
            ModelLoader();

            [[nodiscard]] std::expected<void, std::string> load(const std::string& filepath, ModelData& outModel) const;

        private:
            void registerLoader(std::unique_ptr<IModelLoader> loader);

            [[nodiscard]] static std::string extractExtension(const std::string& filepath);

            std::unordered_map<std::string, std::unique_ptr<IModelLoader>> _loaders;
    };

} // namespace render
