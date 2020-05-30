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
    glfwSetScrollCallback(window, scrollCallback);
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
}

glm::ivec2 Window::getSize() {
    return size;
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

bool Window::shouldEnd() {
    return static_cast<bool>(glfwWindowShouldClose(window)) || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}
