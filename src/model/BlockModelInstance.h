//
// Created by aurailus on 2020-05-31.
//

#pragma once

#include <memory>

#include "../graph/Renderer.h"

class BlockModel;

class BlockModelInstance {
public:
    BlockModelInstance(std::shared_ptr<BlockModel> model);

    void render(Renderer& renderer);

    glm::ivec3 getPos();
    void setPos(glm::ivec3 pos);

    std::shared_ptr<BlockModel> getModel();
    void setHighlighted(bool highlighted);
private:
    std::shared_ptr<BlockModel> model;

    glm::ivec3 pos;
    bool highlighted = false;
};
