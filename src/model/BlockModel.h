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
    void setPos(glm::vec3 pos);

    void updateMesh();
    void render(Renderer& renderer);

    void setHighlighted(bool highlighted);
private:
    glm::vec3 pos;
    bool highlighted = false;

    BlockMesh mesh;
    std::vector<BlockFace> faces {};
};
