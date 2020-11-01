//
// Created by aurailus on 2020-07-05.
//

#pragma once

#include "ViewportController.h"

class Input;
class Camera;
class Window;
class BlockModelManager;

class Controller {
public:
    Controller(Input& input, Window& window, Camera& camera, BlockModelManager& blockManager);

    void update();

private:
    void modelSelect();
    void modelEdit();

    ViewportController viewport;

    Input& input;
    Window& window;
    Camera& camera;
    BlockModelManager& blockManager;
};
