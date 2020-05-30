//
// Created by aurailus on 2020-05-28.
//

#pragma once

#include "Shader.h"

class Window;
class Camera;

class Renderer {
public:
    explicit Renderer(Window* window, Camera* camera);

    void setModelMatrix(const glm::mat4& modelMatrix);

    void reset();
    void swap();
private:
    Window* window;
    Camera* camera;

    Shader sWorld;
    unsigned int uProjection;
    unsigned int uModel;
    unsigned int uView;

    bool dir = true;
    unsigned char color = 0;
};
