//
// Created by aurailus on 2020-05-28.
//

#pragma once

#include "Window.h"
#include "Camera.h"
#include "Renderer.h"

class App {
public:
    App();

    void update();
    void render();

private:
    Window window;
    Camera camera;
    Renderer renderer;
};
