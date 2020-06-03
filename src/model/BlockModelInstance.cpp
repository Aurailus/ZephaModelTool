//
// Created by aurailus on 2020-05-31.
//

#include <glm/gtc/matrix_transform.hpp>

#include "BlockModelInstance.h"

#include "BlockModel.h"

BlockModelInstance::BlockModelInstance(std::shared_ptr<BlockModel> model) :
    model(model) {}

void BlockModelInstance::render(Renderer &renderer) {
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(pos));
    renderer.setModelMatrix(model);
    renderer.sWorld.set(renderer.uHighlight, highlighted);
    this->model->render();
}

glm::ivec3 BlockModelInstance::getPos() {
    return pos;
}

void BlockModelInstance::setPos(glm::ivec3 pos) {
    this->pos = pos;
}

std::shared_ptr<BlockModel> BlockModelInstance::getModel() {
    return model;
}

void BlockModelInstance::setHighlighted(bool highlighted) {
    this->highlighted = highlighted;
}
