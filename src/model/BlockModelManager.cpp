//
// Created by aurailus on 2020-05-31.
//

#include <glm/glm.hpp>

#include "BlockModelManager.h"

#include "../graph/Camera.h"
#include "../graph/Window.h"
#include "../graph/Renderer.h"

BlockModelManager::BlockModelManager(Camera* camera, Window* window) :
    dirt("../assets/textures/dirt.png"),
    camera(camera),
    window(window) {

    models.emplace_back();
    models.emplace_back();
    models.emplace_back();
    models.emplace_back();
    models.emplace_back();

    models[1].setPos({1, 0, 1});
    models[2].setPos({-1, 0, 1});
    models[3].setPos({1, 0, -1});
    models[4].setPos({-1, 0, -1});
}

void BlockModelManager::update(Input& input) {
    for (auto& model : models) model.setHighlighted(false);

    glm::vec4 ray_clip = glm::vec4 {
        (2.f * input.mousePos().x) / window->getSize().x - 1.f,
        1.f - (2.f * input.mousePos().y) / window->getSize().y, -1.f, 1.f };


    glm::vec4 ray_eye = glm::inverse(camera->getProjectionMatrix()) * ray_clip;
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

    glm::vec3 ray = glm::vec3(glm::inverse(camera->getViewMatrix()) * ray_eye);
    ray *= 20;
    models[0].setPos(camera->getPos() + glm::vec3(ray));

    std::cout << ray.x << ", " << ray.y << ", " << ray.z << std::endl;
}

void BlockModelManager::render(Renderer &renderer) {
    dirt.use();
    for (auto& model : models) model.render(renderer);
}
