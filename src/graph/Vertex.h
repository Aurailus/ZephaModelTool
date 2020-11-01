//
// Created by aurailus on 2020-05-29.
//

#pragma once

#include <array>
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct VertexParam { unsigned int offset, size, type, stride, pointer; };
struct VertexParamList { unsigned char count; std::array<VertexParam, 16> params; };

#define STRIDE_OFFSET(c, m) sizeof(struct c), offsetof(struct c, m)

// Block Vertex
// For blocks, rendered in 3d space.

struct BlockVertex {
    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;
};

constexpr static VertexParamList BlockVertexParams {3, {
    VertexParam {0, 3, GL_FLOAT, STRIDE_OFFSET(BlockVertex, position)},
    VertexParam {1, 2, GL_FLOAT, STRIDE_OFFSET(BlockVertex, texCoords)},
    VertexParam {2, 3, GL_FLOAT, STRIDE_OFFSET(BlockVertex, normal)}
}};

// Gui Vertex
// For Gui Elements, rendered in 2d space.

struct GuiVertex {
    glm::vec2 position;
    glm::vec2 texCoords;
};

constexpr static VertexParamList GuiVertexParams {2, {
    VertexParam {0, 2, GL_FLOAT, STRIDE_OFFSET(GuiVertex, position)},
    VertexParam {1, 2, GL_FLOAT, STRIDE_OFFSET(GuiVertex, texCoords)}
}};