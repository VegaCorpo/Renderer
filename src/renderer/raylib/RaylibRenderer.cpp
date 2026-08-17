#include "RaylibRenderer.hpp"
#include <iostream>

render::RaylibRenderer::~RaylibRenderer()
{
    shutdown();
}

bool render::RaylibRenderer::initialize(const RendererConfig& config)
{
    if (!ARenderer::initialize(config)) {
        return false;
    }

    SetTraceLogLevel(LOG_LEVEL);

    InitWindow(this->_width, this->_height, config.title.c_str());
    SetTargetFPS(config.fps);

    return IsWindowReady();
}

void render::RaylibRenderer::shutdown()
{
    this->_textures.clear();
    this->_models.clear();

    if (IsWindowReady()) {
        CloseWindow();
    }
}

void render::RaylibRenderer::beginMode3D(const CameraView& camera)
{
    ::Camera3D cam{};
    cam.position = _toRaylibVec3(camera.position);
    cam.target = _toRaylibVec3(camera.target);
    cam.up = _toRaylibVec3(camera.up);
    cam.fovy = camera.fovy;
    cam.projection = CAMERA_PERSPECTIVE;

    ::BeginMode3D(cam);
}

void render::RaylibRenderer::drawMesh(MeshHandle mesh, TextureHandle texture, const Vector3& position, float scale)
{
    auto modelIt = this->_models.find(mesh);
    if (modelIt == this->_models.end()) {
        return;
    }

    raylib::Model& model = modelIt->second;

    auto texIt = this->_textures.find(texture);
    if (texIt != this->_textures.end()) {
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texIt->second;
    }

    DrawModel(model, _toRaylibVec3(position), scale, ::WHITE);
}

void render::RaylibRenderer::drawLine3D(const Vector3& start, const Vector3& end, Color color)
{
    DrawLine3D(_toRaylibVec3(start), _toRaylibVec3(end), _toRaylibColor(color));
}

render::TextureHandle render::RaylibRenderer::_loadTextureImpl(const std::string& filepath)
{
    Texture2D tex = LoadTexture(filepath.c_str());
    if (tex.id == 0) {
        std::cerr << "[RaylibRenderer] Erreur de chargement de la texture: " << filepath << "\n";
        return INVALID_TEXTURE;
    }

    TextureHandle handle = _nextTextureHandle();
    this->_textures[handle] = tex;
    return handle;
}

render::Color render::RaylibRenderer::_computeDominantColorImpl(TextureHandle handle) const
{
    auto it = _textures.find(handle);
    if (it == _textures.end()) {
        return Color{255, 255, 255, 255};
    }

    Image img = LoadImageFromTexture(it->second);
    ::Color* pixels = LoadImageColors(img);

    long r = 0, g = 0, b = 0;
    const size_t count = static_cast<size_t>(img.width) * static_cast<size_t>(img.height);

    for (size_t i = 0; i < count; ++i) {
        r += pixels[i].r;
        g += pixels[i].g;
        b += pixels[i].b;
    }

    UnloadImageColors(pixels);
    UnloadImage(img);

    return Color{static_cast<unsigned char>(r / count), static_cast<unsigned char>(g / count),
                 static_cast<unsigned char>(b / count), 255};
}

render::MeshHandle render::RaylibRenderer::_loadMeshImpl(const std::string& filepath)
{
    raylib::Model model = LoadModel(filepath.c_str());
    if (model.meshCount == 0) {
        std::cerr << "[RaylibRenderer] Erreur de chargement du mesh: " << filepath << "\n";
        return INVALID_MESH;
    }

    MeshHandle handle = _nextMeshHandle();
    // this->_models[handle] = std::move(model);
    this->_models.try_emplace(handle, std::move(model));
    return handle;
}
