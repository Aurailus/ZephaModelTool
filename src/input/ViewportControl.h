//
// Created by aurailus on 2020-05-31.
//

#pragma once

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
    double distance = 60;

    double pitch, yaw;
};
