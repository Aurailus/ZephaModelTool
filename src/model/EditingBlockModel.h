//
// Created by aurailus on 2020-06-02.
//

#pragma once

#include <memory>
#include <vector>

#include "../graph/Mesh.h"

class Window;
class Camera;
class Renderer;
class BlockModel;
class ViewportControl;

class EditingBlockModel {
public:
    EditingBlockModel(glm::vec3 pos, std::shared_ptr<BlockModel> model);

    void update(ViewportControl &viewport, Window &window, Camera &camera);
    void render(Renderer& renderer);

private:
    void updateFaces();

    glm::vec3 pos;
    std::shared_ptr<BlockModel> model;

    std::vector<BlockMesh> faces;
    std::vector<bool> facesHighlighted;
};
