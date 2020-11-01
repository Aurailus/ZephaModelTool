//
// Created by aurailus on 2020-07-05.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Controller.h"

#include "Input.h"
#include "../model/BlockModelManager.h"
#include "../util/Ray.h"

Controller::Controller(Input& input, Window& window, Camera& camera, BlockModelManager& blockManager) :
    input(input),
    window(window),
    camera(camera),
    viewport(input, camera),
    blockManager(blockManager) {

}

void Controller::update() {
    viewport.update();

    if (!blockManager.getEditingModel()) modelSelect();
    else modelEdit();
}

void Controller::modelSelect() {
    glm::vec3 dir = Ray::worldRayFromCursor(window, camera);
    glm::vec3 ray = camera.getPos();

    float dis = 0.05f;
    while (dis < 20) {
        glm::vec3 end = ray + (dir * dis);
        glm::ivec3 pos = glm::floor(end + glm::vec3(0.5));

        if (blockManager.highlightInstanceAtPos(pos)) {
            if (input.keyPressed(GLFW_MOUSE_BUTTON_LEFT)) {
                blockManager.setEditingInstance(pos);
                viewport.setViewFocus(pos);
            }
            break;
        }

        dis += 0.05;
    }
}

void Controller::modelEdit() {

}
