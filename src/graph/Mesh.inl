//
// Created by aurailus on 2020-05-29.
//

#include "Mesh.h"

template <class V>
Mesh<V>::Mesh(const std::vector<V>& vertices, const std::vector<unsigned int>& indices) {
    create(vertices, indices);
}

template <class V>
void Mesh<V>::create(const std::vector<V> &vertices, const std::vector<unsigned int> &indices) {
    indCount = static_cast<size_t>(indices.size());

    createArrays(static_cast<unsigned int>(vertices.size() * sizeof(V)),
        static_cast<unsigned int>(indices.size() * sizeof(unsigned int)),
        &vertices.front(), &indices.front());
}

template<class V>
void Mesh<V>::finish() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

template <class V>
void Mesh<V>::createArrays(unsigned int vboLength, unsigned int iboLength, const void *verticesPtr, const void *indicesPtr) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iboLength, indicesPtr, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vboLength, verticesPtr, GL_STATIC_DRAW);
}

template <class V>
void Mesh<V>::createVertexAttrib(unsigned int offset, unsigned int size, int type, unsigned int stride, const void* pointer) {
    glEnableVertexAttribArray(offset);
    if (type == GL_INT) glVertexAttribIPointer(offset, size, type, stride, pointer);
    else glVertexAttribPointer(offset, size, type, GL_FALSE, stride, pointer);
}

template <class V>
void Mesh<V>::draw() const {
    if (VAO == 0) return;
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, indCount, GL_UNSIGNED_INT, nullptr);
}

template <class V>
void Mesh<V>::cleanup() {
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (IBO) glDeleteBuffers(1, &IBO);

    VAO = 0;
    VBO = 0;
    IBO = 0;

    indCount = 0;
}

template <class V>
Mesh<V>::~Mesh() {
    if (refs.use_count() == 1) cleanup();
}
