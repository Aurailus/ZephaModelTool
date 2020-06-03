//
// Created by aurailus on 2020-05-31.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>

#include "ViewportControl.h"

#include "../graph/Camera.h"
#include "Input.h"

ViewportControl::ViewportControl(Input &input, Camera &camera) :
    input(input),
    camera(camera) {

    this->cb = input.addScrollCallback([&](int delta) { distance = fmin(fmax(distance - delta * (distance / 6), 1.1), 20); });
}

void ViewportControl::update() {
    if (input.keyDown(GLFW_MOUSE_BUTTON_MIDDLE)) {
        input.setMouseLocked(true);
        yaw += -input.mouseDelta().x * panFactor;
        pitch += -input.mouseDelta().y * panFactor;
        pitch = fmin(fmax(pitch, -1.55), 1.55);
    }
    else input.setMouseLocked(false);

    glm::vec3 camPos = {
        distance * -sinf(yaw) * cosf(pitch),
        distance * -sinf(pitch),
        -distance * cosf(yaw) * cosf(pitch)
    };

    glm::vec3 look = -camPos;
    float length = glm::length(look) + 0.000001;

    float lookPitch = asin(look.y / length);
    float lookYaw = asin(look.z / (cos(asin(look.y / length)) * length));

    if (look.x <= 0) {
        lookYaw *= -1;
        lookYaw += M_PI;
    }

    camera.setPos(camPos + focus);
    camera.setPitch(lookPitch);
    camera.setYaw(lookYaw);
}

void ViewportControl::setViewFocus(glm::vec3 focus) {
    this->focus = focus;
}
