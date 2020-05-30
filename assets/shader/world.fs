#version 330 core

in vec2 texCoords;
in vec3 normal;

//uniform sampler2D tex;

out vec3 color;

void main() {
    vec4 spec = vec4(1, 0, 0, 1);
//    vec4 spec = texture(tex, texCoords);
    if (spec.a < 0.1) discard;

    color = spec.xyz;
}