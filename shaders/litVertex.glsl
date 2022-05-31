#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 texCoord;
out vec3 normal;
out vec3 positionWS;

uniform mat4 model;
uniform mat4 model_inv_trans;
uniform mat4 view;
uniform mat4 projection;

void main ()
{
	vec4 posOS = vec4(aPos, 1.0f);
	gl_Position = projection * view * model * posOS;
	positionWS = vec3(model * posOS);
	texCoord = aTexCoord;
	normal = mat3(model_inv_trans) * aNormal;
}