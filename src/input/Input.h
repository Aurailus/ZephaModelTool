//
// Created by aurailus on 09/04/19.
//

#pragma once

#include <glm/vec2.hpp>

class GLFWwindow;

class Input {
public:
    Input();
    void init(GLFWwindow* window);
    void update();

    bool keyDown(int key) const;
    bool keyPressed(int key) const;
    bool keyReleased(int key) const;

    glm::ivec2 mousePos() const;
    glm::ivec2 mouseDelta() const;
private:
    static void keyCallback(GLFWwindow* window, int key, int code, int action, int mode);
    static void scrollCallback(GLFWwindow* window, double, double yO);

    bool keysNew[1024] {false};
    bool keysDown[1024] {false};
    bool keysPressed[1024] {false};
    bool keysReleased[1024] {false};

    GLFWwindow* window = nullptr;
    glm::ivec2 mouse, lastMouse;
};