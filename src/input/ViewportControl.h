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

private:
    Input& input;
    Camera& camera;

    double panFactor = 0.01;
    double distance = 120;

    double pitch, yaw;

    std::shared_ptr<std::function<void(int delta)>> cb;
};
