#version 330 core

layout (location = 0) in vec3 aPosition;
//layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

//out vec2 texCoords;
out vec3 normal;

void main() {
    vec4 worldPos = model * vec4(aPosition, 1);
    gl_Position = projection * view * worldPos;
    normal = aNormal;
//    texCoords = aTexCoords;
}
