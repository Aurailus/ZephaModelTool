//
// Created by aurailus on 2020-05-28.
//

#pragma once

#include "graph/Window.h"
#include "graph/Camera.h"
#include "graph/Renderer.h"

#include "input/ViewportControl.h"

#include "graph/Mesh.h"
#include "graph/Texture.h"

class App {
public:
    App();

    void update();
    void render();

private:
    Window window;
    Camera camera;
    Renderer renderer;
    Input& input;

    ViewportControl controller;

    BlockMesh test,test2;
    Texture tex;
};
