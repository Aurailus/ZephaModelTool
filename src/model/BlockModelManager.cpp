//
// Created by aurailus on 2020-05-31.
//

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "BlockModel.h"
#include "BlockModelManager.h"
#include "EditingBlockModel.h"

#include "../graph/Camera.h"
#include "../graph/Window.h"
#include "../graph/Renderer.h"
#include "../input/ViewportControl.h"
#include "../input/Ray.h"

BlockModelManager::BlockModelManager(Camera* camera, Window* window) :
    dirt("../assets/textures/dirt.png"),
    camera(camera),
    window(window) {

    models.emplace_back(std::make_shared<BlockModel>());

    instances.emplace_back(models[0]);
    instances.emplace_back(models[0]);
    instances.emplace_back(models[0]);
//    instances.emplace_back(models[0]);
//    instances.emplace_back(models[0]);
//    instances.emplace_back(models[0]);
//    instances.emplace_back(models[0]);

    instances[1].setPos({1, 0, 0});
    instances[2].setPos({-1, 0, 0});
//    instances[3].setPos({0, 0, 1});
//    instances[4].setPos({0, 0, -1});
//    instances[5].setPos({0, 1, 0});
//    instances[6].setPos({0, -1, 0});
}

void BlockModelManager::update(Input& input, ViewportControl& viewport) {
    for (auto& instance : instances) instance.setHighlighted(false);

    if (!editingModel) {
        glm::vec3 dir = Ray::worldRayFromCursor(*window, *camera);
        glm::vec3 ray = camera->getPos();

        bool found = false;
        float dis = 0.05f;

        while (dis < 20) {
            glm::vec3 end = ray + (dir * dis);
            glm::ivec3 blockSpace = glm::floor(end + glm::vec3(0.5));

            for (auto& instance : instances) {
                if (instance.getPos() == blockSpace) {
                    instance.setHighlighted(true);
                    if (input.keyPressed(GLFW_MOUSE_BUTTON_LEFT)) {
                        viewport.setViewFocus(instance.getPos());
                        setEditingModel(instance);
                    }
                    found = true;
                    break;
                }
            }

            if (found) break;
            dis += 0.05;
        }
    }
    else editingInstance->update(viewport, *window, *camera);
}

void BlockModelManager::render(Renderer &renderer) {
    dirt.use();
    for (auto& instance : instances)
        if (!editingModel || editingPos != instance.getPos()) instance.render(renderer);
    if (editingInstance) editingInstance->render(renderer);
}

void BlockModelManager::setEditingModel(BlockModelInstance& instance) {
    editingPos = instance.getPos();
    editingModel = instance.getModel();

    editingInstance = std::make_shared<EditingBlockModel>(editingPos, editingModel);
}
