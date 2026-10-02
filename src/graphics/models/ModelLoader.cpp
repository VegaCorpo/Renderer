#include "ModelLoader.hpp"
#include <algorithm>
#include <cctype>
#include <format>
#include "OBJLoader.hpp"

render::ModelLoader::ModelLoader()
{
    registerLoader(std::make_unique<OBJLoader>());
}

void render::ModelLoader::registerLoader(std::unique_ptr<IModelLoader> loader)
{
    const std::string extension = loader->getExtension();
    this->_loaders[extension] = std::move(loader);
}

std::string render::ModelLoader::extractExtension(const std::string& filepath)
{
    const auto dot = filepath.find_last_of('.');
    if (dot == std::string::npos)
        return {};

    std::string ext = filepath.substr(dot);
    std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { return std::tolower(c); });
    return ext;
}

std::expected<void, std::string> render::ModelLoader::load(const std::string& filepath, ModelData& outModel) const
{
    const std::string extension = extractExtension(filepath);

    const auto it = this->_loaders.find(extension);
    if (it == this->_loaders.end()) {
        return std::unexpected(std::format("[ModelLoader] unsupported file format '{}' for '{}'",
                                           extension.empty() ? "<none>" : extension, filepath));
    }

    return it->second->load(filepath, outModel);
}
