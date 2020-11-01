//
// Created by aurailus on 2020-05-28.
//

#pragma once

#include <memory>
#include <functional>
#include <glm/vec2.hpp>
#include <unordered_set>

#include "../input/Input.h"

class GLFWwindow;

class Window {
public:
    Window() : Window({800, 600}) {};
    explicit Window(glm::ivec2 size);

    std::shared_ptr<std::function<void(glm::ivec2)>> addResizeCallback(std::function<void(glm::ivec2)> cb);
    void update();

    glm::ivec2 getSize();
    Input& getInput();

    void swapBuffers();
    bool shouldEnd();
private:
    glm::ivec2 size;
    GLFWwindow* window;
    Input input;

    std::unordered_set<std::shared_ptr<std::function<void(glm::ivec2)>>> callbacks;

    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {};
    static void resizeCallback(GLFWwindow* window, int width, int height);
};
