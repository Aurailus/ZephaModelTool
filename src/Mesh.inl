//
// Created by aurailus on 2020-05-29.
//

#include <GL/glew.h>

#include "Mesh.h"

template <const VertexParamList* P, class V>
Mesh<P, V>::Mesh(const std::vector<V>& vertices, const std::vector<unsigned int>& indices) {
    create(vertices, indices);
}

template <const VertexParamList* P, class V>
void Mesh<P, V>::create(const std::vector<V> &vertices, const std::vector<unsigned int> &indices) {
    indCount = static_cast<size_t>(indices.size());

    genArrays(static_cast<unsigned int>(vertices.size() * sizeof(V)),
              static_cast<unsigned int>(indices.size() * sizeof(unsigned int)),
              &vertices.front(), &indices.front());

    for (unsigned int idx = 0; idx < P->count; idx++) {
        const auto& param = P->params[idx];
        createVertexAttrib(idx, param.size, param.type, param.stride, param.pointer);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

template <const VertexParamList* P, class V>
void Mesh<P, V>::genArrays(unsigned int vboLength, unsigned int iboLength, const void *verticesPtr, const void *indicesPtr) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iboLength, indicesPtr, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vboLength, verticesPtr, GL_STATIC_DRAW);
}

template <const VertexParamList* P, class V>
void Mesh<P, V>::createVertexAttrib(unsigned int offset, unsigned int size, int type, unsigned int stride, const void* pointer) {
    glEnableVertexAttribArray(offset);
    if (type == GL_INT) glVertexAttribIPointer(offset, size, type, stride, pointer);
    else glVertexAttribPointer(offset, size, type, GL_FALSE, stride, pointer);
}

template <const VertexParamList* P, class V>
void Mesh<P, V>::draw() const {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_TRIANGLES, indCount, GL_UNSIGNED_INT, nullptr);
}

template <const VertexParamList* P, class V>
void Mesh<P, V>::cleanup() {
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (IBO) glDeleteBuffers(1, &IBO);

    VAO = 0;
    VBO = 0;
    IBO = 0;

    indCount = 0;
}

template <const VertexParamList* P, class V>
Mesh<P, V>::~Mesh() {
    cleanup();
}