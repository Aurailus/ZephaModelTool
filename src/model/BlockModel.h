//
// Created by aurailus on 2020-06-02.
//

#pragma once

#include "BlockFace.h"
#include "../graph/Mesh.h"

class BlockModel {
    friend class EditingBlockModel;
public:
    BlockModel();

    void updateMesh();
    void render();
private:
    BlockMesh mesh;
    std::vector<BlockFace> faces {};
};
