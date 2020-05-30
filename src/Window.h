//
// Created by aurailus on 2020-05-28.
//

#pragma once

#include <glm/vec2.hpp>

class GLFWwindow;

class Window {
public:
    Window() : Window({800, 600}) {};
    explicit Window(glm::ivec2 size);

    glm::ivec2 getSize();
    void swapBuffers();
    bool shouldEnd();

private:
    glm::ivec2 size;
    GLFWwindow* window;

    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {};
    static void resizeCallback(GLFWwindow* window, int width, int height) {};
};
