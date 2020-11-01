//
// Created by aurailus on 31/05/20.
//

#pragma once

#include <memory>
#include <string>
#include <glm/vec2.hpp>

class Texture {
public:
    Texture() = default;
    explicit Texture(const std::string& file);

    void loadFromFile(std::string file);
    void loadFromBytes(unsigned char* bytes, glm::ivec2 size);
    void updateTexture(glm::ivec2 pos, glm::ivec2 size, unsigned char* bytes);

    void use(unsigned short position = 0);
    void clear();

    ~Texture();

protected:
    glm::ivec2 size {};
    unsigned int textureID = 0;
    std::shared_ptr<int> refs = std::make_shared<int>();
};

