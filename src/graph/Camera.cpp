//
// Created by aurailus on 2020-05-29.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Camera.h"

Camera::Camera(Window* window) :
    size(window->getSize()) {
    createMatrices();
    resizeCallback = window->addResizeCallback([&](glm::ivec2 size) { changeSize(size); });
}

void Camera::changeSize(glm::ivec2 size){
    this->size = size;
    createMatrices();
}

glm::vec3 Camera::getPos() {
    return pos;
}

void Camera::setPos(glm::vec3 pos) {
    this->pos = pos;
}

double Camera::getPitch() {
    return pitch;
}

void Camera::setPitch(double pitch) {
    this->pitch = pitch;
}

double Camera::getYaw() {
    return yaw;
}

void Camera::setYaw(double yaw) {
    this->yaw = yaw;
}

glm::mat4 Camera::getProjectionMatrix() {
    return projectionMatrix;
}

glm::mat4 Camera::getOrthographicMatrix() {
    return orthographicMatrix;
}

glm::mat4 Camera::getViewMatrix() {
    update();
    return glm::lookAt(pos, pos + front, up);
}

glm::vec3 Camera::getFront() {
    return front;
}

glm::vec3 Camera::getRight() {
    return right;
}

void Camera::createMatrices() {
    ratio = size.x / static_cast<float>(size.y);
    projectionMatrix = glm::perspective(glm::radians(fov), ratio, projNearClip, projFarClip);
    orthographicMatrix = glm::ortho(0.0f, static_cast<float>(size.x), static_cast<float>(size.y), 0.0f, orthNearClip, orthFarClip);
}

void Camera::update() {
    front = glm::normalize(glm::vec3 {
            static_cast<float>(cos(yaw) * cos(pitch)),
            static_cast<float>(sin(pitch)),
            static_cast<float>(sin(yaw) * cos(pitch))});
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}