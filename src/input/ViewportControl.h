//
// Created by aurailus on 2020-05-31.
//

#pragma once

#include <memory>
#include <functional>

class Input;
class Camera;

class ViewportControl {
public:
    ViewportControl(Input& input, Camera& camera);

    void update();
    void setViewFocus(glm::vec3 focus);

private:
    Input& input;
    Camera& camera;

    double panFactor = 0.0075;
    double distance = 4;

    glm::vec3 focus;
    double pitch, yaw;

    std::shared_ptr<std::function<void(int delta)>> cb;
};
