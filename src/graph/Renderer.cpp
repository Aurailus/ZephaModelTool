//
// Created by aurailus on 2020-05-28.
//

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Renderer.h"

#include "Window.h"
#include "Camera.h"

Renderer::Renderer(Window *window, Camera* camera) :
    window(window),
    camera(camera) {
    assert(window && camera);

    sWorld.createFromFile("../assets/shader/world.vs", "../assets/shader/world.fs");
    sWorld.use();

    uProjection = sWorld.get("projection");
    uModel = sWorld.get("model");
    uView = sWorld.get("view");
    uHighlight = sWorld.get("highlight");
}

void Renderer::setModelMatrix(const glm::mat4& modelMatrix) {
    glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void Renderer::setClearColor(glm::vec4 color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::reset() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDisable(GL_BLEND);

    glViewport(0, 0, window->getSize().x, window->getSize().y);

    sWorld.set(uProjection, camera->getProjectionMatrix());
    sWorld.set(uView, camera->getViewMatrix());

    sWorld.set(uHighlight, false);
}

void Renderer::swap() {
    window->swapBuffers();
}