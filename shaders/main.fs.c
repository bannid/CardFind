#version 330

in vec3 FragNormal;
in vec2 FragUv;
in vec3 FragWorld;

out vec4 FragColour;

uniform vec3 uColour;

uniform sampler2D uTexture;

#define LIGHT_DIRECTION normalize(vec3(0,1,2))

void main()
{
    float Dot = dot(FragNormal, LIGHT_DIRECTION) * .5 + .5;
    vec3 Colour = texture(uTexture, FragUv).rgb;
    // NOTE(Banni): Output colour
    FragColour = vec4(Colour, 1.0f);
}