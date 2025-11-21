#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUv;

out vec3 FragNormal;
out vec2 FragUv;
out vec3 FragWorld;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0f);
    vec4 Normal = uModel * vec4(aNormal, .0f);
	FragNormal = normalize(Normal.xyz);
    FragWorld = (uModel * vec4(aPos, 1.0f)).xyz;
	FragUv = aUv;
}