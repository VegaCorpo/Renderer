#pragma once
#include <expected>
#include <string>
#include "GLMesh.hpp"

namespace render {

    struct ModelData {
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;
    };

    // Base class every concrete format loader must derive from. Each loader
    // owns the knowledge of which extension it handles, set once at
    // construction - ModelLoader never hardcodes a format-to-extension
    // mapping itself, it just asks each registered loader what it supports.
    class IModelLoader {
        public:
            explicit IModelLoader(std::string extension) : _extension(std::move(extension)) {}
            virtual ~IModelLoader() = default;

            [[nodiscard]] virtual std::expected<void, std::string> load(const std::string& filepath,
                                                                        ModelData& outModel) = 0;

            [[nodiscard]] const std::string& getExtension() const { return this->_extension; }

        private:
            const std::string _extension;
    };

} // namespace render
