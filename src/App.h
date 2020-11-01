//
// Created by aurailus on 2020-05-28.
//

#pragma once

#include "graph/Window.h"
#include "graph/Camera.h"
#include "graph/Renderer.h"

#include "model/BlockModelManager.h"
#include "input/Controller.h"

class App {
public:
    App();

    void update();
    void render();

private:
    Window window;
    Camera camera;
    Renderer renderer;

    BlockModelManager blockManager;

    Input& input;
    Controller controller;
};
