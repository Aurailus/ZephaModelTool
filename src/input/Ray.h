//
// Created by aurailus on 2020-06-02.
//

#pragma once

#include <glm/glm.hpp>

#include "../graph/Window.h"
#include "../graph/Camera.h"

namespace Ray {
    static glm::vec3 worldRayFromCursor(Window &window, Camera &camera) {
        return glm::vec3(glm::inverse(camera.getViewMatrix()) *
            glm::vec4(glm::vec2(glm::inverse(camera.getProjectionMatrix()) * glm::vec4 {
                (2.f * window.getInput().mousePos().x) / window.getSize().x - 1.f,
                    1.f - (2.f * window.getInput().mousePos().y) / window.getSize().y, -1.f, 1.f }), -1.0, 0.0));
    }

    static float rayInterceptsRect(std::array<glm::vec3, 4> p, glm::vec3 rayOrigin, glm::vec3 rayDir) {
        rayDir = glm::normalize(rayDir);
        glm::vec3 v1 = p[1] - p[0];
        glm::vec3 v2 = p[3] - p[0];
        glm::vec3 n = glm::normalize(glm::cross(v1, v2));

        float A = p[0].y * (p[1].z - p[2].z) + p[1].y * (p[2].z - p[0].z) + p[2].y * (p[0].z - p[1].z);
        float B = p[0].z * (p[1].x - p[2].x) + p[1].z * (p[2].x - p[0].x) + p[2].z * (p[0].x - p[1].x);
        float C = p[0].x * (p[1].y - p[2].y) + p[1].x * (p[2].y - p[0].y) + p[2].x * (p[0].y - p[1].y);
        float D = -p[0].x * (p[1].y * p[2].z - p[2].y * p[1].z) - p[1].x * (p[2].y * p[0].z - p[0].y * p[2].z) - p[2].x * (p[0].y * p[1].z - p[1].y * p[0].z);

        float t = -(A * rayOrigin.x + B * rayOrigin.y + C * rayOrigin.z + D) / (A * rayDir.x + B * rayDir.y + C * rayDir.z);
        if (t < 0) return 0;
        glm::vec3 intercepts = rayOrigin + rayDir * t;

        v1 = glm::normalize(v1);
        glm::vec3 v3 = glm::normalize(p[3] - p[2]);
        glm::vec3 v4 = glm::normalize(intercepts - p[0]);
        glm::vec3 v5 = glm::normalize(intercepts - p[2]);

        if (glm::dot(v1, v4) > 0 && glm::dot(v3, v5) > 0) return t;
        return 0;
    }
}