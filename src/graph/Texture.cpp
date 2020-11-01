
//
// Created by aurailus on 31/05/20.
//

#include <GL/glew.h>
#include <iostream>


#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#define STB_IMAGE_IMPLEMENTATION
#pragma clang diagnostic pop
#include <stb_image/stb_image.h>

#include "Texture.h"

Texture::Texture(const std::string& file) {
    loadFromFile(file);
}

void Texture::loadFromFile(std::string file) {
    int bitDepth;
    unsigned char *texData = stbi_load(file.c_str(), &size.x, &size.y, &bitDepth, 0);

    if (!texData) {
        std::cout << "Failed to load texture \"" << file << "\"" << std::endl;
        exit(0);
    }

    loadFromBytes(texData, size);
    stbi_image_free(texData);
}

void Texture::loadFromBytes(unsigned char* bytes, glm::ivec2 size) {
    if (textureID != 0) clear();
    this->size = size;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::updateTexture(glm::ivec2 pos, glm::ivec2 size, unsigned char *bytes) {
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, pos.x, pos.y, size.x, size.y, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
}


void Texture::use(unsigned short position) {
    glActiveTexture(GL_TEXTURE0 + position);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::clear() {
    glDeleteTextures(1, &textureID);
    textureID = 0;
    size = {};
}

Texture::~Texture() {
    if (refs.use_count() == 1) clear();
}