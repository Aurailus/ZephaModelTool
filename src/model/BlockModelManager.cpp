//
// Created by aurailus on 2020-05-31.
//

#include "BlockModelManager.h"

#include "../graph/Renderer.h"

BlockModelManager::BlockModelManager() :
    dirt("../assets/textures/dirt.png") {
    models.emplace_back();
    models.emplace_back();
    models.emplace_back();
    models.emplace_back();
    models.emplace_back();

    models[1].setPos({1, 0, 0});
    models[2].setPos({-1, 0, 0});
    models[3].setPos({0, 0, 1});
    models[4].setPos({0, 0, -1});
}

void BlockModelManager::render(Renderer &renderer) {
    dirt.use();
    for (auto& model : models) model.render(renderer);
}
