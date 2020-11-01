//
// Created by aurailus on 2020-05-31.
//

#pragma once

#include "../graph/Mesh.h"
#include "../graph/Texture.h"
#include "BlockModelInstance.h"

class Input;
class Camera;
class Window;
class Renderer;
class ViewportController;
class EditingBlockModel;

class BlockModelManager {
public:
    BlockModelManager(Camera* camera, Window* window);

    void render(Renderer& renderer);

    bool highlightInstanceAtPos(glm::ivec3 pos);
    std::shared_ptr<BlockModel> getEditingModel();
    void setEditingInstance(glm::ivec3 pos);

    std::vector<std::shared_ptr<BlockModel>> models;
    std::vector<BlockModelInstance> instances;
private:
    Camera* camera;
    Window* window;

    Texture dirt;

    std::shared_ptr<BlockModel> editingModel = nullptr;
    std::shared_ptr<EditingBlockModel> editingInstance = nullptr;
    glm::ivec3 editingPos {};
};
