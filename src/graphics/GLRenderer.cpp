#include "GLRenderer.hpp"
#include <glad/gl.h>
#include <iostream>
#include "BasicShaderSources.hpp"
#include "CameraMath.hpp"
#include "ModelLoader.hpp"

bool render::GLRenderer::initialize(const RendererConfig& config)
{
    if (!this->_context.create(config))
        return false;

    if (!this->_loadShaders())
        return false;

    this->_createLineBuffers();
    this->_createCameraUbo();
    return true;
}

void render::GLRenderer::shutdown()
{
    for (auto& [handle, texture] : this->_textures)
        GLTexture::destroy(texture);

    this->_textures.clear();
    this->_meshes.clear();

    if (this->_lineVbo) {
        glDeleteBuffers(1, &this->_lineVbo);
    }
    if (this->_lineVao) {
        glDeleteVertexArrays(1, &this->_lineVao);
    }

    this->_context.destroy();
}

bool render::GLRenderer::_loadShaders()
{
    if (!this->_meshShader.compile(shaders::MeshVertex, shaders::MeshFragment)) {
        return false;
    }
    if (!this->_lineShader.compile(shaders::LineVertex, shaders::LineFragment)) {
        return false;
    }

    this->_meshShader.bindUniformBlock("Camera", CAMERA_UBO_BINDING);
    this->_lineShader.bindUniformBlock("Camera", CAMERA_UBO_BINDING);
    return true;
}

void render::GLRenderer::_createCameraUbo()
{
    glGenBuffers(1, &this->_cameraUbo);
    glBindBuffer(GL_UNIFORM_BUFFER, this->_cameraUbo);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(Eigen::Matrix4f), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, CAMERA_UBO_BINDING, this->_cameraUbo);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void render::GLRenderer::_createLineBuffers()
{
    glGenVertexArrays(1, &this->_lineVao);
    glGenBuffers(1, &this->_lineVbo);

    glBindVertexArray(this->_lineVao);
    glBindBuffer(GL_ARRAY_BUFFER, this->_lineVbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Eigen::Vector3f), nullptr);

    glBindVertexArray(0);
}

void render::GLRenderer::clear(Color color) const
{
    glClearColor(color.r_f(), color.g_f(), color.b_f(), color.a_f());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render::GLRenderer::beginMode3D(const CameraView& camera)
{
    float aspect = getHeight() > 0 ? static_cast<float>(getWidth()) / static_cast<float>(getHeight()) : 1.0f;

    this->_viewMatrix = math::buildView(camera);
    this->_projMatrix = math::buildProjection(camera.fovy, aspect, 0.1f, 5000.0f);

    glBindBuffer(GL_UNIFORM_BUFFER, this->_cameraUbo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Eigen::Matrix4f), this->_viewMatrix.data());
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Eigen::Matrix4f), sizeof(Eigen::Matrix4f), this->_projMatrix.data());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

render::TextureHandle render::GLRenderer::loadTexture(const std::string& filepath)
{
    if (auto it = this->_texturePathCache.find(filepath); it != this->_texturePathCache.end())
        return it->second;

    TextureData data;
    if (!GLTexture::load(filepath, data))
        return INVALID_TEXTURE;

    TextureHandle handle = ++this->_nextTextureHandle;
    this->_textures[handle] = data;
    this->_texturePathCache[filepath] = handle;
    return handle;
}

render::Color render::GLRenderer::getTextureDominantColor(TextureHandle handle) const
{
    auto it = this->_textures.find(handle);
    return it != this->_textures.end() ? it->second.dominantColor : Color::White();
}

render::MeshHandle render::GLRenderer::loadMesh(const std::string& filepath)
{
    if (auto it = this->_meshPathCache.find(filepath); it != this->_meshPathCache.end()) {
        return it->second;
    }

    ModelData data;
    if (auto result = this->_modelLoader.load(filepath, data); !result) {
        std::cerr << result.error() << "\n";
        return INVALID_MESH;
    }

    GLMesh mesh;
    mesh.upload(data.vertices, data.indices);

    MeshHandle handle = ++this->_nextMeshHandle;
    this->_meshes[handle] = std::move(mesh);
    this->_meshPathCache[filepath] = handle;
    return handle;
}

void render::GLRenderer::drawMesh(MeshHandle mesh, TextureHandle texture, const Eigen::Vector3f& position, float scale)
{
    auto meshIt = this->_meshes.find(mesh);
    if (meshIt == this->_meshes.end())
        return;

    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    model.block<3, 1>(0, 3) = position;
    model.block<3, 3>(0, 0) *= scale;

    this->_meshShader.use();
    this->_meshShader.setMat4("uModel", model);

    if (auto texIt = this->_textures.find(texture); texIt != this->_textures.end()) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texIt->second.glId);
        this->_meshShader.setInt("uTexture", 0);
    }

    meshIt->second.draw();
}

void render::GLRenderer::drawText(const std::string& /*text*/, const Eigen::Vector2f& /*screenPosition*/,
                                  Color /*color*/)
{
    // TODO: text rendering (font atlas + glyph quads) is a separate task.
}

void render::GLRenderer::drawLineStrip(const std::vector<Eigen::Vector3f>& points, Color color)
{
    if (points.size() < 2)
        return;

    this->_lineShader.use();
    this->_lineShader.setVec3("uColor", Eigen::Vector3f(color.r_f(), color.g_f(), color.b_f()));

    glBindVertexArray(this->_lineVao);
    glBindBuffer(GL_ARRAY_BUFFER, this->_lineVbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long>(points.size() * sizeof(Eigen::Vector3f)), points.data(),
                 GL_DYNAMIC_DRAW);
    glDrawArrays(GL_LINE_STRIP, 0, static_cast<int>(points.size()));
    glBindVertexArray(0);
}
