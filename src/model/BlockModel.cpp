//
// Created by aurailus on 2020-05-31.
//

#include <glm/gtc/matrix_transform.hpp>

#include "BlockModel.h"

BlockModel::BlockModel() {

    faces = {
        BlockFace({ glm::vec3 {-0.5, -0.5, 0.5}, {-0.5, 0.5, 0.5}, {-0.5, 0.5, -0.5}, {-0.5, -0.5, -0.5}},
            { glm::vec2 {0, 0}, {0, 1}, {1, 1}, {1, 0}}),
        BlockFace({ glm::vec3 {0.5, -0.5, -0.5}, {0.5, 0.5, -0.5}, {0.5, 0.5, 0.5}, {0.5, -0.5, 0.5}},
            { glm::vec2 {0, 0}, {0, 1}, {1, 1}, {1, 0}}),
        BlockFace({ glm::vec3 {-0.5, -0.5, -0.5}, {-0.5, 0.5, -0.5}, {0.5, 0.5, -0.5}, {0.5, -0.5, -0.5}},
            { glm::vec2 {0, 0}, {0, 1}, {1, 1}, {1, 0}}),
        BlockFace({ glm::vec3 {0.5, -0.5, 0.5}, {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5}, {-0.5, -0.5, 0.5}},
            { glm::vec2 {0, 0}, {0, 1}, {1, 1}, {1, 0}}),
        BlockFace({ glm::vec3 {-0.5, -0.5, 0.5}, {-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5}, {0.5, -0.5, 0.5}},
            { glm::vec2 {0, 0}, {0, 1}, {1, 1}, {1, 0}}),
        BlockFace({ glm::vec3 {0.5, 0.5, 0.5}, {0.5, 0.5, -0.5}, {-0.5, 0.5, -0.5}, {-0.5, 0.5, 0.5}},
            { glm::vec2 {0, 0}, {0, 1}, {1, 1}, {1, 0}}),
    };

    updateMesh();
}

glm::ivec3 BlockModel::getPos() {
    return pos;
}

void BlockModel::setPos(glm::ivec3 pos) {
    this->pos = pos;
}

void BlockModel::updateMesh() {
    std::vector<BlockVertex> vertices {};
    std::vector<unsigned int> indices {};

    unsigned int vertexOffset = 0;

    for (auto& face : faces) {
        vertices.push_back(BlockVertex { face.points[0], face.texCoords[0], {} });
        vertices.push_back(BlockVertex { face.points[1], face.texCoords[1], {} });
        vertices.push_back(BlockVertex { face.points[2], face.texCoords[2], {} });
        vertices.push_back(BlockVertex { face.points[3], face.texCoords[3], {} });

        indices.push_back(0 + vertexOffset);
        indices.push_back(1 + vertexOffset);
        indices.push_back(2 + vertexOffset);
        indices.push_back(2 + vertexOffset);
        indices.push_back(3 + vertexOffset);
        indices.push_back(0 + vertexOffset);

        vertexOffset += 4;
    }

    mesh.create(vertices, indices);
}

void BlockModel::render(Renderer &renderer) {
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, pos);
    renderer.setModelMatrix(model);
    mesh.draw();
}
