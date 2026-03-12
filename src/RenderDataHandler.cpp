#include "RenderDataHandler.hpp"
#include <Matrix.hpp>
#include "rlgl.h"
#include <iostream>

render::RenderDataHandler::RenderDataHandler() : _mesh(nullptr)
{}

void render::RenderDataHandler::update(common::RenderDataBuffer buffer)
{
    if (buffer.vertices.empty() || buffer.indices.empty()) {
        return;
    }

    const size_t vertexCount = buffer.vertices.size();
    const size_t indexCount = buffer.indices.size();

    auto mesh = std::make_unique<raylib::Mesh>();

    mesh->vertexCount = vertexCount;
    mesh->triangleCount = indexCount / 3;

    mesh->vertices = static_cast<float*>(malloc(sizeof(float) * vertexCount * 3));
    mesh->texcoords = static_cast<float*>(malloc(sizeof(float) * vertexCount * 2));
    mesh->colors = static_cast<unsigned char*>(malloc(sizeof(unsigned char) * vertexCount * 4));
    mesh->indices = static_cast<unsigned short*>(malloc(sizeof(unsigned short) * indexCount));

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

void render::RenderDataHandler::render(const common::RenderDataBuffer& buffer)
{
    if (buffer.vertices.empty()) return;

    rlDrawRenderBatchActive();      // On vide le batch Raylib actuel
    rlDisableDepthTest();
    rlDisableBackfaceCulling();

    rlMatrixMode(RL_PROJECTION);
    rlPushMatrix();
    rlLoadIdentity();
    rlOrtho(0.0, 1280.0, 800.0, 0.0, -1.0, 1.0);

    rlMatrixMode(RL_MODELVIEW);
    rlPushMatrix();
    rlLoadIdentity();

    // Correction des noms de fonctions ici :
    rlEnableColorBlend();
    rlSetBlendFactorsSeparate(RL_SRC_ALPHA, RL_ONE_MINUS_SRC_ALPHA, RL_ONE, RL_ONE_MINUS_SRC_ALPHA, RL_FUNC_ADD, RL_FUNC_ADD);

    for (const auto& cmd : buffer.commands) {
        BeginScissorMode(
            (int)cmd.clipX, (int)cmd.clipY,
            (int)(cmd.clipZ - cmd.clipX),
            (int)(cmd.clipW - cmd.clipY)
        );

        rlEnableTexture(cmd.textureID); 
        rlSetTexture(cmd.textureID);

        rlBegin(RL_TRIANGLES);
        for (uint32_t i = 0; i < cmd.elementCount; i++) {
            uint32_t idx = buffer.indices[cmd.indexOffset + i];
            const auto& v = buffer.vertices[idx];
            
            rlColor4ub(
                (v.color >> 0)  & 0xFF,
                (v.color >> 8)  & 0xFF,
                (v.color >> 16) & 0xFF,
                (v.color >> 24) & 0xFF
            );
            rlTexCoord2f(v.u, v.v);
            rlVertex2f(v.x, v.y);
        }
        rlEnd();

        rlDisableTexture();
        rlSetTexture(0);
        EndScissorMode();
    }

    rlDisableColorBlend(); // Correction ici aussi

    rlMatrixMode(RL_PROJECTION);
    rlPopMatrix();
    rlMatrixMode(RL_MODELVIEW);
    rlPopMatrix();

    rlEnableBackfaceCulling();
    rlEnableDepthTest();
}