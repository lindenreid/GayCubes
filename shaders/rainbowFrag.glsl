#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D globalTex;

void main ()
{
    FragColor = texture(globalTex, texCoord);
}