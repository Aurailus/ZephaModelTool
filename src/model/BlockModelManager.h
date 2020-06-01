//
// Created by aurailus on 2020-05-31.
//

#pragma once

#include "BlockModel.h"
#include "../graph/Mesh.h"
#include "../graph/Texture.h"

class Input;
class Window;
class Renderer;
class Camera;

class BlockModelManager {
public:
    BlockModelManager(Camera* camera, Window* window);

    void render(Renderer& renderer);
    void update(Input& input);
private:
    Camera* camera;
    Window* window;

    std::vector<BlockModel> models;
    Texture dirt;
};
