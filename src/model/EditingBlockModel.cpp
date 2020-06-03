//
// Created by aurailus on 2020-06-02.
//

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "EditingBlockModel.h"

#include "BlockModel.h"
#include "../input/Ray.h"
#include "../graph/Renderer.h"

EditingBlockModel::EditingBlockModel(glm::vec3 pos, std::shared_ptr<BlockModel> model) :
    pos(pos),
    model(model) {
    updateFaces();
}

void EditingBlockModel::update(ViewportControl &viewport, Window &window, Camera &camera) {
    glm::vec3 dir = Ray::worldRayFromCursor(window, camera);
    glm::vec3 ray = camera.getPos();

//    bool found = false;
//    float dis = 0.05f;
//
//    while (dis < 20) {
//        glm::vec3 end = ray + (dir * dis);
//        glm::ivec3 blockSpace = glm::floor(end + glm::vec3(0.5));
//
//        for (auto& face : model->faces) {
////            if (instance.getPos() == blockSpace) {
////                instance.setHighlighted(true);
////                if (input.keyPressed(GLFW_MOUSE_BUTTON_LEFT)) {
////                    viewport.setViewFocus(instance.getPos());
////                    setEditingModel(instance);
////                }
////                found = true;
////                break;
////            }
//        }
//
//        if (found) break;
//        dis += 0.05;
//    }

    std::cout << Ray::rayInterceptsRect(this->model->faces[0].points, ray, dir) << std::endl;

    int ind = -1;
    float smallestDistance = 1000;
    for (int i = 0; i < faces.size(); i++) {
        facesHighlighted[i] = false;
        float dist = Ray::rayInterceptsRect(this->model->faces[i].points
//                {
//                                                             this->model->faces[i].points[3],
//                                                             this->model->faces[i].points[2],
//                                                             this->model->faces[i].points[1],
//                                                             this->model->faces[i].points[0]
//            }
            , ray, dir);
        if (dist != 0 && dist < smallestDistance) {
            smallestDistance = dist;
            ind = i;
        }
    }
    if (ind != -1) facesHighlighted[ind] = true;
}

void EditingBlockModel::render(Renderer &renderer) {
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(pos));
    renderer.setModelMatrix(model);

    for (int i = 0; i < faces.size(); i++) {
        renderer.sWorld.set(renderer.uHighlight, facesHighlighted[i]);
        faces[i].draw();
    }
}

void EditingBlockModel::updateFaces() {
    faces.clear();
    facesHighlighted.clear();
    for (auto& face : this->model->faces) {
        BlockMesh mesh;
        mesh.create({
            BlockVertex { face.points[0], face.texCoords[0], {} },
            BlockVertex { face.points[1], face.texCoords[1], {} },
            BlockVertex { face.points[2], face.texCoords[2], {} },
            BlockVertex { face.points[3], face.texCoords[3], {} }
        }, {0, 1, 2, 2, 3, 0});
        faces.push_back(mesh);
        facesHighlighted.push_back(false);
    }
}
