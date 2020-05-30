//
// Created by aurailus on 2020-05-29.
//

#pragma once

#include <vector>

#include "Vertex.h"

template <const VertexParamList* P, class V>
class Mesh {
public:
    Mesh() = default;
    Mesh(const std::vector<V>& vertices, const std::vector<unsigned int>& indices);
    void create(const std::vector<V>& vertices, const std::vector<unsigned int>& indices);

    virtual void draw() const;

    void cleanup();
    ~Mesh();

private:
    void genArrays(unsigned int vboLength, unsigned int iboLength, const void* verticesPtr, const void* indicesPtr);
    void createVertexAttrib(unsigned int offset, unsigned int size, int type, unsigned int stride, const void* pointer);

    unsigned int VAO, VBO, IBO;
    unsigned long indCount;
};

typedef Mesh<&blockVertexParams, BlockVertex> BlockMesh;

#include "Mesh.inl"
