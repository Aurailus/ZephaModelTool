//
// Created by aurailus on 2020-05-31.
//

#include <glm/glm.hpp>

#include "BlockModel.h"
#include "BlockModelManager.h"
#include "EditingBlockModel.h"

#include "../graph/Camera.h"
#include "../graph/Window.h"
#include "../graph/Renderer.h"
#include "../input/ViewportController.h"

BlockModelManager::BlockModelManager(Camera* camera, Window* window) :
    dirt("../assets/textures/dirt.png"),
    camera(camera),
    window(window) {

    models.emplace_back(std::make_shared<BlockModel>());
    instances.emplace_back(models[0]);
}

void BlockModelManager::render(Renderer &renderer) {
    dirt.use();

    for (auto& instance : instances)
        if (!editingModel || editingPos != instance.getPos())
            instance.render(renderer);

    if (editingInstance) editingInstance->render(renderer);
}

std::shared_ptr<BlockModel> BlockModelManager::getEditingModel() {
    return editingModel;
}

void BlockModelManager::setEditingInstance(glm::ivec3 pos) {
    for (auto& instance : instances) {
        if (instance.getPos() != pos) continue;

        editingPos = instance.getPos();
        editingModel = instance.getModel();
        editingInstance = std::make_shared<EditingBlockModel>(editingPos, editingModel);

        break;
    }
}

bool BlockModelManager::highlightInstanceAtPos(glm::ivec3 pos) {
    for (auto& instance : instances) {
        instance.setHighlighted(instance.getPos() == pos);
        if (instance.getPos() == pos) return true;
    }
    return false;
}
