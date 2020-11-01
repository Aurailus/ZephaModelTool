//
// Created by aurailus on 2020-06-02.
//

#pragma once

#include <memory>
#include <vector>

#include "../graph/Mesh.h"
#include "BlockFace.h"

class Window;
class Camera;
class Renderer;
class BlockModel;
class ViewportController;

class EditingBlockModel {
public:
    EditingBlockModel(glm::vec3 pos, std::shared_ptr<BlockModel> model);

    void update(ViewportController &viewport, Window &window, Camera &camera);
    void render(Renderer& renderer);

private:
    glm::vec3 findHoveredFace(ViewportController &viewport, Window &window, Camera &camera);
    void manipulateFace(ViewportController &viewport, Window &window, Camera &camera);

    void updateFaces();

    glm::vec3 pos;
    std::shared_ptr<BlockModel> model;

    BlockFace* highlightedFace = nullptr;
    glm::vec3 holdOrigin;

    std::vector<BlockMesh> faces;
    std::vector<bool> facesHighlighted;
};
