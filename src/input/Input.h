//
// Created by aurailus on 09/04/19.
//

#pragma once

#include <memory>
#include <functional>
#include <glm/vec2.hpp>
#include <unordered_set>

class GLFWwindow;

class Input {
public:
    Input();
    void init(GLFWwindow* window);
    void update();

    bool keyDown(int key) const;
    bool keyPressed(int key) const;
    bool keyReleased(int key) const;

    std::shared_ptr<std::function<void(int delta)>> addScrollCallback(std::function<void(int delta)> cb);

    glm::ivec2 mousePos() const;
    glm::ivec2 mouseDelta() const;
private:
    static void keyCallback(GLFWwindow* window, int key, int code, int action, int mode);
    static void scrollCallback(GLFWwindow* window, double, double yO);

    bool keysNew[1024] {false};
    bool keysDown[1024] {false};
    bool keysPressed[1024] {false};
    bool keysReleased[1024] {false};

    std::unordered_set<std::shared_ptr<std::function<void(int delta)>>> callbacks;

    GLFWwindow* window = nullptr;
    glm::ivec2 mouse, lastMouse;
};