#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main ()
{
    vec4 tex1 = texture(texture1, texCoord);
    vec4 tex2 = texture(texture2, texCoord);
    FragColor = tex1 * tex2;
}