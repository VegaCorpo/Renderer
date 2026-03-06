#include "RenderDataHandler.hpp"
#include <Matrix.hpp>

void render::RenderDataHandler::update(common::RenderDataBuffer& buffer)
{
    if (buffer.vertices.empty() || buffer.indices.empty()) {
        return;
    }

    const size_t vertexCount = buffer.vertices.size();
    const size_t indexCount = buffer.indices.size();

    auto mesh = std::make_unique<raylib::Mesh>();

    mesh->vertexCount = vertexCount;
    mesh->triangleCount = indexCount / 3;

    mesh->vertices = new float[vertexCount * 3];
    mesh->texcoords = new float[vertexCount * 2];
    mesh->colors = new unsigned char[vertexCount * 4];
    mesh->indices = new unsigned short[indexCount];

    for (size_t i = 0; i < vertexCount; ++i) {
        const auto& v = buffer.vertices[i];

        mesh->vertices[i * 3 + 0] = v.x;
        mesh->vertices[i * 3 + 1] = v.y;
        mesh->vertices[i * 3 + 2] = 0.0f;

        mesh->texcoords[i * 2 + 0] = v.u;
        mesh->texcoords[i * 2 + 1] = v.v;

        mesh->colors[i * 4 + 0] = (v.color >> 0) & 0xFF;
        mesh->colors[i * 4 + 1] = (v.color >> 8) & 0xFF;
        mesh->colors[i * 4 + 2] = (v.color >> 16) & 0xFF;
        mesh->colors[i * 4 + 3] = (v.color >> 24) & 0xFF;
    }

    for (size_t i = 0; i < indexCount; ++i)
        mesh->indices[i] = static_cast<unsigned short>(buffer.indices[i]);

    mesh->Upload(false);

    _mesh = std::move(mesh);
}

void render::RenderDataHandler::render()
{
    if (!_mesh) {
        return;
    }

    DrawMesh(*_mesh, LoadMaterialDefault(), MatrixIdentity());
}
