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
    camera(camera) {}

void ViewportControl::update() {
    if (input.keyDown(GLFW_MOUSE_BUTTON_LEFT)) {
        yaw += -input.mouseDelta().x * panFactor;
        pitch += -input.mouseDelta().y * panFactor;
        pitch = fmin(fmax(pitch, -1.5), 1.5);
    }

    glm::vec3 camPos = {
        distance * -sinf(yaw) * cosf(pitch),
        distance * -sinf(pitch),
        -distance * cosf(yaw) * cosf(pitch)
    };

    glm::vec3 look = -camPos;
    float length = glm::length(look) + 0.00001;

    float lookPitch = asin(look.y / length);
    float lookYaw = asin(look.z / (cos(asin(look.y / length)) * length));

    if (look.x <= 0) {
        lookYaw *= -1;
        lookYaw += 3.14159;
    }

    camera.setPos(camPos);
    camera.setPitch(lookPitch);
    camera.setYaw(lookYaw);
}
