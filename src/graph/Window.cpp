//
// Created by aurailus on 2020-05-28.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

Window::Window(glm::ivec2 size) :
    size(size) {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW context." << std::endl;
        glfwTerminate();
        exit(1);
    }

    // Version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Compatibility - No Backwards compat, only forwards
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the window
    if (!(window = glfwCreateWindow(size.x, size.y, "ModelTool", nullptr, nullptr))) {
        std::cout << "Failed to initialize GLFW window." << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);

    // Setup callbacks
    glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeCallback(window, resizeCallback);

    // Set basic properties (v-sync, cursor mode, maximize)
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSwapInterval(1);
//    glfwMaximizeWindow(mainWindow);

    // Initialize GLEW
    GLenum error;
    glewExperimental = GL_TRUE;
    if ((error = glewInit()) != GLEW_OK) {
        std::cout << "GLEW Encountered a fatal error:\n" << glewGetErrorString(error) << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(1);
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, size.x, size.y);

    input.init(window);
}

std::shared_ptr<std::function<void(glm::ivec2)>> Window::addResizeCallback(std::function<void(glm::ivec2)> cb) {
    auto sPtr = std::make_shared<std::function<void(glm::ivec2)>>(cb);
    callbacks.emplace(sPtr);
    return sPtr;
}

void Window::update() {
    input.update();
}

glm::ivec2 Window::getSize() {
    return size;
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Window::shouldEnd() {
    return static_cast<bool>(glfwWindowShouldClose(window)) || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

Input &Window::getInput() {
    return input;
}

void Window::resizeCallback(GLFWwindow* window, int width, int height) {
    auto w = static_cast<Window*>(glfwGetWindowUserPointer(window));

    glfwGetFramebufferSize(window, &w->size.x, &w->size.y);
    glViewport(0, 0, w->size.x, w->size.y);

    auto it = w->callbacks.cbegin();
    while (it != w->callbacks.cend()) {
        auto& cb = *it;
        if (cb.use_count() == 1) it = w->callbacks.erase(it);
        else {
            (*cb)(w->size);
            it++;
        }
    }
}