//
// Created by aurailus on 2020-05-31.
//

#pragma once

#include "../graph/Mesh.h"
#include "../graph/Texture.h"
#include "BlockModel.h"

class Renderer;

class BlockModelManager {
public:
    BlockModelManager();

    void render(Renderer& renderer);
private:
    std::vector<BlockModel> models;
    Texture dirt;
};
