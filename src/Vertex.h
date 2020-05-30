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

struct BlockVertex {
    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;
};

#define STRIDE_OFFSET_BLOCK(m) sizeof(struct BlockVertex), offsetof(struct BlockVertex, m)

constexpr static VertexParamList blockVertexParams {3, {
    VertexParam {0, 3, GL_FLOAT, STRIDE_OFFSET_BLOCK(position)},
    VertexParam {1, 2, GL_FLOAT, STRIDE_OFFSET_BLOCK(texCoords)},
    VertexParam {2, 3, GL_FLOAT, STRIDE_OFFSET_BLOCK(normal)} }};
