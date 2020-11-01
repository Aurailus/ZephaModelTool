//
// Created by aurailus on 2020-06-02.
//

#pragma once

#include <glm/glm.hpp>

#include "../graph/Window.h"
#include "../graph/Camera.h"

namespace Ray {
    static glm::vec3 lookVecFromCamera(Camera& camera) {
        return glm::normalize(glm::vec3 {
            cos(camera.getYaw()) * cos(camera.getPitch()),
            sin(camera.getPitch()),
            sin(camera.getYaw()) * cos(camera.getPitch()),
        });
    }

    static glm::vec3 worldRayFromCursor(Window &window, Camera &camera) {
        return glm::vec3(glm::inverse(camera.getViewMatrix()) *
            glm::vec4(glm::vec2(glm::inverse(camera.getProjectionMatrix()) * glm::vec4 {
                (2.f * window.getInput().mousePos().x) / window.getSize().x - 1.f,
                    1.f - (2.f * window.getInput().mousePos().y) / window.getSize().y, -1.f, 1.f }), -1.0, 0.0));
    }

    static void rayInterceptsRect(glm::vec3 rayOrigin, glm::vec3 rayDir,
        std::array<glm::vec3, 4> p, glm::vec3 pO, float& intDist, glm::vec3& intPos) {

        rayDir = glm::normalize(rayDir);
        rayOrigin -= pO;
        glm::vec3 v1 = p[1] - p[0];
        glm::vec3 v2 = p[3] - p[0];
        glm::vec3 n = glm::normalize(glm::cross(v1, v2));

        float D = -glm::dot(n, p[0]);

        float t = -(glm::dot(n, rayOrigin) + D) / (glm::dot(n, rayDir));
        if (t < 0) {
            intDist = 0;
            intPos = {};
            return;
        }
        glm::vec3 intercepts = rayOrigin + rayDir * t;

        // First pass
        v1 = glm::normalize(v1);
        glm::vec3 v3 = glm::normalize(p[3] - p[2]);
        glm::vec3 v4 = glm::normalize(intercepts - p[0]);
        glm::vec3 v5 = glm::normalize(intercepts - p[2]);

        if (!(glm::dot(v1, v4) >= 0 && glm::dot(v3, v5) >= 0)) {
            intDist = 0;
            intPos = {};
            return;
        }

        // Second pass
        v2 = glm::normalize(v2);
        glm::vec3 v6 = glm::normalize(p[0] - p[3]);
        glm::vec3 v7 = glm::normalize(intercepts - p[1]);
        glm::vec3 v8 = intercepts - p[3];

        if (!(glm::dot(v2, v7) >= 0 && glm::dot(v6, v8) >= 0)) {
            intDist = 0;
            intPos = {};
            return;
        };

        intDist = t;
        intPos = intercepts;
    }

    static float rayInterceptsRectDist(glm::vec3 rayOrigin, glm::vec3 rayDir, std::array<glm::vec3, 4> p, glm::vec3 pO = {}) {
        float dist;
        glm::vec3 pos;
        rayInterceptsRect(rayOrigin, rayDir, p, pO, dist, pos);
        return dist;
    }

    static bool rayInterceptsRects(glm::vec3 rayOrigin, glm::vec3 rayDir, std::vector<std::array<glm::vec3, 4>> pointsVec, glm::vec3 pO = {}) {
        for (auto& p : pointsVec)
            if (rayInterceptsRectDist(rayOrigin, rayDir, p, pO)) return true;
        return false;
    }
}