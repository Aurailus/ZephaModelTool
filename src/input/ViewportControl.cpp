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
    }

    float camAngleX = yaw;
    float camAngleY = pitch;

    camera.setPos({
        distance * -sinf(camAngleX) * cosf(camAngleY),
        distance * -sinf(camAngleY),
        -distance * cosf(camAngleX) * cosf(camAngleY)
    });

    std::cout << camera.getPos().x << ", " << camera.getPos().y << ", " << camera.getPos().z << std::endl;

    glm::vec3 cp = -camera.getPos();

//    camera.setPitch(asin(-cp.y));
//    camera.setYaw(atan2(cp.x, cp.z));

    camera.setPitch(asin(cp.y / glm::length(cp)));
    camera.setYaw(asin(cp.z / (cos(asin(cp.y / glm::length(cp))) * glm::length(cp))));



//    camera.setPos({sin(yaw) * distance * sin(pitch), sin(pitch) * distance, cos(yaw) * distance * sin(pitch)});
//    camera.setYaw(-yaw);
//    camera.setPitch(-pitch);
}
