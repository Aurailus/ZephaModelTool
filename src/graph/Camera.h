//
// Created by aurailus on 2020-05-29.
//

#pragma once

#include <memory>
#include <functional>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Window;

class Camera {
public:
    Camera(Window* window);
    void changeSize(glm::ivec2 size);

    glm::vec3 getPos();
    void setPos(glm::vec3 pos);

    double getPitch();
    void setPitch(double pitch);

    double getYaw();
    void setYaw(double yaw);

    glm::mat4 getProjectionMatrix();
    glm::mat4 getOrthographicMatrix();
    glm::mat4 getViewMatrix();

    glm::vec3 getFront();
    glm::vec3 getRight();

private:
    void createMatrices();
    void update();

    glm::ivec2 size;
    glm::mat4 projectionMatrix;
    glm::mat4 orthographicMatrix;

    float fov = 90.0f;
    float ratio = 0;

    static constexpr float projNearClip = 0.1f;
    static constexpr float projFarClip = 1000.0f;
    static constexpr float orthNearClip = -1000.f;
    static constexpr float orthFarClip = 1000.f;

    const glm::vec3 worldUp = {0, 1, 0};
    glm::vec3 front {0, 0, -1}, right, up;

    glm::vec3 pos {0, 0, 0};
    double yaw = 0;
    double pitch = 0;

    std::shared_ptr<std::function<void(glm::ivec2)>> resizeCallback;
};

