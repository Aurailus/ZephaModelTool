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
    static void setClearColor(glm::vec4 color);

    void reset();
    void swap();

    Shader sWorld;
    unsigned int uProjection;
    unsigned int uModel;
    unsigned int uView;
    unsigned int uHighlight;

private:
    Window* window;
    Camera* camera;
};
