//
// Created by aurailus on 2020-05-28.
//

#pragma once

#include <string>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Shader {
public:
    void createFromString(std::string& vertexSource, std::string& fragmentSource);
    void createFromFile(const std::string& vertexFile, const std::string& fragmentFile);

    int get(const std::string &name);

    void use();
    static void clearShader();

    void set(int loc, unsigned int val);
    void set(int loc, int val);
    void set(int loc, float val);
    void set(int loc, glm::vec3 val);
    void set(int loc, glm::vec4 val);
    void set(int loc, glm::mat4 val);

    void setArr(int loc, unsigned int count, glm::mat4 &start);

    void cleanup();
    ~Shader();

private:
    static std::string readFile(const std::string& fileLocation);
    void compileShader(const std::string& vertexSource, const std::string& fragmentSource);
    void addShader(unsigned int program, const std::string& shaderCode, int shaderType);

    inline void checkActive();

    unsigned int shaderID = 0;
    std::string vertexFile {};
    std::string fragmentFile {};
};
