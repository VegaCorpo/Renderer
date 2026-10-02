#pragma once
#include <string>
#include "IModelLoader.hpp"

namespace render {
    class OBJLoader : public IModelLoader {
            constexpr static const std::string MODEL_EXT = ".obj";

        public:
            // In the obj file, each face is made of 3 vertices, here we store the index of each vertex,
            // its texture coordinate and its normal
            struct Index {
                    int v = 0, vt = 0, vn = 0;
            };

            explicit OBJLoader() : IModelLoader(MODEL_EXT) {}

            [[nodiscard]] static Index parseFaceToken(const std::string& token);

            [[nodiscard]] std::expected<void, std::string> load(const std::string& filepath,
                                                                ModelData& outModel) override;
    };
} // namespace render
