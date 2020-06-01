//
// Created by aurailus on 2020-05-31.
//

#pragma once

#include "BlockFace.h"
#include "../graph/Mesh.h"
#include "../graph/Renderer.h"

class BlockModel {
public:
    BlockModel();

    glm::ivec3 getPos();
    void setPos(glm::ivec3 pos);

    void updateMesh();
    void render(Renderer& renderer);
private:
    glm::vec3 pos;

    BlockMesh mesh;
    std::vector<BlockFace> faces {};
};
