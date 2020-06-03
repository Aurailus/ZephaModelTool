//
// Created by aurailus on 09/04/19.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Input.h"

#include "../graph/Window.h"

Input::Input() {
    for (bool& key : keysDown)     key = false;
    for (bool& key : keysPressed)  key = false;
    for (bool& key : keysReleased) key = false;
    for (bool& key : keysNew)      key = false;
}

void Input::init(GLFWwindow *window) {
    this->window = window;
    glfwSetKeyCallback(window, keyCallback);
    glfwSetScrollCallback(window, scrollCallback);
}

void Input::update() {
    for (bool &key : keysPressed)  key = false;
    for (bool &key : keysReleased) key = false;

    for (int i = 32; i < 1024; i++) {
        if (keysNew[i]) {
            if (!keysDown[i]) keysPressed[i] = true;
            keysDown[i] = true;
        }
        else {
            if (keysDown[i]) keysReleased[i] = true;
            keysDown[i] = false;
        }
    }

    for (unsigned int i = GLFW_MOUSE_BUTTON_1; i < GLFW_MOUSE_BUTTON_LAST; i++) {
        if (glfwGetMouseButton(window, i) == GLFW_PRESS) {
            if (!keysDown[i]) keysPressed[i] = true;
            keysDown[i] = true;
        }
        else {
            if (keysDown[i]) keysReleased[i] = true;
            keysDown[i] = false;
        }
    }

    double x, y;
    glm::ivec2 lastMouse = mouse;
    glfwGetCursorPos(window, &x, &y);
    mouse = { static_cast<int>(x), static_cast<int>(y) };
    delta = mouse - lastMouse;

    if (mouseLocked) {
        glfwSetCursorPos(window, lock.x, lock.y);
        mouse = lock;
    }
}

bool Input::keyDown(int key) const {
    return keysDown[key];
}

bool Input::keyPressed(int key) const {
    return keysPressed[key];
}

bool Input::keyReleased(int key) const {
    return keysReleased[key];
}

std::shared_ptr<std::function<void(int delta)>> Input::addScrollCallback(std::function<void(int delta)> cb) {
    auto sPtr = std::make_shared<std::function<void(int delta)>>(cb);
    callbacks.emplace(sPtr);
    return sPtr;
}

void Input::keyCallback(GLFWwindow* window, int key, int, int action, int) {
    auto w = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 32 && key < 1024) {
        if (action == GLFW_PRESS) w->getInput().keysNew[key] = true;
        else if (action == GLFW_RELEASE) w->getInput().keysNew[key] = false;
    }
}

void Input::scrollCallback(GLFWwindow *window, double xO, double yO) {
    auto w = static_cast<Window*>(glfwGetWindowUserPointer(window));

    auto it = w->getInput().callbacks.cbegin();
    while (it != w->getInput().callbacks.cend()) {
        auto& cb = *it;
        if (cb.use_count() == 1) it = w->getInput().callbacks.erase(it);
        else {
            (*cb)(yO);
            it++;
        }
    }
}

glm::ivec2 Input::mousePos() const {
    return mouse;
}

glm::ivec2 Input::mouseDelta() const {
    return delta;
}

void Input::setMouseLocked(bool locked) {
    if ((this->mouseLocked && locked) || (!this->mouseLocked & !locked)) return;
    this->mouseLocked = locked;
    this->lock = mouse;
    glfwSetInputMode(window, GLFW_CURSOR, locked ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);
}
