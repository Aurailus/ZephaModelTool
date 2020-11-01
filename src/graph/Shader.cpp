//
// Created by aurailus on 2020-05-28.
//

#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

void Shader::createFromString(std::string& vertexSource, std::string& fragmentSource) {
    compileShader(vertexSource, fragmentSource);
}

void Shader::createFromFile(const std::string& vertexFile, const std::string& fragmentFile) {
    this->vertexFile = vertexFile;
    this->fragmentFile = fragmentFile;

    std::string vertexSource   = readFile(vertexFile);
    std::string fragmentSource = readFile(fragmentFile);

    compileShader(vertexSource, fragmentSource);
}

void Shader::use() {
    glUseProgram(shaderID);
}

void Shader::clearShader() {
    glUseProgram(0);
}

GLint Shader::get(const std::string &name) {
    return glGetUniformLocation(shaderID, name.c_str());
}

void Shader::set(int loc, unsigned int val) {
    checkActive();
    glUniform1ui(loc, val);
}

void Shader::set(int loc, int val) {
    checkActive();
    glUniform1i(loc, val);
}

void Shader::set(int loc, float val) {
    checkActive();
    glUniform1f(loc, val);
}

void Shader::set(int loc, glm::vec3 val) {
    checkActive();
    glUniform3f(loc, val.x, val.y, val.z);
}

void Shader::set(int loc, glm::vec4 val) {
    checkActive();
    glUniform4f(loc, val.x, val.y, val.z, val.w);
}

void Shader::set(int loc, glm::mat4 val) {
    checkActive();
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setArr(int loc, unsigned int count, glm::mat4 &start) {
    checkActive();
    glUniformMatrix4fv(loc, count, GL_FALSE, glm::value_ptr(start));
}

void Shader::cleanup() {
    if (shaderID != 0) {
        glDeleteProgram(shaderID);
    }
}

Shader::~Shader() {
    cleanup();
}

std::string Shader::readFile(const std::string& fileLocation) {
    std::string contents;
    std::ifstream fileStream(fileLocation, std::ios::in);

    if (!fileStream.is_open()) {
        std::cout << "Failed to open shader file '" << fileLocation << "'." << std::endl;
        exit(1);
    }

    std::string line;
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        contents.append(line + "\n");
    }

    fileStream.close();
    return contents;
}

void Shader::compileShader(const std::string& vertexSource, const std::string& fragmentSource) {
    shaderID = glCreateProgram();

    if (!shaderID) {
        std::cout << "Error creating shader program." << std::endl;
        exit(1);
    }

    addShader(shaderID, vertexSource, GL_VERTEX_SHADER);
    addShader(shaderID, fragmentSource, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);

    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        std::cout << "Error linking program.\n" << eLog << std::endl;
        exit(1);
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);

    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        std::cout << "Error validating program.\n" << eLog << std::endl;
        exit(1);
    }
}

void Shader::addShader(GLuint program, const std::string& shaderCode, int shaderType) {
    GLuint shader = glCreateShader(shaderType);


    const GLchar* shaderCodeCStr = shaderCode.data();
    int shaderLength = static_cast<int>(shaderCode.length());

    glShaderSource(shader, 1, &shaderCodeCStr, &shaderLength);
    glCompileShader(shader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if (!result) {
        std::string& shaderName = (shaderType == GL_VERTEX_SHADER) ? vertexFile : fragmentFile;
        glGetShaderInfoLog(shader, sizeof(eLog), nullptr, eLog);
        std::cout << "Error compiling '" << shaderName << "':\n" << eLog << std::endl << shaderCode << std::endl;
        return;
    }

    glAttachShader(program, shader);
}

void Shader::checkActive() {
    int cProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &cProgram);
    if (cProgram != shaderID) throw std::runtime_error("Attempted an action on an inactive shader!");
}