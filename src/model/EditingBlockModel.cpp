//
// Created by aurailus on 2020-06-02.
//

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "EditingBlockModel.h"

#include "BlockModel.h"
#include "../util/Ray.h"
#include "../graph/Renderer.h"

EditingBlockModel::EditingBlockModel(glm::vec3 pos, std::shared_ptr<BlockModel> model) :
    pos(pos),
    model(model) {
    updateFaces();
}

void EditingBlockModel::update(ViewportController &viewport, Window &window, Camera &camera) {
    if (!highlightedFace || !window.getInput().keyDown(GLFW_MOUSE_BUTTON_LEFT))
        holdOrigin = findHoveredFace(viewport, window, camera);
    else if (highlightedFace)
        manipulateFace(viewport, window, camera);
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

glm::vec3 EditingBlockModel::findHoveredFace(ViewportController &viewport, Window &window, Camera &camera) {
    glm::vec3 dir = Ray::worldRayFromCursor(window, camera);
    glm::vec3 ray = camera.getPos();

    int ind = -1;
    float smallestDistance = 1000;
    glm::vec3 targetPos;

    for (int i = 0; i < faces.size(); i++) {
        facesHighlighted[i] = false;

        float dist;
        glm::vec3 intPos;

        Ray::rayInterceptsRect(ray, dir, this->model->faces[i].points, pos, dist, intPos);
        if (dist != 0 && dist < smallestDistance) {
            smallestDistance = dist;
            targetPos = intPos;
            ind = i;
        }
    }
    if (ind != -1) {
        highlightedFace = &this->model->faces[ind];
        this->facesHighlighted[ind] = true;
    }
    else highlightedFace = nullptr;

    return targetPos;
}

void EditingBlockModel::manipulateFace(ViewportController &viewport, Window &window, Camera &camera) {
    if (window.getInput().keyDown(GLFW_MOUSE_BUTTON_LEFT)) {
        glm::vec3 ray = camera.getPos();
        glm::vec3 dir = Ray::worldRayFromCursor(window, camera);

        glm::vec3 nml = glm::normalize(glm::cross(highlightedFace->points[1] - highlightedFace->points[0],
                highlightedFace->points[3] - highlightedFace->points[0]));

        // Get ray to be on plane determined by the camera view-angle.
        auto lookVec = glm::abs(Ray::lookVecFromCamera(camera));
        float b = lookVec.x > lookVec.y ? lookVec.x > lookVec.z ? 0 : 2 : lookVec.y > lookVec.z ? 1 : 2;

        // Looking head-on at face, use a different lock value.
        if (nml[b] != 0) b = b == 1 ? 0 : 1;

        if (ray[b] < holdOrigin[b]) {
            while (ray[b] < holdOrigin[b]) ray += dir;
            while (ray[b] > holdOrigin[b]) ray -= dir / 20.f;
        }
        else {
            while (ray[b] > holdOrigin[b]) ray += dir;
            while (ray[b] < holdOrigin[b]) ray -= dir / 20.f;
        }
        ray[b] = holdOrigin[b];

        for (auto& point : highlightedFace->points) {
            glm::vec3 diff = ray - point - pos;
            if (true) diff = glm::vec3(glm::ivec3(diff * 16.f)) / 16.f;
            point += diff * glm::abs(nml);
        }

        std::cout << nml.x << ", " << nml.y << ", " << nml.z << std::endl;
        std::cout << b << std::endl;

        updateFaces();

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
    model->updateMesh();
}
