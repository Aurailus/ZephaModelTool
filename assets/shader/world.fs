#version 330 core

in vec2 texCoords;
in vec3 normal;
in vec3 blend;
in vec3 add;

uniform sampler2D tex;
uniform bool highlight;

out vec3 outColor;

void main() {
    vec4 spec = texture(tex, texCoords);
    if (spec.a < 0.1) discard;
    vec3 color = spec.xyz;

    if (highlight) {
        color *= 1.4;
        color += 0.025;
    }

    outColor = color;
}