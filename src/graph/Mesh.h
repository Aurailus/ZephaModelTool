//
// Created by aurailus on 2020-05-29.
//

#include "Vertex.h"

#pragma once

#include <memory>
#include <vector>
#include <GL/glew.h>

template <class V>
class Mesh {
public:
    Mesh() = default;
    Mesh(const std::vector<V>& vertices, const std::vector<unsigned int>& indices);
    void create(const std::vector<V>& vertices, const std::vector<unsigned int>& indices);

    virtual void draw() const;

    void cleanup();
    ~Mesh();

protected:
    void createArrays(unsigned int vboLength, unsigned int iboLength, const void* verticesPtr, const void* indicesPtr);
    void createVertexAttrib(unsigned int offset, unsigned int size, int type, unsigned int stride, const void* pointer);
    void finish();

    unsigned int VAO, VBO, IBO;
    unsigned long indCount;
    std::shared_ptr<int> refs = std::make_shared<int>();
};

#include "Mesh.inl"

class BlockMesh : public Mesh<BlockVertex> {
public:
    BlockMesh(const std::vector<BlockVertex>& vertices, const std::vector<unsigned int>& indices) : Mesh(vertices, indices) {
        auto& p = BlockVertexParams;
        for (unsigned int idx = 0; idx < p.count; idx++)
            createVertexAttrib(idx, p.params[idx].size, p.params[idx].type,
                p.params[idx].stride, reinterpret_cast<const void*>(p.params[idx].pointer));
        finish();
    };
};

class GuiMesh : public Mesh<GuiVertex> {
public:
    GuiMesh(const std::vector<GuiVertex>& vertices, const std::vector<unsigned int>& indices) : Mesh(vertices, indices) {
        auto& p = BlockVertexParams;
        for (unsigned int idx = 0; idx < p.count; idx++)
            createVertexAttrib(idx, p.params[idx].size, p.params[idx].type,
                p.params[idx].stride, reinterpret_cast<const void*>(p.params[idx].pointer));
        finish();
    };
};
