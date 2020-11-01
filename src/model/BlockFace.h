//
// Created by aurailus on 2020-05-31.
//

#pragma once

#include <array>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class BlockFace {
public:
    BlockFace(std::array<glm::vec3, 4> points, std::array<glm::vec2, 4> texCoords) :
        points(points), texCoords(texCoords) {}

    std::array<glm::vec3, 4> points;
    std::array<glm::vec2, 4> texCoords;
};
